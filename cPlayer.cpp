#include "stdafx.h"
#include "cPlayer.h"
#include"cItemManager.h"
#include "enemyManager.h"

HRESULT cPlayer::init(void)
{
	//기본 플레이어 정보 
	IsFly = false;
	key = 0;
	money = 0;
	bomb = 0;
	arrow = 기본총알;
	space = 없음;
	x = WINSIZEX / 2;
	y = WINSIZEY / 2;
	moveSpeed = PLAYERMOVESPEED;
	faceState = pIDLE;
	keyState = pIDLE;
	animState = IDLE;   //아이템먹었때, stat Up,기본 
	range = 200;
	cardOn = false;
	if (arrow == 유황)
	{
		range = IMAGEMANAGER->findImage("혈사좌우")->getFrameWidth();
	}
	damage = 1;
	//기본데미지1, 알약먹었을때 3, 유황먹었을 때 10 
	tears = 10;
	bulletSpeed = 3;
	hp = 6;
	maxHp = 6;
	rc = RectMakeCenter(x, y, PLAYERSIZEX, PLAYERSIZEY); //플레이어 몸통
	rcHead = RectMakeCenter(x, y - PLAYERSIZEY / 2 - PLAYERHEADSIZEY / 2 + 10, PLAYERHEADSIZEX, PLAYERHEADSIZEY);//플레이어 머리 
																												 //애니메이션 필요한 Count 
	frameCount = 0;
	leftFrame = 0;               //왼쪽걸어갈때 
	rightFrame = 0;            //오른쪽걸어갈때
	upDownFrame = 0;       //아래 위 카운트
	returnCount = 0;         //다시 머리 고개를 돌리는 카운트 
	bulletCount = 0;         //총알발사되는 카운트 
	itemCount = 0;          //아이템먹었을 때 이미지 계속 띄워주는 count 
	statUpCount = 0;
	fire = false;          //총알이 발사 되었냐?
								//여기서 총알종류 두가지 만들 것임! 
	_bullet = new bullet;
	_bullet->init("기본총알", 200);
	_유황 = new missile;
	_유황->init(200, 200);
	_큰총알 = new bullet;
	_큰총알->init("큰총알", 200);
	//새롭게 추가 
	damageCount = 0;
	damageFrameCount = 0;
	wingCount = 0;
	wingFrame = 0;
	dSlide = false;
	dfireX = 0;
	aSlide = false;
	afireX = 0;
	wSlide = false;
	wfireY = 0;;
	sSlide = false;
	sfireY = 0;
	//
	monsterShot = false; 
	minionShot = false; 
	deadCount = 0;
	deadFrame = 0;
	deadAlpha = 255;
	playerShot = false; 
	hitCount = 0;
	//유황추가
	//
	charge = 0;
	isCharge = false;
	
	return S_OK;
}

void cPlayer::release(void)
{
	_bullet->release();
	SAFE_DELETE(_bullet);
	_유황->release();
	SAFE_DELETE(_유황);
	_큰총알->release();
	SAFE_DELETE(_큰총알);
}

void cPlayer::update(void)
{
	if (hp <= 0)
	{
		animState = DEAD;
	}
	//폭탄이나 적한테 부디칠때 밀리게함
	PlayerKeyState();
	bulletFire();

	_bullet->update();
	_유황->update();
	_큰총알->update();
	DamagedPlayer();
	animation();
	enemyIntersect();
	if (hitCount > 0)
	{
		hitCount--;
	}
	
}

void cPlayer::render(void)
{
	_bullet->render();
	_큰총알->render();
	for (int i = 0; i < vInventory.size(); i++)
	{
		if (vInventory[i] == 유황)
		{
			arrow = 유황;
		}
		if (vInventory[i] == 구렁텅이의군주)
		{
			wingCount++;
			if (wingCount > 5)
			{
				wingCount = 0;
				wingFrame++;
			}
			if (wingFrame > 5)
			{
				wingFrame = 0;
			}
			if (arrow == 유황)
				IMAGEMANAGER->frameRender("유황날개", getMemDC(), rc.left - 35, rc.top - 14, wingFrame, 0);
			if (arrow == 기본총알)
				IMAGEMANAGER->frameRender("아이작날개", getMemDC(), rc.left - 35, rc.top - 14, wingFrame, 0);

		}
	}

	if (animState == IDLE)
	{
		if (arrow == 기본총알)
		{
			if (KEYMANAGER->isStayKeyDown('D'))
			{
				IMAGEMANAGER->frameRender("아이작왼쪽몸통", getMemDC(), rc.left, rc.top, leftFrame, 1);
			}
			else if (KEYMANAGER->isStayKeyDown('A'))
			{
				IMAGEMANAGER->frameRender("아이작오른쪽몸통", getMemDC(), rc.left, rc.top, rightFrame, 1);
			}
			else if (KEYMANAGER->isStayKeyDown('W'))
			{
				IMAGEMANAGER->frameRender("아이작UPDOWN", getMemDC(), rc.left, rc.top, upDownFrame, 1);
			}
			else if (KEYMANAGER->isStayKeyDown('S'))
			{
				IMAGEMANAGER->frameRender("아이작UPDOWN", getMemDC(), rc.left, rc.top, upDownFrame, 1);
			}
			else
			{
				IMAGEMANAGER->render("아이작몸통", getMemDC(), rc.left, rc.top, 0, 0, PLAYERSIZEX, PLAYERSIZEY);
			}

			switch (faceState)
			{
			case pLEFT:
				IMAGEMANAGER->render("아이작왼쪽얼굴", getMemDC(), rcHead.left, rcHead.top, 0, 0, PLAYERHEADSIZEX, PLAYERHEADSIZEY);
				//	cout << "left" << endl;
				break;
			case pRIGHT:
				IMAGEMANAGER->render("아이작오른쪽얼굴", getMemDC(), rcHead.left, rcHead.top, 0, 0, PLAYERHEADSIZEX, PLAYERHEADSIZEY);
				break;
			case pIDLE:
				IMAGEMANAGER->render("아이작IDLE", getMemDC(), rcHead.left, rcHead.top, 0, 0, PLAYERHEADSIZEX, PLAYERHEADSIZEY);
				break;
			case pUP:
				IMAGEMANAGER->render("아이작뒷통수", getMemDC(), rcHead.left, rcHead.top, 0, 0, PLAYERHEADSIZEX, PLAYERHEADSIZEY);
				break;
			default:
				break;
			}
		}
		//RectangleMake(getMemDC(), rc);
		else if (arrow == 유황)
		{
			if (KEYMANAGER->isStayKeyDown('D'))
			{
				IMAGEMANAGER->frameRender("유황왼쪽몸통", getMemDC(), rc.left, rc.top, leftFrame, 1);
			}
			else if (KEYMANAGER->isStayKeyDown('A'))
			{
				IMAGEMANAGER->frameRender("유황오른쪽몸통", getMemDC(), rc.left, rc.top, rightFrame, 1);
			}
			else if (KEYMANAGER->isStayKeyDown('W'))
			{
				IMAGEMANAGER->frameRender("유황UPDOWN", getMemDC(), rc.left, rc.top, upDownFrame, 1);
			}
			else if (KEYMANAGER->isStayKeyDown('S'))
			{
				IMAGEMANAGER->frameRender("유황UPDOWN", getMemDC(), rc.left, rc.top, upDownFrame, 1);
			}
			else
			{
				IMAGEMANAGER->render("유황몸통", getMemDC(), rc.left, rc.top, 0, 0, PLAYERSIZEX, PLAYERSIZEY);
			}

			switch (faceState)
			{
			case pLEFT:
				if (isCharge == false)
					IMAGEMANAGER->render("유황왼쪽얼굴", getMemDC(), rcHead.left - 5, rcHead.top, 0, 0, PLAYERHEADSIZEX + 10, PLAYERHEADSIZEY);
				if (isCharge == true)
				{
					if (charge % 3 == 0 || charge % 3 == 1)
						IMAGEMANAGER->render("유황왼쪽얼굴", getMemDC(), rcHead.left - 5, rcHead.top, 0, 0, PLAYERHEADSIZEX + 10, PLAYERHEADSIZEY);
					if (charge % 3 == 2)
						IMAGEMANAGER->render("유황LEFTRED", getMemDC(), rcHead.left - 5, rcHead.top, 0, 0, PLAYERHEADSIZEX + 10, PLAYERHEADSIZEY);
				}
				_유황->render();
				//cout << "left" << endl;
				break;
			case pRIGHT:
				if (isCharge == false)
					IMAGEMANAGER->render("유황오른쪽얼굴", getMemDC(), rcHead.left - 5, rcHead.top, 0, 0, PLAYERHEADSIZEX + 10, PLAYERHEADSIZEY);
				if (isCharge == true)
				{
					if (charge % 3 == 0 || charge % 3 == 1)
						IMAGEMANAGER->render("유황오른쪽얼굴", getMemDC(), rcHead.left - 5, rcHead.top, 0, 0, PLAYERHEADSIZEX + 10, PLAYERHEADSIZEY);
					if (charge % 3 == 2)
						IMAGEMANAGER->render("유황RIGHTRED", getMemDC(), rcHead.left - 5, rcHead.top, 0, 0, PLAYERHEADSIZEX + 10, PLAYERHEADSIZEY);
				}
				_유황->render();
				break;
			case pIDLE:
				if (isCharge == false)
					IMAGEMANAGER->render("유황IDLEFIRE", getMemDC(), rcHead.left - 10, rcHead.top, 0, 0, PLAYERHEADSIZEX + 20, PLAYERHEADSIZEY);
				if (isCharge == true)
				{
					if (charge % 3 == 0 || charge % 3 == 1)
						IMAGEMANAGER->render("유황IDLEFIRE", getMemDC(), rcHead.left - 10, rcHead.top, 0, 0, PLAYERHEADSIZEX + 20, PLAYERHEADSIZEY);
					if (charge % 3 == 2)
						IMAGEMANAGER->render("유황IDLERED", getMemDC(), rcHead.left - 10, rcHead.top, 0, 0, PLAYERHEADSIZEX + 20, PLAYERHEADSIZEY);
				}
				_유황->render();
				break;
			case pUP:
				_유황->render();
				if (isCharge == false)
					IMAGEMANAGER->render("유황뒷통수", getMemDC(), rcHead.left - 10, rcHead.top, 0, 0, PLAYERHEADSIZEX + 20, PLAYERHEADSIZEY);
				if (isCharge == true)
				{
					if (charge % 3 == 0 || charge % 3 == 1)
						IMAGEMANAGER->render("유황뒷통수", getMemDC(), rcHead.left - 10, rcHead.top, 0, 0, PLAYERHEADSIZEX + 20, PLAYERHEADSIZEY);
					if (charge % 3 == 2)
						IMAGEMANAGER->render("유황IDLERED", getMemDC(), rcHead.left - 10, rcHead.top, 0, 0, PLAYERHEADSIZEX + 20, PLAYERHEADSIZEY);
				}
				break;
			default:
				break;
			}
		}
	}

	if (animState == CARD)
	{
		if (arrow == 기본총알)
		{
			itemCount++;
			if (itemCount % 30 == 0)
				statUpCount++;
			if (statUpCount >= 2)
			{
				//
				cardOn = true;
				//
				animState = IDLE;
				statUpCount = 0;
				itemCount = 0;
			}
			IMAGEMANAGER->frameRender("아이작STATUP", getMemDC(), rcHead.left, rcHead.top, statUpCount, 1);
		}
		else if (arrow == 유황)
		{
			itemCount++;
			if (itemCount % 30 == 0)
				statUpCount++;
			if (statUpCount >= 2)
			{
				animState = IDLE;
				statUpCount = 0;
				itemCount = 0;
			}
			IMAGEMANAGER->frameRender("유황STATUP", getMemDC(), rcHead.left, rcHead.top, statUpCount, 1);
		}

	}
	if (animState == ETC)
	{
		if (arrow == 기본총알 || arrow == CARD)
		{
			itemCount++;
			if (itemCount > 50)
			{
				animState = IDLE;
				itemCount = 0;
			}
			IMAGEMANAGER->render("아이작ITEM", getMemDC(), rcHead.left, rcHead.top, 0, 0, PLAYERHEADSIZEX, PLAYERSIZEY + PLAYERHEADSIZEY);
		}
		else if (arrow == 유황)
		{
			itemCount++;
			if (itemCount > 50)
			{
				animState = IDLE;
				itemCount = 0;
			}
			IMAGEMANAGER->render("유황ITEM", getMemDC(), rcHead.left, rcHead.top, 0, 0, PLAYERHEADSIZEX, PLAYERSIZEY + PLAYERHEADSIZEY);
		}
	}
	if (animState == DAMAGE)
	{
		if (arrow == 기본총알)
		{
			damageCount++;
			if (damageCount % 20 == 0)
				damageFrameCount++;
			if (damageFrameCount >= 2)
			{
				animState = IDLE;
				damageFrameCount = 0;
				damageCount = 0;
			}
			IMAGEMANAGER->frameRender("아이작HURT", getMemDC(), rcHead.left, rcHead.top, damageFrameCount, 1);
		}
		if (arrow == 유황)
		{
			damageCount++;
			if (damageCount % 20 == 0)
				damageFrameCount++;
			if (damageFrameCount >= 2)
			{
				animState = IDLE;
				damageFrameCount = 0;
				damageCount = 0;
			}
			IMAGEMANAGER->frameRender("유황HURT", getMemDC(), rcHead.left, rcHead.top, damageFrameCount, 1);
		}
	}
	if (animState == DEAD)
	{
		deadCount++;
		if (deadCount % 15 == 0 && deadFrame<3)
		{
			deadFrame++;
		}
		if (deadCount < 16)
		{
			if (arrow == 기본총알)
			{
				IMAGEMANAGER->frameRender("아이작DEAD", getMemDC(), rc.left, rc.top, deadFrame, 0);
			}
			else
			{
				IMAGEMANAGER->frameRender("유황DEAD", getMemDC(), rc.left, rc.top, deadFrame, 0);
			}
		}
		deadAlpha--;
		if (deadAlpha>0 && deadCount>16)
		{
			if (arrow == 기본총알)
			{
				IMAGEMANAGER->alphaRender("아이작DEAD2", getMemDC(), rc.left, rc.top, PLAYERHEADSIZEX * 2, 0, PLAYERHEADSIZEX, PLAYERSIZEY + PLAYERHEADSIZEY, deadAlpha);
			}
			if (arrow == 유황)
			{
				IMAGEMANAGER->alphaRender("유황DEAD2", getMemDC(), rc.left, rc.top, PLAYERHEADSIZEX * 2, 0, PLAYERHEADSIZEX, PLAYERSIZEY + PLAYERHEADSIZEY, deadAlpha);
			}
		}

	}
	//	RectangleMake(getMemDC(), rc);

	//==================================================================
	//		## 수치확인용 ##
	//==================================================================
	/*for (int i = 0; i < vInventory.size(); i++)
	{
		wsprintf(buffer, TEXT("플레이어인벤:%d"), vInventory[i]);
		TextOut(getMemDC(), 100, 10 + 20 * i, buffer, lstrlen(buffer));
	}

	wsprintf(buffer, TEXT("bomb:%d,  key:%d  money:%d"), bomb, key, money);
	TextOut(getMemDC(), 10, 10, buffer, lstrlen(buffer));*/
}

void cPlayer::animation(void)
{
	if (fire == true)
	{
		returnCount++;
		if (returnCount > 50)
		{
			fire = false;
			returnCount = 0;
			faceState = pIDLE;

		}
	}
	if (KEYMANAGER->isStayKeyDown('D'))
	{
		//frameCount = 0;
		frameCount++;
		if (frameCount % 5 == 0)
			leftFrame++;
		if (leftFrame == 10)
			leftFrame = 0;
	}
	if (KEYMANAGER->isStayKeyDown('A'))
	{
		//	frameCount = 0;
		frameCount++;
		if (frameCount % 5 == 0)
			rightFrame++;
		if (rightFrame == 10)
			rightFrame = 0;
	}
	if (KEYMANAGER->isStayKeyDown('W'))
	{
		//	frameCount = 0;
		frameCount++;
		if (frameCount % 5 == 0)
			upDownFrame++;
		if (upDownFrame == 10)
			upDownFrame = 0;
	}
	if (KEYMANAGER->isStayKeyDown('S'))
	{
		//		frameCount = 0;
		frameCount++;
		if (frameCount % 5 == 0)
			upDownFrame++;
		if (upDownFrame == 10)
			upDownFrame = 0;
	}
	RectangleMake(getMemDC(), rc);
}

void cPlayer::bulletFire(void)
{
	if (arrow == 기본총알)
	{
		if (cardOn == false)
		{
			bulletCount++;
			if (bulletCount % 10 == 0)
			{
				if (KEYMANAGER->isStayKeyDown(VK_UP))
				{
					if (KEYMANAGER->isStayKeyDown('A'))
					{
						_bullet->fire(x, y, (PI / 1.9), range, damage, bulletSpeed);
						//기본총알 이동거리 300, 데미지 10, 이동속도 5

					}
					else if (KEYMANAGER->isStayKeyDown('D'))
					{
						_bullet->fire(x, y, (PI / 2.1), range, damage, bulletSpeed);

					}
					else
					{
						_bullet->fire(x, y, (PI / 2), range, damage, bulletSpeed);

					}
					fire = true;
					faceState = pUP;
				}

				////////////////////
				if (KEYMANAGER->isStayKeyDown(VK_DOWN))
				{
					if (KEYMANAGER->isStayKeyDown('A'))
					{
						_bullet->fire(x, y, -(PI / 1.5), range, damage, bulletSpeed);

						//기본총알 이동거리 300, 데미지 10, 이동속도 5
					}
					else if (KEYMANAGER->isStayKeyDown('D'))
					{
						_bullet->fire(x, y, -(PI / 2.5), range, damage, bulletSpeed);

					}
					else
					{
						_bullet->fire(x, y, -(PI / 2), range, damage, bulletSpeed);

					}
					faceState = pIDLE;
					fire = true;

				}
				if (KEYMANAGER->isStayKeyDown(VK_LEFT))
				{
					if (KEYMANAGER->isStayKeyDown('W'))
					{
						_bullet->fire(x, y, (PI / 1.5), range, damage, bulletSpeed);

						//기본총알 이동거리 300, 데미지 10, 이동속도 5
					}
					else if (KEYMANAGER->isStayKeyDown('S'))
					{
						_bullet->fire(x, y, -(PI / 1.5), range, damage, bulletSpeed);

					}
					else
					{
						_bullet->fire(x, y, PI, range, damage, bulletSpeed);

					}
					faceState = pLEFT;
					fire = true;
				}
				if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
				{
					if (KEYMANAGER->isStayKeyDown('W'))
					{
						_bullet->fire(x, y, (PI / 2.5), range, damage, bulletSpeed);

						//기본총알 이동거리 300, 데미지 10, 이동속도 5
					}
					else if (KEYMANAGER->isStayKeyDown('S'))
					{
						_bullet->fire(x, y, -(PI / 2.5), range, damage, bulletSpeed);

					}
					else
					{
						_bullet->fire(x, y, (PI * 2), range, damage, bulletSpeed);

					}
					faceState = pRIGHT;
					fire = true;
				}
			}
		}
		if (cardOn == true)
		{
			bulletCount++;
			if (bulletCount % 10 == 0)
			{
				if (KEYMANAGER->isStayKeyDown(VK_UP))
				{
					if (KEYMANAGER->isStayKeyDown('A'))
					{
						_큰총알->fire(x, y, (PI / 1.9), range, 3, bulletSpeed);
						//기본총알 이동거리 300, 데미지 10, 이동속도 5

					}
					else if (KEYMANAGER->isStayKeyDown('D'))
					{
						_큰총알->fire(x, y, (PI / 2.1), range, 3, bulletSpeed);

					}
					else
					{
						_큰총알->fire(x, y, (PI / 2), range, 3, bulletSpeed);

					}
					fire = true;
					faceState = pUP;
				}

				////////////////////
				if (KEYMANAGER->isStayKeyDown(VK_DOWN))
				{
					if (KEYMANAGER->isStayKeyDown('A'))
					{
						_큰총알->fire(x, y, -(PI / 1.5), range, 3, bulletSpeed);

						//기본총알 이동거리 300, 데미지 10, 이동속도 5
					}
					else if (KEYMANAGER->isStayKeyDown('D'))
					{
						_큰총알->fire(x, y, -(PI / 2.5), range, 3, bulletSpeed);

					}
					else
					{
						_큰총알->fire(x, y, -(PI / 2), range, 3, bulletSpeed);

					}
					faceState = pIDLE;
					fire = true;

				}
				if (KEYMANAGER->isStayKeyDown(VK_LEFT))
				{
					if (KEYMANAGER->isStayKeyDown('W'))
					{
						_큰총알->fire(x, y, (PI / 1.5), range, 3, bulletSpeed);

						//기본총알 이동거리 300, 데미지 10, 이동속도 5
					}
					else if (KEYMANAGER->isStayKeyDown('S'))
					{
						_큰총알->fire(x, y, -(PI / 1.5), range, 3, bulletSpeed);

					}
					else
					{
						_큰총알->fire(x, y, PI, range, 3, bulletSpeed);

					}
					faceState = pLEFT;
					fire = true;
				}
				if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
				{
					if (KEYMANAGER->isStayKeyDown('W'))
					{
						_큰총알->fire(x, y, (PI / 2.5), range, 3, bulletSpeed);

						//기본총알 이동거리 300, 데미지 10, 이동속도 5
					}
					else if (KEYMANAGER->isStayKeyDown('S'))
					{
						_큰총알->fire(x, y, -(PI / 2.5), range, 3, bulletSpeed);

					}
					else
					{
						_큰총알->fire(x, y, (PI * 2), range, 3, bulletSpeed);

					}
					faceState = pRIGHT;
					fire = true;
				}
			}
		}
	}
	else if (arrow == 유황)

		{
			bulletCount++;
			if (bulletCount % 20 == 0)
			{
				if (KEYMANAGER->isOnceKeyUp(VK_UP))
				{
					if (charge >= 50)
					{
						_유황->fire(x, y - PLAYERSIZEY / 2 - PLAYERHEADSIZEY / 2 + 10, 3, 56 * 7, 10, 3);
						fire = true;
					}
					faceState = pUP;
					charge = 0;
					isCharge = false;
				}
				if (KEYMANAGER->isOnceKeyUp(VK_DOWN))
				{
					if (charge >= 50)
					{
						_유황->fire(x, y - PLAYERSIZEY / 2 - PLAYERHEADSIZEY / 2 + 25, 4, 56 * 7, 10, 3);
						fire = true;
					}
					faceState = pIDLE;
					charge = 0;
					isCharge = false;
				}
				if (KEYMANAGER->isOnceKeyUp(VK_LEFT))
				{
					if (charge >= 50)
					{
						_유황->fire(x - 20, y - PLAYERSIZEY / 2 - PLAYERHEADSIZEY / 2 + 20, 2, 56 * 7, 10, 3);
						fire = true;
					}
					faceState = pLEFT;
					charge = 0;
					isCharge = false;
				}
				if (KEYMANAGER->isOnceKeyUp(VK_RIGHT))
				{
					if (charge >= 50)
					{
						_유황->fire(x + 20, y - PLAYERSIZEY / 2 - PLAYERHEADSIZEY / 2 + 20, 1, 56 * 7, 10, 3);
						fire = true;
					}
					charge = 0;
					isCharge = false;
					faceState = pRIGHT;
				}
				////유황일때 기본 range 200,damage 1, 속도 30 

			}
			if (KEYMANAGER->isStayKeyDown(VK_UP))
			{
				charge++;
				isCharge = true;
				faceState = pUP;
			}
			if (KEYMANAGER->isStayKeyDown(VK_DOWN))
			{
				charge++;
				isCharge = true;
				faceState = pIDLE;
			}
			if (KEYMANAGER->isStayKeyDown(VK_LEFT))
			{
				charge++;
				isCharge = true;
				faceState = pLEFT;
			}
			if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
			{
				charge++;
				isCharge = true;
				faceState = pRIGHT;
			}
		}
	//알약을 먹으면 set(arrow=알약)으로 하고 // damage도 3으로 바꾸기. 

}

void cPlayer::PlayerKeyState(void)
{
	PlayerSlide();
	if (KEYMANAGER->isStayKeyDown('D'))
	{
		if (fire == false)
			faceState = pIDLE;
		keyState = pRIGHT;
		dSlide = false;
		aSlide = false;
		sSlide = false;
		wSlide = false;
		x += moveSpeed;
	}
	if (KEYMANAGER->isStayKeyDown('A'))
	{
		if (fire == false)
			faceState = pIDLE;
		keyState = pLEFT;
		dSlide = false;
		aSlide = false;
		sSlide = false;
		wSlide = false;
		x -= moveSpeed;
	}
	if (KEYMANAGER->isStayKeyDown('W'))
	{
		if (fire == false)
			faceState = pIDLE;
		keyState = pUP;
		dSlide = false;
		aSlide = false;
		sSlide = false;
		wSlide = false;
		y -= moveSpeed;
	}
	if (KEYMANAGER->isStayKeyDown('S'))
	{
		if (fire == false)
			faceState = pIDLE;
		keyState = pIDLE;
		dSlide = false;
		aSlide = false;
		sSlide = false;
		wSlide = false;
		y += moveSpeed;
	}

	if (KEYMANAGER->isOnceKeyDown('E'))
	{
		if (bomb > 0)
		{
			_im->ItemUse(폭탄);
		}
	}

	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		if (space == 박사의조정기)
		{
			_im->ItemUse(박사의조정기);
		}
		if (space == 모래시계)
		{
			_im->ItemUse(모래시계);
		}
	}

	if (KEYMANAGER->isOnceKeyDown('Q'))
	{
		if (card == 카드)
		{
			_im->ItemUse(카드);
		}
	}
	rc = RectMakeCenter(x, y, PLAYERSIZEX, PLAYERSIZEY);
	rcHead = RectMakeCenter(x, y - PLAYERSIZEY / 2 - PLAYERHEADSIZEY / 2 + 10, PLAYERHEADSIZEX, PLAYERHEADSIZEY);
}

void cPlayer::DamagedPlayer()
{
	if (animState == DAMAGE)
	{
		int static nCount = 0;
		nCount++;
		x += cosf(angle)*moveSpeed;
		y +=-sinf(angle)*moveSpeed;
		if (nCount>20)
		{
			nCount = 0;
			animState = IDLE;
		}						
	}
}

void cPlayer::PlayerSlide(void)
{
	if (KEYMANAGER->isOnceKeyUp('D'))
	{
		dfireX = x;
		dSlide = true;
	}
	if (KEYMANAGER->isOnceKeyUp('A'))
	{
		afireX = x;
		aSlide = true;
	}
	if (KEYMANAGER->isOnceKeyUp('W'))
	{
		wfireY = y;
		wSlide = true;
	}
	if (KEYMANAGER->isOnceKeyUp('S'))
	{
		sfireY = y;
		sSlide = true;
	}
	if (dSlide == true)
	{
		x += moveSpeed;
	}
	if (x > dfireX + 50)
	{
		dSlide = false;
		dfireX = 0;
	}
	if (aSlide == true)
	{
		x -= moveSpeed;
	}
	if (x < afireX - 50)
	{
		aSlide = false;
	}
	if (sSlide == true)
	{
		y += moveSpeed;
	}
	if (y > sfireY + 50)
	{
		sSlide = false;
	}
	if (wSlide == true)
	{
		y -= moveSpeed;
	}
	if (y < wfireY - 50)
	{
		wSlide = false;
	}
}
void cPlayer::enemyIntersect(void)
{
	//유황을 쏘았을 때  보스, 기본 미니언들 충돌 한번만 되게 
	if (arrow == 유황)
	{
		int itemp = _enemy->getVMinionPt()->size();
		for (int i = 0; i < _enemy->getVMinionPt()->size(); i++)
		{
			RECT temp;
			RECT temp2 = _enemy->getVMinionPt()->at(i)->getRect();
			
			if (!_유황->getVBulletPt()->empty())
			{
				for (int j = 0; j < _유황->getVBulletPt()->size(); j++)
				{
					if (_enemy->getVMinionPt()->at(i)->getMobType() == BOSS)
					{
						if (IntersectRect(&temp, &_유황->getVBulletPt()->at(j).rc, &temp2)&&monsterShot==false&& _enemy->getVMinionPt()->at(i)->isHit())
						{
							_enemy->getVMinionPt()->at(i)->setHP(_enemy->getVMinionPt()->at(i)->getHP() - _유황->getVBulletPt()->at(j).damage);
							_enemy->getVMinionPt()->at(i)->setHitTime(2);
							monsterShot = true;
						}
						if (monsterShot == true)
						{
							int static nCount = 0;
							nCount++;
							if (nCount>50)
							{
								nCount = 0;
								monsterShot = false;
							}
							
						}
					}
					else
					{
						if (IntersectRect(&temp, &_유황->getVBulletPt()->at(j).rc, &temp2))
						{
							minionShot = true;
						}
						if (minionShot == true)
						{
							_enemy->getVMinionPt()->at(i)->setHP(_enemy->getVMinionPt()->at(i)->getHP() - _유황->getVBulletPt()->at(j).damage);
							minionShot = false;
						}
					}
				}

			}
		}
	}
	//기본총알 또는 큰총알을 쏘았을 때 
	//if (arrow == 기본총알 && cardOn == true)
	//{
	//	int itemp = _enemy->getVMinionPt()->size();				//전체 개수를 템프에 담는다. 
	//	for (int i = 0; i < _enemy->getVMinionPt()->size(); i++)	//전체 개수만큼 조사한다.
	//	{
	//		RECT temp;
	//		RECT temp2 = _enemy->getVMinionPt()->at(i)->getRect(); //현재 몬스터의 몸체를  temp2에 담는다. 
	//		if (!_큰총알->getVBulletPt()->empty())						 //총알이 살아있다면! 즉 발사되었다면 
	//		{
	//			for (int j = 0; j < _큰총알->getVBulletPt()->size(); j++)
	//			{
	//				if (IntersectRect(&temp, &_큰총알->getVBulletPt()->at(j).rc, &temp2))	//큰총알의 몸체와, 적의 몸체가 부딪히면 
	//				{//적의 몸체->장소(i)번째..->hp를 깎아라. 
	//					_enemy->getVMinionPt()->at(i)->setHP(_enemy->getVMinionPt()->at(i)->getHP() - _큰총알->getVBulletPt()->at(j).damage);
	//				}
	//			}
	//		}
	//	}
	//}
	//총알에 플레이어가 맞았을 때. 
	for (int i = 0; i < _enemy->getFrameBullet()->getVBulletPt()->size(); i++)
	{
		RECT temp;
		if (IntersectRect(&temp, &_enemy->getFrameBullet()->getVBulletPt()->at(i).rc, &rc))
		{
			if (hitCount <= 0)
			{
				animState = DAMAGE;
				angle = getAngle(_enemy->getFrameBullet()->getVBulletPt()->at(i).x, _enemy->getFrameBullet()->getVBulletPt()->at(i).y
					, x, y);
				playerShot = true;
				_enemy->getFrameBullet()->removeBullet(i);
			}
			
		}
		if (playerShot == true)
		{
			hitCount == 20;
			hp--;
			playerShot = false; 
		}
	}

	for (int i = 0; i < _enemy->getHFrameBullet()->getVBulletPt()->size(); i++)
	{
		RECT temp;
		if (IntersectRect(&temp, &_enemy->getHFrameBullet()->getVBulletPt()->at(i).rc, &rc))
		{
			if (hitCount <= 0)
			{
				if (_enemy->getHFrameBullet()->getVBulletPt()->at(i)._height < 5)
				{
					animState = DAMAGE;
					angle = getAngle(_enemy->getHFrameBullet()->getVBulletPt()->at(i).x, _enemy->getHFrameBullet()->getVBulletPt()->at(i).y, x, y);
					playerShot = true;
					_enemy->getHFrameBullet()->removeBullet(i);
				}
				if (playerShot == true)
				{
					hitCount = 20;
					hp--;
					playerShot = false;
				}
			}
			
		}
	}

}


void cPlayer::addInVentory(int _item)
{
	vInventory.push_back(_item);
}
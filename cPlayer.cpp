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
	fire = false;               //총알이 발사 되었냐?
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


	//폭탄이나 적한테 부디칠때 밀리게함
	PlayerKeyState();
	bulletFire();

	_bullet->update();
	_유황->update();
	_큰총알->update();
	DamagedPlayer();
	animation();
	enemyIntersect();
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
				IMAGEMANAGER->render("유황왼쪽얼굴", getMemDC(), rcHead.left - 5, rcHead.top, 0, 0, PLAYERHEADSIZEX + 10, PLAYERHEADSIZEY);
				_유황->render();
				//cout << "left" << endl;
				break;
			case pRIGHT:
				IMAGEMANAGER->render("유황오른쪽얼굴", getMemDC(), rcHead.left - 5, rcHead.top, 0, 0, PLAYERHEADSIZEX + 10, PLAYERHEADSIZEY);
				_유황->render();
				break;
			case pIDLE:
				IMAGEMANAGER->render("유황IDLEFIRE", getMemDC(), rcHead.left - 10, rcHead.top, 0, 0, PLAYERHEADSIZEX + 20, PLAYERHEADSIZEY);
				_유황->render();
				break;
			case pUP:
				_유황->render();
				IMAGEMANAGER->render("유황뒷통수", getMemDC(), rcHead.left - 10, rcHead.top, 0, 0, PLAYERHEADSIZEX + 20, PLAYERHEADSIZEY);
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
	//	RectangleMake(getMemDC(), rc);

	//==================================================================
	//		## 수치확인용 ##
	//==================================================================
	for (int i = 0; i < vInventory.size(); i++)
	{
		wsprintf(buffer, TEXT("플레이어인벤:%d"), vInventory[i]);
		TextOut(getMemDC(), 100, 10 + 20 * i, buffer, lstrlen(buffer));
	}

	wsprintf(buffer, TEXT("bomb:%d,  key:%d  money:%d"), bomb, key, money);
	TextOut(getMemDC(), 10, 10, buffer, lstrlen(buffer));
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
			////유황일때 기본 range 200,damage 1, 속도 30 
			if (KEYMANAGER->isStayKeyDown(VK_UP))
			{
				_유황->fire(x, y - PLAYERSIZEY / 2 - PLAYERHEADSIZEY / 2 + 10, 3, 56 * 7, 10, 3);
				fire = true;
				faceState = pUP;
			}
			if (KEYMANAGER->isStayKeyDown(VK_DOWN))
			{
				_유황->fire(x, y - PLAYERSIZEY / 2 - PLAYERHEADSIZEY / 2 + 25, 4, 56 * 7, 10, 3);
				faceState = pIDLE;
				fire = true;
			}
			if (KEYMANAGER->isStayKeyDown(VK_LEFT))
			{
				_유황->fire(x - 12, y - PLAYERSIZEY / 2 - PLAYERHEADSIZEY / 2 + 20, 2, 56 * 7, 10, 3);
				faceState = pLEFT;
				fire = true;
			}
			if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
			{
				_유황->fire(x + 20, y - PLAYERSIZEY / 2 - PLAYERHEADSIZEY / 2 + 20, 1, 56 * 7, 10, 3);
				faceState = pRIGHT;
				fire = true;
			}
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
		moveSpeed -= 0.1f;
		x += cosf(angle)*moveSpeed;
		y += -sinf(angle)*moveSpeed;

		if (moveSpeed<0.0f)
		{
			moveSpeed = PLAYERMOVESPEED;
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
	int itemp = _enemy->getVMinionPt()->size();
	for (int i = 0; i < _enemy->getVMinionPt()->size(); i++)
	{
		RECT temp;
		RECT temp2 = _enemy->getVMinionPt()->at(i)->getRect();
		if (!_유황->getVBulletPt()->empty())
		{
			if (IntersectRect(&temp, &_유황->getVBulletPt()->at(0).rc, &temp2))
			{
				_enemy->getVMinionPt()->at(i)->setHP(_enemy->getVMinionPt()->at(i)->getHP() - _유황->getVBulletPt()->at(0).damage);
			}
		}

	}
}


void cPlayer::addInVentory(int _item)
{
	vInventory.push_back(_item);
}
#include "stdafx.h"
#include "cPlayer.h"
#include"cItemManager.h"
#include "enemyManager.h"

HRESULT cPlayer::init(void)
{
	//�⺻ �÷��̾� ���� 
	IsFly = false;
	key = 0;
	money = 0;
	bomb = 0;
	arrow = �⺻�Ѿ�;
	space = ����;
	x = WINSIZEX / 2;
	y = WINSIZEY / 2;
	moveSpeed = PLAYERMOVESPEED;
	faceState = pIDLE;
	keyState = pIDLE;
	animState = IDLE;   //�����۸Ծ���, stat Up,�⺻ 
	range = 200;
	cardOn = false;
	if (arrow == ��Ȳ)
	{
		range = IMAGEMANAGER->findImage("�����¿�")->getFrameWidth();
	}
	damage = 1;
	//�⺻������1, �˾�Ծ����� 3, ��Ȳ�Ծ��� �� 10 
	tears = 10;
	bulletSpeed = 3;
	hp = 6;
	maxHp = 6;
	rc = RectMakeCenter(x, y, PLAYERSIZEX, PLAYERSIZEY); //�÷��̾� ����
	rcHead = RectMakeCenter(x, y - PLAYERSIZEY / 2 - PLAYERHEADSIZEY / 2 + 10, PLAYERHEADSIZEX, PLAYERHEADSIZEY);//�÷��̾� �Ӹ� 
																												 //�ִϸ��̼� �ʿ��� Count 
	frameCount = 0;
	leftFrame = 0;               //���ʰɾ�� 
	rightFrame = 0;            //�����ʰɾ��
	upDownFrame = 0;       //�Ʒ� �� ī��Ʈ
	returnCount = 0;         //�ٽ� �Ӹ� ���� ������ ī��Ʈ 
	bulletCount = 0;         //�Ѿ˹߻�Ǵ� ī��Ʈ 
	itemCount = 0;          //�����۸Ծ��� �� �̹��� ��� ����ִ� count 
	statUpCount = 0;
	fire = false;          //�Ѿ��� �߻� �Ǿ���?
								//���⼭ �Ѿ����� �ΰ��� ���� ����! 
	_bullet = new bullet;
	_bullet->init("�⺻�Ѿ�", 200);
	_��Ȳ = new missile;
	_��Ȳ->init(200, 200);
	_ū�Ѿ� = new bullet;
	_ū�Ѿ�->init("ū�Ѿ�", 200);
	//���Ӱ� �߰� 
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
	//��Ȳ�߰�
	//
	charge = 0;
	isCharge = false;
	
	return S_OK;
}

void cPlayer::release(void)
{
	_bullet->release();
	SAFE_DELETE(_bullet);
	_��Ȳ->release();
	SAFE_DELETE(_��Ȳ);
	_ū�Ѿ�->release();
	SAFE_DELETE(_ū�Ѿ�);
}

void cPlayer::update(void)
{
	if (hp <= 0)
	{
		animState = DEAD;
	}
	//��ź�̳� ������ �ε�ĥ�� �и�����
	PlayerKeyState();
	bulletFire();

	_bullet->update();
	_��Ȳ->update();
	_ū�Ѿ�->update();
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
	_ū�Ѿ�->render();
	for (int i = 0; i < vInventory.size(); i++)
	{
		if (vInventory[i] == ��Ȳ)
		{
			arrow = ��Ȳ;
		}
		if (vInventory[i] == ���������Ǳ���)
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
			if (arrow == ��Ȳ)
				IMAGEMANAGER->frameRender("��Ȳ����", getMemDC(), rc.left - 35, rc.top - 14, wingFrame, 0);
			if (arrow == �⺻�Ѿ�)
				IMAGEMANAGER->frameRender("�����۳���", getMemDC(), rc.left - 35, rc.top - 14, wingFrame, 0);

		}
	}

	if (animState == IDLE)
	{
		if (arrow == �⺻�Ѿ�)
		{
			if (KEYMANAGER->isStayKeyDown('D'))
			{
				IMAGEMANAGER->frameRender("�����ۿ��ʸ���", getMemDC(), rc.left, rc.top, leftFrame, 1);
			}
			else if (KEYMANAGER->isStayKeyDown('A'))
			{
				IMAGEMANAGER->frameRender("�����ۿ����ʸ���", getMemDC(), rc.left, rc.top, rightFrame, 1);
			}
			else if (KEYMANAGER->isStayKeyDown('W'))
			{
				IMAGEMANAGER->frameRender("������UPDOWN", getMemDC(), rc.left, rc.top, upDownFrame, 1);
			}
			else if (KEYMANAGER->isStayKeyDown('S'))
			{
				IMAGEMANAGER->frameRender("������UPDOWN", getMemDC(), rc.left, rc.top, upDownFrame, 1);
			}
			else
			{
				IMAGEMANAGER->render("�����۸���", getMemDC(), rc.left, rc.top, 0, 0, PLAYERSIZEX, PLAYERSIZEY);
			}

			switch (faceState)
			{
			case pLEFT:
				IMAGEMANAGER->render("�����ۿ��ʾ�", getMemDC(), rcHead.left, rcHead.top, 0, 0, PLAYERHEADSIZEX, PLAYERHEADSIZEY);
				//	cout << "left" << endl;
				break;
			case pRIGHT:
				IMAGEMANAGER->render("�����ۿ����ʾ�", getMemDC(), rcHead.left, rcHead.top, 0, 0, PLAYERHEADSIZEX, PLAYERHEADSIZEY);
				break;
			case pIDLE:
				IMAGEMANAGER->render("������IDLE", getMemDC(), rcHead.left, rcHead.top, 0, 0, PLAYERHEADSIZEX, PLAYERHEADSIZEY);
				break;
			case pUP:
				IMAGEMANAGER->render("�����۵����", getMemDC(), rcHead.left, rcHead.top, 0, 0, PLAYERHEADSIZEX, PLAYERHEADSIZEY);
				break;
			default:
				break;
			}
		}
		//RectangleMake(getMemDC(), rc);
		else if (arrow == ��Ȳ)
		{
			if (KEYMANAGER->isStayKeyDown('D'))
			{
				IMAGEMANAGER->frameRender("��Ȳ���ʸ���", getMemDC(), rc.left, rc.top, leftFrame, 1);
			}
			else if (KEYMANAGER->isStayKeyDown('A'))
			{
				IMAGEMANAGER->frameRender("��Ȳ�����ʸ���", getMemDC(), rc.left, rc.top, rightFrame, 1);
			}
			else if (KEYMANAGER->isStayKeyDown('W'))
			{
				IMAGEMANAGER->frameRender("��ȲUPDOWN", getMemDC(), rc.left, rc.top, upDownFrame, 1);
			}
			else if (KEYMANAGER->isStayKeyDown('S'))
			{
				IMAGEMANAGER->frameRender("��ȲUPDOWN", getMemDC(), rc.left, rc.top, upDownFrame, 1);
			}
			else
			{
				IMAGEMANAGER->render("��Ȳ����", getMemDC(), rc.left, rc.top, 0, 0, PLAYERSIZEX, PLAYERSIZEY);
			}

			switch (faceState)
			{
			case pLEFT:
				if (isCharge == false)
					IMAGEMANAGER->render("��Ȳ���ʾ�", getMemDC(), rcHead.left - 5, rcHead.top, 0, 0, PLAYERHEADSIZEX + 10, PLAYERHEADSIZEY);
				if (isCharge == true)
				{
					if (charge % 3 == 0 || charge % 3 == 1)
						IMAGEMANAGER->render("��Ȳ���ʾ�", getMemDC(), rcHead.left - 5, rcHead.top, 0, 0, PLAYERHEADSIZEX + 10, PLAYERHEADSIZEY);
					if (charge % 3 == 2)
						IMAGEMANAGER->render("��ȲLEFTRED", getMemDC(), rcHead.left - 5, rcHead.top, 0, 0, PLAYERHEADSIZEX + 10, PLAYERHEADSIZEY);
				}
				_��Ȳ->render();
				//cout << "left" << endl;
				break;
			case pRIGHT:
				if (isCharge == false)
					IMAGEMANAGER->render("��Ȳ�����ʾ�", getMemDC(), rcHead.left - 5, rcHead.top, 0, 0, PLAYERHEADSIZEX + 10, PLAYERHEADSIZEY);
				if (isCharge == true)
				{
					if (charge % 3 == 0 || charge % 3 == 1)
						IMAGEMANAGER->render("��Ȳ�����ʾ�", getMemDC(), rcHead.left - 5, rcHead.top, 0, 0, PLAYERHEADSIZEX + 10, PLAYERHEADSIZEY);
					if (charge % 3 == 2)
						IMAGEMANAGER->render("��ȲRIGHTRED", getMemDC(), rcHead.left - 5, rcHead.top, 0, 0, PLAYERHEADSIZEX + 10, PLAYERHEADSIZEY);
				}
				_��Ȳ->render();
				break;
			case pIDLE:
				if (isCharge == false)
					IMAGEMANAGER->render("��ȲIDLEFIRE", getMemDC(), rcHead.left - 10, rcHead.top, 0, 0, PLAYERHEADSIZEX + 20, PLAYERHEADSIZEY);
				if (isCharge == true)
				{
					if (charge % 3 == 0 || charge % 3 == 1)
						IMAGEMANAGER->render("��ȲIDLEFIRE", getMemDC(), rcHead.left - 10, rcHead.top, 0, 0, PLAYERHEADSIZEX + 20, PLAYERHEADSIZEY);
					if (charge % 3 == 2)
						IMAGEMANAGER->render("��ȲIDLERED", getMemDC(), rcHead.left - 10, rcHead.top, 0, 0, PLAYERHEADSIZEX + 20, PLAYERHEADSIZEY);
				}
				_��Ȳ->render();
				break;
			case pUP:
				_��Ȳ->render();
				if (isCharge == false)
					IMAGEMANAGER->render("��Ȳ�����", getMemDC(), rcHead.left - 10, rcHead.top, 0, 0, PLAYERHEADSIZEX + 20, PLAYERHEADSIZEY);
				if (isCharge == true)
				{
					if (charge % 3 == 0 || charge % 3 == 1)
						IMAGEMANAGER->render("��Ȳ�����", getMemDC(), rcHead.left - 10, rcHead.top, 0, 0, PLAYERHEADSIZEX + 20, PLAYERHEADSIZEY);
					if (charge % 3 == 2)
						IMAGEMANAGER->render("��ȲIDLERED", getMemDC(), rcHead.left - 10, rcHead.top, 0, 0, PLAYERHEADSIZEX + 20, PLAYERHEADSIZEY);
				}
				break;
			default:
				break;
			}
		}
	}

	if (animState == CARD)
	{
		if (arrow == �⺻�Ѿ�)
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
			IMAGEMANAGER->frameRender("������STATUP", getMemDC(), rcHead.left, rcHead.top, statUpCount, 1);
		}
		else if (arrow == ��Ȳ)
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
			IMAGEMANAGER->frameRender("��ȲSTATUP", getMemDC(), rcHead.left, rcHead.top, statUpCount, 1);
		}

	}
	if (animState == ETC)
	{
		if (arrow == �⺻�Ѿ� || arrow == CARD)
		{
			itemCount++;
			if (itemCount > 50)
			{
				animState = IDLE;
				itemCount = 0;
			}
			IMAGEMANAGER->render("������ITEM", getMemDC(), rcHead.left, rcHead.top, 0, 0, PLAYERHEADSIZEX, PLAYERSIZEY + PLAYERHEADSIZEY);
		}
		else if (arrow == ��Ȳ)
		{
			itemCount++;
			if (itemCount > 50)
			{
				animState = IDLE;
				itemCount = 0;
			}
			IMAGEMANAGER->render("��ȲITEM", getMemDC(), rcHead.left, rcHead.top, 0, 0, PLAYERHEADSIZEX, PLAYERSIZEY + PLAYERHEADSIZEY);
		}
	}
	if (animState == DAMAGE)
	{
		if (arrow == �⺻�Ѿ�)
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
			IMAGEMANAGER->frameRender("������HURT", getMemDC(), rcHead.left, rcHead.top, damageFrameCount, 1);
		}
		if (arrow == ��Ȳ)
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
			IMAGEMANAGER->frameRender("��ȲHURT", getMemDC(), rcHead.left, rcHead.top, damageFrameCount, 1);
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
			if (arrow == �⺻�Ѿ�)
			{
				IMAGEMANAGER->frameRender("������DEAD", getMemDC(), rc.left, rc.top, deadFrame, 0);
			}
			else
			{
				IMAGEMANAGER->frameRender("��ȲDEAD", getMemDC(), rc.left, rc.top, deadFrame, 0);
			}
		}
		deadAlpha--;
		if (deadAlpha>0 && deadCount>16)
		{
			if (arrow == �⺻�Ѿ�)
			{
				IMAGEMANAGER->alphaRender("������DEAD2", getMemDC(), rc.left, rc.top, PLAYERHEADSIZEX * 2, 0, PLAYERHEADSIZEX, PLAYERSIZEY + PLAYERHEADSIZEY, deadAlpha);
			}
			if (arrow == ��Ȳ)
			{
				IMAGEMANAGER->alphaRender("��ȲDEAD2", getMemDC(), rc.left, rc.top, PLAYERHEADSIZEX * 2, 0, PLAYERHEADSIZEX, PLAYERSIZEY + PLAYERHEADSIZEY, deadAlpha);
			}
		}

	}
	//	RectangleMake(getMemDC(), rc);

	//==================================================================
	//		## ��ġȮ�ο� ##
	//==================================================================
	/*for (int i = 0; i < vInventory.size(); i++)
	{
		wsprintf(buffer, TEXT("�÷��̾��κ�:%d"), vInventory[i]);
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
	if (arrow == �⺻�Ѿ�)
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
						//�⺻�Ѿ� �̵��Ÿ� 300, ������ 10, �̵��ӵ� 5

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

						//�⺻�Ѿ� �̵��Ÿ� 300, ������ 10, �̵��ӵ� 5
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

						//�⺻�Ѿ� �̵��Ÿ� 300, ������ 10, �̵��ӵ� 5
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

						//�⺻�Ѿ� �̵��Ÿ� 300, ������ 10, �̵��ӵ� 5
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
						_ū�Ѿ�->fire(x, y, (PI / 1.9), range, 3, bulletSpeed);
						//�⺻�Ѿ� �̵��Ÿ� 300, ������ 10, �̵��ӵ� 5

					}
					else if (KEYMANAGER->isStayKeyDown('D'))
					{
						_ū�Ѿ�->fire(x, y, (PI / 2.1), range, 3, bulletSpeed);

					}
					else
					{
						_ū�Ѿ�->fire(x, y, (PI / 2), range, 3, bulletSpeed);

					}
					fire = true;
					faceState = pUP;
				}

				////////////////////
				if (KEYMANAGER->isStayKeyDown(VK_DOWN))
				{
					if (KEYMANAGER->isStayKeyDown('A'))
					{
						_ū�Ѿ�->fire(x, y, -(PI / 1.5), range, 3, bulletSpeed);

						//�⺻�Ѿ� �̵��Ÿ� 300, ������ 10, �̵��ӵ� 5
					}
					else if (KEYMANAGER->isStayKeyDown('D'))
					{
						_ū�Ѿ�->fire(x, y, -(PI / 2.5), range, 3, bulletSpeed);

					}
					else
					{
						_ū�Ѿ�->fire(x, y, -(PI / 2), range, 3, bulletSpeed);

					}
					faceState = pIDLE;
					fire = true;

				}
				if (KEYMANAGER->isStayKeyDown(VK_LEFT))
				{
					if (KEYMANAGER->isStayKeyDown('W'))
					{
						_ū�Ѿ�->fire(x, y, (PI / 1.5), range, 3, bulletSpeed);

						//�⺻�Ѿ� �̵��Ÿ� 300, ������ 10, �̵��ӵ� 5
					}
					else if (KEYMANAGER->isStayKeyDown('S'))
					{
						_ū�Ѿ�->fire(x, y, -(PI / 1.5), range, 3, bulletSpeed);

					}
					else
					{
						_ū�Ѿ�->fire(x, y, PI, range, 3, bulletSpeed);

					}
					faceState = pLEFT;
					fire = true;
				}
				if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
				{
					if (KEYMANAGER->isStayKeyDown('W'))
					{
						_ū�Ѿ�->fire(x, y, (PI / 2.5), range, 3, bulletSpeed);

						//�⺻�Ѿ� �̵��Ÿ� 300, ������ 10, �̵��ӵ� 5
					}
					else if (KEYMANAGER->isStayKeyDown('S'))
					{
						_ū�Ѿ�->fire(x, y, -(PI / 2.5), range, 3, bulletSpeed);

					}
					else
					{
						_ū�Ѿ�->fire(x, y, (PI * 2), range, 3, bulletSpeed);

					}
					faceState = pRIGHT;
					fire = true;
				}
			}
		}
	}
	else if (arrow == ��Ȳ)

		{
			bulletCount++;
			if (bulletCount % 20 == 0)
			{
				if (KEYMANAGER->isOnceKeyUp(VK_UP))
				{
					if (charge >= 50)
					{
						_��Ȳ->fire(x, y - PLAYERSIZEY / 2 - PLAYERHEADSIZEY / 2 + 10, 3, 56 * 7, 10, 3);
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
						_��Ȳ->fire(x, y - PLAYERSIZEY / 2 - PLAYERHEADSIZEY / 2 + 25, 4, 56 * 7, 10, 3);
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
						_��Ȳ->fire(x - 20, y - PLAYERSIZEY / 2 - PLAYERHEADSIZEY / 2 + 20, 2, 56 * 7, 10, 3);
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
						_��Ȳ->fire(x + 20, y - PLAYERSIZEY / 2 - PLAYERHEADSIZEY / 2 + 20, 1, 56 * 7, 10, 3);
						fire = true;
					}
					charge = 0;
					isCharge = false;
					faceState = pRIGHT;
				}
				////��Ȳ�϶� �⺻ range 200,damage 1, �ӵ� 30 

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
	//�˾��� ������ set(arrow=�˾�)���� �ϰ� // damage�� 3���� �ٲٱ�. 

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
			_im->ItemUse(��ź);
		}
	}

	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		if (space == �ڻ���������)
		{
			_im->ItemUse(�ڻ���������);
		}
		if (space == �𷡽ð�)
		{
			_im->ItemUse(�𷡽ð�);
		}
	}

	if (KEYMANAGER->isOnceKeyDown('Q'))
	{
		if (card == ī��)
		{
			_im->ItemUse(ī��);
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
	//��Ȳ�� ����� ��  ����, �⺻ �̴Ͼ�� �浹 �ѹ��� �ǰ� 
	if (arrow == ��Ȳ)
	{
		int itemp = _enemy->getVMinionPt()->size();
		for (int i = 0; i < _enemy->getVMinionPt()->size(); i++)
		{
			RECT temp;
			RECT temp2 = _enemy->getVMinionPt()->at(i)->getRect();
			
			if (!_��Ȳ->getVBulletPt()->empty())
			{
				for (int j = 0; j < _��Ȳ->getVBulletPt()->size(); j++)
				{
					if (_enemy->getVMinionPt()->at(i)->getMobType() == BOSS)
					{
						if (IntersectRect(&temp, &_��Ȳ->getVBulletPt()->at(j).rc, &temp2)&&monsterShot==false&& _enemy->getVMinionPt()->at(i)->isHit())
						{
							_enemy->getVMinionPt()->at(i)->setHP(_enemy->getVMinionPt()->at(i)->getHP() - _��Ȳ->getVBulletPt()->at(j).damage);
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
						if (IntersectRect(&temp, &_��Ȳ->getVBulletPt()->at(j).rc, &temp2))
						{
							minionShot = true;
						}
						if (minionShot == true)
						{
							_enemy->getVMinionPt()->at(i)->setHP(_enemy->getVMinionPt()->at(i)->getHP() - _��Ȳ->getVBulletPt()->at(j).damage);
							minionShot = false;
						}
					}
				}

			}
		}
	}
	//�⺻�Ѿ� �Ǵ� ū�Ѿ��� ����� �� 
	//if (arrow == �⺻�Ѿ� && cardOn == true)
	//{
	//	int itemp = _enemy->getVMinionPt()->size();				//��ü ������ ������ ��´�. 
	//	for (int i = 0; i < _enemy->getVMinionPt()->size(); i++)	//��ü ������ŭ �����Ѵ�.
	//	{
	//		RECT temp;
	//		RECT temp2 = _enemy->getVMinionPt()->at(i)->getRect(); //���� ������ ��ü��  temp2�� ��´�. 
	//		if (!_ū�Ѿ�->getVBulletPt()->empty())						 //�Ѿ��� ����ִٸ�! �� �߻�Ǿ��ٸ� 
	//		{
	//			for (int j = 0; j < _ū�Ѿ�->getVBulletPt()->size(); j++)
	//			{
	//				if (IntersectRect(&temp, &_ū�Ѿ�->getVBulletPt()->at(j).rc, &temp2))	//ū�Ѿ��� ��ü��, ���� ��ü�� �ε����� 
	//				{//���� ��ü->���(i)��°..->hp�� ��ƶ�. 
	//					_enemy->getVMinionPt()->at(i)->setHP(_enemy->getVMinionPt()->at(i)->getHP() - _ū�Ѿ�->getVBulletPt()->at(j).damage);
	//				}
	//			}
	//		}
	//	}
	//}
	//�Ѿ˿� �÷��̾ �¾��� ��. 
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
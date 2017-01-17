#include "stdafx.h"
#include "bullet.h"
#include"cSceneManager.h"
//=============================================================
//	## bullet ## (공용총알 - 너희들이 만들어라~~~)
//=============================================================
HRESULT bullet::init(char * imageName, int bulletMax)
{
	//총알 이미지 초기화
	_imageName = imageName;
	//총알갯수 및 총알사거리 초기화
	_bulletMax = bulletMax;
	return S_OK;
}


void bullet::release(void)
{
	//	EFFECTMANAGER->release();
}

void bullet::update(void)
{
	move();

}

void bullet::render(void)
{
	_viBullet = _vBullet.begin();
	for (_viBullet; _viBullet != _vBullet.end(); ++_viBullet)
	{
		_viBullet->bulletImage->render(getMemDC(), _viBullet->rc.left, _viBullet->rc.top);
	}

}

void bullet::fire(float x, float y, float angle, float range, int damage, int bulletSpeed)
{
	//총알 벡터에 담는것을 제한한다
	if (_bulletMax < _vBullet.size() + 1) return;

	tagBullet bullet;

	//제로메모리 모르면 사용안해도 무방함
	//구조체의 변수들을 한번에 0으로 초기화 시켜준다
	ZeroMemory(&bullet, sizeof(tagBullet));
	bullet._range = range;
	bullet.damage = damage;
	bullet.bulletImage = IMAGEMANAGER->findImage(_imageName);
	bullet.speed = bulletSpeed;
	bullet.angle = angle;
	bullet.count = 0;
	//	bullet.gravity = gravity;
	bullet.x = bullet.fireX = x;
	bullet.y = bullet.fireY = y;
	bullet.rc = RectMakeCenter(bullet.x, bullet.y,
		bullet.bulletImage->getWidth(),
		bullet.bulletImage->getHeight());

	//벡터에 담기
	_vBullet.push_back(bullet);
}

void bullet::move(void)
{
	_viBullet = _vBullet.begin();
	for (; _viBullet != _vBullet.end();)
	{
		_viBullet->x += cosf(_viBullet->angle) * _viBullet->speed;
		_viBullet->y += -sinf(_viBullet->angle) * _viBullet->speed;

		_viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y,
			_viBullet->bulletImage->getWidth(),
			_viBullet->bulletImage->getHeight());

		//총알이 사거리보다 커졌을때
		float distance = getDistance(_viBullet->fireX, _viBullet->fireY,
			_viBullet->x, _viBullet->y);
		if (_viBullet->_range - 50 < distance &&_viBullet->_range > distance)
		{
			if (_viBullet->angle == (PI * 2))//오른쪽쏠때
			{
				_viBullet->y++;
			}
			if (_viBullet->angle == (PI))//왼쪽쏠때
			{
				_viBullet->y++;
			}
			if (_viBullet->angle == (PI / 2))//위로쏠때
			{
				_viBullet->x++;
			}
			if (_viBullet->angle == -(PI / 2))//아래쏠때
			{
				_viBullet->x++;
			}

		}
		if (_viBullet->_range < distance)
		{
			EFFECTMANAGER->addEffect("큰총알효과", _viBullet->x, _viBullet->y);
			_viBullet = _vBullet.erase(_viBullet);
		}
		else
		{
			++_viBullet;
		}

	}

}


void bullet::removeBullet(int index)
{
	_vBullet.erase(_vBullet.begin() + index);
}

//=============================================================
//	##유황총알 ## (missile[0] => 배열처럼 미리 장전해두고 총알발사)
//=============================================================
HRESULT missile::init(int bulletMax, float range)
{
	//사거리 초기화
	_range = range;
	_bulletMax = bulletMax;

	//총알의 갯수만큼 구조체를 초기화 한 후 벡터에 담기
	for (int i = 0; i < bulletMax; i++)
	{
		//총알 구조체 선언
		tagBullet bullet;
		//제로메모리 모르면 사용안해도 무방함
		//구조체의 변수들을 한번에 0으로 초기화 시켜준다
		ZeroMemory(&bullet, sizeof(tagBullet));
		//	bullet.bulletImage = new image;
		//	bullet.bulletImage->init("test.bmp", 300, 30, true, RGB(255, 0, 255));
		bullet.speed = 5.0f;
		bullet.fire = false;
		//bullet.rc = RectMake(bullet.x, bullet.y, bullet.bulletImage->getHeight, bullet.bulletImage->getWidth);
		//벡터에 담기

	}

	return S_OK;
}

void missile::release(void)
{

}

void missile::update(void)
{
	move();
}

void missile::fire(float x, float y, int bulletKind, float range, int damage, int bulletSpeed)
{
	tagBullet bullet;

	bullet.angle = bulletKind;
	bullet._range = range;
	bullet.damage = damage;
	bullet.speed = bulletSpeed;
	bullet.fire = true;
	bullet.x = bullet.fireX = x;
	bullet.y = bullet.fireY = y;



	bullet.count = 0;

	_vBullet.push_back(bullet);


	//_viBullet = _vBullet.begin();
	//for (_viBullet; _viBullet != _vBullet.end(); ++_viBullet)
	//{
	//	//	if (_viBullet->fire) continue;
	//	_viBullet->angle = bulletKind;
	//	_viBullet->_range = range;
	//	_viBullet->damage = damage;
	//	_viBullet->speed = bulletSpeed;
	//	_viBullet->fire = true;
	//	_viBullet->x = _viBullet->fireX = x;
	//	_viBullet->y = _viBullet->fireY = y;
	//	_viBullet->count = 0;
	//	//	_viBullet->rc = RectMakeCenter(_viBullet->fireX, _viBullet->fireY,
	//	//		_viBullet->bulletImage->getWidth(),_viBullet->bulletImage->getHeight());
	//	
	//	break;
	//}
}

void missile::move(void)
{
	_viBullet = _vBullet.begin();
	for (_viBullet; _viBullet != _vBullet.end(); ++_viBullet)
	{
		if (!_viBullet->fire) continue;
		if (_viBullet->angle == 1)
		{
			_viBullet->x = _viBullet->fireX + _viBullet->_range / 2;
			_viBullet->y = _viBullet->fireY;
			_viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y,
				_viBullet->_range, 20);
			_viBullet->count++;
			if (_viBullet->count>20)
			{
				_viBullet->fire = false;
			}
		}
		else if (_viBullet->angle == 2)
		{
			_viBullet->x = _viBullet->fireX - (_viBullet->_range / 2);
			_viBullet->y = _viBullet->fireY;
			_viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y,
				_viBullet->_range, 20);
			_viBullet->count++;
			if (_viBullet->count>20)
			{
				_viBullet->fire = false;
			}
		}
		else if (_viBullet->angle == 3)
		{
			_viBullet->x = _viBullet->fireX;
			_viBullet->y = _viBullet->fireY - (_viBullet->_range / 2);
			_viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y,
				20, _viBullet->_range);
			_viBullet->count++;
			if (_viBullet->count>20)
			{
				_viBullet->fire = false;
			}
		}
		else if (_viBullet->angle == 4)
		{
			_viBullet->x = _viBullet->fireX;
			_viBullet->y = _viBullet->fireY + (_viBullet->_range / 2);
			_viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y,
				20, _viBullet->_range);
			_viBullet->count++;
			if (_viBullet->count>20)
			{
				_viBullet->fire = false;
			}
		}


		if (_viBullet->fire == false)
		{
			_viBullet = _vBullet.erase(_viBullet);
			break;
		}
	}

}


void missile::render(void)
{
	_viBullet = _vBullet.begin();
	for (_viBullet; _viBullet != _vBullet.end(); ++_viBullet)
	{
		if (!_viBullet->fire) continue;
		if (_viBullet->angle == 4 || _viBullet->angle == 3)
		{
			IMAGEMANAGER->frameRender("혈사상하", getMemDC(), _viBullet->rc.left, _viBullet->rc.top, _viBullet->count % 4, 1);
		}
		if (_viBullet->angle == 1 || _viBullet->angle == 2)
		{
			IMAGEMANAGER->frameRender("혈사좌우", getMemDC(), _viBullet->rc.left, _viBullet->rc.top, 1, _viBullet->count % 4);
		}
		if (KEYMANAGER->isToggleKey(VK_F1))
		{
			Rectangle(getMemDC(), _viBullet->rc.left, _viBullet->rc.top, _viBullet->rc.right, _viBullet->rc.bottom);
		}

	}
}



//=============================================================
//	## FrameBullet ## (프레임 이미지가 있는 총알을 쓸때 사용하는 클래스)
//=============================================================


HRESULT frameBullet::init(char * imageName, int bulletMax)
{
	//총알 이미지 초기화
	_imageName = imageName;
	//총알갯수 및 총알사거리 초기화
	_bulletMax = bulletMax;

	_time = 0;
	return S_OK;
}



void frameBullet::release(void)
{
}

void frameBullet::update(void)
{
	move();
	pixelCol();
}

void frameBullet::render(void)
{
	_viBullet = _vBullet.begin();
	for (_viBullet; _viBullet != _vBullet.end(); ++_viBullet)
	{
		_viBullet->bulletImage->frameRender(getMemDC(), _viBullet->rc.left, _viBullet->rc.top, _viBullet->bulletImage->getFrameX(), _viBullet->bulletImage->getFrameY());
	}
}

void frameBullet::fire(float x, float y, float angle, float range, int damage, int bulletSpeed)
{
	//총알 벡터에 담는것을 제한한다
	if (_bulletMax < _vBullet.size() + 1) return;

	tagBullet bullet;

	//제로메모리 모르면 사용안해도 무방함
	//구조체의 변수들을 한번에 0으로 초기화 시켜준다
	ZeroMemory(&bullet, sizeof(tagBullet));
	bullet._range = range;
	bullet.damage = damage;
	bullet.bulletImage = IMAGEMANAGER->findImage(_imageName);
	bullet.speed = bulletSpeed;
	bullet.angle = angle;
	//	bullet.gravity = gravity;
	bullet.x = bullet.fireX = x;
	bullet.y = bullet.fireY = y;
	bullet.rc = RectMakeCenter(bullet.x, bullet.y,
		bullet.bulletImage->getFrameWidth(),
		bullet.bulletImage->getFrameHeight());

	//벡터에 담기
	_vBullet.push_back(bullet);
}

void frameBullet::move(void)
{
	_viBullet = _vBullet.begin();
	for (; _viBullet != _vBullet.end();)
	{
		_viBullet->x += cosf(_viBullet->angle) * _viBullet->speed;
		_viBullet->y += -sinf(_viBullet->angle) * _viBullet->speed;

		_viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y,
			_viBullet->bulletImage->getFrameWidth(),
			_viBullet->bulletImage->getFrameHeight());
		if (_time % 2 == 0)
		{
			if (_viBullet->bulletImage->getFrameX() < _viBullet->bulletImage->getMaxFrameX())
			{
				_viBullet->bulletImage->setFrameX(_viBullet->bulletImage->getFrameX() + 1);
			}
			else
			{
				_viBullet->bulletImage->setFrameX(0);
			}
		}


		//총알이 사거리보다 커졌을때
		float distance = getDistance(_viBullet->fireX, _viBullet->fireY,
			_viBullet->x, _viBullet->y);
		if (_viBullet->_range < distance)
		{
			EFFECTMANAGER->addEffect("bulletEffect", _viBullet->x, _viBullet->y);
			_viBullet = _vBullet.erase(_viBullet);

		}
		else
		{
			++_viBullet;
		}
	}
	_time;
}

void frameBullet::removeBullet(int index)
{
	EFFECTMANAGER->addEffect("bulletEffect", _vBullet[index].x, _vBullet[index].y);
	_vBullet.erase(_vBullet.begin() + index);
}

void frameBullet::pixelCol()
{
	int current = _scene->GetCurrentMap();
	_viBullet = _vBullet.begin();
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		if (current == 첫번째방)
		{
			COLORREF colorL = GetPixel(IMAGEMANAGER->findImage("firstMapPX")->getMemDC(), _viBullet->rc.left, _viBullet->y - 90);
			COLORREF colorR = GetPixel(IMAGEMANAGER->findImage("firstMapPX")->getMemDC(), _viBullet->rc.right, _viBullet->y - 90);
			COLORREF colorU = GetPixel(IMAGEMANAGER->findImage("firstMapPX")->getMemDC(), _viBullet->x, _viBullet->rc.top - 90);
			COLORREF colorD = GetPixel(IMAGEMANAGER->findImage("firstMapPX")->getMemDC(), _viBullet->x, _viBullet->rc.bottom - 90);

			int r = GetRValue(colorL);
			int g = GetGValue(colorL);
			int b = GetBValue(colorL);
			if ((r == 255 && g == 0 && b == 0) || (r == 0 && g == 255 && b == 0))
			{
				EFFECTMANAGER->addEffect("bulletEffect", _viBullet->x, _viBullet->y);
				_viBullet = _vBullet.erase(_viBullet);
				break;
			}

			r = GetRValue(colorR);
			g = GetGValue(colorR);
			b = GetBValue(colorR);
			if ((r == 255 && g == 0 && b == 0) || (r == 0 && g == 255 && b == 0))
			{
				EFFECTMANAGER->addEffect("bulletEffect", _viBullet->x, _viBullet->y);
				_viBullet = _vBullet.erase(_viBullet);
				break;
			}

			r = GetRValue(colorU);
			g = GetGValue(colorU);
			b = GetBValue(colorU);
			if ((r == 255 && g == 0 && b == 0) || (r == 0 && g == 255 && b == 0))
			{
				EFFECTMANAGER->addEffect("bulletEffect", _viBullet->x, _viBullet->y);
				_viBullet = _vBullet.erase(_viBullet);
				break;
			}

			r = GetRValue(colorD);
			g = GetGValue(colorD);
			b = GetBValue(colorD);
			if ((r == 255 && g == 0 && b == 0) || (r == 0 && g == 255 && b == 0))
			{
				EFFECTMANAGER->addEffect("bulletEffect", _viBullet->x, _viBullet->y);
				_viBullet = _vBullet.erase(_viBullet);
				break;
			}
		}
		else if (current == 두번째방)
		{
			COLORREF colorL = GetPixel(IMAGEMANAGER->findImage("secondMapPX")->getMemDC(), _viBullet->rc.left, _viBullet->y - 90);
			COLORREF colorR = GetPixel(IMAGEMANAGER->findImage("secondMapPX")->getMemDC(), _viBullet->rc.right, _viBullet->y - 90);
			COLORREF colorU = GetPixel(IMAGEMANAGER->findImage("secondMapPX")->getMemDC(), _viBullet->x, _viBullet->rc.top - 90);
			COLORREF colorD = GetPixel(IMAGEMANAGER->findImage("secondMapPX")->getMemDC(), _viBullet->x, _viBullet->rc.bottom - 90);

			int r = GetRValue(colorL);
			int g = GetGValue(colorL);
			int b = GetBValue(colorL);
			if ((r == 255 && g == 0 && b == 0) || (r == 0 && g == 255 && b == 0))
			{
				EFFECTMANAGER->addEffect("bulletEffect", _viBullet->x, _viBullet->y);
				_viBullet = _vBullet.erase(_viBullet);
				break;
			}

			r = GetRValue(colorR);
			g = GetGValue(colorR);
			b = GetBValue(colorR);
			if ((r == 255 && g == 0 && b == 0) || (r == 0 && g == 255 && b == 0))
			{
				EFFECTMANAGER->addEffect("bulletEffect", _viBullet->x, _viBullet->y);
				_viBullet = _vBullet.erase(_viBullet);
				break;
			}

			r = GetRValue(colorU);
			g = GetGValue(colorU);
			b = GetBValue(colorU);
			if ((r == 255 && g == 0 && b == 0) || (r == 0 && g == 255 && b == 0))
			{
				EFFECTMANAGER->addEffect("bulletEffect", _viBullet->x, _viBullet->y);
				_viBullet = _vBullet.erase(_viBullet);
				break;
			}

			r = GetRValue(colorD);
			g = GetGValue(colorD);
			b = GetBValue(colorD);
			if ((r == 255 && g == 0 && b == 0) || (r == 0 && g == 255 && b == 0))
			{
				EFFECTMANAGER->addEffect("bulletEffect", _viBullet->x, _viBullet->y);
				_viBullet = _vBullet.erase(_viBullet);
				break;
			}
		}
		else if (current == 세번째방)
		{
			COLORREF colorL = GetPixel(IMAGEMANAGER->findImage("thirdMapPX")->getMemDC(), _viBullet->rc.left, _viBullet->y - 90);
			COLORREF colorR = GetPixel(IMAGEMANAGER->findImage("thirdMapPX")->getMemDC(), _viBullet->rc.right, _viBullet->y - 90);
			COLORREF colorU = GetPixel(IMAGEMANAGER->findImage("thirdMapPX")->getMemDC(), _viBullet->x, _viBullet->rc.top - 90);
			COLORREF colorD = GetPixel(IMAGEMANAGER->findImage("thirdMapPX")->getMemDC(), _viBullet->x, _viBullet->rc.bottom - 90);

			int r = GetRValue(colorL);
			int g = GetGValue(colorL);
			int b = GetBValue(colorL);
			if ((r == 255 && g == 0 && b == 0) || (r == 0 && g == 255 && b == 0))
			{
				EFFECTMANAGER->addEffect("bulletEffect", _viBullet->x, _viBullet->y);
				_viBullet = _vBullet.erase(_viBullet);
				break;
			}

			r = GetRValue(colorR);
			g = GetGValue(colorR);
			b = GetBValue(colorR);
			if ((r == 255 && g == 0 && b == 0) || (r == 0 && g == 255 && b == 0))
			{
				EFFECTMANAGER->addEffect("bulletEffect", _viBullet->x, _viBullet->y);
				_viBullet = _vBullet.erase(_viBullet);
				break;
			}

			r = GetRValue(colorU);
			g = GetGValue(colorU);
			b = GetBValue(colorU);
			if ((r == 255 && g == 0 && b == 0) || (r == 0 && g == 255 && b == 0))
			{
				EFFECTMANAGER->addEffect("bulletEffect", _viBullet->x, _viBullet->y);
				_viBullet = _vBullet.erase(_viBullet);
				break;
			}

			r = GetRValue(colorD);
			g = GetGValue(colorD);
			b = GetBValue(colorD);
			if ((r == 255 && g == 0 && b == 0) || (r == 0 && g == 255 && b == 0))
			{
				EFFECTMANAGER->addEffect("bulletEffect", _viBullet->x, _viBullet->y);
				_viBullet = _vBullet.erase(_viBullet);
				break;
			}
		}
		else if (current == 네번째방)
		{
			COLORREF colorL = GetPixel(IMAGEMANAGER->findImage("forthMapPX")->getMemDC(), _viBullet->rc.left, _viBullet->y - 90);
			COLORREF colorR = GetPixel(IMAGEMANAGER->findImage("forthMapPX")->getMemDC(), _viBullet->rc.right, _viBullet->y - 90);
			COLORREF colorU = GetPixel(IMAGEMANAGER->findImage("forthMapPX")->getMemDC(), _viBullet->x, _viBullet->rc.top - 90);
			COLORREF colorD = GetPixel(IMAGEMANAGER->findImage("forthMapPX")->getMemDC(), _viBullet->x, _viBullet->rc.bottom - 90);

			int r = GetRValue(colorL);
			int g = GetGValue(colorL);
			int b = GetBValue(colorL);
			if ((r == 255 && g == 0 && b == 0) || (r == 0 && g == 255 && b == 0))
			{
				EFFECTMANAGER->addEffect("bulletEffect", _viBullet->x, _viBullet->y);
				_viBullet = _vBullet.erase(_viBullet);
				break;
			}

			r = GetRValue(colorR);
			g = GetGValue(colorR);
			b = GetBValue(colorR);
			if ((r == 255 && g == 0 && b == 0) || (r == 0 && g == 255 && b == 0))
			{
				EFFECTMANAGER->addEffect("bulletEffect", _viBullet->x, _viBullet->y);
				_viBullet = _vBullet.erase(_viBullet);
				break;
			}

			r = GetRValue(colorU);
			g = GetGValue(colorU);
			b = GetBValue(colorU);
			if ((r == 255 && g == 0 && b == 0) || (r == 0 && g == 255 && b == 0))
			{
				EFFECTMANAGER->addEffect("bulletEffect", _viBullet->x, _viBullet->y);
				_viBullet = _vBullet.erase(_viBullet);
				break;
			}

			r = GetRValue(colorD);
			g = GetGValue(colorD);
			b = GetBValue(colorD);
			if ((r == 255 && g == 0 && b == 0) || (r == 0 && g == 255 && b == 0))
			{
				EFFECTMANAGER->addEffect("bulletEffect", _viBullet->x, _viBullet->y);
				_viBullet = _vBullet.erase(_viBullet);
				break;
			}
		}
		else if (current == 다섯번째방)
		{
			COLORREF colorL = GetPixel(IMAGEMANAGER->findImage("fifthMapPX")->getMemDC(), _viBullet->rc.left, _viBullet->y - 90);
			COLORREF colorR = GetPixel(IMAGEMANAGER->findImage("fifthMapPX")->getMemDC(), _viBullet->rc.right, _viBullet->y - 90);
			COLORREF colorU = GetPixel(IMAGEMANAGER->findImage("fifthMapPX")->getMemDC(), _viBullet->x, _viBullet->rc.top - 90);
			COLORREF colorD = GetPixel(IMAGEMANAGER->findImage("fifthMapPX")->getMemDC(), _viBullet->x, _viBullet->rc.bottom - 90);

			int r = GetRValue(colorL);
			int g = GetGValue(colorL);
			int b = GetBValue(colorL);
			if ((r == 255 && g == 0 && b == 0) || (r == 0 && g == 255 && b == 0))
			{
				EFFECTMANAGER->addEffect("bulletEffect", _viBullet->x, _viBullet->y);
				_viBullet = _vBullet.erase(_viBullet);
				break;
			}

			r = GetRValue(colorR);
			g = GetGValue(colorR);
			b = GetBValue(colorR);
			if ((r == 255 && g == 0 && b == 0) || (r == 0 && g == 255 && b == 0))
			{
				EFFECTMANAGER->addEffect("bulletEffect", _viBullet->x, _viBullet->y);
				_viBullet = _vBullet.erase(_viBullet);
				break;
			}

			r = GetRValue(colorU);
			g = GetGValue(colorU);
			b = GetBValue(colorU);
			if ((r == 255 && g == 0 && b == 0) || (r == 0 && g == 255 && b == 0))
			{
				EFFECTMANAGER->addEffect("bulletEffect", _viBullet->x, _viBullet->y);
				_viBullet = _vBullet.erase(_viBullet);
				break;
			}

			r = GetRValue(colorD);
			g = GetGValue(colorD);
			b = GetBValue(colorD);
			if ((r == 255 && g == 0 && b == 0) || (r == 0 && g == 255 && b == 0))
			{
				EFFECTMANAGER->addEffect("bulletEffect", _viBullet->x, _viBullet->y);
				_viBullet = _vBullet.erase(_viBullet);
				break;
			}
		}
		else if (current == 여섯번째방)
		{
			COLORREF colorL = GetPixel(IMAGEMANAGER->findImage("sixthMapPX")->getMemDC(), _viBullet->rc.left, _viBullet->y - 90);
			COLORREF colorR = GetPixel(IMAGEMANAGER->findImage("sixthMapPX")->getMemDC(), _viBullet->rc.right, _viBullet->y - 90);
			COLORREF colorU = GetPixel(IMAGEMANAGER->findImage("sixthMapPX")->getMemDC(), _viBullet->x, _viBullet->rc.top - 90);
			COLORREF colorD = GetPixel(IMAGEMANAGER->findImage("sixthMapPX")->getMemDC(), _viBullet->x, _viBullet->rc.bottom - 90);

			int r = GetRValue(colorL);
			int g = GetGValue(colorL);
			int b = GetBValue(colorL);
			if ((r == 255 && g == 0 && b == 0) || (r == 0 && g == 255 && b == 0))
			{
				EFFECTMANAGER->addEffect("bulletEffect", _viBullet->x, _viBullet->y);
				_viBullet = _vBullet.erase(_viBullet);
				break;
			}

			r = GetRValue(colorR);
			g = GetGValue(colorR);
			b = GetBValue(colorR);
			if ((r == 255 && g == 0 && b == 0) || (r == 0 && g == 255 && b == 0))
			{
				EFFECTMANAGER->addEffect("bulletEffect", _viBullet->x, _viBullet->y);
				_viBullet = _vBullet.erase(_viBullet);
				break;
			}

			r = GetRValue(colorU);
			g = GetGValue(colorU);
			b = GetBValue(colorU);
			if ((r == 255 && g == 0 && b == 0) || (r == 0 && g == 255 && b == 0))
			{
				EFFECTMANAGER->addEffect("bulletEffect", _viBullet->x, _viBullet->y);
				_viBullet = _vBullet.erase(_viBullet);
				break;
			}

			r = GetRValue(colorD);
			g = GetGValue(colorD);
			b = GetBValue(colorD);
			if ((r == 255 && g == 0 && b == 0) || (r == 0 && g == 255 && b == 0))
			{
				EFFECTMANAGER->addEffect("bulletEffect", _viBullet->x, _viBullet->y);
				_viBullet = _vBullet.erase(_viBullet);
				break;
			}
		}
		else if (current == 일곱번째방)
		{
			COLORREF colorL = GetPixel(IMAGEMANAGER->findImage("seventhMapPX")->getMemDC(), _viBullet->rc.left, _viBullet->y - 90);
			COLORREF colorR = GetPixel(IMAGEMANAGER->findImage("seventhMapPX")->getMemDC(), _viBullet->rc.right, _viBullet->y - 90);
			COLORREF colorU = GetPixel(IMAGEMANAGER->findImage("seventhMapPX")->getMemDC(), _viBullet->x, _viBullet->rc.top - 90);
			COLORREF colorD = GetPixel(IMAGEMANAGER->findImage("seventhMapPX")->getMemDC(), _viBullet->x, _viBullet->rc.bottom - 90);

			int r = GetRValue(colorL);
			int g = GetGValue(colorL);
			int b = GetBValue(colorL);
			if ((r == 255 && g == 0 && b == 0) || (r == 0 && g == 255 && b == 0))
			{
				EFFECTMANAGER->addEffect("bulletEffect", _viBullet->x, _viBullet->y);
				_viBullet = _vBullet.erase(_viBullet);
				break;
			}

			r = GetRValue(colorR);
			g = GetGValue(colorR);
			b = GetBValue(colorR);
			if ((r == 255 && g == 0 && b == 0) || (r == 0 && g == 255 && b == 0))
			{
				EFFECTMANAGER->addEffect("bulletEffect", _viBullet->x, _viBullet->y);
				_viBullet = _vBullet.erase(_viBullet);
				break;
			}

			r = GetRValue(colorU);
			g = GetGValue(colorU);
			b = GetBValue(colorU);
			if ((r == 255 && g == 0 && b == 0) || (r == 0 && g == 255 && b == 0))
			{
				EFFECTMANAGER->addEffect("bulletEffect", _viBullet->x, _viBullet->y);
				_viBullet = _vBullet.erase(_viBullet);
				break;
			}

			r = GetRValue(colorD);
			g = GetGValue(colorD);
			b = GetBValue(colorD);
			if ((r == 255 && g == 0 && b == 0) || (r == 0 && g == 255 && b == 0))
			{
				EFFECTMANAGER->addEffect("bulletEffect", _viBullet->x, _viBullet->y);
				_viBullet = _vBullet.erase(_viBullet);
				break;
			}
		}
		else if (current == 여덟번째방)
		{
			COLORREF colorL = GetPixel(IMAGEMANAGER->findImage("eighthMapPX")->getMemDC(), _viBullet->rc.left, _viBullet->y - 90);
			COLORREF colorR = GetPixel(IMAGEMANAGER->findImage("eighthMapPX")->getMemDC(), _viBullet->rc.right, _viBullet->y - 90);
			COLORREF colorU = GetPixel(IMAGEMANAGER->findImage("eighthMapPX")->getMemDC(), _viBullet->x, _viBullet->rc.top - 90);
			COLORREF colorD = GetPixel(IMAGEMANAGER->findImage("eighthMapPX")->getMemDC(), _viBullet->x, _viBullet->rc.bottom - 90);

			int r = GetRValue(colorL);
			int g = GetGValue(colorL);
			int b = GetBValue(colorL);
			if ((r == 255 && g == 0 && b == 0) || (r == 0 && g == 255 && b == 0))
			{
				EFFECTMANAGER->addEffect("bulletEffect", _viBullet->x, _viBullet->y);
				_viBullet = _vBullet.erase(_viBullet);
				break;
			}

			r = GetRValue(colorR);
			g = GetGValue(colorR);
			b = GetBValue(colorR);
			if ((r == 255 && g == 0 && b == 0) || (r == 0 && g == 255 && b == 0))
			{
				EFFECTMANAGER->addEffect("bulletEffect", _viBullet->x, _viBullet->y);
				_viBullet = _vBullet.erase(_viBullet);
				break;
			}

			r = GetRValue(colorU);
			g = GetGValue(colorU);
			b = GetBValue(colorU);
			if ((r == 255 && g == 0 && b == 0) || (r == 0 && g == 255 && b == 0))
			{
				EFFECTMANAGER->addEffect("bulletEffect", _viBullet->x, _viBullet->y);
				_viBullet = _vBullet.erase(_viBullet);
				break;
			}

			r = GetRValue(colorD);
			g = GetGValue(colorD);
			b = GetBValue(colorD);
			if ((r == 255 && g == 0 && b == 0) || (r == 0 && g == 255 && b == 0))
			{
				EFFECTMANAGER->addEffect("bulletEffect", _viBullet->x, _viBullet->y);
				_viBullet = _vBullet.erase(_viBullet);
				break;
			}
		}


	}
}


//=============================================================
//	## hoppingBullet ## (곡사총알)
//=============================================================


HRESULT hoppingBullet::init(char * imageName, int bulletMax)
{
	//총알 이미지 초기화
	_imageName = imageName;
	//총알갯수 및 총알사거리 초기화
	_bulletMax = bulletMax;
	_time = 0;
	return S_OK;
}



void hoppingBullet::release(void)
{
}

void hoppingBullet::update(void)
{
	move();
	pixelCol();
}

void hoppingBullet::render(void)
{
	_viBullet = _vBullet.begin();
	for (_viBullet; _viBullet != _vBullet.end(); ++_viBullet)
	{
		_viBullet->bulletImage->frameRender(getMemDC(), _viBullet->rc.left, _viBullet->rc.top, _viBullet->bulletImage->getFrameX(), _viBullet->bulletImage->getFrameY());
		IMAGEMANAGER->findImage("shadowB")->render(getMemDC(), _viBullet->x - 7, _viBullet->y + 17);
	}
}

void hoppingBullet::fire(float x, float y, float angle, float jumpPower, int damage, int bulletSpeed)
{
	//총알 벡터에 담는것을 제한한다
	if (_bulletMax < _vBullet.size() + 1) return;

	tagHBullet bullet;

	//제로메모리 모르면 사용안해도 무방함
	//구조체의 변수들을 한번에 0으로 초기화 시켜준다
	ZeroMemory(&bullet, sizeof(tagHBullet));

	bullet._jumpPower = jumpPower;
	bullet.damage = damage;
	bullet.bulletImage = IMAGEMANAGER->findImage(_imageName);
	bullet.speed = bulletSpeed;
	bullet.angle = angle;
	//	bullet.gravity = gravity;
	bullet.x = bullet.fireX = x;
	bullet.y = bullet.fireY = y;
	bullet.rc = RectMakeCenter(bullet.x, bullet.y,
		bullet.bulletImage->getFrameWidth(),
		bullet.bulletImage->getFrameHeight());

	//벡터에 담기
	_vBullet.push_back(bullet);
}

void hoppingBullet::move(void)
{
	_viBullet = _vBullet.begin();
	for (; _viBullet != _vBullet.end();)
	{
		_viBullet->x += cosf(_viBullet->angle) * _viBullet->speed;
		_viBullet->y += -sinf(_viBullet->angle) * _viBullet->speed;

		_viBullet->gravity += 0.3f;
		_viBullet->_height += _viBullet->gravity - _viBullet->_jumpPower;

		_viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y + _viBullet->_height,
			_viBullet->bulletImage->getFrameWidth(),
			_viBullet->bulletImage->getFrameHeight());

		if (_time % 2 == 0)
		{
			if (_viBullet->bulletImage->getFrameX() < _viBullet->bulletImage->getMaxFrameX())
			{
				_viBullet->bulletImage->setFrameX(_viBullet->bulletImage->getFrameX() + 1);
			}
			else
			{
				_viBullet->bulletImage->setFrameX(0);
			}
		}


		//총알이 사거리보다 커졌을때

		if (_viBullet->_height>10)
		{
			EFFECTMANAGER->addEffect("bulletEffect", _viBullet->x, _viBullet->y + _viBullet->_height);
			_viBullet = _vBullet.erase(_viBullet);
		}
		else
		{
			++_viBullet;
		}
	}
	_time++;
}

void hoppingBullet::pixelCol()
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		COLORREF colorL = GetPixel(IMAGEMANAGER->findImage("thirdMapPX")->getMemDC(), _viBullet->x - (_viBullet->bulletImage->getFrameWidth() / 2), _viBullet->y - 90);
		COLORREF colorR = GetPixel(IMAGEMANAGER->findImage("thirdMapPX")->getMemDC(), _viBullet->x + (_viBullet->bulletImage->getFrameWidth() / 2), _viBullet->y - 90);
		COLORREF colorU = GetPixel(IMAGEMANAGER->findImage("thirdMapPX")->getMemDC(), _viBullet->x, _viBullet->y - (_viBullet->bulletImage->getFrameHeight() / 2) - 90);
		COLORREF colorD = GetPixel(IMAGEMANAGER->findImage("thirdMapPX")->getMemDC(), _viBullet->x, _viBullet->y + (_viBullet->bulletImage->getFrameHeight() - 90));

		int r = GetRValue(colorL);
		int g = GetGValue(colorL);
		int b = GetBValue(colorL);
		if ((r == 255 && g == 0 && b == 0) || (r == 0 && g == 255 && b == 0))
		{
			EFFECTMANAGER->addEffect("bulletEffect", _viBullet->x, _viBullet->y + _viBullet->_height);
			_viBullet = _vBullet.erase(_viBullet);
			break;
		}

		r = GetRValue(colorR);
		g = GetGValue(colorR);
		b = GetBValue(colorR);
		if ((r == 255 && g == 0 && b == 0) || (r == 0 && g == 255 && b == 0))
		{
			EFFECTMANAGER->addEffect("bulletEffect", _viBullet->x, _viBullet->y + _viBullet->_height);
			_viBullet = _vBullet.erase(_viBullet);
			break;
		}

		r = GetRValue(colorU);
		g = GetGValue(colorU);
		b = GetBValue(colorU);
		if ((r == 255 && g == 0 && b == 0) || (r == 0 && g == 255 && b == 0))
		{

			EFFECTMANAGER->addEffect("bulletEffect", _viBullet->x, _viBullet->y + _viBullet->_height);
			_viBullet = _vBullet.erase(_viBullet);
			break;
		}

		r = GetRValue(colorD);
		g = GetGValue(colorD);
		b = GetBValue(colorD);
		if ((r == 255 && g == 0 && b == 0) || (r == 0 && g == 255 && b == 0))
		{
			if (_viBullet->_height < 10)
			{
				EFFECTMANAGER->addEffect("bulletEffect", _viBullet->x, _viBullet->y + _viBullet->_height);
				_viBullet = _vBullet.erase(_viBullet);
			}
			break;
		}
	}

}

void hoppingBullet::removeBullet(int index)
{
	EFFECTMANAGER->addEffect("bulletEffect", _vBullet[index].x, _vBullet[index].y);
	_vBullet.erase(_vBullet.begin() + index);
}






//=============================================================
//	## missileM1 ## (한발씩 총알 발사하면서 생성하고 자동삭제)
//=============================================================

HRESULT missileM1::init(int bulletMax, float range)
{
	//총알갯수 및 사거리 초기화
	_bulletMax = bulletMax;
	_range = range;

	return S_OK;
}

void missileM1::release(void)
{
}

void missileM1::update(void)
{
	move();
}

void missileM1::render(void)
{
	_viBullet = _vBullet.begin();
	for (_viBullet; _viBullet != _vBullet.end(); ++_viBullet)
	{
		_viBullet->bulletImage->frameRender(getMemDC(), _viBullet->rc.left, _viBullet->rc.top);

		_viBullet->count++;
		if (_viBullet->count % 3 == 0)
		{
			_viBullet->bulletImage->setFrameX(_viBullet->bulletImage->getFrameX() + 1);
			if (_viBullet->bulletImage->getFrameX() >= _viBullet->bulletImage->getMaxFrameX())
			{
				_viBullet->bulletImage->setFrameX(0);
			}
			_viBullet->count = 0;
		}
	}
}

void missileM1::fire(float x, float y)
{
	//총알 벡터에 담는것을 제한한다
	if (_bulletMax < _vBullet.size() + 1) return;

	tagBullet bullet;
	//제로메모리 모르면 사용안해도 무방함
	//구조체의 변수들을 한번에 0으로 초기화 시켜준다
	ZeroMemory(&bullet, sizeof(tagBullet));
	bullet.bulletImage = new image;
	bullet.bulletImage->init("missile.bmp", 416, 64, 13, 1, true, RGB(255, 0, 255));
	bullet.speed = 5.0f;
	bullet.x = bullet.fireX = x;
	bullet.y = bullet.fireY = y;
	bullet.rc = RectMakeCenter(bullet.x, bullet.y,
		bullet.bulletImage->getFrameWidth(),
		bullet.bulletImage->getFrameHeight());

	//벡터에 담기
	_vBullet.push_back(bullet);
}

void missileM1::move(void)
{
	_viBullet = _vBullet.begin();
	for (; _viBullet != _vBullet.end();)
	{
		_viBullet->y -= _viBullet->speed;
		_viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y,
			_viBullet->bulletImage->getFrameWidth(),
			_viBullet->bulletImage->getFrameHeight());

		//총알이 사거리보다 커졌을때
		float distance = getDistance(_viBullet->fireX, _viBullet->fireY,
			_viBullet->x, _viBullet->y);
		if (_range < distance)
		{
			_viBullet->bulletImage->release();
			SAFE_DELETE(_viBullet->bulletImage);
			_viBullet = _vBullet.erase(_viBullet);
		}
		else
		{
			++_viBullet;
		}
	}
}

void missileM1::removeBullet(int index)
{
	_vBullet[index].bulletImage->release();
	SAFE_DELETE(_vBullet[index].bulletImage);
	_vBullet.erase(_vBullet.begin() + index);
}



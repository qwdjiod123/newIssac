#include "stdafx.h"
#include "bullet.h"
#include"cSceneManager.h"
//=============================================================
//	## bullet ## (�����Ѿ� - ������� ������~~~)
//=============================================================
HRESULT bullet::init(char * imageName, int bulletMax)
{
	//�Ѿ� �̹��� �ʱ�ȭ
	_imageName = imageName;
	//�Ѿ˰��� �� �Ѿ˻�Ÿ� �ʱ�ȭ
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
	//�Ѿ� ���Ϳ� ��°��� �����Ѵ�
	if (_bulletMax < _vBullet.size() + 1) return;

	tagBullet bullet;

	//���θ޸� �𸣸� �����ص� ������
	//����ü�� �������� �ѹ��� 0���� �ʱ�ȭ �����ش�
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

	//���Ϳ� ���
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

		//�Ѿ��� ��Ÿ����� Ŀ������
		float distance = getDistance(_viBullet->fireX, _viBullet->fireY,
			_viBullet->x, _viBullet->y);
		if (_viBullet->_range - 50 < distance &&_viBullet->_range > distance)
		{
			if (_viBullet->angle == (PI * 2))//�����ʽ�
			{
				_viBullet->y++;
			}
			if (_viBullet->angle == (PI))//���ʽ�
			{
				_viBullet->y++;
			}
			if (_viBullet->angle == (PI / 2))//���ν�
			{
				_viBullet->x++;
			}
			if (_viBullet->angle == -(PI / 2))//�Ʒ���
			{
				_viBullet->x++;
			}

		}
		if (_viBullet->_range < distance)
		{
			EFFECTMANAGER->addEffect("ū�Ѿ�ȿ��", _viBullet->x, _viBullet->y);
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
//	##��Ȳ�Ѿ� ## (missile[0] => �迭ó�� �̸� �����صΰ� �Ѿ˹߻�)
//=============================================================
HRESULT missile::init(int bulletMax, float range)
{
	//��Ÿ� �ʱ�ȭ
	_range = range;
	_bulletMax = bulletMax;

	//�Ѿ��� ������ŭ ����ü�� �ʱ�ȭ �� �� ���Ϳ� ���
	for (int i = 0; i < bulletMax; i++)
	{
		//�Ѿ� ����ü ����
		tagBullet bullet;
		//���θ޸� �𸣸� �����ص� ������
		//����ü�� �������� �ѹ��� 0���� �ʱ�ȭ �����ش�
		ZeroMemory(&bullet, sizeof(tagBullet));
		//	bullet.bulletImage = new image;
		//	bullet.bulletImage->init("test.bmp", 300, 30, true, RGB(255, 0, 255));
		bullet.speed = 5.0f;
		bullet.fire = false;
		//bullet.rc = RectMake(bullet.x, bullet.y, bullet.bulletImage->getHeight, bullet.bulletImage->getWidth);
		//���Ϳ� ���

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
			IMAGEMANAGER->frameRender("�������", getMemDC(), _viBullet->rc.left, _viBullet->rc.top, _viBullet->count % 4, 1);
		}
		if (_viBullet->angle == 1 || _viBullet->angle == 2)
		{
			IMAGEMANAGER->frameRender("�����¿�", getMemDC(), _viBullet->rc.left, _viBullet->rc.top, 1, _viBullet->count % 4);
		}
		if (KEYMANAGER->isToggleKey(VK_F1))
		{
			Rectangle(getMemDC(), _viBullet->rc.left, _viBullet->rc.top, _viBullet->rc.right, _viBullet->rc.bottom);
		}

	}
}



//=============================================================
//	## FrameBullet ## (������ �̹����� �ִ� �Ѿ��� ���� ����ϴ� Ŭ����)
//=============================================================


HRESULT frameBullet::init(char * imageName, int bulletMax)
{
	//�Ѿ� �̹��� �ʱ�ȭ
	_imageName = imageName;
	//�Ѿ˰��� �� �Ѿ˻�Ÿ� �ʱ�ȭ
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
	//�Ѿ� ���Ϳ� ��°��� �����Ѵ�
	if (_bulletMax < _vBullet.size() + 1) return;

	tagBullet bullet;

	//���θ޸� �𸣸� �����ص� ������
	//����ü�� �������� �ѹ��� 0���� �ʱ�ȭ �����ش�
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

	//���Ϳ� ���
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


		//�Ѿ��� ��Ÿ����� Ŀ������
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
		if (current == ù��°��)
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
		else if (current == �ι�°��)
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
		else if (current == ����°��)
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
		else if (current == �׹�°��)
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
		else if (current == �ټ���°��)
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
		else if (current == ������°��)
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
		else if (current == �ϰ���°��)
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
		else if (current == ������°��)
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
//	## hoppingBullet ## (����Ѿ�)
//=============================================================


HRESULT hoppingBullet::init(char * imageName, int bulletMax)
{
	//�Ѿ� �̹��� �ʱ�ȭ
	_imageName = imageName;
	//�Ѿ˰��� �� �Ѿ˻�Ÿ� �ʱ�ȭ
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
	//�Ѿ� ���Ϳ� ��°��� �����Ѵ�
	if (_bulletMax < _vBullet.size() + 1) return;

	tagHBullet bullet;

	//���θ޸� �𸣸� �����ص� ������
	//����ü�� �������� �ѹ��� 0���� �ʱ�ȭ �����ش�
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

	//���Ϳ� ���
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


		//�Ѿ��� ��Ÿ����� Ŀ������

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
//	## missileM1 ## (�ѹ߾� �Ѿ� �߻��ϸ鼭 �����ϰ� �ڵ�����)
//=============================================================

HRESULT missileM1::init(int bulletMax, float range)
{
	//�Ѿ˰��� �� ��Ÿ� �ʱ�ȭ
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
	//�Ѿ� ���Ϳ� ��°��� �����Ѵ�
	if (_bulletMax < _vBullet.size() + 1) return;

	tagBullet bullet;
	//���θ޸� �𸣸� �����ص� ������
	//����ü�� �������� �ѹ��� 0���� �ʱ�ȭ �����ش�
	ZeroMemory(&bullet, sizeof(tagBullet));
	bullet.bulletImage = new image;
	bullet.bulletImage->init("missile.bmp", 416, 64, 13, 1, true, RGB(255, 0, 255));
	bullet.speed = 5.0f;
	bullet.x = bullet.fireX = x;
	bullet.y = bullet.fireY = y;
	bullet.rc = RectMakeCenter(bullet.x, bullet.y,
		bullet.bulletImage->getFrameWidth(),
		bullet.bulletImage->getFrameHeight());

	//���Ϳ� ���
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

		//�Ѿ��� ��Ÿ����� Ŀ������
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



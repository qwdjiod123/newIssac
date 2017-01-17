#include "stdafx.h"
#include "shootEnemy.h"
#include"cPlayer.h"
#include"cSceneGame.h"

HRESULT shootEnemy::init(void)
{
	return S_OK;
}

HRESULT shootEnemy::init(int x, int y, cPlayer * player)
{
	img = IMAGEMANAGER->findImage("shootEnemy");
	shootAnime= IMAGEMANAGER->findImage("shootEnemyAnime");
	_HP = 5;
	_shootCount = 0;
	_player = player;
	_x = x;
	_y = y;
	_rc = RectMakeCenter(_x, _y, img->getWidth(), img->getHeight());
	_knockBackAngle = 0;			//넉백 각도
	_knockBackCount = 0;			//넉백 타이머
	vibration = 0;
	vLeft = false;
	shootFrameX=0;
	isAttack=false;
	time=0;
	isStartFrame = false;
	_hitTime = 0;
	return S_OK;
}

void shootEnemy::release(void)
{
}

void shootEnemy::update(void)
{
	move();
	animation();
}

void shootEnemy::render(void)
{
	draw();
}

void shootEnemy::move()
{
	if (!vLeft)
	{
		vibration -= 3;
	}
	else
	{
		vibration += 3;
	}
	if (vibration < -5)
	{
		vLeft = true;
	}

	if (vibration > 5)
	{
		vLeft = false;
	}

	if (_knockBackCount > 0)
	{
		_knockBackCount--;
		_x += cosf(_knockBackAngle)*KONCKBACKPOWER;
		_y += -sinf(_knockBackAngle)*KONCKBACKPOWER;
	}
	else
	{
		_knockBackCount = 0;
		_knockBackAngle = 0;
	}


	if(getDistance(_player->GetX(), _player->GetY(), _x, _y) < 300)
	{
		if(_shootCount > 0)
		{
			_shootCount--;
		}
		else
		{
			if(!isAttack)
			{
				isAttack=true;
			}

		}
	}

	if(isAttack)
	{
		if(shootFrameX < shootAnime->getMaxFrameX())
		{
			if(time % 4 == 0)
			{
				shootFrameX++;
				isStartFrame = true;
			}
			else
			{
				isStartFrame = false;
			}
		}
		else
		{
			
			isAttack=false;
			shootFrameX =0;
			_shootCount=100;
		}
	}

	pixelCol();

	_rc = RectMakeCenter(_x+vibration, _y, img->getWidth(), img->getHeight());
	_shootCount--;
	time++;
}

void shootEnemy::draw()
{
	if(isAttack)
	{
		shootAnime->frameRender(getMemDC(),_x-(shootAnime->getFrameWidth()/2),_y - (shootAnime->getFrameHeight() / 2),shootFrameX,0);
		if (_hitTime > 0)
		{
			IMAGEMANAGER->findImage("shootEnemyAnimeR")->frameRender(getMemDC(), _x - (shootAnime->getFrameWidth() / 2), _y - (shootAnime->getFrameHeight() / 2), shootFrameX, 0);
			_hitTime--;
		}
	}
	else
	{
		img->render(getMemDC(), _rc.left, _rc.top);
		if (_hitTime > 0)
		{
			IMAGEMANAGER->findImage("shootEnemyR")->render(getMemDC(), _rc.left, _rc.top);
			_hitTime--;
		}
	}
}

void shootEnemy::animation()
{
}

void shootEnemy::pixelCol()
{
	int currentMap = _sceneManager->GetCurrentMap();
	if (currentMap == 첫번째방)
	{
		COLORREF colorL = GetPixel(IMAGEMANAGER->findImage("firstMapPX")->getMemDC(), _rc.left, _y - 90);
		COLORREF colorR = GetPixel(IMAGEMANAGER->findImage("firstMapPX")->getMemDC(), _rc.right, _y - 90);
		COLORREF colorU = GetPixel(IMAGEMANAGER->findImage("firstMapPX")->getMemDC(), _x, _rc.top - 90);
		COLORREF colorD = GetPixel(IMAGEMANAGER->findImage("firstMapPX")->getMemDC(), _x, _rc.bottom - 90);

		int r = GetRValue(colorL);
		int g = GetGValue(colorL);
		int b = GetBValue(colorL);
		if ((r == 255 && g == 0 && b == 0) || (r == 0 && g == 255 && b == 0))
		{
			if (_knockBackCount > 0)
			{
				_knockBackAngle = PI - _knockBackAngle;
			}
		}

		r = GetRValue(colorR);
		g = GetGValue(colorR);
		b = GetBValue(colorR);
		if ((r == 255 && g == 0 && b == 0) || (r == 0 && g == 255 && b == 0))
		{
			if (_knockBackCount > 0)
			{
				_knockBackAngle = PI - _knockBackAngle;
			}
		}

		r = GetRValue(colorU);
		g = GetGValue(colorU);
		b = GetBValue(colorU);
		if ((r == 255 && g == 0 && b == 0) || (r == 0 && g == 255 && b == 0))
		{
			if (_knockBackCount > 0)
			{
				_knockBackAngle = -_knockBackAngle;
			}
		}

		r = GetRValue(colorD);
		g = GetGValue(colorD);
		b = GetBValue(colorD);
		if ((r == 255 && g == 0 && b == 0) || (r == 0 && g == 255 && b == 0))
		{
			if (_knockBackCount > 0)
			{
				_knockBackAngle = -_knockBackAngle;
			}
		}


	}
	else if (currentMap == 두번째방)
	{
		COLORREF colorL = GetPixel(IMAGEMANAGER->findImage("secondMapPX")->getMemDC(), _rc.left, _y - 90);
		COLORREF colorR = GetPixel(IMAGEMANAGER->findImage("secondMapPX")->getMemDC(), _rc.right, _y - 90);
		COLORREF colorU = GetPixel(IMAGEMANAGER->findImage("secondMapPX")->getMemDC(), _x, _rc.top - 90);
		COLORREF colorD = GetPixel(IMAGEMANAGER->findImage("secondMapPX")->getMemDC(), _x, _rc.bottom - 90);

		int r = GetRValue(colorL);
		int g = GetGValue(colorL);
		int b = GetBValue(colorL);
		if ((r == 255 && g == 0 && b == 0) || (r == 0 && g == 255 && b == 0))
		{
			if (_knockBackCount > 0)
			{
				_knockBackAngle = PI - _knockBackAngle;
			}
		}

		r = GetRValue(colorR);
		g = GetGValue(colorR);
		b = GetBValue(colorR);
		if ((r == 255 && g == 0 && b == 0) || (r == 0 && g == 255 && b == 0))
		{
			if (_knockBackCount > 0)
			{
				_knockBackAngle = PI - _knockBackAngle;
			}
		}

		r = GetRValue(colorU);
		g = GetGValue(colorU);
		b = GetBValue(colorU);
		if ((r == 255 && g == 0 && b == 0) || (r == 0 && g == 255 && b == 0))
		{
			if (_knockBackCount > 0)
			{
				_knockBackAngle = -_knockBackAngle;
			}
		}

		r = GetRValue(colorD);
		g = GetGValue(colorD);
		b = GetBValue(colorD);
		if ((r == 255 && g == 0 && b == 0) || (r == 0 && g == 255 && b == 0))
		{
			if (_knockBackCount > 0)
			{
				_knockBackAngle = -_knockBackAngle;
			}
		}

	}
	else if (currentMap == 세번째방)
	{
		COLORREF colorL = GetPixel(IMAGEMANAGER->findImage("thirdMapPX")->getMemDC(), _rc.left, _y - 90);
		COLORREF colorR = GetPixel(IMAGEMANAGER->findImage("thirdMapPX")->getMemDC(), _rc.right, _y - 90);
		COLORREF colorU = GetPixel(IMAGEMANAGER->findImage("thirdMapPX")->getMemDC(), _x, _rc.top - 90);
		COLORREF colorD = GetPixel(IMAGEMANAGER->findImage("thirdMapPX")->getMemDC(), _x, _rc.bottom - 90);

		int r = GetRValue(colorL);
		int g = GetGValue(colorL);
		int b = GetBValue(colorL);
		if ((r == 255 && g == 0 && b == 0) || (r == 0 && g == 255 && b == 0))
		{
			if (_knockBackCount > 0)
			{
				_knockBackAngle = PI - _knockBackAngle;
			}
		}

		r = GetRValue(colorR);
		g = GetGValue(colorR);
		b = GetBValue(colorR);
		if ((r == 255 && g == 0 && b == 0) || (r == 0 && g == 255 && b == 0))
		{
			if (_knockBackCount > 0)
			{
				_knockBackAngle = PI - _knockBackAngle;
			}
		}

		r = GetRValue(colorU);
		g = GetGValue(colorU);
		b = GetBValue(colorU);
		if ((r == 255 && g == 0 && b == 0) || (r == 0 && g == 255 && b == 0))
		{
			if (_knockBackCount > 0)
			{
				_knockBackAngle = -_knockBackAngle;
			}
		}

		r = GetRValue(colorD);
		g = GetGValue(colorD);
		b = GetBValue(colorD);
		if ((r == 255 && g == 0 && b == 0) || (r == 0 && g == 255 && b == 0))
		{
			if (_knockBackCount > 0)
			{
				_knockBackAngle = -_knockBackAngle;
			}
		}
	}
	else if (currentMap == 네번째방)
	{
		COLORREF colorL = GetPixel(IMAGEMANAGER->findImage("fourthMapPX")->getMemDC(), _rc.left, _y - 90);
		COLORREF colorR = GetPixel(IMAGEMANAGER->findImage("fourthMapPX")->getMemDC(), _rc.right, _y - 90);
		COLORREF colorU = GetPixel(IMAGEMANAGER->findImage("fourthMapPX")->getMemDC(), _x, _rc.top - 90);
		COLORREF colorD = GetPixel(IMAGEMANAGER->findImage("fourthMapPX")->getMemDC(), _x, _rc.bottom - 90);

		int r = GetRValue(colorL);
		int g = GetGValue(colorL);
		int b = GetBValue(colorL);
		if ((r == 255 && g == 0 && b == 0) || (r == 0 && g == 255 && b == 0))
		{
			if (_knockBackCount > 0)
			{
				_knockBackAngle = PI - _knockBackAngle;
			}
		}

		r = GetRValue(colorR);
		g = GetGValue(colorR);
		b = GetBValue(colorR);
		if ((r == 255 && g == 0 && b == 0) || (r == 0 && g == 255 && b == 0))
		{
			if (_knockBackCount > 0)
			{
				_knockBackAngle = PI - _knockBackAngle;
			}
		}

		r = GetRValue(colorU);
		g = GetGValue(colorU);
		b = GetBValue(colorU);
		if ((r == 255 && g == 0 && b == 0) || (r == 0 && g == 255 && b == 0))
		{
			if (_knockBackCount > 0)
			{
				_knockBackAngle = -_knockBackAngle;
			}
		}

		r = GetRValue(colorD);
		g = GetGValue(colorD);
		b = GetBValue(colorD);
		if ((r == 255 && g == 0 && b == 0) || (r == 0 && g == 255 && b == 0))
		{
			if (_knockBackCount > 0)
			{
				_knockBackAngle = -_knockBackAngle;
			}
		}
	}
	else if (currentMap == 다섯번째방)
	{
		COLORREF colorL = GetPixel(IMAGEMANAGER->findImage("fifthMapPX")->getMemDC(), _rc.left, _y - 90);
		COLORREF colorR = GetPixel(IMAGEMANAGER->findImage("fifthMapPX")->getMemDC(), _rc.right, _y - 90);
		COLORREF colorU = GetPixel(IMAGEMANAGER->findImage("fifthMapPX")->getMemDC(), _x, _rc.top - 90);
		COLORREF colorD = GetPixel(IMAGEMANAGER->findImage("fifthMapPX")->getMemDC(), _x, _rc.bottom - 90);

		int r = GetRValue(colorL);
		int g = GetGValue(colorL);
		int b = GetBValue(colorL);
		if ((r == 255 && g == 0 && b == 0) || (r == 0 && g == 255 && b == 0))
		{
			if (_knockBackCount > 0)
			{
				_knockBackAngle = PI - _knockBackAngle;
			}
		}

		r = GetRValue(colorR);
		g = GetGValue(colorR);
		b = GetBValue(colorR);
		if ((r == 255 && g == 0 && b == 0) || (r == 0 && g == 255 && b == 0))
		{
			if (_knockBackCount > 0)
			{
				_knockBackAngle = PI - _knockBackAngle;
			}
		}

		r = GetRValue(colorU);
		g = GetGValue(colorU);
		b = GetBValue(colorU);
		if ((r == 255 && g == 0 && b == 0) || (r == 0 && g == 255 && b == 0))
		{
			if (_knockBackCount > 0)
			{
				_knockBackAngle = -_knockBackAngle;
			}
		}

		r = GetRValue(colorD);
		g = GetGValue(colorD);
		b = GetBValue(colorD);
		if ((r == 255 && g == 0 && b == 0) || (r == 0 && g == 255 && b == 0))
		{
			if (_knockBackCount > 0)
			{
				_knockBackAngle = -_knockBackAngle;
			}
		}
	}
	else if (currentMap == 여섯번째방)
	{
		COLORREF colorL = GetPixel(IMAGEMANAGER->findImage("sixthMapPX")->getMemDC(), _rc.left, _y - 90);
		COLORREF colorR = GetPixel(IMAGEMANAGER->findImage("sixthMapPX")->getMemDC(), _rc.right, _y - 90);
		COLORREF colorU = GetPixel(IMAGEMANAGER->findImage("sixthMapPX")->getMemDC(), _x, _rc.top - 90);
		COLORREF colorD = GetPixel(IMAGEMANAGER->findImage("sixthMapPX")->getMemDC(), _x, _rc.bottom - 90);

		int r = GetRValue(colorL);
		int g = GetGValue(colorL);
		int b = GetBValue(colorL);
		if ((r == 255 && g == 0 && b == 0) || (r == 0 && g == 255 && b == 0))
		{
			if (_knockBackCount > 0)
			{
				_knockBackAngle = PI - _knockBackAngle;
			}
		}

		r = GetRValue(colorR);
		g = GetGValue(colorR);
		b = GetBValue(colorR);
		if ((r == 255 && g == 0 && b == 0) || (r == 0 && g == 255 && b == 0))
		{
			if (_knockBackCount > 0)
			{
				_knockBackAngle = PI - _knockBackAngle;
			}
		}

		r = GetRValue(colorU);
		g = GetGValue(colorU);
		b = GetBValue(colorU);
		if ((r == 255 && g == 0 && b == 0) || (r == 0 && g == 255 && b == 0))
		{
			if (_knockBackCount > 0)
			{
				_knockBackAngle = -_knockBackAngle;
			}
		}

		r = GetRValue(colorD);
		g = GetGValue(colorD);
		b = GetBValue(colorD);
		if ((r == 255 && g == 0 && b == 0) || (r == 0 && g == 255 && b == 0))
		{
			if (_knockBackCount > 0)
			{
				_knockBackAngle = -_knockBackAngle;
			}
		}
	}
	else if (currentMap == 일곱번째방)
	{
		COLORREF colorL = GetPixel(IMAGEMANAGER->findImage("seventhMapPX")->getMemDC(), _rc.left, _y - 90);
		COLORREF colorR = GetPixel(IMAGEMANAGER->findImage("seventhMapPX")->getMemDC(), _rc.right, _y - 90);
		COLORREF colorU = GetPixel(IMAGEMANAGER->findImage("seventhMapPX")->getMemDC(), _x, _rc.top - 90);
		COLORREF colorD = GetPixel(IMAGEMANAGER->findImage("seventhMapPX")->getMemDC(), _x, _rc.bottom - 90);

		int r = GetRValue(colorL);
		int g = GetGValue(colorL);
		int b = GetBValue(colorL);
		if ((r == 255 && g == 0 && b == 0) || (r == 0 && g == 255 && b == 0))
		{
			if (_knockBackCount > 0)
			{
				_knockBackAngle = PI - _knockBackAngle;
			}
		}

		r = GetRValue(colorR);
		g = GetGValue(colorR);
		b = GetBValue(colorR);
		if ((r == 255 && g == 0 && b == 0) || (r == 0 && g == 255 && b == 0))
		{
			if (_knockBackCount > 0)
			{
				_knockBackAngle = PI - _knockBackAngle;
			}
		}

		r = GetRValue(colorU);
		g = GetGValue(colorU);
		b = GetBValue(colorU);
		if ((r == 255 && g == 0 && b == 0) || (r == 0 && g == 255 && b == 0))
		{
			if (_knockBackCount > 0)
			{
				_knockBackAngle = -_knockBackAngle;
			}
		}

		r = GetRValue(colorD);
		g = GetGValue(colorD);
		b = GetBValue(colorD);
		if ((r == 255 && g == 0 && b == 0) || (r == 0 && g == 255 && b == 0))
		{
			if (_knockBackCount > 0)
			{
				_knockBackAngle = -_knockBackAngle;
			}
		}
	}
	else if (currentMap == 여덟번째방)
	{
		COLORREF colorL = GetPixel(IMAGEMANAGER->findImage("eighthMapPX")->getMemDC(), _rc.left, _y - 90);
		COLORREF colorR = GetPixel(IMAGEMANAGER->findImage("eighthMapPX")->getMemDC(), _rc.right, _y - 90);
		COLORREF colorU = GetPixel(IMAGEMANAGER->findImage("eighthMapPX")->getMemDC(), _x, _rc.top - 90);
		COLORREF colorD = GetPixel(IMAGEMANAGER->findImage("eighthMapPX")->getMemDC(), _x, _rc.bottom - 90);

		int r = GetRValue(colorL);
		int g = GetGValue(colorL);
		int b = GetBValue(colorL);
		if ((r == 255 && g == 0 && b == 0) || (r == 0 && g == 255 && b == 0))
		{
			if (_knockBackCount > 0)
			{
				_knockBackAngle = PI - _knockBackAngle;
			}
		}

		r = GetRValue(colorR);
		g = GetGValue(colorR);
		b = GetBValue(colorR);
		if ((r == 255 && g == 0 && b == 0) || (r == 0 && g == 255 && b == 0))
		{
			if (_knockBackCount > 0)
			{
				_knockBackAngle = PI - _knockBackAngle;
			}
		}

		r = GetRValue(colorU);
		g = GetGValue(colorU);
		b = GetBValue(colorU);
		if ((r == 255 && g == 0 && b == 0) || (r == 0 && g == 255 && b == 0))
		{
			if (_knockBackCount > 0)
			{
				_knockBackAngle = -_knockBackAngle;
			}
		}

		r = GetRValue(colorD);
		g = GetGValue(colorD);
		b = GetBValue(colorD);
		if ((r == 255 && g == 0 && b == 0) || (r == 0 && g == 255 && b == 0))
		{
			if (_knockBackCount > 0)
			{
				_knockBackAngle = -_knockBackAngle;
			}
		}
	}
}

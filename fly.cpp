#include "stdafx.h"
#include "fly.h"
#include"cPlayer.h"
#include"cSceneManager.h"

HRESULT fly::init(void)
{
	return S_OK;
}

HRESULT fly::init(string imageName, int x, int y, cPlayer * player)
{
	_img = IMAGEMANAGER->findImage(imageName);
	_x = x;
	_y = y;
	_rc = RectMakeCenter(_x, _y, _img->getFrameWidth(), _img->getFrameHeight());
	_player = player;
	_angle = 0;
	_moveSpeed = 0;
	_HP = 2;
	_isMove = false;
	_currentFrameX = 0;
	_currentFrameY = 0;
	_hitTime = 0;
	rendercount = 0;

	return S_OK;
}

void fly::release(void)
{
}

void fly::update(void)
{
	move();
	animation();
}

void fly::render(void)
{
	draw();

}

void fly::move()
{
	if (_isMove)
	{
		_angle = getAngle(_x, _y, _player->GetX(), _player->GetY());
		_moveSpeed = 1.5;
	}

	_x += cosf(_angle)*_moveSpeed;
	_y += -sinf(_angle)*_moveSpeed;

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


	if (getDistance(_x, _y, _player->GetX(), _player->GetY())<200)
	{
		_isMove = true;
	}
	_rc = RectMakeCenter(_x, _y, _img->getFrameWidth(), _img->getFrameHeight());
}

void fly::draw()
{
	_img->frameRender(getMemDC(), _rc.left, _rc.top, _currentFrameX, _currentFrameY);
	if (_hitTime > 0)
	{
		IMAGEMANAGER->findImage("flyR")->frameRender(getMemDC(), _rc.left, _rc.top, _currentFrameX, _currentFrameY);
		_hitTime--;
	}
}

void fly::animation()
{
	if (rendercount % 2 == 0)
	{
		if (_currentFrameX > _img->getMaxFrameX())
		{
			_currentFrameX = 0;
		}
		else
		{
			_currentFrameX++;
		}
	}
	

	rendercount++;
}

void fly::pixelCol()
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



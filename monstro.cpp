#include "stdafx.h"
#include "monstro.h"
#include"cPlayer.h"
#include"bullet.h"
#include"cSceneManager.h"

HRESULT monstro::init(void)
{
	return S_OK;
}

HRESULT monstro::init(int x, int y, cPlayer * player, hoppingBullet* bullet)
{
	_img = IMAGEMANAGER->findImage("monstroAll");
	currentFrameX = 0;
	_player = player;
	_x = x;
	_y = y;
	_rc = RectMakeCenter(_x, _y, IMAGEMANAGER->findImage("monstroAll")->getFrameWidth(), IMAGEMANAGER->findImage("monstroAll")->getFrameHeight());
	_angle = 0;
	_moveSpeed = 0;
	pattern = NORMAL;
	_jumpHeight=0;
	_gravity=0;
	_jumpPower=0;
	_maxHP=_HP = 200;
	_knockBackAngle=0;			//넉백 각도
	_knockBackCount=0;			//넉백 타이머
	_coolTime = 0;
	_patternTime = 0;
	_bullet = bullet;
	_hitTime = 0;
	return S_OK;
}

void monstro::release(void)
{
}

void monstro::update(void)
{
	move();
	animation();

}

void monstro::render(void)
{
	draw();
}

void monstro::move()
{
	if (_coolTime == 40)
	{
		pattern = NORMAL;
	}

	if (_coolTime <= 0)
	{
		if (pattern == NORMAL)//가만히 있는 보통상태일때
		{
			pattern = RND->getFromIntTo(1, 3);//나머지 3가지 패턴들 중에 하나로 설정을 해준다.

			if (pattern == JUMP)
			{
				_patternTime = 20;
			}

			if (pattern == SHOOT)
			{
				_patternTime = 30;
			}

			if (pattern == BIGJUMP)
			{
				_patternTime = 120;
			}
		}


		else if (pattern == JUMP)
		{
			if (_patternTime > 0)
			{
				_patternTime--;
			}
			else
			{
				if (_jumpHeight <= 0)
				{
					_angle = getAngle(_x, _rc.bottom, _player->GetX(), _player->GetY());
				}

				_jumpPower = 10;
				_gravity += 0.5f;
				_moveSpeed = 2;
				_jumpHeight += (_jumpPower - _gravity);


				if (_jumpHeight < 0)
				{
					_jumpHeight = 0;
					_gravity = 0;
					_coolTime = 60;
				}


				_x += cosf(_angle)*_moveSpeed;
				_y += -sinf(_angle)*_moveSpeed;
				_rc = RectMakeCenter(_x, _y - _jumpHeight, IMAGEMANAGER->findImage("monstroAll")->getFrameWidth(), IMAGEMANAGER->findImage("monstroAll")->getFrameHeight());
			}
		}

		else if (pattern == SHOOT)
		{
			if (_patternTime == 15)
			{
				for (int i = 0; i < 20; i++)
				{
					float angle = getAngle(_x, _y, _player->GetX(), _player->GetY());
					_bullet->fire(RND->getFromIntTo((int)(_x - 10), (int)(_x + 10)), RND->getFromIntTo((int)(_y - 10), (int)(_y + 10))
						, RND->getFromFloatTo(angle - 0.5, angle + 0.5), RND->getFromIntTo(7, 10), 1, RND->getFromFloatTo(3.0f, 5.0f));
				}
			}
			if (_patternTime <= 0)
			{
			
				_coolTime = 60;
			}
			_patternTime--;
		}

		else if (pattern == BIGJUMP)
		{

			if (_patternTime > 80&&_patternTime<100)
			{
				_angle = getAngle(_x, _y, _player->GetX(), _player->GetY());
				_jumpPower = 50;
				_jumpHeight += _jumpPower;
			}

			if (_patternTime < 20)
			{
				_jumpPower = 50;
				_jumpHeight -= _jumpPower;
			}


			if (_jumpHeight <= 1&&_patternTime<50)
			{
				for (int i = 0; i < 30; i++)
				{
					float angle = getAngle(_x, _y, _player->GetX(), _player->GetY());
					_bullet->fire(RND->getFromIntTo((int)(_x - 10), (int)(_x + 10)), RND->getFromIntTo((int)(_y - 10), (int)(_y + 10))
						, RND->getFromFloatTo(0, PI*2), RND->getFromIntTo(7, 10), 1, RND->getFromFloatTo(3.0f, 5.0f));
				}
				_jumpHeight = 0;
				_coolTime = 60;
				
			}

			if (_patternTime == 80)
			{
				_angle = getAngle(_x, _y, _player->GetX(), _player->GetY());
				_moveSpeed = (getDistance(_x, _y, _player->GetX(), _player->GetY())) / 60;
			}

			if (_patternTime < 80 && _patternTime >= 20)
			{
				_x += cosf(_angle)*_moveSpeed;
				_y += -sinf(_angle)*_moveSpeed;
			}
			
			_rc = RectMakeCenter(_x, _y - _jumpHeight, IMAGEMANAGER->findImage("monstroAll")->getFrameWidth(), IMAGEMANAGER->findImage("monstroAll")->getFrameHeight());
			_patternTime--;

		}
	}
	
	pixelCol();

	if (_coolTime > 0)
	{
		_coolTime--;
	}

}

void monstro::draw()
{
	HPrender();

	//IMAGEMANAGER->findImage("shadowBOSS")->render(getMemDC(), _x - 75, _y + 15);

	if (KEYMANAGER->isToggleKey(VK_F1))
	{
		RectangleMake(getMemDC(), _rc);
	}
	_img->frameRender(getMemDC(), _x - (_img->getFrameWidth() / 2), _y-_jumpHeight - (_img->getFrameHeight()) / 2, currentFrameX, 0);
	if (_hitTime > 0)
	{
		if (pattern == NORMAL)
		{
			IMAGEMANAGER->findImage("monstroAllR")->frameRender(getMemDC(), _x - (_img->getFrameWidth() / 2), _y - _jumpHeight - (_img->getFrameHeight()) / 2, currentFrameX, 0);
		}
		else if (pattern == SHOOT)
		{
			IMAGEMANAGER->findImage("monstroShootAnimeR")->frameRender(getMemDC(), _x - (_img->getFrameWidth() / 2), _y - _jumpHeight - (_img->getFrameHeight()) / 2, currentFrameX, 0);
		}
		else
		{
			IMAGEMANAGER->findImage("monstroJumpMotionR")->frameRender(getMemDC(), _x - (_img->getFrameWidth() / 2), _y - _jumpHeight - (_img->getFrameHeight()) / 2, currentFrameX, 0);
		}
		_hitTime--;
	}


}

void monstro::animation()
{

	if (_coolTime > 40)
	{
		
		
		if (pattern == BIGJUMP)
		{
			_img = IMAGEMANAGER->findImage("monstroJumpMotion");
			if (_coolTime > 50)
			{
				currentFrameX = 4;
			}
			else if (_coolTime > 40)
			{
				currentFrameX = 5;
			}
		}

		if (pattern == JUMP)
		{
			_img = IMAGEMANAGER->findImage("monstroJumpMotion");
			if (_coolTime > 50)
			{
				currentFrameX = 4;
			}
			else if (_coolTime > 40)
			{
				currentFrameX = 5;
			}
		}

		if (pattern == SHOOT)
		{
			_img = IMAGEMANAGER->findImage("monstroShootAnime");
			currentFrameX = 2;
		}

	}

	else if (_coolTime == 40)
	{
		pattern = NORMAL;
	}


	else
	{
		if (pattern == NORMAL)//가만히 있는 보통상태일때
		{
			_img = IMAGEMANAGER->findImage("monstroAll");
			currentFrameX = 0;
		}


		else if (pattern == JUMP)
		{
			if (_patternTime>10)
			{
				currentFrameX = 1;
			}
			else if (_patternTime > 0)
			{
				_img = IMAGEMANAGER->findImage("monstroJumpMotion");
				currentFrameX = 0;
			}
			else
			{
				_img = IMAGEMANAGER->findImage("monstroJumpMotion");
				if (_jumpPower - _gravity>5)
				{
					currentFrameX = 1;
				}
				else if (_jumpPower - _gravity>-5)
				{
					currentFrameX = 2;
				}
				else
				{
					currentFrameX = 3;
				}
			}

		}

		else if (pattern == SHOOT)
		{
			if (_patternTime > 25)
			{
				currentFrameX = 1;
			}

			if (_patternTime <= 25)
			{
				_img = IMAGEMANAGER->findImage("monstroShootAnime");
				if (_patternTime > 20)
				{
					currentFrameX = 0;
				}
				else if (_patternTime>15)
				{
					currentFrameX = 1;
				}
				else if (_patternTime > 0)
				{
					currentFrameX = 2;
				}
			}
		}

		else if (pattern == BIGJUMP)
		{
			if (_patternTime > 110)
			{
				currentFrameX = 1;
			}

			if (_patternTime <= 110)
			{
				_img = IMAGEMANAGER->findImage("monstroJumpMotion");
				if (_patternTime > 100)
				{
					currentFrameX = 0;
				}

				if (_patternTime > 80)
				{
					currentFrameX = 1;
				}
				else if (_patternTime < 80 && _patternTime >= 20)
				{
					currentFrameX = 2;
				}
				else if (_patternTime > 0)
				{
					currentFrameX = 3;
				}
			}


		}
	}
	
}

void monstro::HPrender()
{
	float width = ((float)IMAGEMANAGER->findImage("HP")->getWidth())*((float)_HP) / ((float)_maxHP);
	IMAGEMANAGER->findImage("emptyHP")->render(getMemDC(), 200, 100);
	IMAGEMANAGER->findImage("HP")->render(getMemDC(), 229, 110,0,0, width, IMAGEMANAGER->findImage("HP")->getHeight());

	


}

void monstro::pixelCol()
{
	COLORREF colorL = GetPixel(IMAGEMANAGER->findImage("thirdMapPX")->getMemDC(), _x- (IMAGEMANAGER->findImage("monstroAll")->getFrameWidth()/2), _y - 90);
	COLORREF colorR = GetPixel(IMAGEMANAGER->findImage("thirdMapPX")->getMemDC(), _x + (IMAGEMANAGER->findImage("monstroAll")->getFrameWidth() / 2), _y - 90);
	COLORREF colorU = GetPixel(IMAGEMANAGER->findImage("thirdMapPX")->getMemDC(), _x, _y- (IMAGEMANAGER->findImage("monstroAll")->getFrameHeight() / 2) - 90);
	COLORREF colorD = GetPixel(IMAGEMANAGER->findImage("thirdMapPX")->getMemDC(), _x, _y + (IMAGEMANAGER->findImage("monstroAll")->getFrameHeight() / 2) - 90);

	int r = GetRValue(colorL);
	int g = GetGValue(colorL);
	int b = GetBValue(colorL);
	if ((r == 255 && g == 0 && b == 0) || (r == 0 && g == 255 && b == 0))
	{
		if (_coolTime <= 0)
		{
			_x -= cosf(_angle)*_moveSpeed;
			_y -= -sinf(_angle)*_moveSpeed;
		}
	
	}

	r = GetRValue(colorR);
	g = GetGValue(colorR);
	b = GetBValue(colorR);
	if ((r == 255 && g == 0 && b == 0) || (r == 0 && g == 255 && b == 0))
	{
		if (_coolTime <= 0)
		{
			_x -= cosf(_angle)*_moveSpeed;
			_y -= -sinf(_angle)*_moveSpeed;
		}
	}

	r = GetRValue(colorU);
	g = GetGValue(colorU);
	b = GetBValue(colorU);
	if ((r == 255 && g == 0 && b == 0) || (r == 0 && g == 255 && b == 0))
	{
		if (_coolTime <= 0)
		{
			_x -= cosf(_angle)*_moveSpeed;
			_y -= -sinf(_angle)*_moveSpeed;
		}
	}

	r = GetRValue(colorD);
	g = GetGValue(colorD);
	b = GetBValue(colorD);
	if ((r == 255 && g == 0 && b == 0) || (r == 0 && g == 255 && b == 0))
	{
		if (_coolTime <= 0)
		{
			_x -= cosf(_angle)*_moveSpeed;
			_y -= -sinf(_angle)*_moveSpeed;
		}
	}
}

#include "stdafx.h"
#include "shootEnemy.h"
#include"cPlayer.h"

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
	_knockBackAngle = 0;			//≥ÀπÈ ∞¢µµ
	_knockBackCount = 0;			//≥ÀπÈ ≈∏¿Ã∏”
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

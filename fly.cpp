#include "stdafx.h"
#include "fly.h"
#include"cPlayer.h"

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



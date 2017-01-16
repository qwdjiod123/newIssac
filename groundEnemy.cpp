#include "stdafx.h"
#include "groundEnemy.h"
#include"cPlayer.h"

groundEnemy::groundEnemy()
{
}


groundEnemy::~groundEnemy()
{
}

HRESULT groundEnemy::init(void)
{
	return S_OK;
}

HRESULT groundEnemy::init(int x,int y, cPlayer* player)
{
	_img= IMAGEMANAGER->findImage("wormH");
	_currentFrameX = 0;
	_currentFrameY = 0;
	time = 0;
	_x = x;
	_y = y;
	_rc = RectMakeCenter(_x, _y, _img->getFrameWidth(), _img->getFrameHeight());
	_moveSpeed = 2;
	_attackCount = 0;
	_player = player;
	isAttack = false;
	_moveCount = RND->getFromIntTo(10, 30);
	_move = LEFT;
	_HP = 5;
	_hitTime = 0;
	return E_NOTIMPL;
}



void groundEnemy::release(void)
{
}

void groundEnemy::update(void)
{
	animation();
	move();
	
}

void groundEnemy::render(void)
{
	draw();
}

void groundEnemy::move()
{
	switch (_move)
	{
	case UP:
		_y -= _moveSpeed;
		break;
	case DOWN:
		_y += _moveSpeed;
		break;
	case LEFT:
		_x -= _moveSpeed;
		break;
	case RIGHT:
		_x += _moveSpeed;
		break;
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


	_rc = RectMakeCenter(_x, _y, _img->getFrameWidth(), _img->getFrameHeight());

	if (_attackCount <= 0)
	{
		if (_y < _player->GetRC().bottom&&_y > _player->GetRC().top)//y범위에 걸렸을 경우
		{
			if (_x < _player->GetRC().left)
			{
				isAttack = true;
				_attackCount = 80;
				_move = RIGHT;
				_moveSpeed = 3.0f;
			}

			if (_x > _player->GetRC().right)
			{
				isAttack = true;
				_attackCount = 80;
				_move = LEFT;
				_moveSpeed = 3.0f;
			}
		}

		if (_x > _player->GetRC().left&&_x < _player->GetRC().right)//y범위에 걸렸을 경우
		{
			if (_y < _player->GetRC().top)
			{
				isAttack = true;
				_attackCount = 80;
				_move = DOWN;
				_moveSpeed = 3.0f;
			}

			if (_y >_player->GetRC().bottom)
			{
				isAttack = true;
				_attackCount = 80;
				_move = UP;
				_moveSpeed = 3.0f;
			}
		}
	}
	

	if (_attackCount > 0)
	{
		_attackCount--;
	}
	else
	{
		_moveSpeed = 2.0f;
		if (_moveCount > 0)
		{
			_moveCount--;
		}
		else
		{
			_moveCount = RND->getFromIntTo(100, 200);
			_move = (MOVESTATE)RND->getInt(4);
		}
	}


	

}

void groundEnemy::draw()
{
	if (KEYMANAGER->isToggleKey(VK_F1))
	{
		Rectangle(getMemDC(), _rc.left, _rc.top, _rc.right, _rc.bottom);
	}
	_img->frameRender(getMemDC(), _rc.left, _rc.top, _currentFrameX, _currentFrameY);
	if (_hitTime > 0)
	{
		if (_moveSpeed < 2.5)
		{
			switch (_move)
			{
			case UP:
				IMAGEMANAGER->findImage("wormUR")->frameRender(getMemDC(), _rc.left, _rc.top, _currentFrameX, _currentFrameY);
				break;
			case DOWN:
				IMAGEMANAGER->findImage("wormDR")->frameRender(getMemDC(), _rc.left, _rc.top, _currentFrameX, _currentFrameY);
				
				break;
			case LEFT:
				IMAGEMANAGER->findImage("wormHR")->frameRender(getMemDC(), _rc.left, _rc.top, _currentFrameX, _currentFrameY);
				
				break;
			case RIGHT:
				IMAGEMANAGER->findImage("wormHR")->frameRender(getMemDC(), _rc.left, _rc.top, _currentFrameX, _currentFrameY);

				break;
			}
		}
		else
		{
			switch (_move)
			{
			case UP:
				IMAGEMANAGER->findImage("wormUAR")->frameRender(getMemDC(), _rc.left, _rc.top, _currentFrameX, _currentFrameY);
				
				break;
			case DOWN:
				IMAGEMANAGER->findImage("wormDAR")->frameRender(getMemDC(), _rc.left, _rc.top, _currentFrameX, _currentFrameY);
				

				break;
			case LEFT:
				IMAGEMANAGER->findImage("wormHAR")->frameRender(getMemDC(), _rc.left, _rc.top, _currentFrameX, _currentFrameY);
				break;
			case RIGHT:
				IMAGEMANAGER->findImage("wormHAR")->frameRender(getMemDC(), _rc.left, _rc.top, _currentFrameX, _currentFrameY);

				break;
			}
		}
		_hitTime--;
	}
	

}

void groundEnemy::animation()
{
	if (_moveSpeed < 2.5)
	{
		switch (_move)
		{
		case UP:
			_img = IMAGEMANAGER->findImage("wormU");
			_currentFrameY = 0;
			_currentFrameX = 0;
			
			break;
		case DOWN:
			_img = IMAGEMANAGER->findImage("wormD");
			_currentFrameY = 0;
			if (time % 2 == 0)
			{
				if (_currentFrameX >= _img->getMaxFrameX())
				{
					_currentFrameX = 0;
				}
				else
				{
					_currentFrameX++;
				}
			}
			break;
		case LEFT:
			_img = IMAGEMANAGER->findImage("wormH");
			_currentFrameY = 0;
			if (time % 2 == 0)
			{
				if (_currentFrameX >= _img->getMaxFrameX())
				{
					_currentFrameX = 0;
				}
				else
				{
					_currentFrameX++;
				}
			}
			
			break;
		case RIGHT:
			_img = IMAGEMANAGER->findImage("wormH");
			_currentFrameY = 1;
			if (time % 2 == 0)
			{
				if (_currentFrameX <= 0)
				{
					_currentFrameX = _img->getMaxFrameX() - 1;
				}
				else
				{
					_currentFrameX--;
				}
			}
			
			break;
		}
	}
	else
	{
		switch (_move)
		{
		case UP:
			_img = IMAGEMANAGER->findImage("wormU");
			_currentFrameY = 0;
			_currentFrameX = 0;

			break;
		case DOWN:
			_img = IMAGEMANAGER->findImage("wormDA");
			_currentFrameX = 0;
			_currentFrameY = 0;
		
			break;
		case LEFT:
			_img = IMAGEMANAGER->findImage("wormHA");
			_currentFrameX = 0;
			_currentFrameY = 0;
			

			break;
		case RIGHT:
			_img = IMAGEMANAGER->findImage("wormHA");
			_currentFrameX = 0;
			_currentFrameY = 1;
			

			break;
		}
	}
	time++;
}


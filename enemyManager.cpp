#include "stdafx.h"
#include "enemyManager.h"
#include"cPlayer.h"
#include"cSceneManager.h"

HRESULT enemyManager::init(void)
{
	//미니언 생성
	
	_count = 0;
	
	//총알클래스 생성 및 초기화
	_bullet = new frameBullet;
	_bullet->init("enemyBullet", 15);
	_bullet->setScene(_SceneManager);

	_hBullet = new hoppingBullet;
	_hBullet->init("enemyBullet", 50);
	_hBullet->setScene(_SceneManager);

	for (int i = 0; i < 10; i++)
	{
		monsterSet[i] = false;
	}

	monsterSet[0] = true;
	monsterSet[2] = true;
	monsterSet[7] = true;


	setMinion();

	return S_OK;
}

void enemyManager::release(void)
{
	//총알클래스 해제
	_bullet->release();
	SAFE_DELETE(_bullet);
	_hBullet->release();
	SAFE_DELETE(_hBullet);
}

void enemyManager::update(void)
{
	//벡터에 담긴 미니언들 업데이트
	_viMinion = _vMinion.begin();
	for (_viMinion; _viMinion != _vMinion.end(); ++_viMinion)
	{
		(*_viMinion)->update();
		
	}

	_viMinion = _vMinion.begin();
	for (_viMinion; _viMinion != _vMinion.end(); ++_viMinion)
	{
		if ((*_viMinion)->getHP() <= 0)
		{
			_viMinion = _vMinion.erase(_viMinion);
			break;
		}
	}

	spwnMonster();

	//총알클래스 업데이트
	_bullet->update();
	_hBullet->update();
	//미니언 총알발사
	this->minionBulletFire();

	//충돌처리
	this->collision();

}

void enemyManager::render(void)
{
	//벡터에 담긴 미니언들 렌더
	_viMinion = _vMinion.begin();
	for (_viMinion; _viMinion != _vMinion.end(); ++_viMinion)
	{
		(*_viMinion)->render();
	}

	_bullet->render();
	_hBullet->render();
}

void enemyManager::setMinion(void)
{
	/*groundEnemy* temp = new groundEnemy;
	temp->init("worm_V","worm_H",100,100,3.0f,_player);
	_vMinion.push_back(temp);*/

	
	//addEnemy("파리", 600, 300);

	//addEnemy("보스", 100, 400);

	//addEnemy("벌레", 100, 400);

	//addEnemy("슈팅", 100, 400);

}

void enemyManager::minionBulletFire(void)
{
	_viMinion = _vMinion.begin();
	for (_viMinion; _viMinion != _vMinion.end(); ++_viMinion)
	{
		if ((*_viMinion)->bulletCountFire())
		{
			float angle = getAngle((*_viMinion)->getX(), (*_viMinion)->getY(), _player->GetX(), _player->GetY());

			_bullet->fire((*_viMinion)->getX(), (*_viMinion)->getY(),angle,300,1,3);
		}
	}
}

void enemyManager::removeMinion(int index)
{
	_vMinion.erase(_vMinion.begin() + index);
}

//적총알과 플레이어
void enemyManager::collision()
{
	_viMinion = _vMinion.begin();
	for (_viMinion; _viMinion != _vMinion.end(); ++_viMinion)
	{
		RECT temp;
		if (IntersectRect(&temp, &(*_viMinion)->getRect(), &_player->GetRC()))//몸통박치기 당한경우 
		{
			if (_player->getHitCount() <= 0)
			{
				if ((*_viMinion)->getMobType() == BOSS)
				{
					if ((*_viMinion)->isHit())
					{
						_player->SetAnimState(DAMAGE);
						_player->setHitCount(50);
						float angle = getAngle((*_viMinion)->getX(), (*_viMinion)->getY(), _player->GetX(), _player->GetY());
						_player->SetAngle(angle);
						_player->SetHp(_player->GetHp() - 1);
					}
				}
				else
				{
					_player->SetAnimState(DAMAGE);
					_player->setHitCount(50);
					float angle = getAngle((*_viMinion)->getX(), (*_viMinion)->getY(), _player->GetX(), _player->GetY());
					_player->SetAngle(angle);
					_player->SetHp(_player->GetHp() - 1);
				}
			}
			
		
		}

		RECT colTemp;
		for (int i = 0; i < _player->getBullet()->getVBulletPt()->size(); i++)
		{
			if (IntersectRect(&colTemp, &(*_viMinion)->getRect(), &_player->getBullet()->getVBulletPt()->at(i).rc))
			{
				(*_viMinion)->setknockBackCount(5);
				(*_viMinion)->setknockBackAngle(getAngle(_player->getBullet()->getVBulletPt()->at(i).x, _player->getBullet()->getVBulletPt()->at(i).y, (*_viMinion)->getX(), (*_viMinion)->getY()));
				(*_viMinion)->setHP(((*_viMinion)->getHP()) - _player->getBullet()->getVBulletPt()->at(i).damage);
				EFFECTMANAGER->addEffect("큰총알효과", _player->getBullet()->getVBulletPt()->at(i).x, _player->getBullet()->getVBulletPt()->at(i).y);
				_player->getBullet()->getVBulletPt()->erase(_player->getBullet()->getVBulletPt()->begin() + i);
				(*_viMinion)->setHitTime(2);
				break;
			}
		}

		for (int i = 0; i < _player->getBigBullet()->getVBulletPt()->size(); i++)
		{
			if (IntersectRect(&colTemp, &(*_viMinion)->getRect(), &_player->getBigBullet()->getVBulletPt()->at(i).rc))
			{
				(*_viMinion)->setknockBackCount(5);
				(*_viMinion)->setknockBackAngle(getAngle(_player->getBigBullet()->getVBulletPt()->at(i).x, _player->getBigBullet()->getVBulletPt()->at(i).y, (*_viMinion)->getX(), (*_viMinion)->getY()));
				(*_viMinion)->setHP(((*_viMinion)->getHP()) - _player->getBigBullet()->getVBulletPt()->at(i).damage);
				EFFECTMANAGER->addEffect("큰총알효과", _player->getBigBullet()->getVBulletPt()->at(i).x, _player->getBigBullet()->getVBulletPt()->at(i).y);
				_player->getBigBullet()->getVBulletPt()->erase(_player->getBigBullet()->getVBulletPt()->begin() + i);
				(*_viMinion)->setHitTime(2);
				break;
			}
		}

	}
}

void enemyManager::addEnemy(string KEY, float centerX, float centerY)
{
	if (KEY == "벌레")
	{
		groundEnemy* temp = new groundEnemy;
		temp->setSceneManager(_SceneManager);
		temp->init(centerX, centerY, _player);
		_vMinion.push_back(temp);
	}
	
	if (KEY == "파리")
	{
		fly* temp = new fly;
		temp->setSceneManager(_SceneManager);
		temp->init("fly", centerX, centerY, _player);
		_vMinion.push_back(temp);
	}

	if (KEY == "슈팅")
	{
		shootEnemy* temp = new shootEnemy;
		temp->setSceneManager(_SceneManager);
		temp->init(centerX, centerY, _player);
		_vMinion.push_back(temp);
	}
	if (KEY == "보스")
	{
		monstro* temp = new monstro;
		temp->setSceneManager(_SceneManager);
		temp->init(centerX, centerY, _player,_hBullet);
		_vMinion.push_back(temp);
	}
}

void enemyManager::spwnMonster()
{
	int currentMap = _SceneManager->GetCurrentMap();
	if (_vMinion.empty())
	{
		if (_SceneManager->GetdoorChangeFrame()==300)
		{
			if (!monsterSet[currentMap])
			{
				if (currentMap == 첫번째방)
				{
					addEnemy("파리", 100, 200);
					addEnemy("파리", 100, 500);
					addEnemy("파리", 700, 200);
					addEnemy("파리", 700, 500);
					monsterSet[currentMap] = true;
				}

				if (currentMap == 세번째방)
				{
					addEnemy("보스", 300, 250);
					
					monsterSet[currentMap] = true;
				}

				if (currentMap == 네번째방)
				{
					addEnemy("벌레", 100, 200);
					addEnemy("벌레", 100, 500);
					addEnemy("벌레", 700, 200);
					addEnemy("벌레", 700, 500);

					monsterSet[currentMap] = true;
				}

				if (currentMap == 여섯번째방)
				{
					addEnemy("슈팅", 100, 200);
					addEnemy("슈팅", 100, 500);
					addEnemy("슈팅", 700, 200);
					addEnemy("슈팅", 700, 500);

					monsterSet[currentMap] = true;
				}

				if (currentMap == 여덟번째방)
				{
					addEnemy("파리", 100, 200);
					addEnemy("벌레", 100, 500);
					addEnemy("슈팅", 700, 200);
					addEnemy("슈팅", 700, 500);

					monsterSet[currentMap] = true;
				}
			}
		}
	}

	if (currentMap == 여덟번째방)
	{
		if (KEYMANAGER->isOnceKeyDown(VK_F5))
		{
			addEnemy("파리", RND->getFromIntTo(100,200), RND->getFromIntTo(200, 300));
		}
	}

}

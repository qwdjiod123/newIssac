#include "stdafx.h"
#include "cSceneGame.h"


HRESULT cSceneGame::init(void)
{
	_player =new cPlayer();	
	_sm = new cSceneManager();
	_im = new cItemManager();
	_enemy = new enemyManager;

	_player->SetIM(_im);
	_player->SetEM(_enemy);
	_sm->SetPlayer(_player);	
	_sm->SetIM(_im);
	_im->SetIM(_sm);
	_im->SetPlayer(_player);
	_im->SetEnemy(_enemy);

	_player->init();	
	_sm->init();
	_im->init();
	
	_enemy->setPlayer(_player);
	_enemy->setSceneManager(_sm);
	_enemy->init();
	

	return S_OK;
}

void cSceneGame::release(void)
{
	_player->release();
	_im->release();
	_sm->release();
	_enemy->release();
}

void cSceneGame::update(void)
{		
	_player->update();
	_im->update();
	_sm->update();
	_enemy->update();
	EFFECTMANAGER->update();
}

void cSceneGame::render(void)
{		
	_sm->render();	
	_im->render();
	_enemy->render();
	_player->render();
	EFFECTMANAGER->render(getMemDC());
}


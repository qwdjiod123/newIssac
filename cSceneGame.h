#pragma once
#include "gameNode.h"
#include "cPlayer.h"
#include"cItemManager.h"
#include "cSceneManager.h"
#include"enemyManager.h"

//�̰� �����ֽŹ�����

class cSceneGame :public gameNode
{

private:

	cPlayer* _player;
	cItemManager* _im;
	cSceneManager* _sm;
	enemyManager* _enemy;

public:		
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	cSceneGame() {}
	~cSceneGame() {}
};


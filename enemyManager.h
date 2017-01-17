#pragma once
#include "gameNode.h"
#include "minion.h"
#include "bullet.h"
#include"groundEnemy.h"
#include"fly.h"
#include"shootEnemy.h"
#include"monstro.h"

//상호참조용 플레이어 클래스 전방선언

class cPlayer;
class cSceneManager;
class enemyManager : public gameNode
{
private:
	vector<enemy*> _vMinion;
	vector<enemy*>::iterator _viMinion;

	cPlayer* _player;
	frameBullet* _bullet;
	hoppingBullet* _hBullet;
	cSceneManager* _SceneManager;
	int _count;
	bool monsterSet[10];
		//동적할당 하면 안된다!!!

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	//미니언 세팅 => 초기화에 넣어줄것
	void setMinion(void);

	//미니언 총알발사
	void minionBulletFire(void);

	//미니언 삭제
	void removeMinion(int index);

	//충돌함수
	void collision();

	//미니언 벡터 가져오기
	vector<enemy*> getVMinion() { return _vMinion; }
	vector<enemy*>* getVMinionPt() { return &_vMinion; }

	frameBullet* getFrameBullet() { return _bullet; }
	hoppingBullet* getHFrameBullet() { return _hBullet; }

	void setPlayer(cPlayer* player) { _player = player; }

	void setSceneManager(cSceneManager* SceneManager) { _SceneManager = SceneManager; }

	void addEnemy(string KEY,float centerX,float centerY);

	void spwnMonster();

	//상호참조시 플레이어포인터를 넘길 셋터함수
	

	enemyManager() {}
	~enemyManager() {}
};


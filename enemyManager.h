#pragma once
#include "gameNode.h"
#include "minion.h"
#include "bullet.h"
#include"groundEnemy.h"
#include"fly.h"
#include"shootEnemy.h"
#include"monstro.h"
//��ȣ������ �÷��̾� Ŭ���� ���漱��

class cPlayer;
class enemyManager : public gameNode
{
private:
	vector<enemy*> _vMinion;
	vector<enemy*>::iterator _viMinion;

	cPlayer* _player;
	frameBullet* _bullet;
	hoppingBullet* _hBullet;
	int _count;

		//�����Ҵ� �ϸ� �ȵȴ�!!!

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	//�̴Ͼ� ���� => �ʱ�ȭ�� �־��ٰ�
	void setMinion(void);

	//�̴Ͼ� �Ѿ˹߻�
	void minionBulletFire(void);

	//�̴Ͼ� ����
	void removeMinion(int index);

	//�浹�Լ�
	void collision();

	//�̴Ͼ� ���� ��������
	vector<enemy*> getVMinion() { return _vMinion; }
	vector<enemy*>* getVMinionPt() { return &_vMinion; }

	frameBullet* getFrameBullet() { return _bullet; }
	hoppingBullet* getHFrameBullet() { return _hBullet; }

	void setPlayer(cPlayer* player) { _player = player; }

	void addEnemy(string KEY,float centerX,float centerY);


	//��ȣ������ �÷��̾������͸� �ѱ� �����Լ�
	

	enemyManager() {}
	~enemyManager() {}
};


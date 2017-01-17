#pragma once
#include "enemy.h"
#define KONCKBACKPOWER 2
class cPlayer;

class shootEnemy :
	public enemy
{
	RECT _rc;
	image* img;
	image* shootAnime;
	float _x;						//�߽� x
	float _y;						//�߽� Y
	float _moveSpeed;				//������ �ӵ�
	int _HP;						//���� ü��
	cPlayer* _player;				//�÷��̾��� �ּ� ���� ����
	bool isAttack;					//���� ����������? Ȯ���ϴ� �Ҹ���
	int _moveCount;					//�������� ��ȭ�� �ִº���
	float _knockBackAngle;			//�˹� ����
	int _knockBackCount;			//�˹� Ÿ�̸�
	int _shootCount;
	int vibration;
	bool vLeft;
	int shootFrameX;
	int time;
	bool isStartFrame;
	int _hitTime;
public:

	virtual HRESULT init(void);
	HRESULT init(int x, int y, cPlayer* player);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	virtual void move();			//������Ʈ�� �ֱ�
	virtual void draw();			//���� �ȿ� �ֱ�
	virtual void animation();		//������Ʈ�� �ֱ�

	virtual void setSpeed(float speed) { _moveSpeed = speed; }
	virtual float getSpeed() { return _moveSpeed; }

	virtual void setHP(float HP) { _HP = HP; }
	virtual float getHP() { return _HP; }

	virtual void setknockBackCount(int count) { _knockBackCount = count; }
	virtual void setknockBackAngle(float angle) { _knockBackAngle = angle; }


	virtual float getX() { return _x; }
	virtual float getY() { return _y; }

	virtual RECT getRect() { return _rc; }

	virtual bool bulletCountFire(void) { return ((shootFrameX==6)&& isStartFrame); }

	virtual int getMobType() { return SHOOTER; }

	virtual void setShootCount(int count) { _shootCount = count; }

	virtual void setHitTime(int count) { _hitTime = count; }

	void pixelCol();

	void damage(int dmg) { _HP -= dmg; }
	shootEnemy() {};
	~shootEnemy() {};
};


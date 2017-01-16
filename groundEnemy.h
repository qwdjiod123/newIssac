#pragma once
#include "enemy.h"
#define KONCKBACKPOWER 1.0f
enum MOVESTATE
{
	UP,
	DOWN,
	LEFT,
	RIGHT
};

class cPlayer;


class groundEnemy :
	public enemy
{
private:
	RECT _rc;
	
	image* _img;
	int _currentFrameX;
	int _currentFrameY;
	int time;
	float _x;						//�߽� x
	float _y;						//�߽� Y
	float _moveSpeed;				//������ �ӵ�
	int _HP;						//���� ü��
	MOVESTATE _move;				//�����̴� Ÿ���� ���� �̳ѹ�
	int _attackCount;				//�������� ī��Ʈ �ð�
	cPlayer* _player;				//�÷��̾��� �ּ� ���� ����
	bool isAttack;					//���� ����������? Ȯ���ϴ� �Ҹ���
	int _moveCount;					//�������� ��ȭ�� �ִº���
	float _knockBackAngle;			//�˹� ����
	int _knockBackCount;			//�˹� Ÿ�̸�
	int _hitTime;
public:

	virtual HRESULT init(void);
	HRESULT init( int x, int y,cPlayer* player);
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

	virtual int getMobType() { return WORM; }

	virtual void setHitTime(int count) { _hitTime = count; }

	void damage(int dmg) { _HP -= dmg; }


	groundEnemy();
	~groundEnemy();
};


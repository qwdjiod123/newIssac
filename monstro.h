#pragma once
#include "enemy.h"

class cPlayer;
class hoppingBullet;
enum BOSS_PATTERN
{
	NORMAL,
	JUMP,
	SHOOT,
	BIGJUMP
};

class monstro :
	public enemy
{
	RECT _rc;
	image* _img;
	image* shootAnime;
	float _x;						//�߽� x
	float _y;						//�߽� Y
	float _jumpHeight;
	float _gravity;
	float _jumpPower;
	float _moveSpeed;				//������ �ӵ�
	int _HP;						//���� ü��
	int _maxHP;
	cPlayer* _player;				//�÷��̾��� �ּ� ���� ����
	bool isAttack;					//���� ����������? Ȯ���ϴ� �Ҹ���
	int _moveCount;					//�������� ��ȭ�� �ִº���
	float _knockBackAngle;			//�˹� ����
	int _knockBackCount;			//�˹� Ÿ�̸�
	int _shootCount;
	
	hoppingBullet* _bullet;
	int currentFrameX;

	int _coolTime;
	int _patternTime;

	int _hitTime;

	bool isStartFrame;
	int pattern;
	float _angle;
public:

	virtual HRESULT init(void);
	HRESULT init(int x, int y, cPlayer* player, hoppingBullet* bullet);
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

	virtual int getMobType() { return BOSS; }

	virtual void setShootCount(int count) { _shootCount = count; }

	void damage(int dmg) { _HP -= dmg; }
	
	void HPrender();

	virtual bool isHit() { return _jumpHeight<20; }

	virtual void setHitTime(int count) { _hitTime = count; }

	monstro() {};
	~monstro() {};
};


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
	float _x;						//중심 x
	float _y;						//중심 Y
	float _moveSpeed;				//움직임 속도
	int _HP;						//몹의 체력
	cPlayer* _player;				//플레이어의 주소 저장 변수
	bool isAttack;					//지금 공격중인지? 확인하는 불리언
	int _moveCount;					//움직임의 변화를 주는변수
	float _knockBackAngle;			//넉백 각도
	int _knockBackCount;			//넉백 타이머
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

	virtual void move();			//업데이트에 넣기
	virtual void draw();			//렌더 안에 넣기
	virtual void animation();		//업데이트에 넣기

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


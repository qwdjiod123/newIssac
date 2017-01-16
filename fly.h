#pragma once
#include "enemy.h"

#define KONCKBACKPOWER 3

class cPlayer;

class fly :
	public enemy
{
	RECT _rc;
	image* _img;
	float _x;						//중심 x
	float _y;						//중심 Y
	float _moveSpeed;				//움직임 속도
	int _HP;						//몹의 체력
	cPlayer* _player;				//플레이어의 주소 저장 변수
	float _angle;
	
	int _currentFrameX;
	int _currentFrameY;

	int _hitTime;

	int rendercount;

	bool _isMove;
	float _knockBackAngle;			//넉백 각도
	int _knockBackCount;			//넉백 타이머
public:

	virtual HRESULT init(void);
	HRESULT init(string imageName, int x, int y, cPlayer* player);
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

	virtual int getMobType() { return FLY; }

	virtual void setHitTime(int count) { _hitTime = count; }

	void damage(int dmg) { _HP -= dmg; }



	fly() {};
	~fly() {};
};


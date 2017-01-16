#pragma once
#include "gameNode.h"

//부모클래스 => 이놈을 상속받아서 보스, 일반몬스터등을 만든다

enum mobType
{
	FLY,
	SHOOTER,
	WORM,
	BOSS
};

class enemy : public gameNode
{
private:
	RECT _rc;			//충돌용 렉트
	image* _image;		//에너미 이미지 

	//프레임 이미지를 돌리기 위한 변수들
	int _count;
	int _currentFrameX;
	int _currentFrameY;

	//랜덤으로 총알 발사 쿨타임주기
	int _fireCount;
	int _rndFireCount;

public:
	virtual HRESULT init(void);
	virtual HRESULT init(char* imageName, POINT position);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	virtual void move();			//업데이트에 넣기
	virtual void draw();			//렌더 안에 넣기
	virtual void animation();		//업데이트에 넣기

	virtual void setSpeed(float speed) {}
	virtual float getSpeed() { return 0.0f; }

	virtual void setHP(float HP) {}
	virtual float getHP() { return 0; }

	virtual void setknockBackCount(int count){}
	virtual void setknockBackAngle(float angle) {}

	virtual float getX() { return 0; }
	virtual float getY() { return 0; }
	
	virtual int getMobType() { return -1; }

	virtual bool bulletCountFire(void) { return false; }

	virtual void setShootCount(int count) {}

	virtual void setHitTime(int count) {}

	virtual RECT getRect() { return _rc; }
	
	virtual bool isHit() { return true; }

	enemy() {}
	virtual ~enemy() {}
};


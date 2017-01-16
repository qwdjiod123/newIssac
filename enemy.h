#pragma once
#include "gameNode.h"

//�θ�Ŭ���� => �̳��� ��ӹ޾Ƽ� ����, �Ϲݸ��͵��� �����

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
	RECT _rc;			//�浹�� ��Ʈ
	image* _image;		//���ʹ� �̹��� 

	//������ �̹����� ������ ���� ������
	int _count;
	int _currentFrameX;
	int _currentFrameY;

	//�������� �Ѿ� �߻� ��Ÿ���ֱ�
	int _fireCount;
	int _rndFireCount;

public:
	virtual HRESULT init(void);
	virtual HRESULT init(char* imageName, POINT position);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	virtual void move();			//������Ʈ�� �ֱ�
	virtual void draw();			//���� �ȿ� �ֱ�
	virtual void animation();		//������Ʈ�� �ֱ�

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


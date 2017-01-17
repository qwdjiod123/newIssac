#pragma once
#include "gameNode.h"

//�Ѿ� ����ü
struct tagBullet
{
	image* bulletImage;
	RECT rc;
	float x, y;
	float fireX, fireY;
	float speed;
	float angle;
	float gravity;
	float radius;
	bool fire;
	int count;
	float _range;		//�Ѿ� ��Ÿ�
	int damage;
};

//=============================================================
//	## bullet ## (�����Ѿ� - ������� ������~~~)
//=============================================================
class bullet : public gameNode
{
private:
	//�Ѿ� ����ü�� ���� ����, �ݺ���
	vector<tagBullet> _vBullet;
	vector<tagBullet>::iterator _viBullet;

private:
	char* _imageName;	//�Ѿ� �̹��� Ű��	
	int _bulletMax;		//�Ѿ� �ִ밹��

public:
	//�Ѿ��̹���Ű��, �Ѿ˰���, �Ѿ˻�Ÿ��� �ʱ�ȭ
	HRESULT init(char* imageName, int bulletMax);
	void release(void);
	void update(void);
	void render(void);

	//�Ѿ˹߻�
	void fire(float x, float y, float angle, float range, int damage, int bulletSpeed);
	//�Ѿ˹���
	void move(void);

	//�Ѿ˻���
	void removeBullet(int index);

	//�Ѿ˺��� ��������
	vector<tagBullet> getVBullet() { return _vBullet; }
	vector<tagBullet>* getVBulletPt() { return &_vBullet; }
	vector<tagBullet>::iterator getViBullet() { return _viBullet; }

public:
	bullet() {}
	~bullet() {}
};

//=============================================================
//	## ��Ȳ�̹��� ## (missile[0] => �迭ó�� �̸� �����صΰ� �Ѿ˹߻�)
//=============================================================
class missile : public gameNode
{
private:
	//�Ѿ� ����ü�� ���� ����, �ݺ���
	vector<tagBullet> _vBullet;
	vector<tagBullet>::iterator _viBullet;

private:
	float _range;		//�Ѿ� ��Ÿ�
	int _bulletMax;		//�Ѿ� �ִ밹��

public:
	//�Ѿ˰���, �Ѿ˻�Ÿ��� �ʱ�ȭ
	HRESULT init(int bulletMax, float range);
	void release(void);
	void update(void);
	void render(void);

	//�Ѿ˹߻�
	void fire(float x, float y, int bulletKind, float range, int damage, int bulletSpeed);
	//�Ѿ˹���
	void move(void);
	//�Ѿ˺��� �������� 
	vector<tagBullet> getVBullet() { return _vBullet; }
	vector<tagBullet>* getVBulletPt() { return &_vBullet; }
	vector<tagBullet>::iterator getViBullet() { return _viBullet; }
	missile() {}
	~missile() {}
};

//=============================================================
//	## frameBullet ## (������ �̹����� �ִ� �Ѿ��� ���� ����ϴ� Ŭ����)
//=============================================================



class cSceneManager;
class frameBullet : public gameNode
{
private:
	//�Ѿ� ����ü�� ���� ����, �ݺ���
	vector<tagBullet> _vBullet;
	vector<tagBullet>::iterator _viBullet;

private:
	char* _imageName;	//�Ѿ� �̹��� Ű��	
	int _bulletMax;		//�Ѿ� �ִ밹��
	int _time;
	cSceneManager* _scene;
public:
	//�Ѿ��̹���Ű��, �Ѿ˰���, �Ѿ˻�Ÿ��� �ʱ�ȭ
	HRESULT init(char* imageName, int bulletMax);
	void release(void);
	void update(void);
	void render(void);

	//�Ѿ˹߻�
	void fire(float x, float y, float angle, float jumpPower, int damage, int bulletSpeed);
	//�Ѿ˹���
	void move(void);

	//�Ѿ˻���
	void removeBullet(int index);

	void setScene(cSceneManager* scene) { _scene = scene; }

	void pixelCol();

	//�Ѿ˺��� ��������
	vector<tagBullet> getVBullet() { return _vBullet; }
	vector<tagBullet>* getVBulletPt() { return &_vBullet; }
	vector<tagBullet>::iterator getViBullet() { return _viBullet; }

public:
	frameBullet() {}
	~frameBullet() {}
};


//=============================================================
//	## hoppingBullet ## (�������� �׸��� �Ѿ�)
//=============================================================

struct tagHBullet
{
	image* bulletImage;
	RECT rc;
	float x, y;
	float fireX, fireY;
	float speed;
	float angle;
	float gravity;
	float radius;
	bool fire;
	int count;
	float _range;		//�Ѿ� ��Ÿ�
	float _height;
	float _jumpPower;
	int damage;
};

class hoppingBullet : public gameNode
{
private:
	//�Ѿ� ����ü�� ���� ����, �ݺ���
	vector<tagHBullet> _vBullet;
	vector<tagHBullet>::iterator _viBullet;

private:
	char* _imageName;	//�Ѿ� �̹��� Ű��	
	int _bulletMax;		//�Ѿ� �ִ밹��
	int _time;
	cSceneManager* _scene;
public:
	//�Ѿ��̹���Ű��, �Ѿ˰���, �Ѿ˻�Ÿ��� �ʱ�ȭ
	HRESULT init(char* imageName, int bulletMax);
	void release(void);
	void update(void);
	void render(void);

	//�Ѿ˹߻�
	void fire(float x, float y, float angle, float jumpPower, int damage, int bulletSpeed);
	//�Ѿ˹���
	void move(void);

	void setScene(cSceneManager* scene) { _scene = scene; }

	void pixelCol();

	//�Ѿ˻���
	void removeBullet(int index);

	//�Ѿ˺��� ��������
	vector<tagHBullet> getVBullet() { return _vBullet; }
	vector<tagHBullet>* getVBulletPt() { return &_vBullet; }
	vector<tagHBullet>::iterator getViBullet() { return _viBullet; }

public:
	hoppingBullet() {}
	~hoppingBullet() {}
};





//=============================================================
//	## missileM1 ## (�ѹ߾� �Ѿ� �߻��ϸ鼭 �����ϰ� �ڵ�����)
//=============================================================
class missileM1 : public gameNode
{
private:
	//�Ѿ� ����ü�� ���� ����, �ݺ���
	vector<tagBullet> _vBullet;
	vector<tagBullet>::iterator _viBullet;

private:
	float _range;		//�Ѿ� ��Ÿ�
	int _bulletMax;		//�Ѿ� �ִ밹��

public:
	//�Ѿ˰���, �Ѿ˻�Ÿ��� �ʱ�ȭ
	HRESULT init(int bulletMax, float range);
	void release(void);
	void update(void);
	void render(void);

	//�Ѿ˹߻�
	void fire(float x, float y);
	//�Ѿ˹���
	void move(void);

	//�Ѿ˻���
	void removeBullet(int index);

	//�Ѿ˺��� ��������
	vector<tagBullet> getVBullet() { return _vBullet; }

	missileM1() {}
	~missileM1() {}
};

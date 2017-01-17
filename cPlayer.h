#pragma once
#include "gameNode.h"
#include "bullet.h"
#define PLAYERMOVESPEED 3.0f
class cItemManager;
class enemyManager;

enum PlayerFaceState
{
	pLEFT,
	pRIGHT,
	pIDLE,
	pUP,
};

enum PlayerAnimation
{
	IDLE,
	CARD,
	ETC,
	DAMAGE,
	DEAD,
};

class cPlayer : public gameNode
{
private:
	TCHAR buffer[256]; // Textout�Ҷ� ���¿뵵!

	bullet* _bullet;
	bullet* _ū�Ѿ�;
	missile* _��Ȳ;
	cItemManager* _im;
	enemyManager* _enemy;
	PlayerFaceState faceState;
	PlayerFaceState keyState;
	RECT rc;
	RECT rcHead;
	float x;
	float y;
	float angle; // �˹��ų������ �׿ܿ� �ޱ۾Ⱦ�
	//�ִϸ��̼� 
	int bulletCount;
	int frameCount;
	int returnCount;
	bool fire;
	bool cardOn;
	int leftFrame;
	int rightFrame;
	int upDownFrame;
	int animState;
	int itemCount;
	int statUpCount;
	// ���࿡ ����������(���������Ǳ���?)�� ������ ������ �Ŵ����ʿ��� �긦 true�� �ٲܰ���.
	// �ʸŴ����ʿ��� �ȼ��浹�� IsFly==false�϶��� �˻��ϰ� true���Ǹ� �ȼ��浹 �����ʰ� ¥��ɵ�?
	bool IsFly = false;
	//���Ӱ� �߰� 
	int damageCount;
	int damageFrameCount;
	int wingCount;  //���� ī��Ʈ 
	int wingFrame;
	bool dSlide;
	int dfireX;
	bool aSlide;
	int afireX;
	bool wSlide;
	int wfireY;
	bool sSlide;
	int sfireY;
	//
	int deadCount;  //������ ī��Ʈ 
	int deadFrame;
	int deadAlpha;
	bool monsterShot; 
	bool minionShot;
	bool playerShot; 
	vector<int> vInventory;
	int hitCount;


	//==================================================================
	//		## ���� ## �߰��ε��� �����ʼ�!
	//==================================================================
	int hp;  //ü��
	int maxHp;
	int range; //�Ѿ˹���
	int damage;	//�����
	int tears; //�Ѿ˹߻簣��,����ӵ�
	float moveSpeed; //�̵��ӵ�
	float bulletSpeed; //�Ѿ˼ӵ� ��� �ٲ�°��� �ƴ��� �𸣰ٽ�;

					   //==================================================================
					   //		## ������ ##  �߰��ε��� �����ʼ�!
					   //==================================================================
	int money;	//��
	int key;	//����
	int bomb;   //��ź
	int arrow;  //�����Ѿ�����
	int space;  //������
	int card; //�ɷ�ġ�÷��ִ�ī��

public:
	void SetIM(cItemManager* iim) { _im = iim; }
	void SetEM(enemyManager* eem) { _enemy = eem; }
	bool GetIsFly() { return IsFly; }
	void SetIsFly(bool _IsFly) { IsFly = _IsFly; }

	int GetMoney() { return money; }
	void SetMoney(int _money) { money = _money; }

	int GetKey() { return key; }
	void SetKey(int _key) { key = _key; }

	int GetBomb() { return bomb; }
	void SetBomb(int _bomb) { bomb = _bomb; }

	int GetArrow() { return arrow; }
	void SetArrow(int _arrow) { arrow = _arrow; }

	int GetSpace() { return space; }
	void SetSpace(int _space) { space = _space; }

	void SetX(float _x) { x = _x; }
	float GetX() { return x; }

	float GetY() { return y; }
	void SetY(float _y) { y = _y; }

	int GetHp() { return hp; }
	void SetHp(int _hp) { hp = _hp; }

	int GetmaxHp() { return maxHp; }
	void SetmaxHp(int _maxHp) { maxHp = _maxHp; }

	int GetRange() { return range; }
	void SetRange(int _range) { range = _range; }

	int GetDamage() { return damage; }
	void SetDamage(int _damage) { damage = _damage; }

	bool GetplayrShot() { return playerShot; }
	void SetplayerShot(bool _playerShot) { playerShot = _playerShot; }

	void SetAngle(float _angle) { angle = _angle; }

	void SetBulletSpeed(int _speed) { bulletSpeed = _speed; }
	int GetBulletSpeed() { return bulletSpeed; }
	void SetBulletDamage(int _bulletSpeed) { bulletSpeed = _bulletSpeed; }
	void addInVentory(int _item); // ������ �Ŵ������� ��

	int GetAnimState() { return animState; }
	void SetAnimState(int _animState) { animState = _animState; }

	int getHitCount() { return hitCount; }
	void setHitCount(int input) { hitCount = input; }

	int GetDeadAlpha() { return deadAlpha; }
	//�ִϸ��̼� �ټ� �Ϸ�! 
	RECT GetRC() { return rc; }

	bullet* getBullet() { return _bullet; }
	bullet* getBigBullet() { return _ū�Ѿ�; }
	missile* get��Ȳ() { return _��Ȳ; }
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
	void animation(void);
	void bulletFire(void);
	void PlayerKeyState(void);
	void DamagedPlayer(); // �˹��Ű���Լ�
	void PlayerSlide(void);

	void enemyIntersect(void);
	cPlayer() {}
	~cPlayer() {}
};


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
	TCHAR buffer[256]; // Textout할때 쓰는용도!

	bullet* _bullet;
	bullet* _큰총알;
	missile* _유황;
	cItemManager* _im;
	enemyManager* _enemy;
	PlayerFaceState faceState;
	PlayerFaceState keyState;
	RECT rc;
	RECT rcHead;
	float x;
	float y;
	float angle; // 넉백시킬떄만씀 그외에 앵글안씀
	//애니메이션 
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
	// 만약에 날개아이템(구렁텅잉의군주?)을 먹으면 아이템 매니져쪽에서 얘를 true로 바꿀거임.
	// 맵매니져쪽에서 픽셀충돌을 IsFly==false일때만 검사하고 true가되면 픽셀충돌 하지않게 짜면될듯?
	bool IsFly = false;
	//새롭게 추가 
	int damageCount;
	int damageFrameCount;
	int wingCount;  //날개 카운트 
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
	int deadCount;  //죽을때 카운트 
	int deadFrame;
	int deadAlpha;
	bool monsterShot; 
	bool minionShot;
	bool playerShot; 
	vector<int> vInventory;
	int hitCount;


	//==================================================================
	//		## 스탯 ## 추가로들어갈거 수정필수!
	//==================================================================
	int hp;  //체력
	int maxHp;
	int range; //총알범위
	int damage;	//대미지
	int tears; //총알발사간격,연사속도
	float moveSpeed; //이동속도
	float bulletSpeed; //총알속도 얘는 바뀌는건지 아닌지 모르겟슴;

					   //==================================================================
					   //		## 아이템 ##  추가로들어갈거 수정필수!
					   //==================================================================
	int money;	//돈
	int key;	//열쇠
	int bomb;   //폭탄
	int arrow;  //현재총알종류
	int space;  //아이템
	int card; //능력치올려주는카드

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
	void addInVentory(int _item); // 아이템 매니져에서 씀

	int GetAnimState() { return animState; }
	void SetAnimState(int _animState) { animState = _animState; }

	int getHitCount() { return hitCount; }
	void setHitCount(int input) { hitCount = input; }

	int GetDeadAlpha() { return deadAlpha; }
	//애니메이션 겟셋 완료! 
	RECT GetRC() { return rc; }

	bullet* getBullet() { return _bullet; }
	bullet* getBigBullet() { return _큰총알; }
	missile* get유황() { return _유황; }
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
	void animation(void);
	void bulletFire(void);
	void PlayerKeyState(void);
	void DamagedPlayer(); // 넉백시키는함수
	void PlayerSlide(void);

	void enemyIntersect(void);
	cPlayer() {}
	~cPlayer() {}
};


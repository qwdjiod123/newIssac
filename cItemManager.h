#pragma once
#include "gameNode.h"
//아이템마다 애니매이션 카운트와 렉트사이즈 다르게설정함
//여기다수정해야함
#define 보물상자렉트 50
#define 보물상자카운트 10

#define 폭탄렉트 40
#define 폭탄카운트 3
#define BOMBSIZE 100 // 아이템매니져만씀  폭팔할떄(렉트)사이즈

#define 열쇠렉트 40
#define 열쇠카운트 8

#define 빨간하트반렉트 30
#define 빨간하트반카운트 10

#define 빨간하트렉트 30
#define 빨간하트카운트 7

#define 동전1렉트 30 
#define 동전1카운트 5

#define 동전99렉트 40 
#define 동전99카운트 10

#define 썩은고기렉트 40 
#define 썩은고기카운트 10

#define 카드렉트 30 
#define 카드카운트 10

#define 유황렉트 40 
#define 유황카운트 10

#define 구렁텅이의군주렉트 40 
#define 구렁텅이의군주카운트 10

#define 모래시계렉트 40 
#define 모래시계카운트 10

#define 박사조정기렉트 40 
#define 박사조정기카운트 10
#define 박사의조정기조준경 50
#define 박사의조정기폭발 100
#define 미사일스피드 3.0f
/////////////////////////////////////////////////////


#define ITEMMOVETIME 3.0f

class cSceneManager;
class cPlayer;
class enemyManager;


//==================================================================
//		## 아이템종류 여기에다 추가예정 ## 상호참조하면 다른데서 이거 참조가능
//==================================================================

enum EITEM  // 패시브아이템다포함
{
	보물상자 = -1,
	기본총알 = 0,
	폭탄,
	열쇠,
	동전1,
	빨간하트반, //피 1증가   플레이어의 하트1개가 피2개임
	빨간하트,   //피 2증가 	
	동전99, //테스트를위해
	썩은고기, //체력+2 맥스체력+2	
	유황, // 기본공격 바뀜! (이미지바뀜) 
	구렁텅이의군주, // 날라다님지형물무시 (이미지바뀜)	
};

enum EACTIVEITEM // 스페이스바눌러서쓰는템들
{
	없음 = 100,
	박사의조정기, // 일정부분에 미사일생성 발사되기전까지 조준경위치변경가능 // 얘도할지안할지미정
	모래시계, // 적의움직임과 발사체를 느리게함 혹은 멈추게하는것도 괸찮을듯
};

enum EACTIVECARD // 카드는그냥 먹었을때 스탯등등 증가하는거보여주기위해 1개만만들예정
{
	카드 = 1000, // 사거리+2, 공격력+2, 이동속도+2, 공격속도+2 
	돌맹이,
	상점캐릭터,
	상점2,
	상점3,
	벽돌,
};



struct tag_Item
{
	RECT rc;
	float x;
	float y;
	float gravity = 0.0f;
	float angle; // 아이템도 움직임 ㅠㅠ
	float moveSpeed; // 아이템도 움직임 ㅠㅠ	
	int state; // 이아이템이 무엇인지 예 : state=폭탄
	int currentmap; // 현재 무슨맵에 생성되어있는 아이템인지

	bool IsMove = false;
	bool IsBomb = false;  // 폭탄사용하는거떄문에 따로만든 변수 
	int contdown = 0; // 폭탄사용하는거떄문에 따로만든 변수 
	int AnimX = 0;
	int RectSize;
};

struct tag_missile
{
	float x = WINSIZEX / 2;
	float y = WINSIZEY / 2;
	int AnimX = 0;
	RECT rc;
	RECT rcBomb; // 얘랑 충돌검사하면됨
	bool IsBomb = false;
	int nCount = 0;
	int AnimY = 300;
};

struct tag_Store
{
	float StartX;
	float StartY;
	float x;
	float y;
	float angle;
	RECT rc;
	int currentmap;
	int nCount = 0;
	bool IsMove = false;
	bool IsLive = true;
	int AnimX = 0;
};

struct tag_mapRC
{
	float x;
	float y;
	RECT rc;
};
class cItemManager : public gameNode
{
private:

	cSceneManager* _sm;
	cPlayer* _player;
	enemyManager* _enemy;

	TCHAR buffer[256]; // TextOut에씀
	RECT temp; // 렉트충돌하는데쓰임
	tag_mapRC mapRC; //픽셀로 말고 그냥 렉트충돌로할게요 ㅠㅠ

	bool ItemSetOnce[10] = { false, }; // 맵체인지할때 아이템리셋하는거막기위해 맵담당자말고는 중요하지않음
	int AnimCount = 0; // 아이템들 프레임렌더 공통 카운트
	bool IsChange; // 아이템교체하는 로직때문에 야매로씀	
	bool IsTime = false; // 모래시계아이템전용으로 쓰는 변수
	bool IsPlayerDamaged;
	//테스트//
	bool IsLR = true; //렉트충돌 좌우 true일때 좌우만충돌준비! false일떄 상하만충돌준비!
	float distanceX = 0.0f; // 상점 렉트충돌할때 씀	
							//==================================================================
							//		## 아이템관리 백터 ##
							//==================================================================
	vector<tag_Item> vItem;	 // 맵에 기본적으로 셋팅되있는 아이템들
	vector<tag_Item> vNewItem; // 무언가 유동적으로 생기는아이템들! 상점에서 템사면 생성되는아이템들 혹은 플레이거 폭탄사용할떄 여기추가함

							   //==================================================================
							   //		## 추가적인 아이템들 ##
							   //==================================================================

	tag_missile missileBomb; // 박사의구렁텅이아이템을 쓰고난후 미사일 구조체
	tag_Store store; // 돈내고 랜덤으로 탬나오는 기계

public:


	void SetIM(cSceneManager* ssm) { _sm = ssm; }
	void SetPlayer(cPlayer* pplayer) { _player = pplayer; }
	void SetEnemy(enemyManager* eem) { _enemy = eem; }

	void ItemSetting(); // 화면바뀔때마다 한번만 셋팅

	void ItemMapSet(float _x, float _y, int _state, int _currentmap); // 위에함수에서 이 함수호출!

	void ItemUse(int _item); // 플레이어에서씁니다. 열쇠하고 동전제외

	void ItemMake(float _x, float _y, int _state, int _currentmap, bool _IsMove);  // 맵쪽 : 폭탄,열쇠,동전1,동전99 적쪽 : 모르겟슴

	void DeleteItem(int index); // 아이템매니져에서만 씁니다.
	void DeleteNewItem(int index); // 아이템매니져에서만 씁니다.

	void ItemUpdate(int _currentmap);      //아이템 매니져에서만씀
	void NewItemUpdate(int _currentmap);   //아이템 매니져에서만씀
	void ItemRender(int _currentmap);      //아이템 매니져에서만씀 , 맵만드는사람이쓸수도있슴(확인용)
	void NewItemRender(int _currentmap);   //아이템 매니져에서만씀 , 맵만드는사람이쓸수도있슴(확인용)

	void Collision(); // 폭탄과 각종 부디쳣을떄로직 플레이어,상점,등등
	void ItemRectCollision(int _currentmap); // <화면>과 <바위>랑충돌했을떄

	void MissileControl(); // 박사의조정기 로직
	void MissileRender();  // 박사의조정기 렌더

	void StoreSetting(int _currentmap); // 상점셋팅
	void StoreUpdate(); // 상점업뎃 렉트충돌로만듬
	void StoreRener();  // 상점렌더

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);



	cItemManager() {}
	~cItemManager() {}
};


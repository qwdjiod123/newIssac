#pragma once
#include "gameNode.h"
//�����۸��� �ִϸ��̼� ī��Ʈ�� ��Ʈ������ �ٸ��Լ�����
//����ټ����ؾ���
#define �������ڷ�Ʈ 50
#define ��������ī��Ʈ 10

#define ��ź��Ʈ 40
#define ��źī��Ʈ 3
#define BOMBSIZE 100 // �����۸Ŵ�������  �����ҋ�(��Ʈ)������

#define ���跺Ʈ 40
#define ����ī��Ʈ 8

#define ������Ʈ�ݷ�Ʈ 30
#define ������Ʈ��ī��Ʈ 10

#define ������Ʈ��Ʈ 30
#define ������Ʈī��Ʈ 7

#define ����1��Ʈ 30 
#define ����1ī��Ʈ 5

#define ����99��Ʈ 40 
#define ����99ī��Ʈ 10

#define ������ⷺƮ 40 
#define �������ī��Ʈ 10

#define ī�巺Ʈ 30 
#define ī��ī��Ʈ 10

#define ��Ȳ��Ʈ 40 
#define ��Ȳī��Ʈ 10

#define ���������Ǳ��ַ�Ʈ 40 
#define ���������Ǳ���ī��Ʈ 10

#define �𷡽ð跺Ʈ 40 
#define �𷡽ð�ī��Ʈ 10

#define �ڻ������ⷺƮ 40 
#define �ڻ�������ī��Ʈ 10
#define �ڻ������������ذ� 50
#define �ڻ������������� 100
#define �̻��Ͻ��ǵ� 3.0f
/////////////////////////////////////////////////////


#define ITEMMOVETIME 3.0f

class cSceneManager;
class cPlayer;
class enemyManager;


//==================================================================
//		## ���������� ���⿡�� �߰����� ## ��ȣ�����ϸ� �ٸ����� �̰� ��������
//==================================================================

enum EITEM  // �нú�����۴�����
{
	�������� = -1,
	�⺻�Ѿ� = 0,
	��ź,
	����,
	����1,
	������Ʈ��, //�� 1����   �÷��̾��� ��Ʈ1���� ��2����
	������Ʈ,   //�� 2���� 	
	����99, //�׽�Ʈ������
	�������, //ü��+2 �ƽ�ü��+2	
	��Ȳ, // �⺻���� �ٲ�! (�̹����ٲ�) 
	���������Ǳ���, // ����ٴ����������� (�̹����ٲ�)	
};

enum EACTIVEITEM // �����̽��ٴ����������۵�
{
	���� = 100,
	�ڻ���������, // �����κп� �̻��ϻ��� �߻�Ǳ������� ���ذ���ġ���氡�� // �굵��������������
	�𷡽ð�, // ���ǿ����Ӱ� �߻�ü�� �������� Ȥ�� ���߰��ϴ°͵� ��������
};

enum EACTIVECARD // ī��±׳� �Ծ����� ���ȵ�� �����ϴ°ź����ֱ����� 1�������鿹��
{
	ī�� = 1000, // ��Ÿ�+2, ���ݷ�+2, �̵��ӵ�+2, ���ݼӵ�+2 
	������,
	����ĳ����,
	����2,
	����3,
	����,
};



struct tag_Item
{
	RECT rc;
	float x;
	float y;
	float gravity = 0.0f;
	float angle; // �����۵� ������ �Ф�
	float moveSpeed; // �����۵� ������ �Ф�	
	int state; // �̾������� �������� �� : state=��ź
	int currentmap; // ���� �����ʿ� �����Ǿ��ִ� ����������

	bool IsMove = false;
	bool IsBomb = false;  // ��ź����ϴ°ŋ����� ���θ��� ���� 
	int contdown = 0; // ��ź����ϴ°ŋ����� ���θ��� ���� 
	int AnimX = 0;
	int RectSize;
};

struct tag_missile
{
	float x = WINSIZEX / 2;
	float y = WINSIZEY / 2;
	int AnimX = 0;
	RECT rc;
	RECT rcBomb; // ��� �浹�˻��ϸ��
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

	TCHAR buffer[256]; // TextOut����
	RECT temp; // ��Ʈ�浹�ϴµ�����
	tag_mapRC mapRC; //�ȼ��� ���� �׳� ��Ʈ�浹���ҰԿ� �Ф�

	bool ItemSetOnce[10] = { false, }; // ��ü�����Ҷ� �����۸����ϴ°Ÿ������� �ʴ���ڸ���� �߿���������
	int AnimCount = 0; // �����۵� �����ӷ��� ���� ī��Ʈ
	bool IsChange; // �����۱�ü�ϴ� ���������� �߸ŷξ�	
	bool IsTime = false; // �𷡽ð�������������� ���� ����
	bool IsPlayerDamaged;
	//�׽�Ʈ//
	bool IsLR = true; //��Ʈ�浹 �¿� true�϶� �¿츸�浹�غ�! false�ϋ� ���ϸ��浹�غ�!
	float distanceX = 0.0f; // ���� ��Ʈ�浹�Ҷ� ��	
							//==================================================================
							//		## �����۰��� ���� ##
							//==================================================================
	vector<tag_Item> vItem;	 // �ʿ� �⺻������ ���õ��ִ� �����۵�
	vector<tag_Item> vNewItem; // ���� ���������� ����¾����۵�! �������� �ۻ�� �����Ǵ¾����۵� Ȥ�� �÷��̰� ��ź����ҋ� �����߰���

							   //==================================================================
							   //		## �߰����� �����۵� ##
							   //==================================================================

	tag_missile missileBomb; // �ڻ��Ǳ������̾������� ������ �̻��� ����ü
	tag_Store store; // ������ �������� �Ƴ����� ���

public:


	void SetIM(cSceneManager* ssm) { _sm = ssm; }
	void SetPlayer(cPlayer* pplayer) { _player = pplayer; }
	void SetEnemy(enemyManager* eem) { _enemy = eem; }

	void ItemSetting(); // ȭ��ٲ𶧸��� �ѹ��� ����

	void ItemMapSet(float _x, float _y, int _state, int _currentmap); // �����Լ����� �� �Լ�ȣ��!

	void ItemUse(int _item); // �÷��̾�����ϴ�. �����ϰ� ��������

	void ItemMake(float _x, float _y, int _state, int _currentmap, bool _IsMove);  // ���� : ��ź,����,����1,����99 ���� : �𸣰ٽ�

	void DeleteItem(int index); // �����۸Ŵ��������� ���ϴ�.
	void DeleteNewItem(int index); // �����۸Ŵ��������� ���ϴ�.

	void ItemUpdate(int _currentmap);      //������ �Ŵ�����������
	void NewItemUpdate(int _currentmap);   //������ �Ŵ�����������
	void ItemRender(int _currentmap);      //������ �Ŵ����������� , �ʸ���»���̾������ֽ�(Ȯ�ο�)
	void NewItemRender(int _currentmap);   //������ �Ŵ����������� , �ʸ���»���̾������ֽ�(Ȯ�ο�)

	void Collision(); // ��ź�� ���� �ε��������� �÷��̾�,����,���
	void ItemRectCollision(int _currentmap); // <ȭ��>�� <����>���浹������

	void MissileControl(); // �ڻ��������� ����
	void MissileRender();  // �ڻ��������� ����

	void StoreSetting(int _currentmap); // ��������
	void StoreUpdate(); // �������� ��Ʈ�浹�θ���
	void StoreRener();  // ��������

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);



	cItemManager() {}
	~cItemManager() {}
};


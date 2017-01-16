#pragma once
#include "gameNode.h"
class cPlayer;
class cItemManager;
#define MAPMAX 5 // �ʸŴ����������� 

enum INTROSTATE
{
	INTRO1,
	INTRO1_1,
	INTRO1_2,
	INTRO1_3,
	INTRO2,
	INTRO2_1,
	INTRO2_2,
	INTRO2_3,
	INTRO3,
	INTRO3_1,
	INTRO3_2,
	INTRO3_3,
	INTRO4,
	INTRO4_1,
	INTRO4_2,
	INTRO4_3,
	INTRO4_4,
	INTRO4_5,
	INTRO4_6,
	INTRO5,
	MAINGAME,
	STARTAFTER,
	CHARACTERCHANGE,
	//����
};
class cIntro :
	public gameNode
{
private:
	RECT temp; //�׽�Ʈ��! ��Ʈ�浹�Լ��������!

	int currentMap;	 // ���� ���������� ���Ŭ������ �̰� ������
	int mapTime;
	int startAfterTime;
	bool mapIntroSwap;
	bool changeScene;
public:

	int introAlpha;
	int intro2Alpha;
	int intro3Alpha;
	int flyFrameX;
	int motherFrameX;

	RECT startRect;
	RECT selectRect;

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void animation(void);
	void introRender(void);

	cIntro() {}
	~cIntro() {}
};


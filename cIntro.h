#pragma once
#include "gameNode.h"
class cPlayer;
class cItemManager;
#define MAPMAX 5 // 맵매니져에서만씀 

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
	//등등등
};
class cIntro :
	public gameNode
{
private:
	RECT temp; //테스트용! 렉트충돌함수에서사용!

	int currentMap;	 // 현재 무슨맵인지 모든클래스가 이거 참조함
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


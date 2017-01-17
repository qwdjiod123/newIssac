#pragma once
#include "gameNode.h"
class cPlayer;
class cItemManager;
#define MAPMAX 5 // 맵매니져에서만씀 



enum EMAPSTATE
{
	정보방,
	첫번째방,
	두번째방,
	세번째방,
	네번째방,
	다섯번째방,
	여섯번째방,
	일곱번째방,
	여덟번째방,
	아홉번째방,
	맵12,
	맵13,
	맵14,
	맵1보스
	//등등등
};

enum DOORSTATE
{
	닫히는중,
	닫힘,
	열리는중,
	열림
	//등등등
};


class cSceneManager : public gameNode
{
private:

	TCHAR buffer[256];
	cPlayer* _player;
	cItemManager* _im;

	RECT rc; // 테스트용! 실제로는 픽셀로 만들자!
	RECT rc2; // 테스트용! 실제로는 픽셀로 만들자!	
	RECT temp; //테스트용! 렉트충돌함수에서사용!
	RECT store;


	bool ItemSetting[MAPMAX]; // 맵체인지할때 아이템리셋하는거막기위해 맵담당자말고는 중요하지않음
	int beforMap;
	int currentMap;	 // 현재 무슨맵인지 모든클래스가 이거 참조함
	bool isPixel;
	int inGameAlpha;
	bool isMapChange;
	bool isDoorState;
	int mapChangeFrame;
	int doorChangeFrame;
	int time;
	bool isInfo;
	bool isFirst;
	bool isSecond;
	bool isThird;
	bool isFourth;
	bool isFifth;
	bool isSixth;
	bool isSeventh;
	bool isEighth;

public:



	int GetCurrentMap() { return currentMap; }

	void SetIM(cItemManager* iim) { _im = iim; }
	void SetPlayer(cPlayer* pplayer) { _player = pplayer; }

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	int GetdoorChangeFrame() { return doorChangeFrame; }

	void mapChangeUpdate(void);
	void mapChangeRender(void);
	void mapMiniRender(void);
	void hpUiRender(void);
	bool GetIsMapChange() { return isMapChange; }
	void SetIsMapChange(bool _isMapChange) { isMapChange = _isMapChange; }

	cSceneManager() {}
	~cSceneManager() {}
};


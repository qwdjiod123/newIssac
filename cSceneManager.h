#pragma once
#include "gameNode.h"
class cPlayer;
class cItemManager;
#define MAPMAX 5 // �ʸŴ����������� 



enum EMAPSTATE
{
	������,
	ù��°��,
	�ι�°��,
	����°��,
	�׹�°��,
	�ټ���°��,
	������°��,
	�ϰ���°��,
	������°��,
	��ȩ��°��,
	��12,
	��13,
	��14,
	��1����
	//����
};

enum DOORSTATE
{
	��������,
	����,
	��������,
	����
	//����
};


class cSceneManager : public gameNode
{
private:

	TCHAR buffer[256];
	cPlayer* _player;
	cItemManager* _im;

	RECT rc; // �׽�Ʈ��! �����δ� �ȼ��� ������!
	RECT rc2; // �׽�Ʈ��! �����δ� �ȼ��� ������!	
	RECT temp; //�׽�Ʈ��! ��Ʈ�浹�Լ��������!
	RECT store;


	bool ItemSetting[MAPMAX]; // ��ü�����Ҷ� �����۸����ϴ°Ÿ������� �ʴ���ڸ���� �߿���������
	int beforMap;
	int currentMap;	 // ���� ���������� ���Ŭ������ �̰� ������
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


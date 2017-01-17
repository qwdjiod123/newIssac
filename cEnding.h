#pragma once
#include "gameNode.h"
class cPlayer;
class cItemManager;
class cEnding :
	public gameNode
{
private:

	TCHAR buffer[256];
	cPlayer* _player;
	cItemManager* _im;
	int endingTime;
	int endingFrame;
public:

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
};


#include "stdafx.h"
#include "cSound.h"
#include"cSceneManager.h"


HRESULT cSound::init(void)
{
	SOUNDMANAGER->addSound("게임브금", "game.mp3",true,true);	
	return S_OK;
}

void cSound::release(void)
{
}

void cSound::update(void)
{
	if (_sm->GetCurrentMap()==정보방)
	{
		if (!SOUNDMANAGER->isPlaySound("게임브금"))
		{
			SOUNDMANAGER->play("게임브금");
		}
	}

}

void cSound::render(void)
{
}

#include "stdafx.h"
#include "cSound.h"
#include"cSceneManager.h"


HRESULT cSound::init(void)
{
	SOUNDMANAGER->addSound("���Ӻ��", "game.mp3",true,true);	
	return S_OK;
}

void cSound::release(void)
{
}

void cSound::update(void)
{
	if (_sm->GetCurrentMap()==������)
	{
		if (!SOUNDMANAGER->isPlaySound("���Ӻ��"))
		{
			SOUNDMANAGER->play("���Ӻ��");
		}
	}

}

void cSound::render(void)
{
}

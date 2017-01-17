#include "stdafx.h"
#include "cEnding.h"
#include"cPlayer.h"
#include"cItemManager.h"


HRESULT cEnding::init(void)
{
	endingTime = 0;
	endingFrame = 1;
	return S_OK;
}

void cEnding::release(void)
{
}

void cEnding::update(void)
{
		
}

void cEnding::render(void)
{
	if (endingTime % 5 == 0)
	{
		endingFrame++;
	}
	else
	{
		endingTime++;
	}

	if (endingFrame > 78)
	{
		endingFrame = 78;
		SCENEMANAGER->changeScene("인트로화면");
	}
	IMAGEMANAGER->findImage(to_string(endingFrame))->render(getMemDC(), -400, -200);
	endingTime++;
}

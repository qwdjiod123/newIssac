#include "stdafx.h"
#include "cIntro.h"

HRESULT cIntro::init(void)
{

	currentMap = INTRO1;

	mapTime = 0;
	startAfterTime = 0;
	introAlpha = 255;
	intro2Alpha = 0;
	intro3Alpha = 255;

	flyFrameX = 0;
	motherFrameX = 0;

	mapIntroSwap = false;
	changeScene = false;

	startRect = RectMake(312, 452, 163, 64);
	selectRect = RectMake(555, 400, 150, 150);
	return S_OK;
}

void cIntro::release(void)
{
}

void cIntro::update(void)
{
	//애니메이션 업데이트
	animation();
	if (currentMap == STARTAFTER)
	{
		startAfterTime++;
	}
	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		currentMap = MAINGAME;
		mapTime = 1000;
		introAlpha = 0;
	}


}

void cIntro::render(void)
{
	introRender();

	//char str[32];
	//wsprintf(str, "introAlpha: %d", currentMap);
	//TextOut(getMemDC(), 100, 100, str, strlen(str));
}

void cIntro::animation(void)
{
	mapTime++;
	//아이작+엄마 애니메이션
	if (mapTime % 10 == 0)
	{
		motherFrameX += 320;
		if (motherFrameX == 1600)
		{
			motherFrameX = 0;
		}
	}
	//파리 애니메이션
	if (mapTime % 2 == 0)
	{
		flyFrameX += 130;
		if (flyFrameX == 260)
		{
			flyFrameX = 0;
		}
	}
	//인트로 애니메이션
	if (mapTime % 10 == 0)
	{
		if (mapIntroSwap == false)
		{
			mapIntroSwap = true;
		}
		else if (mapIntroSwap == true)
		{
			mapIntroSwap = false;
		}
	}
}


void cIntro::introRender(void)
{
	if (mapTime == 200)
	{
		currentMap = INTRO1_1;
	}
	if (mapTime == 205)
	{
		currentMap = INTRO1_2;
	}
	if (mapTime == 210)
	{
		currentMap = INTRO1_3;
	}
	if (mapTime == 215)
	{
		currentMap = INTRO2;
	}
	if (mapTime == 415)
	{
		currentMap = INTRO2_1;
	}
	if (mapTime == 420)
	{
		currentMap = INTRO2_2;
	}
	if (mapTime == 425)
	{
		currentMap = INTRO2_3;
	}
	if (mapTime == 430)
	{
		currentMap = INTRO3;
	}
	if (mapTime == 630)
	{
		currentMap = INTRO3_1;
	}
	if (mapTime == 635)
	{
		currentMap = INTRO3_2;
	}
	if (mapTime == 640)
	{
		currentMap = INTRO3_3;
	}
	if (mapTime == 645)
	{
		currentMap = INTRO4;
	}
	if (mapTime == 845)
	{
		currentMap = INTRO4_1;
	}
	if (mapTime == 850)
	{
		currentMap = INTRO4_2;
	}
	if (mapTime == 855)
	{
		currentMap = INTRO4_3;
	}
	if (mapTime == 860)
	{
		currentMap = INTRO4_4;
	}
	if (mapTime == 865)
	{
		currentMap = INTRO4_5;
	}
	if (mapTime == 870)
	{
		currentMap = INTRO4_6;
	}
	if (mapTime == 875)
	{
		currentMap = INTRO5;
	}
	if (currentMap == INTRO5)
	{
		introAlpha -= 3;
	}
	if (introAlpha == 0)
	{
		currentMap = MAINGAME;
	}
	if (currentMap == MAINGAME)
	{
		introAlpha = -20;
		intro2Alpha += 3;
		if (intro2Alpha >= 255)
		{
			intro2Alpha = 255;
		}
	}

	if (currentMap == INTRO1)
	{
		if (mapIntroSwap == false)
		{
			IMAGEMANAGER->render("intro1Part1", getMemDC());
		}
		if (mapIntroSwap == true)
		{
			IMAGEMANAGER->render("intro1Part2", getMemDC());
		}
	}
	if (currentMap == INTRO1_1)
	{
		IMAGEMANAGER->render("intro1Part3", getMemDC());
	}
	if (currentMap == INTRO1_2)
	{
		IMAGEMANAGER->render("intro1Part4", getMemDC());
	}
	if (currentMap == INTRO1_3)
	{
		IMAGEMANAGER->render("intro1Part5", getMemDC());
	}
	if (currentMap == INTRO2)
	{
		if (mapIntroSwap == false)
		{
			IMAGEMANAGER->render("intro2Part1", getMemDC());
		}
		if (mapIntroSwap == true)
		{
			IMAGEMANAGER->render("intro2Part2", getMemDC());
		}
	}
	if (currentMap == INTRO2_1)
	{
		IMAGEMANAGER->render("intro2Part3", getMemDC());
	}
	if (currentMap == INTRO2_2)
	{
		IMAGEMANAGER->render("intro2Part4", getMemDC());
	}
	if (currentMap == INTRO2_3)
	{
		IMAGEMANAGER->render("intro2Part5", getMemDC());
	}
	if (currentMap == INTRO3)
	{
		if (mapIntroSwap == false)
		{
			IMAGEMANAGER->render("intro3Part1", getMemDC());
		}
		if (mapIntroSwap == true)
		{
			IMAGEMANAGER->render("intro3Part2", getMemDC());
		}
	}
	if (currentMap == INTRO3_1)
	{
		IMAGEMANAGER->render("intro3Part3", getMemDC());
	}
	if (currentMap == INTRO3_2)
	{
		IMAGEMANAGER->render("intro3Part4", getMemDC());
	}
	if (currentMap == INTRO3_3)
	{
		IMAGEMANAGER->render("intro3Part5", getMemDC());
	}
	if (currentMap == INTRO4)
	{
		if (mapIntroSwap == false)
		{
			IMAGEMANAGER->render("intro4Part1", getMemDC());
		}
		if (mapIntroSwap == true)
		{
			IMAGEMANAGER->render("intro4Part2", getMemDC());
		}
	}
	if (currentMap == INTRO4_1)
	{
		IMAGEMANAGER->render("intro4Part3", getMemDC());
	}
	if (currentMap == INTRO4_2)
	{
		IMAGEMANAGER->render("intro4Part4", getMemDC());
	}
	if (currentMap == INTRO4_3)
	{
		IMAGEMANAGER->render("intro4Part5", getMemDC());
	}
	if (currentMap == INTRO4_4)
	{
		IMAGEMANAGER->render("intro4Part6", getMemDC());
	}
	if (currentMap == INTRO4_5)
	{
		IMAGEMANAGER->render("intro4Part7", getMemDC());
	}
	if (currentMap == INTRO4_6)
	{
		IMAGEMANAGER->render("intro4Part8", getMemDC());
	}
	if (currentMap == INTRO5)
	{
		if (mapIntroSwap == false)
		{
			IMAGEMANAGER->alphaRender("intro5Part1", getMemDC(), introAlpha);
		}
		if (mapIntroSwap == true)
		{
			IMAGEMANAGER->alphaRender("intro5Part2", getMemDC(), introAlpha);
		}
	}
	if (currentMap == MAINGAME)
	{
		IMAGEMANAGER->alphaRender("mainGame", getMemDC(), intro2Alpha);
		if (intro2Alpha == 255)
		{
			IMAGEMANAGER->render("flyIntro", getMemDC(), 624, 308, flyFrameX, 0, 130, 130);
			IMAGEMANAGER->render("mother", getMemDC(), 236, 150, motherFrameX, 0, 320, 320);
		}
		if (PtInRect(&startRect, _ptMouse))
		{
			IMAGEMANAGER->render("start", getMemDC(), 312, 452);
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
			{
				currentMap = STARTAFTER;
			}
		}
	}
	if (currentMap == STARTAFTER)
	{
		if (startAfterTime == 1 || startAfterTime == 2)
		{
			IMAGEMANAGER->render("startAfter1", getMemDC());
		}
		if (startAfterTime == 3 || startAfterTime == 4)
		{
			IMAGEMANAGER->render("startAfter2", getMemDC());
		}
		if (startAfterTime == 5 || startAfterTime == 6)
		{
			IMAGEMANAGER->render("startAfter3", getMemDC());
		}
		if (startAfterTime == 7 || startAfterTime == 8)
		{
			IMAGEMANAGER->render("startAfter4", getMemDC());
		}
		if (startAfterTime == 9 || startAfterTime == 10)
		{
			IMAGEMANAGER->render("startAfter5", getMemDC());
		}
		if (startAfterTime == 11 || startAfterTime == 12)
		{
			IMAGEMANAGER->render("startAfter6", getMemDC());
		}
		if (startAfterTime == 13 || startAfterTime == 14)
		{
			IMAGEMANAGER->render("startAfter7", getMemDC());
		}
		if (startAfterTime == 15 || startAfterTime == 16)
		{
			IMAGEMANAGER->render("startAfter8", getMemDC());
		}
		if (startAfterTime == 17 || startAfterTime == 18)
		{
			IMAGEMANAGER->render("startAfter9", getMemDC());
		}
		if (startAfterTime == 19 || startAfterTime == 20)
		{
			IMAGEMANAGER->render("startAfter10", getMemDC());
		}
		if (startAfterTime == 21 || startAfterTime == 22)
		{
			IMAGEMANAGER->render("startAfter11", getMemDC());
		}
		if (startAfterTime == 23 || startAfterTime == 24)
		{
			IMAGEMANAGER->render("startAfter12", getMemDC());
		}
		if (startAfterTime == 25 || startAfterTime == 26)
		{
			IMAGEMANAGER->render("startAfter13", getMemDC());
		}
		if (startAfterTime == 27 || startAfterTime == 28)
		{
			IMAGEMANAGER->render("startAfter14", getMemDC());
		}
		if (startAfterTime == 29 || startAfterTime == 30)
		{
			IMAGEMANAGER->render("startAfter15", getMemDC());
		}
		if (startAfterTime == 31 || startAfterTime == 32)
		{
			IMAGEMANAGER->render("startAfter16", getMemDC());
		}
		if (startAfterTime == 33 || startAfterTime == 34)
		{
			IMAGEMANAGER->render("startAfter17", getMemDC());
		}
		if (startAfterTime == 35 || startAfterTime == 36)
		{
			IMAGEMANAGER->render("startAfter18", getMemDC());
		}
		if (startAfterTime == 37)
		{
			currentMap = CHARACTERCHANGE;
		}
	}

	if (currentMap == CHARACTERCHANGE)
	{
		IMAGEMANAGER->alphaRender("characterChange", getMemDC(), intro3Alpha);
		IMAGEMANAGER->alphaRender("flyIntro", getMemDC(), 60, 20, flyFrameX, 0, 130, 130, intro3Alpha);
		if (PtInRect(&selectRect, _ptMouse))
		{
			IMAGEMANAGER->alphaRender("select", getMemDC(), 555, 400, intro3Alpha);
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
			{
				changeScene = true;
			}
		}

		if (changeScene == true)
		{
			intro3Alpha -= 3;
		}
		if (intro3Alpha == 0)
		{
			SCENEMANAGER->changeScene("게임화면");
		}
	}
}

#include "stdafx.h"
#include "cSceneManager.h"
#include"cPlayer.h"
#include"cItemManager.h"



HRESULT cSceneManager::init(void)
{
	beforMap = 정보방;
	currentMap = 정보방;
	_player->SetX(WINSIZEX / 2);
	_player->SetY(WINSIZEY / 2);

	for (int i = 0; i < MAPMAX; i++)
	{
		ItemSetting[i] = false;

	}

	inGameAlpha = 0;
	isMapChange = false;
	isPixel = false;
	isDoorState = 열림;
	doorChangeFrame = 0;
	mapChangeFrame = 0;
	return S_OK;
}

void cSceneManager::release(void)
{
}

void cSceneManager::update(void)
{
	time++;
	isPixel = KEYMANAGER->isToggleKey('T');
	mapChangeUpdate();

}

void cSceneManager::render(void)
{
	IMAGEMANAGER->alphaRender("UI", getMemDC(), inGameAlpha);
	mapChangeRender();
	//테스트
	sprintf(buffer, TEXT("%f"), mapChangeFrame);
	TextOut(getMemDC(), 100, 100, buffer, lstrlen(buffer));
}

void cSceneManager::mapChangeUpdate(void)
{
	if (currentMap == 정보방)
	{
		inGameAlpha += 3;
		if (inGameAlpha >= 255)
		{
			inGameAlpha = 255;
		}

		COLORREF colorTop = GetPixel(IMAGEMANAGER->findImage("inGameInfoPX")->getMemDC(), _player->GetX(), _player->GetRC().top - 90);
		int rTop = GetRValue(colorTop);
		int gTop = GetGValue(colorTop);
		int bTop = GetBValue(colorTop);
		if ((rTop == 0 && gTop == 255 && bTop == 0))
		{
			_player->SetY(525);
			beforMap = 정보방;
			currentMap = 네번째방;
			mapChangeFrame = 510;
			doorChangeFrame = 0;
		}
		if ((rTop == 255 && gTop == 0 && bTop == 0))
		{
			_player->SetY(180);
		}
		COLORREF colorRight = GetPixel(IMAGEMANAGER->findImage("inGameInfoPX")->getMemDC(), _player->GetRC().right, _player->GetY() - 90);
		int rRight = GetRValue(colorRight);
		int gRight = GetGValue(colorRight);
		int bRight = GetBValue(colorRight);
		if ((rRight == 0 && gRight == 255 && bRight == 0))
		{
			_player->SetX(80);
			beforMap = 정보방;
			currentMap = 여섯번째방;
			mapChangeFrame = 0;
			doorChangeFrame = 0;
		}
		if ((rRight == 255 && gRight == 0 && bRight == 0))
		{
			_player->SetX(710);
		}
		COLORREF colorLeft = GetPixel(IMAGEMANAGER->findImage("inGameInfoPX")->getMemDC(), _player->GetRC().left, _player->GetY() - 90);
		int rLeft = GetRValue(colorLeft);
		int gLeft = GetGValue(colorLeft);
		int bLeft = GetBValue(colorLeft);
		if ((rLeft == 0 && gLeft == 255 && bLeft == 0))
		{
			_player->SetX(720);
			beforMap = 정보방;
			currentMap = 첫번째방;
			mapChangeFrame = 800;
		}
		if ((rLeft == 255 && gLeft == 0 && bLeft == 0))
		{
			_player->SetX(90);
		}
		COLORREF colorBottom = GetPixel(IMAGEMANAGER->findImage("inGameInfoPX")->getMemDC(), _player->GetX(), _player->GetRC().bottom - 90);
		int rBottom = GetRValue(colorBottom);
		int gBottom = GetGValue(colorBottom);
		int bBottom = GetBValue(colorBottom);
		if ((rBottom == 255 && gBottom == 0 && bBottom == 0))
		{
			_player->SetY(520);
		}
	}

	if (currentMap == 첫번째방)
	{
		COLORREF colorTop = GetPixel(IMAGEMANAGER->findImage("firstMapPX")->getMemDC(), _player->GetX(), _player->GetRC().top - 90);
		int rTop = GetRValue(colorTop);
		int gTop = GetGValue(colorTop);
		int bTop = GetBValue(colorTop);
		if ((rTop == 255 && gTop == 0 && bTop == 0) && doorChangeFrame == 300)
		{
			_player->SetY(180);
		}
		COLORREF colorRight = GetPixel(IMAGEMANAGER->findImage("firstMapPX")->getMemDC(), _player->GetRC().right, _player->GetY() - 90);
		int rRight = GetRValue(colorRight);
		int gRight = GetGValue(colorRight);
		int bRight = GetBValue(colorRight);
		if ((rRight == 0 && gRight == 255 && bRight == 0) && doorChangeFrame == 300)
		{
			_player->SetX(80);
			beforMap = 첫번째방;
			currentMap = 정보방;
			mapChangeFrame = 0;
			doorChangeFrame = 0;
		}
		if ((rRight == 255 && gRight == 0 && bRight == 0) && doorChangeFrame == 300)
		{
			_player->SetX(715);
		}
		COLORREF colorLeft = GetPixel(IMAGEMANAGER->findImage("firstMapPX")->getMemDC(), _player->GetRC().left, _player->GetY() - 90);
		int rLeft = GetRValue(colorLeft);
		int gLeft = GetGValue(colorLeft);
		int bLeft = GetBValue(colorLeft);
		if ((rLeft == 0 && gLeft == 255 && bLeft == 0) && doorChangeFrame == 300)
		{
			_player->SetX(720);
			beforMap = 첫번째방;
			currentMap = 두번째방;
			doorChangeFrame = 0;
			mapChangeFrame = 800;
		}
		if ((rLeft == 255 && gLeft == 0 && bLeft == 0) && doorChangeFrame == 300)
		{
			_player->SetX(85);
		}
		COLORREF colorBottom = GetPixel(IMAGEMANAGER->findImage("firstMapPX")->getMemDC(), _player->GetX(), _player->GetRC().bottom - 90);
		int rBottom = GetRValue(colorBottom);
		int gBottom = GetGValue(colorBottom);
		int bBottom = GetBValue(colorBottom);
		if ((rBottom == 0 && gBottom == 255 && bBottom == 0) && doorChangeFrame == 300)
		{
			_player->SetY(180);
			beforMap = 첫번째방;
			currentMap = 세번째방;
			doorChangeFrame = 0;
			mapChangeFrame = 0;
		}
		if ((rBottom == 255 && gBottom == 0 && bBottom == 0) && doorChangeFrame == 300)
		{
			_player->SetY(520);
		}
	}

	//두번째방
	if (currentMap == 두번째방)
	{
		COLORREF colorTop = GetPixel(IMAGEMANAGER->findImage("secondMapPX")->getMemDC(), _player->GetX(), _player->GetRC().top - 90);
		int rTop = GetRValue(colorTop);
		int gTop = GetGValue(colorTop);
		int bTop = GetBValue(colorTop);
		if ((rTop == 255 && gTop == 0 && bTop == 0) && doorChangeFrame == 300)
		{
			_player->SetY(180);
		}
		COLORREF colorRight = GetPixel(IMAGEMANAGER->findImage("secondMapPX")->getMemDC(), _player->GetRC().right, _player->GetY() - 90);
		int rRight = GetRValue(colorRight);
		int gRight = GetGValue(colorRight);
		int bRight = GetBValue(colorRight);
		if ((rRight == 0 && gRight == 255 && bRight == 0) && doorChangeFrame == 300)
		{
			_player->SetX(80);
			beforMap = 두번째방;
			currentMap = 첫번째방;
			doorChangeFrame = 0;
			mapChangeFrame = 0;
		}
		if ((rRight == 255 && gRight == 0 && bRight == 0) && doorChangeFrame == 300)
		{
			_player->SetX(715);
		}
		COLORREF colorLeft = GetPixel(IMAGEMANAGER->findImage("secondMapPX")->getMemDC(), _player->GetRC().left, _player->GetY() - 90);
		int rLeft = GetRValue(colorLeft);
		int gLeft = GetGValue(colorLeft);
		int bLeft = GetBValue(colorLeft);

		if ((rLeft == 255 && gLeft == 0 && bLeft == 0) && doorChangeFrame == 300)
		{
			_player->SetX(85);
		}
		COLORREF colorBottom = GetPixel(IMAGEMANAGER->findImage("secondMapPX")->getMemDC(), _player->GetX(), _player->GetRC().bottom - 90);
		int rBottom = GetRValue(colorBottom);
		int gBottom = GetGValue(colorBottom);
		int bBottom = GetBValue(colorBottom);
		if ((rBottom == 255 && gBottom == 0 && bBottom == 0) && doorChangeFrame == 300)
		{
			_player->SetY(520);
		}
	}

	//세번째방
	if (currentMap == 세번째방)
	{
		COLORREF colorTop = GetPixel(IMAGEMANAGER->findImage("thirdMapPX")->getMemDC(), _player->GetX(), _player->GetRC().top - 90);
		int rTop = GetRValue(colorTop);
		int gTop = GetGValue(colorTop);
		int bTop = GetBValue(colorTop);
		if ((rTop == 0 && gTop == 255 && bTop == 0) && doorChangeFrame == 300)
		{
			_player->SetY(525);
			beforMap = 세번째방;
			currentMap = 첫번째방;
			doorChangeFrame = 0;
			mapChangeFrame = 510;
		}
		if ((rTop == 255 && gTop == 0 && bTop == 0) && doorChangeFrame == 300)
		{
			_player->SetY(180);
		}
		COLORREF colorRight = GetPixel(IMAGEMANAGER->findImage("thirdMapPX")->getMemDC(), _player->GetRC().right, _player->GetY() - 90);
		int rRight = GetRValue(colorRight);
		int gRight = GetGValue(colorRight);
		int bRight = GetBValue(colorRight);
		if ((rRight == 255 && gRight == 0 && bRight == 0) && doorChangeFrame == 300)
		{
			_player->SetX(715);
		}
		COLORREF colorLeft = GetPixel(IMAGEMANAGER->findImage("thirdMapPX")->getMemDC(), _player->GetRC().left, _player->GetY() - 90);
		int rLeft = GetRValue(colorLeft);
		int gLeft = GetGValue(colorLeft);
		int bLeft = GetBValue(colorLeft);

		if ((rLeft == 255 && gLeft == 0 && bLeft == 0) && doorChangeFrame == 300)
		{
			_player->SetX(85);
		}
		COLORREF colorBottom = GetPixel(IMAGEMANAGER->findImage("thirdMapPX")->getMemDC(), _player->GetX(), _player->GetRC().bottom - 90);
		int rBottom = GetRValue(colorBottom);
		int gBottom = GetGValue(colorBottom);
		int bBottom = GetBValue(colorBottom);
		if ((rBottom == 255 && gBottom == 0 && bBottom == 0) && doorChangeFrame == 300)
		{
			_player->SetY(520);
		}
	}

	//네번째방
	if (currentMap == 네번째방)
	{
		COLORREF colorTop = GetPixel(IMAGEMANAGER->findImage("fourthMapPX")->getMemDC(), _player->GetX(), _player->GetRC().top - 90);
		int rTop = GetRValue(colorTop);
		int gTop = GetGValue(colorTop);
		int bTop = GetBValue(colorTop);
		if ((rTop == 0 && gTop == 255 && bTop == 0) && doorChangeFrame == 300)
		{
			_player->SetY(525);
			beforMap = 네번째방;
			currentMap = 다섯번째방;
			doorChangeFrame = 0;
			mapChangeFrame = 510;
		}
		if ((rTop == 255 && gTop == 0 && bTop == 0) && doorChangeFrame == 300)
		{
			_player->SetY(180);
		}
		COLORREF colorRight = GetPixel(IMAGEMANAGER->findImage("fourthMapPX")->getMemDC(), _player->GetRC().right, _player->GetY() - 90);
		int rRight = GetRValue(colorRight);
		int gRight = GetGValue(colorRight);
		int bRight = GetBValue(colorRight);
		if ((rRight == 255 && gRight == 0 && bRight == 0) && doorChangeFrame == 300)
		{
			_player->SetX(710);
		}
		COLORREF colorLeft = GetPixel(IMAGEMANAGER->findImage("fourthMapPX")->getMemDC(), _player->GetRC().left, _player->GetY() - 90);
		int rLeft = GetRValue(colorLeft);
		int gLeft = GetGValue(colorLeft);
		int bLeft = GetBValue(colorLeft);
		if ((rLeft == 255 && gLeft == 0 && bLeft == 0) && doorChangeFrame == 300)
		{
			_player->SetX(90);
		}
		COLORREF colorBottom = GetPixel(IMAGEMANAGER->findImage("fourthMapPX")->getMemDC(), _player->GetX(), _player->GetRC().bottom - 90);
		int rBottom = GetRValue(colorBottom);
		int gBottom = GetGValue(colorBottom);
		int bBottom = GetBValue(colorBottom);
		if ((rBottom == 0 && gBottom == 255 && bBottom == 0) && doorChangeFrame == 300)
		{
			_player->SetY(180);
			beforMap = 네번째방;
			currentMap = 정보방;
			doorChangeFrame = 0;
			mapChangeFrame = 0;
		}
		if ((rBottom == 255 && gBottom == 0 && bBottom == 0) && doorChangeFrame == 300)
		{
			_player->SetY(520);
		}
	}

	//다섯번째방
	if (currentMap == 다섯번째방)
	{
		COLORREF colorTop = GetPixel(IMAGEMANAGER->findImage("fifthMapPX")->getMemDC(), _player->GetX(), _player->GetRC().top - 90);
		int rTop = GetRValue(colorTop);
		int gTop = GetGValue(colorTop);
		int bTop = GetBValue(colorTop);
		if ((rTop == 255 && gTop == 0 && bTop == 0) && doorChangeFrame == 300)
		{
			_player->SetY(180);
		}
		COLORREF colorRight = GetPixel(IMAGEMANAGER->findImage("fifthMapPX")->getMemDC(), _player->GetRC().right, _player->GetY() - 90);
		int rRight = GetRValue(colorRight);
		int gRight = GetGValue(colorRight);
		int bRight = GetBValue(colorRight);
		if ((rRight == 255 && gRight == 0 && bRight == 0) && doorChangeFrame == 300)
		{
			_player->SetX(710);
		}
		COLORREF colorLeft = GetPixel(IMAGEMANAGER->findImage("fifthMapPX")->getMemDC(), _player->GetRC().left, _player->GetY() - 90);
		int rLeft = GetRValue(colorLeft);
		int gLeft = GetGValue(colorLeft);
		int bLeft = GetBValue(colorLeft);

		if ((rLeft == 255 && gLeft == 0 && bLeft == 0) && doorChangeFrame == 300)
		{
			_player->SetX(85);
		}
		COLORREF colorBottom = GetPixel(IMAGEMANAGER->findImage("fifthMapPX")->getMemDC(), _player->GetX(), _player->GetRC().bottom - 90);
		int rBottom = GetRValue(colorBottom);
		int gBottom = GetGValue(colorBottom);
		int bBottom = GetBValue(colorBottom);
		if ((rBottom == 0 && gBottom == 255 && bBottom == 0) && doorChangeFrame == 300)
		{
			_player->SetY(180);
			beforMap = 다섯번째방;
			currentMap = 네번째방;
			doorChangeFrame = 0;
			mapChangeFrame = 0;
		}
		if ((rBottom == 255 && gBottom == 0 && bBottom == 0) && doorChangeFrame == 300)
		{
			_player->SetY(520);
		}
	}

	//여섯번째방
	if (currentMap == 여섯번째방)
	{
		COLORREF colorTop = GetPixel(IMAGEMANAGER->findImage("sixthMapPX")->getMemDC(), _player->GetX(), _player->GetRC().top - 90);
		int rTop = GetRValue(colorTop);
		int gTop = GetGValue(colorTop);
		int bTop = GetBValue(colorTop);
		if ((rTop == 255 && gTop == 0 && bTop == 0) && doorChangeFrame == 300)
		{
			_player->SetY(180);
		}
		COLORREF colorRight = GetPixel(IMAGEMANAGER->findImage("sixthMapPX")->getMemDC(), _player->GetRC().right, _player->GetY() - 90);
		int rRight = GetRValue(colorRight);
		int gRight = GetGValue(colorRight);
		int bRight = GetBValue(colorRight);
		if ((rRight == 0 && gRight == 255 && bRight == 0) && doorChangeFrame == 300)
		{
			_player->SetX(80);
			beforMap = 여섯번째방;
			currentMap = 일곱번째방;
			doorChangeFrame = 0;
			mapChangeFrame = 0;
		}
		if ((rRight == 255 && gRight == 0 && bRight == 0) && doorChangeFrame == 300)
		{
			_player->SetX(710);
		}
		COLORREF colorLeft = GetPixel(IMAGEMANAGER->findImage("sixthMapPX")->getMemDC(), _player->GetRC().left, _player->GetY() - 90);
		int rLeft = GetRValue(colorLeft);
		int gLeft = GetGValue(colorLeft);
		int bLeft = GetBValue(colorLeft);
		if ((rLeft == 0 && gLeft == 255 && bLeft == 0))
		{
			_player->SetX(720);
			beforMap = 여섯번째방;
			currentMap = 정보방;
			mapChangeFrame = 800;
			doorChangeFrame = 0;
		}
		if ((rLeft == 255 && gLeft == 0 && bLeft == 0) && doorChangeFrame == 300)
		{
			_player->SetX(90);
		}
		COLORREF colorBottom = GetPixel(IMAGEMANAGER->findImage("sixthMapPX")->getMemDC(), _player->GetX(), _player->GetRC().bottom - 90);
		int rBottom = GetRValue(colorBottom);
		int gBottom = GetGValue(colorBottom);
		int bBottom = GetBValue(colorBottom);
		if ((rBottom == 0 && gBottom == 255 && bBottom == 0) && doorChangeFrame == 300)
		{
			_player->SetY(180);
			beforMap = 여섯번째방;
			currentMap = 여덟번째방;
			doorChangeFrame = 0;
			mapChangeFrame = 0;
		}
		if ((rBottom == 255 && gBottom == 0 && bBottom == 0) && doorChangeFrame == 300)
		{
			_player->SetY(520);
		}
	}

	//일곱번째방
	if (currentMap == 일곱번째방)
	{
		COLORREF colorTop = GetPixel(IMAGEMANAGER->findImage("seventhMapPX")->getMemDC(), _player->GetX(), _player->GetRC().top - 90);
		int rTop = GetRValue(colorTop);
		int gTop = GetGValue(colorTop);
		int bTop = GetBValue(colorTop);
		if ((rTop == 255 && gTop == 0 && bTop == 0) && doorChangeFrame == 300)
		{
			_player->SetY(180);
		}
		COLORREF colorRight = GetPixel(IMAGEMANAGER->findImage("seventhMapPX")->getMemDC(), _player->GetRC().right, _player->GetY() - 90);
		int rRight = GetRValue(colorRight);
		int gRight = GetGValue(colorRight);
		int bRight = GetBValue(colorRight);
		if ((rRight == 255 && gRight == 0 && bRight == 0) && doorChangeFrame == 300)
		{
			_player->SetX(710);
		}
		COLORREF colorLeft = GetPixel(IMAGEMANAGER->findImage("seventhMapPX")->getMemDC(), _player->GetRC().left, _player->GetY() - 90);
		int rLeft = GetRValue(colorLeft);
		int gLeft = GetGValue(colorLeft);
		int bLeft = GetBValue(colorLeft);
		if ((rLeft == 0 && gLeft == 255 && bLeft == 0))
		{
			_player->SetX(720);
			beforMap = 일곱번째방;
			currentMap = 여섯번째방;
			mapChangeFrame = 800;
			doorChangeFrame = 0;
		}
		if ((rLeft == 255 && gLeft == 0 && bLeft == 0) && doorChangeFrame == 300)
		{
			_player->SetX(90);
		}
		COLORREF colorBottom = GetPixel(IMAGEMANAGER->findImage("seventhMapPX")->getMemDC(), _player->GetX(), _player->GetRC().bottom - 90);
		int rBottom = GetRValue(colorBottom);
		int gBottom = GetGValue(colorBottom);
		int bBottom = GetBValue(colorBottom);
		if ((rBottom == 255 && gBottom == 0 && bBottom == 0) && doorChangeFrame == 300)
		{
			_player->SetY(520);
		}
	}

	//여덟번째방
	if (currentMap == 여덟번째방)
	{
		COLORREF colorTop = GetPixel(IMAGEMANAGER->findImage("eighthMapPX")->getMemDC(), _player->GetX(), _player->GetRC().top - 90);
		int rTop = GetRValue(colorTop);
		int gTop = GetGValue(colorTop);
		int bTop = GetBValue(colorTop);
		if ((rTop == 0 && gTop == 255 && bTop == 0) && doorChangeFrame == 300)
		{
			_player->SetY(525);
			beforMap = 여덟번째방;
			currentMap = 여섯번째방;
			doorChangeFrame = 0;
			mapChangeFrame = 510;
		}
		if ((rTop == 255 && gTop == 0 && bTop == 0) && doorChangeFrame == 300)
		{
			_player->SetY(180);
		}
		COLORREF colorRight = GetPixel(IMAGEMANAGER->findImage("eighthMapPX")->getMemDC(), _player->GetRC().right, _player->GetY() - 90);
		int rRight = GetRValue(colorRight);
		int gRight = GetGValue(colorRight);
		int bRight = GetBValue(colorRight);
		if ((rRight == 255 && gRight == 0 && bRight == 0) && doorChangeFrame == 300)
		{
			_player->SetX(710);
		}
		COLORREF colorLeft = GetPixel(IMAGEMANAGER->findImage("eighthMapPX")->getMemDC(), _player->GetRC().left, _player->GetY() - 90);
		int rLeft = GetRValue(colorLeft);
		int gLeft = GetGValue(colorLeft);
		int bLeft = GetBValue(colorLeft);
		if ((rLeft == 255 && gLeft == 0 && bLeft == 0) && doorChangeFrame == 300)
		{
			_player->SetX(90);
		}
		COLORREF colorBottom = GetPixel(IMAGEMANAGER->findImage("eighthMapPX")->getMemDC(), _player->GetX(), _player->GetRC().bottom - 90);
		int rBottom = GetRValue(colorBottom);
		int gBottom = GetGValue(colorBottom);
		int bBottom = GetBValue(colorBottom);
		if ((rBottom == 255 && gBottom == 0 && bBottom == 0) && doorChangeFrame == 300)
		{
			_player->SetY(520);
		}
	}
}

void cSceneManager::mapChangeRender(void)
{
	if (currentMap == 정보방)
	{
		if (beforMap == 첫번째방)
		{
			mapChangeFrame += 40;
			if (mapChangeFrame >= 800)
			{
				mapChangeFrame = 800;
			}
			IMAGEMANAGER->render("inGameInfo", getMemDC(), 0, 90, mapChangeFrame - 800, 0, 800, 510);
			IMAGEMANAGER->render("firstMap", getMemDC(), 0, 90, mapChangeFrame, 0, 800, 510);
			IMAGEMANAGER->render("inGameInfoMini", getMemDC());
			if (isPixel == true)
			{
				IMAGEMANAGER->render("inGameInfoPX", getMemDC(), 0, 90, mapChangeFrame - 800, 0, 800, 510);
			}
		}
		if (beforMap == 네번째방)
		{
			mapChangeFrame += 30;
			if (mapChangeFrame >= 510)
			{
				mapChangeFrame = 510;
			}
			IMAGEMANAGER->render("fourthMap", getMemDC(), 0, 90, 0, mapChangeFrame, 800, 510);
			IMAGEMANAGER->render("inGameInfo", getMemDC(), 0, 90, 0, mapChangeFrame - 510, 800, 510);
			if (isPixel == true)
			{
				IMAGEMANAGER->render("inGameInfoPX", getMemDC(), 0, 90, 0, mapChangeFrame - 510, 800, 510);
			}
		}

		if (beforMap == 여섯번째방)
		{
			mapChangeFrame -= 40;
			if (mapChangeFrame <= 0)
			{
				mapChangeFrame = 0;
			}
			IMAGEMANAGER->render("inGameInfo", getMemDC(), 0, 90, mapChangeFrame, 0, 800, 510);
			IMAGEMANAGER->render("sixthMap", getMemDC(), 0, 90, mapChangeFrame - 800, 0, 800, 510);
			IMAGEMANAGER->render("inGameInfoMini", getMemDC());
			if (isPixel == true)
			{
				IMAGEMANAGER->render("inGameInfoPX", getMemDC(), 0, 90, mapChangeFrame - 800, 0, 800, 510);
			}
		}

		if (beforMap == 정보방)
		{
			IMAGEMANAGER->alphaRender("inGameInfo", getMemDC(), 0, 90, inGameAlpha);
			IMAGEMANAGER->alphaRender("inGameInfoMini", getMemDC(), inGameAlpha);
			if (isPixel == true)
			{
				IMAGEMANAGER->alphaRender("inGameInfoPX", getMemDC(), 0, 90, inGameAlpha);
			}
		}
	}

	//첫번째방(정보방 왼쪽방)
	if (currentMap == 첫번째방)
	{
		if (beforMap == 정보방)
		{
			mapChangeFrame -= 40;
			if (mapChangeFrame <= 0)
			{
				mapChangeFrame = 0;
			}
			IMAGEMANAGER->render("inGameInfo", getMemDC(), 0, 90, mapChangeFrame - 800, 0, 800, 510);
			IMAGEMANAGER->render("firstMap", getMemDC(), 0, 90, mapChangeFrame, 0, 800, 510);
			IMAGEMANAGER->render("firstMapMini", getMemDC());
			if (mapChangeFrame == 0)
			{
				if (time % 6 == 0)
				{
					doorChangeFrame += 100;
					if (doorChangeFrame >= 300)
					{
						doorChangeFrame = 300;
					}
				}
				IMAGEMANAGER->render("doorRight", getMemDC(), 700, 260, doorChangeFrame, 0, 100, 170);
				IMAGEMANAGER->render("doorLeft", getMemDC(), 0, 260, 300 - doorChangeFrame, 0, 100, 170);
				IMAGEMANAGER->render("doorBottom", getMemDC(), 320, 500, 0, doorChangeFrame, 170, 100);
			}
			if (isPixel == true)
			{
				IMAGEMANAGER->render("firstMapPX", getMemDC(), 0, 90, mapChangeFrame, 0, 800, 510);
			}
		}
		if (beforMap == 두번째방)
		{
			mapChangeFrame += 40;
			if (mapChangeFrame >= 800)
			{
				mapChangeFrame = 800;
			}
			IMAGEMANAGER->render("secondMap", getMemDC(), 0, 90, mapChangeFrame, 0, 800, 510);
			IMAGEMANAGER->render("firstMap", getMemDC(), 0, 90, mapChangeFrame - 800, 0, 800, 510);
			IMAGEMANAGER->render("firstMapMini", getMemDC());
			if (mapChangeFrame == 800)
			{
				if (time % 6 == 0)
				{
					doorChangeFrame += 100;
					if (doorChangeFrame >= 300)
					{
						doorChangeFrame = 300;
					}
				}
				IMAGEMANAGER->render("doorRight", getMemDC(), 700, 260, doorChangeFrame, 0, 100, 170);
				IMAGEMANAGER->render("doorLeft", getMemDC(), 0, 260, 300 - doorChangeFrame, 0, 100, 170);
				IMAGEMANAGER->render("doorBottom", getMemDC(), 320, 500, 0, doorChangeFrame, 170, 100);
			}
			if (isPixel == true)
			{
				IMAGEMANAGER->render("firstMapPX", getMemDC(), 0, 90, mapChangeFrame - 800, 0, 800, 510);
			}

		}
		if (beforMap == 세번째방)
		{
			mapChangeFrame -= 30;
			if (mapChangeFrame <= 0)
			{
				mapChangeFrame = 0;
			}
			IMAGEMANAGER->render("thirdMap", getMemDC(), 0, 90, 0, mapChangeFrame - 510, 800, 510);
			IMAGEMANAGER->render("firstMap", getMemDC(), 0, 90, 0, mapChangeFrame, 800, 510);
			/*IMAGEMANAGER->render("firstMapMini", getMemDC());*/
			if (mapChangeFrame == 0)
			{
				if (time % 6 == 0)
				{
					doorChangeFrame += 100;
					if (doorChangeFrame >= 300)
					{
						doorChangeFrame = 300;
					}
				}
				IMAGEMANAGER->render("doorRight", getMemDC(), 700, 260, doorChangeFrame, 0, 100, 170);
				IMAGEMANAGER->render("doorLeft", getMemDC(), 0, 260, 300 - doorChangeFrame, 0, 100, 170);
				IMAGEMANAGER->render("doorBottom", getMemDC(), 320, 500, 0, doorChangeFrame, 170, 100);
			}
			if (isPixel == true)
			{
				IMAGEMANAGER->render("firstMapPX", getMemDC(), 0, 90, 0, mapChangeFrame, 800, 510);
			}
		}
	}

	if (currentMap == 두번째방)
	{
		if (beforMap == 첫번째방)
		{
			mapChangeFrame -= 40;
			if (mapChangeFrame <= 0)
			{
				mapChangeFrame = 0;
			}
			IMAGEMANAGER->render("firstMap", getMemDC(), 0, 90, mapChangeFrame - 800, 0, 800, 510);
			IMAGEMANAGER->render("secondMap", getMemDC(), 0, 90, mapChangeFrame, 0, 800, 510);
			/*IMAGEMANAGER->render("firstMapMini", getMemDC());*/
			if (mapChangeFrame == 0)
			{
				if (time % 6 == 0)
				{
					doorChangeFrame += 100;
					if (doorChangeFrame >= 300)
					{
						doorChangeFrame = 300;
					}
				}
				IMAGEMANAGER->render("doorRight", getMemDC(), 700, 260, doorChangeFrame, 0, 100, 170);
			}
			if (isPixel == true)
			{
				IMAGEMANAGER->render("secondMapPX", getMemDC(), 0, 90, mapChangeFrame, 0, 800, 510);
			}
		}
	}

	//세번째방
	if (currentMap == 세번째방)
	{
		if (beforMap == 첫번째방)
		{
			mapChangeFrame += 30;
			if (mapChangeFrame >= 510)
			{
				mapChangeFrame = 510;
			}
			IMAGEMANAGER->render("firstMap", getMemDC(), 0, 90, 0, mapChangeFrame, 800, 510);
			IMAGEMANAGER->render("thirdMap", getMemDC(), 0, 90, 0, mapChangeFrame - 510, 800, 510);
			/*IMAGEMANAGER->render("firstMapMini", getMemDC());*/
			if (mapChangeFrame == 510)
			{
				if (time % 6 == 0)
				{
					doorChangeFrame += 100;
					if (doorChangeFrame >= 300)
					{
						doorChangeFrame = 300;
					}
				}
				IMAGEMANAGER->render("doorTop", getMemDC(), 320, 100, 0, 300 - doorChangeFrame, 170, 100);
			}
			if (isPixel == true)
			{
				IMAGEMANAGER->render("thirdMapPX", getMemDC(), 0, 90, 0, mapChangeFrame - 510, 800, 510);
			}
		}
	}

	//네번째방
	if (currentMap == 네번째방)
	{
		if (beforMap == 정보방)
		{
			mapChangeFrame -= 30;
			if (mapChangeFrame <= 0)
			{
				mapChangeFrame = 0;
			}
			IMAGEMANAGER->render("inGameInfo", getMemDC(), 0, 90, 0, mapChangeFrame - 510, 800, 510);
			IMAGEMANAGER->render("fourthMap", getMemDC(), 0, 90, 0, mapChangeFrame, 800, 510);
			/*IMAGEMANAGER->render("firstMapMini", getMemDC());*/
			if (mapChangeFrame == 0)
			{
				if (time % 6 == 0)
				{
					doorChangeFrame += 100;
					if (doorChangeFrame >= 300)
					{
						doorChangeFrame = 300;
					}
				}
				IMAGEMANAGER->render("doorTop", getMemDC(), 320, 100, 0, 300 - doorChangeFrame, 170, 100);
				IMAGEMANAGER->render("doorBottom", getMemDC(), 320, 500, 0, doorChangeFrame, 170, 100);
			}
			if (isPixel == true)
			{
				IMAGEMANAGER->render("fourthMapPX", getMemDC(), 0, 90, 0, mapChangeFrame, 800, 510);
			}
		}
		if (beforMap == 다섯번째방)
		{
			mapChangeFrame += 30;
			if (mapChangeFrame >= 510)
			{
				mapChangeFrame = 510;
			}
			IMAGEMANAGER->render("fifthMap", getMemDC(), 0, 90, 0, mapChangeFrame, 800, 510);
			IMAGEMANAGER->render("fourthMap", getMemDC(), 0, 90, 0, mapChangeFrame - 510, 800, 510);

			if (mapChangeFrame == 510)
			{
				if (time % 6 == 0)
				{
					doorChangeFrame += 100;
					if (doorChangeFrame >= 300)
					{
						doorChangeFrame = 300;
					}
				}
				IMAGEMANAGER->render("doorTop", getMemDC(), 320, 100, 0, 300 - doorChangeFrame, 170, 100);
				IMAGEMANAGER->render("doorBottom", getMemDC(), 320, 500, 0, doorChangeFrame, 170, 100);
			}
			if (isPixel == true)
			{
				IMAGEMANAGER->render("fourthMapPX", getMemDC(), 0, 90, 0, mapChangeFrame - 510, 800, 510);
			}
		}
	}

	//다섯번째방
	if (currentMap == 다섯번째방)
	{
		if (beforMap == 네번째방)
		{
			mapChangeFrame -= 30;
			if (mapChangeFrame <= 0)
			{
				mapChangeFrame = 0;
			}
			IMAGEMANAGER->render("fourthMap", getMemDC(), 0, 90, 0, mapChangeFrame - 510, 800, 510);
			IMAGEMANAGER->render("fifthMap", getMemDC(), 0, 90, 0, mapChangeFrame, 800, 510);
			/*IMAGEMANAGER->render("firstMapMini", getMemDC());*/
			if (mapChangeFrame == 0)
			{
				if (time % 6 == 0)
				{
					doorChangeFrame += 100;
					if (doorChangeFrame >= 300)
					{
						doorChangeFrame = 300;
					}
				}
				IMAGEMANAGER->render("doorBottom", getMemDC(), 320, 500, 0, doorChangeFrame, 170, 100);
			}
			if (isPixel == true)
			{
				IMAGEMANAGER->render("fifthMapPX", getMemDC(), 0, 90, 0, mapChangeFrame, 800, 510);
			}

		}
	}
	//여섯번째방(정보방 오른쪽방)
	if (currentMap == 여섯번째방)
	{
		if (beforMap == 정보방)
		{
			mapChangeFrame += 40;
			if (mapChangeFrame >= 800)
			{
				mapChangeFrame = 800;
			}
			IMAGEMANAGER->render("inGameInfo", getMemDC(), 0, 90, mapChangeFrame, 0, 800, 510);
			IMAGEMANAGER->render("sixthMap", getMemDC(), 0, 90, mapChangeFrame - 800, 0, 800, 510);
			IMAGEMANAGER->render("sixthMapMini", getMemDC());
			if (mapChangeFrame == 800)
			{
				if (time % 6 == 0)
				{
					doorChangeFrame += 100;
					if (doorChangeFrame >= 300)
					{
						doorChangeFrame = 300;
					}
				}
				IMAGEMANAGER->render("doorLeft", getMemDC(), 0, 260, 300 - doorChangeFrame, 0, 100, 170);
				IMAGEMANAGER->render("doorRight", getMemDC(), 700, 260, doorChangeFrame, 0, 100, 170);
				IMAGEMANAGER->render("doorBottom", getMemDC(), 320, 500, 0, doorChangeFrame, 170, 100);
			}
			if (isPixel == true)
			{
				IMAGEMANAGER->render("sixthMapPX", getMemDC(), 0, 90, mapChangeFrame - 800, 0, 800, 510);
			}
		}

		if (beforMap == 일곱번째방)
		{
			mapChangeFrame -= 40;
			if (mapChangeFrame <= 0)
			{
				mapChangeFrame = 0;
			}
			IMAGEMANAGER->render("seventhMap", getMemDC(), 0, 90, mapChangeFrame - 800, 0, 800, 510);
			IMAGEMANAGER->render("sixthMap", getMemDC(), 0, 90, mapChangeFrame, 0, 800, 510);
			/*IMAGEMANAGER->render("firstMapMini", getMemDC());*/
			if (mapChangeFrame == 0)
			{
				if (time % 6 == 0)
				{
					doorChangeFrame += 100;
					if (doorChangeFrame >= 300)
					{
						doorChangeFrame = 300;
					}
				}
				IMAGEMANAGER->render("doorLeft", getMemDC(), 0, 260, 300 - doorChangeFrame, 0, 100, 170);
				IMAGEMANAGER->render("doorRight", getMemDC(), 700, 260, doorChangeFrame, 0, 100, 170);
				IMAGEMANAGER->render("doorBottom", getMemDC(), 320, 500, 0, doorChangeFrame, 170, 100);
			}
			if (isPixel == true)
			{
				IMAGEMANAGER->render("sixthMapPX", getMemDC(), 0, 90, mapChangeFrame, 0, 800, 510);
			}
		}

		if (beforMap == 여덟번째방)
		{
			mapChangeFrame -= 30;
			if (mapChangeFrame <= 0)
			{
				mapChangeFrame = 0;
			}
			IMAGEMANAGER->render("eighthMap", getMemDC(), 0, 90, 0, mapChangeFrame - 510, 800, 510);
			IMAGEMANAGER->render("sixthMap", getMemDC(), 0, 90, 0, mapChangeFrame, 800, 510);
			/*IMAGEMANAGER->render("firstMapMini", getMemDC());*/
			if (mapChangeFrame == 0)
			{
				if (time % 6 == 0)
				{
					doorChangeFrame += 100;
					if (doorChangeFrame >= 300)
					{
						doorChangeFrame = 300;
					}
				}
				IMAGEMANAGER->render("doorLeft", getMemDC(), 0, 260, 300 - doorChangeFrame, 0, 100, 170);
				IMAGEMANAGER->render("doorRight", getMemDC(), 700, 260, doorChangeFrame, 0, 100, 170);
				IMAGEMANAGER->render("doorBottom", getMemDC(), 320, 500, 0, doorChangeFrame, 170, 100);
			}
			if (isPixel == true)
			{
				IMAGEMANAGER->render("sixthMapPX", getMemDC(), 0, 90, 0, mapChangeFrame, 800, 510);
			}
		}
	}

	//일곱번째방
	if (currentMap == 일곱번째방)
	{
		if (beforMap == 여섯번째방)
		{
			mapChangeFrame += 40;
			if (mapChangeFrame >= 800)
			{
				mapChangeFrame = 800;
			}
			IMAGEMANAGER->render("sixthMap", getMemDC(), 0, 90, mapChangeFrame, 0, 800, 510);
			IMAGEMANAGER->render("seventhMap", getMemDC(), 0, 90, mapChangeFrame - 800, 0, 800, 510);
			if (mapChangeFrame == 800)
			{
				if (time % 6 == 0)
				{
					doorChangeFrame += 100;
					if (doorChangeFrame >= 300)
					{
						doorChangeFrame = 300;
					}
				}
				IMAGEMANAGER->render("doorLeft", getMemDC(), 0, 260, 300 - doorChangeFrame, 0, 100, 170);
			}
			if (isPixel == true)
			{
				IMAGEMANAGER->render("seventhMapPX", getMemDC(), 0, 90, mapChangeFrame - 800, 0, 800, 510);
			}
		}
	}

	//여덟번째방
	if (currentMap == 여덟번째방)
	{
		if (beforMap == 여섯번째방)
		{
			mapChangeFrame += 30;
			if (mapChangeFrame >= 510)
			{
				mapChangeFrame = 510;
			}
			IMAGEMANAGER->render("sixthMap", getMemDC(), 0, 90, 0, mapChangeFrame, 800, 510);
			IMAGEMANAGER->render("eighthMap", getMemDC(), 0, 90, 0, mapChangeFrame - 510, 800, 510);
			/*IMAGEMANAGER->render("firstMapMini", getMemDC());*/
			if (mapChangeFrame == 510)
			{
				if (time % 6 == 0)
				{
					doorChangeFrame += 100;
					if (doorChangeFrame >= 300)
					{
						doorChangeFrame = 300;
					}
				}
				IMAGEMANAGER->render("doorTop", getMemDC(), 320, 100, 0, 300 - doorChangeFrame, 170, 100);
			}
			if (isPixel == true)
			{
				IMAGEMANAGER->render("eighthMapPX", getMemDC(), 0, 90, 0, mapChangeFrame - 510, 800, 510);
			}
		}
	}
}

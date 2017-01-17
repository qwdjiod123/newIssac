#include "stdafx.h"
#include "cSceneManager.h"
#include"cPlayer.h"
#include"cItemManager.h"



HRESULT cSceneManager::init(void)
{
	beforMap = ������;
	currentMap = ������;
	_player->SetX(WINSIZEX / 2);
	_player->SetY(WINSIZEY / 2);

	for (int i = 0; i < MAPMAX; i++)
	{
		ItemSetting[i] = false;

	}

	inGameAlpha = 0;
	isMapChange = false;
	isPixel = false;
	isDoorState = ����;
	doorChangeFrame = 0;
	mapChangeFrame = 0;
	isInfo = false;
	isFirst = false;
	isSecond = false;
	isThird = false;
	isFourth = false;
	isFifth = false;
	isSixth = false;
	isSeventh = false;
	isEighth = false;

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
	HFONT font;
	HFONT o_font;
	font = CreateFont(20, 0, 0, 0, FW_NORMAL, 0, 0, 0, ANSI_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT("IMPACT"));
	o_font = (HFONT)SelectObject(getMemDC(), font);
	SetTextColor(getMemDC(), RGB(255, 255, 255));
	SetBkMode(getMemDC(), TRANSPARENT);
	IMAGEMANAGER->alphaRender("UI", getMemDC(), inGameAlpha);
	mapChangeRender();
	mapMiniRender();
	hpUiRender();

	//�׽�Ʈ
	sprintf(buffer, TEXT("0%d"), _player->GetMoney());
	TextOut(getMemDC(), 360, 12, buffer, lstrlen(buffer));
	sprintf(buffer, TEXT("0%d"), _player->GetBomb());
	TextOut(getMemDC(), 360, 37, buffer, lstrlen(buffer));
	sprintf(buffer, TEXT("0%d"), _player->GetKey());
	TextOut(getMemDC(), 360, 62, buffer, lstrlen(buffer));

}

void cSceneManager::mapChangeUpdate(void)
{
	if (currentMap == ������)
	{
		isInfo = true;
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
			beforMap = ������;
			currentMap = �׹�°��;
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
			beforMap = ������;
			currentMap = ������°��;
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
			beforMap = ������;
			currentMap = ù��°��;
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

	if (currentMap == ù��°��)
	{
		isFirst = true;
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
			beforMap = ù��°��;
			currentMap = ������;
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
			beforMap = ù��°��;
			currentMap = �ι�°��;
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
			beforMap = ù��°��;
			currentMap = ����°��;
			doorChangeFrame = 0;
			mapChangeFrame = 0;
		}
		if ((rBottom == 255 && gBottom == 0 && bBottom == 0) && doorChangeFrame == 300)
		{
			_player->SetY(520);
		}
	}

	//�ι�°��
	if (currentMap == �ι�°��)
	{
		isSecond = true;
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
			beforMap = �ι�°��;
			currentMap = ù��°��;
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

	//����°��
	if (currentMap == ����°��)
	{
		isThird = true;
		COLORREF colorTop = GetPixel(IMAGEMANAGER->findImage("thirdMapPX")->getMemDC(), _player->GetX(), _player->GetRC().top - 90);
		int rTop = GetRValue(colorTop);
		int gTop = GetGValue(colorTop);
		int bTop = GetBValue(colorTop);
		if ((rTop == 0 && gTop == 255 && bTop == 0) && doorChangeFrame == 300)
		{
			_player->SetY(525);
			beforMap = ����°��;
			currentMap = ù��°��;
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

	//�׹�°��
	if (currentMap == �׹�°��)
	{
		isFourth = true;
		COLORREF colorTop = GetPixel(IMAGEMANAGER->findImage("fourthMapPX")->getMemDC(), _player->GetX(), _player->GetRC().top - 90);
		int rTop = GetRValue(colorTop);
		int gTop = GetGValue(colorTop);
		int bTop = GetBValue(colorTop);
		if ((rTop == 0 && gTop == 255 && bTop == 0) && doorChangeFrame == 300)
		{
			_player->SetY(525);
			beforMap = �׹�°��;
			currentMap = �ټ���°��;
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
			beforMap = �׹�°��;
			currentMap = ������;
			doorChangeFrame = 0;
			mapChangeFrame = 0;
		}
		if ((rBottom == 255 && gBottom == 0 && bBottom == 0) && doorChangeFrame == 300)
		{
			_player->SetY(520);
		}
	}

	//�ټ���°��
	if (currentMap == �ټ���°��)
	{
		isFifth = true;
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
			beforMap = �ټ���°��;
			currentMap = �׹�°��;
			doorChangeFrame = 0;
			mapChangeFrame = 0;
		}
		if ((rBottom == 255 && gBottom == 0 && bBottom == 0) && doorChangeFrame == 300)
		{
			_player->SetY(520);
		}
	}

	//������°��
	if (currentMap == ������°��)
	{
		isSixth = true;
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
			beforMap = ������°��;
			currentMap = �ϰ���°��;
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
			beforMap = ������°��;
			currentMap = ������;
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
			beforMap = ������°��;
			currentMap = ������°��;
			doorChangeFrame = 0;
			mapChangeFrame = 0;
		}
		if ((rBottom == 255 && gBottom == 0 && bBottom == 0) && doorChangeFrame == 300)
		{
			_player->SetY(520);
		}
	}

	//�ϰ���°��
	if (currentMap == �ϰ���°��)
	{
		isSeventh = true;
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
			beforMap = �ϰ���°��;
			currentMap = ������°��;
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

	//������°��
	if (currentMap == ������°��)
	{
		isEighth = true;
		COLORREF colorTop = GetPixel(IMAGEMANAGER->findImage("eighthMapPX")->getMemDC(), _player->GetX(), _player->GetRC().top - 90);
		int rTop = GetRValue(colorTop);
		int gTop = GetGValue(colorTop);
		int bTop = GetBValue(colorTop);
		if ((rTop == 0 && gTop == 255 && bTop == 0) && doorChangeFrame == 300)
		{
			_player->SetY(525);
			beforMap = ������°��;
			currentMap = ������°��;
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
	if (currentMap == ������)
	{
		if (beforMap == ù��°��)
		{
			mapChangeFrame += 40;
			if (mapChangeFrame >= 800)
			{
				mapChangeFrame = 800;
			}
			IMAGEMANAGER->render("inGameInfo", getMemDC(), 0, 90, mapChangeFrame - 800, 0, 800, 510);
			IMAGEMANAGER->render("firstMap", getMemDC(), 0, 90, mapChangeFrame, 0, 800, 510);
			if (isPixel == true)
			{
				IMAGEMANAGER->render("inGameInfoPX", getMemDC(), 0, 90, mapChangeFrame - 800, 0, 800, 510);
			}
		}
		if (beforMap == �׹�°��)
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

		if (beforMap == ������°��)
		{
			mapChangeFrame -= 40;
			if (mapChangeFrame <= 0)
			{
				mapChangeFrame = 0;
			}
			IMAGEMANAGER->render("inGameInfo", getMemDC(), 0, 90, mapChangeFrame, 0, 800, 510);
			IMAGEMANAGER->render("sixthMap", getMemDC(), 0, 90, mapChangeFrame - 800, 0, 800, 510);
			if (isPixel == true)
			{
				IMAGEMANAGER->render("inGameInfoPX", getMemDC(), 0, 90, mapChangeFrame, 0, 800, 510);
			}
		}

		if (beforMap == ������)
		{

			IMAGEMANAGER->alphaRender("inGameInfo", getMemDC(), 0, 90, inGameAlpha);

			if (isPixel == true)
			{
				IMAGEMANAGER->alphaRender("inGameInfoPX", getMemDC(), 0, 90, inGameAlpha);
			}
		}
	}

	//ù��°��(������ ���ʹ�)
	if (currentMap == ù��°��)
	{
		if (beforMap == ������)
		{
			mapChangeFrame -= 40;
			if (mapChangeFrame <= 0)
			{
				mapChangeFrame = 0;
			}
			IMAGEMANAGER->render("inGameInfo", getMemDC(), 0, 90, mapChangeFrame - 800, 0, 800, 510);
			IMAGEMANAGER->render("firstMap", getMemDC(), 0, 90, mapChangeFrame, 0, 800, 510);

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
		if (beforMap == �ι�°��)
		{
			mapChangeFrame += 40;
			if (mapChangeFrame >= 800)
			{
				mapChangeFrame = 800;
			}
			IMAGEMANAGER->render("secondMap", getMemDC(), 0, 90, mapChangeFrame, 0, 800, 510);
			IMAGEMANAGER->render("firstMap", getMemDC(), 0, 90, mapChangeFrame - 800, 0, 800, 510);
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
		if (beforMap == ����°��)
		{
			mapChangeFrame -= 30;
			if (mapChangeFrame <= 0)
			{
				mapChangeFrame = 0;
			}
			IMAGEMANAGER->render("thirdMap", getMemDC(), 0, 90, 0, mapChangeFrame - 510, 800, 510);
			IMAGEMANAGER->render("firstMap", getMemDC(), 0, 90, 0, mapChangeFrame, 800, 510);
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

	if (currentMap == �ι�°��)
	{
		if (beforMap == ù��°��)
		{
			mapChangeFrame -= 40;
			if (mapChangeFrame <= 0)
			{
				mapChangeFrame = 0;
			}
			IMAGEMANAGER->render("firstMap", getMemDC(), 0, 90, mapChangeFrame - 800, 0, 800, 510);
			IMAGEMANAGER->render("secondMap", getMemDC(), 0, 90, mapChangeFrame, 0, 800, 510);
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

	//����°��
	if (currentMap == ����°��)
	{
		if (beforMap == ù��°��)
		{
			mapChangeFrame += 30;
			if (mapChangeFrame >= 510)
			{
				mapChangeFrame = 510;
			}
			IMAGEMANAGER->render("firstMap", getMemDC(), 0, 90, 0, mapChangeFrame, 800, 510);
			IMAGEMANAGER->render("thirdMap", getMemDC(), 0, 90, 0, mapChangeFrame - 510, 800, 510);

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

	//�׹�°��
	if (currentMap == �׹�°��)
	{
		if (beforMap == ������)
		{
			mapChangeFrame -= 30;
			if (mapChangeFrame <= 0)
			{
				mapChangeFrame = 0;
			}
			IMAGEMANAGER->render("inGameInfo", getMemDC(), 0, 90, 0, mapChangeFrame - 510, 800, 510);
			IMAGEMANAGER->render("fourthMap", getMemDC(), 0, 90, 0, mapChangeFrame, 800, 510);

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
		if (beforMap == �ټ���°��)
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

	//�ټ���°��
	if (currentMap == �ټ���°��)
	{
		if (beforMap == �׹�°��)
		{
			mapChangeFrame -= 30;
			if (mapChangeFrame <= 0)
			{
				mapChangeFrame = 0;
			}
			IMAGEMANAGER->render("fourthMap", getMemDC(), 0, 90, 0, mapChangeFrame - 510, 800, 510);
			IMAGEMANAGER->render("fifthMap", getMemDC(), 0, 90, 0, mapChangeFrame, 800, 510);
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
	//������°��(������ �����ʹ�)
	if (currentMap == ������°��)
	{
		if (beforMap == ������)
		{
			mapChangeFrame += 40;
			if (mapChangeFrame >= 800)
			{
				mapChangeFrame = 800;
			}
			IMAGEMANAGER->render("inGameInfo", getMemDC(), 0, 90, mapChangeFrame, 0, 800, 510);
			IMAGEMANAGER->render("sixthMap", getMemDC(), 0, 90, mapChangeFrame - 800, 0, 800, 510);
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

		if (beforMap == �ϰ���°��)
		{
			mapChangeFrame -= 40;
			if (mapChangeFrame <= 0)
			{
				mapChangeFrame = 0;
			}
			IMAGEMANAGER->render("seventhMap", getMemDC(), 0, 90, mapChangeFrame - 800, 0, 800, 510);
			IMAGEMANAGER->render("sixthMap", getMemDC(), 0, 90, mapChangeFrame, 0, 800, 510);
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

		if (beforMap == ������°��)
		{
			mapChangeFrame -= 30;
			if (mapChangeFrame <= 0)
			{
				mapChangeFrame = 0;
			}
			IMAGEMANAGER->render("eighthMap", getMemDC(), 0, 90, 0, mapChangeFrame - 510, 800, 510);
			IMAGEMANAGER->render("sixthMap", getMemDC(), 0, 90, 0, mapChangeFrame, 800, 510);
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

	//�ϰ���°��
	if (currentMap == �ϰ���°��)
	{
		if (beforMap == ������°��)
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

	//������°��
	if (currentMap == ������°��)
	{
		if (beforMap == ������°��)
		{
			mapChangeFrame += 30;
			if (mapChangeFrame >= 510)
			{
				mapChangeFrame = 510;
			}
			IMAGEMANAGER->render("sixthMap", getMemDC(), 0, 90, 0, mapChangeFrame, 800, 510);
			IMAGEMANAGER->render("eighthMap", getMemDC(), 0, 90, 0, mapChangeFrame - 510, 800, 510);
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

void cSceneManager::mapMiniRender(void)
{
	if (isInfo == true)
	{
		IMAGEMANAGER->render("grayMini", getMemDC(), 130, 50);
	}
	if (isFirst == false)
	{
		IMAGEMANAGER->render("blackMini", getMemDC(), 99, 50);
	}
	else
	{
		IMAGEMANAGER->render("grayMini", getMemDC(), 99, 50);
	}
	if (isFirst == true)
	{
		if (isSecond == false)
		{
			IMAGEMANAGER->render("blackMini", getMemDC(), 68, 50);
		}
		else
		{
			IMAGEMANAGER->render("grayMini", getMemDC(), 68, 50);
		}
		if (isThird == false)
		{
			IMAGEMANAGER->render("blackMini", getMemDC(), 99, 63);
		}
		else
		{
			IMAGEMANAGER->render("grayMini", getMemDC(), 99, 63);
		}
		IMAGEMANAGER->render("kingMini", getMemDC(), 73, 45);
		IMAGEMANAGER->render("scMini", getMemDC(), 106, 58);
	}
	if (isFourth == false)
	{
		IMAGEMANAGER->render("blackMini", getMemDC(), 130, 37);
	}
	else
	{
		IMAGEMANAGER->render("grayMini", getMemDC(), 130, 37);
	}
	if (isFourth == true)
	{
		if (isFifth == false)
		{
			IMAGEMANAGER->render("blackMini", getMemDC(), 130, 24);
		}
		else
		{
			IMAGEMANAGER->render("grayMini", getMemDC(), 130, 24);
		}
	}
	if (isSixth == false)
	{
		IMAGEMANAGER->render("blackMini", getMemDC(), 161, 50);
	}
	else
	{
		IMAGEMANAGER->render("grayMini", getMemDC(), 161, 50);
	}
	if (isSixth == true)
	{
		if (isSeventh == false)
		{
			IMAGEMANAGER->render("blackMini", getMemDC(), 192, 50);
		}
		else
		{
			IMAGEMANAGER->render("grayMini", getMemDC(), 192, 50);
		}
		if (isEighth == false)
		{
			IMAGEMANAGER->render("blackMini", getMemDC(), 161, 63);
		}
		else
		{
			IMAGEMANAGER->render("grayMini", getMemDC(), 161, 63);
		}
	}
	if (currentMap == ������)
	{
		IMAGEMANAGER->render("whiteMini", getMemDC(), 130, 50);
	}
	if (currentMap == ù��°��)
	{
		IMAGEMANAGER->render("whiteMini", getMemDC(), 99, 50);
	}
	if (currentMap == �ι�°��)
	{
		IMAGEMANAGER->render("whiteMini", getMemDC(), 68, 50);
	}
	if (currentMap == ����°��)
	{
		IMAGEMANAGER->render("whiteMini", getMemDC(), 99, 63);
	}
	if (currentMap == �׹�°��)
	{
		IMAGEMANAGER->render("whiteMini", getMemDC(), 130, 37);
	}
	if (currentMap == �ټ���°��)
	{
		IMAGEMANAGER->render("whiteMini", getMemDC(), 130, 24);
	}
	if (currentMap == ������°��)
	{
		IMAGEMANAGER->render("whiteMini", getMemDC(), 161, 50);
	}
	if (currentMap == �ϰ���°��)
	{
		IMAGEMANAGER->render("whiteMini", getMemDC(), 192, 50);
	}
	if (currentMap == ������°��)
	{
		IMAGEMANAGER->render("whiteMini", getMemDC(), 161, 63);
	}

	if (isFirst == true)
	{
		IMAGEMANAGER->render("kingMini", getMemDC(), 73, 45);
		IMAGEMANAGER->render("scMini", getMemDC(), 106, 60);
	}
	if (isFourth == true)
	{
		IMAGEMANAGER->render("itemMini", getMemDC(), 136, 21);
	}
}

void cSceneManager::hpUiRender(void)
{
	if (_player->GetHp() == 8)
	{
		IMAGEMANAGER->alphaRender("fullHeart", getMemDC(), 580, 30, inGameAlpha);
		IMAGEMANAGER->alphaRender("fullHeart", getMemDC(), 615, 30, inGameAlpha);
		IMAGEMANAGER->alphaRender("fullHeart", getMemDC(), 650, 30, inGameAlpha);
		IMAGEMANAGER->alphaRender("fullHeart", getMemDC(), 685, 30, inGameAlpha);
	}
	if (_player->GetHp() == 7)
	{
		IMAGEMANAGER->alphaRender("fullHeart", getMemDC(), 580, 30, inGameAlpha);
		IMAGEMANAGER->alphaRender("fullHeart", getMemDC(), 615, 30, inGameAlpha);
		IMAGEMANAGER->alphaRender("fullHeart", getMemDC(), 650, 30, inGameAlpha);
		IMAGEMANAGER->alphaRender("halfHeart", getMemDC(), 685, 30, inGameAlpha);
	}
	if (_player->GetHp() == 6)
	{
		IMAGEMANAGER->alphaRender("fullHeart", getMemDC(), 580, 30, inGameAlpha);
		IMAGEMANAGER->alphaRender("fullHeart", getMemDC(), 615, 30, inGameAlpha);
		IMAGEMANAGER->alphaRender("fullHeart", getMemDC(), 650, 30, inGameAlpha);
		if (_player->GetmaxHp() == 8)
		{
			IMAGEMANAGER->alphaRender("emptyHeart", getMemDC(), 685, 30, inGameAlpha);
		}
	}
	if (_player->GetHp() == 5)
	{
		IMAGEMANAGER->alphaRender("fullHeart", getMemDC(), 580, 30, inGameAlpha);
		IMAGEMANAGER->alphaRender("fullHeart", getMemDC(), 615, 30, inGameAlpha);
		IMAGEMANAGER->alphaRender("halfHeart", getMemDC(), 650, 30, inGameAlpha);
		if (_player->GetmaxHp() == 8)
		{
			IMAGEMANAGER->alphaRender("emptyHeart", getMemDC(), 685, 30, inGameAlpha);
		}
	}
	if (_player->GetHp() == 4)
	{
		IMAGEMANAGER->alphaRender("fullHeart", getMemDC(), 580, 30, inGameAlpha);
		IMAGEMANAGER->alphaRender("fullHeart", getMemDC(), 615, 30, inGameAlpha);
		IMAGEMANAGER->alphaRender("emptyHeart", getMemDC(), 650, 30, inGameAlpha);
		if (_player->GetmaxHp() == 8)
		{
			IMAGEMANAGER->alphaRender("emptyHeart", getMemDC(), 685, 30, inGameAlpha);
		}
	}
	if (_player->GetHp() == 3)
	{
		IMAGEMANAGER->alphaRender("fullHeart", getMemDC(), 580, 30, inGameAlpha);
		IMAGEMANAGER->alphaRender("halfHeart", getMemDC(), 615, 30, inGameAlpha);
		IMAGEMANAGER->alphaRender("emptyHeart", getMemDC(), 650, 30, inGameAlpha);
		if (_player->GetmaxHp() == 8)
		{
			IMAGEMANAGER->alphaRender("emptyHeart", getMemDC(), 685, 30, inGameAlpha);
		}
	}
	if (_player->GetHp() == 2)
	{
		IMAGEMANAGER->alphaRender("fullHeart", getMemDC(), 580, 30, inGameAlpha);
		IMAGEMANAGER->alphaRender("emptyHeart", getMemDC(), 615, 30, inGameAlpha);
		IMAGEMANAGER->alphaRender("emptyHeart", getMemDC(), 650, 30, inGameAlpha);
		if (_player->GetmaxHp() == 8)
		{
			IMAGEMANAGER->alphaRender("emptyHeart", getMemDC(), 685, 30, inGameAlpha);
		}
	}
	if (_player->GetHp() == 1)
	{
		IMAGEMANAGER->alphaRender("halfHeart", getMemDC(), 580, 30, inGameAlpha);
		IMAGEMANAGER->alphaRender("emptyHeart", getMemDC(), 615, 30, inGameAlpha);
		IMAGEMANAGER->alphaRender("emptyHeart", getMemDC(), 650, 30, inGameAlpha);
		if (_player->GetmaxHp() == 8)
		{
			IMAGEMANAGER->alphaRender("emptyHeart", getMemDC(), 685, 30, inGameAlpha);
		}
	}
	if (_player->GetHp() == 0)
	{
		IMAGEMANAGER->alphaRender("emptyHeart", getMemDC(), 580, 30, inGameAlpha);
		IMAGEMANAGER->alphaRender("emptyHeart", getMemDC(), 615, 30, inGameAlpha);
		IMAGEMANAGER->alphaRender("emptyHeart", getMemDC(), 650, 30, inGameAlpha);
		if (_player->GetmaxHp() == 8)
		{
			IMAGEMANAGER->alphaRender("emptyHeart", getMemDC(), 685, 30, inGameAlpha);
		}
	}

	if (_player->GetSpace() == �ڻ���������)
	{
		IMAGEMANAGER->alphaRender("remocon", getMemDC(), 493, 30, inGameAlpha);
	}
	if (_player->GetSpace() == �𷡽ð�)
	{
		IMAGEMANAGER->alphaRender("sandclock", getMemDC(), 493, 30, inGameAlpha);
	}
}

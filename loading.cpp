#include "stdafx.h"
#include "loading.h"
//=============================================================
//	## loadItem ## (�ε������ Ŭ����)
//=============================================================
HRESULT loadItem::init(string keyName, int width, int height)
{
	//�ε����� �ʱ�ȭ
	_kind = LOAD_KIND_IMAGE_0;
	//�̹��� ����ü �ʱ�ȭ
	_imageResource.keyName = keyName;
	_imageResource.width = width;
	_imageResource.height = height;

	return S_OK;
}

HRESULT loadItem::init(string keyName, const char * fileName, int width, int height, BOOL isTrans, COLORREF transColor)
{
	//�ε����� �ʱ�ȭ
	_kind = LOAD_KIND_IMAGE_1;
	//�̹��� ����ü �ʱ�ȭ
	_imageResource.keyName = keyName;
	_imageResource.fileName = fileName;
	_imageResource.width = width;
	_imageResource.height = height;
	_imageResource.trans = isTrans;
	_imageResource.transColor = transColor;

	return S_OK;
}

HRESULT loadItem::init(string keyName, const char * fileName, float x, float y, int width, int height, BOOL isTrans, COLORREF transColor)
{
	//�ε����� �ʱ�ȭ
	_kind = LOAD_KIND_IMAGE_2;
	//�̹��� ����ü �ʱ�ȭ
	_imageResource.keyName = keyName;
	_imageResource.fileName = fileName;
	_imageResource.x = x;
	_imageResource.y = y;
	_imageResource.width = width;
	_imageResource.height = height;
	_imageResource.trans = isTrans;
	_imageResource.transColor = transColor;

	return S_OK;
}

HRESULT loadItem::init(string keyName, const char * fileName, int width, int height, int maxFrameX, int maxFrameY, BOOL isTrans, COLORREF transColor)
{
	//�ε����� �ʱ�ȭ
	_kind = LOAD_KIND_FRAMEIMAGE_0;
	//�̹��� ����ü �ʱ�ȭ
	_imageResource.keyName = keyName;
	_imageResource.fileName = fileName;
	_imageResource.width = width;
	_imageResource.height = height;
	_imageResource.frameX = maxFrameX;
	_imageResource.frameY = maxFrameY;
	_imageResource.trans = isTrans;
	_imageResource.transColor = transColor;

	return S_OK;
}

HRESULT loadItem::init(string keyName, const char * fileName, float x, float y, int width, int height, int maxFrameX, int maxFrameY, BOOL isTrans, COLORREF transColor)
{
	//�ε����� �ʱ�ȭ
	_kind = LOAD_KIND_FRAMEIMAGE_1;
	//�̹��� ����ü �ʱ�ȭ
	_imageResource.keyName = keyName;
	_imageResource.fileName = fileName;
	_imageResource.x = x;
	_imageResource.y = y;
	_imageResource.width = width;
	_imageResource.height = height;
	_imageResource.frameX = maxFrameX;
	_imageResource.frameY = maxFrameY;
	_imageResource.trans = isTrans;
	_imageResource.transColor = transColor;

	return S_OK;
}


//=============================================================
//	## loading ## (�ε� Ŭ����)
//=============================================================

HRESULT loading::init(void)
{
	//�ε�ȭ�� ��׶��� �̹��� �ʱ�ȭ
	_background = IMAGEMANAGER->addImage("bgLoadingScene", "background.bmp", WINSIZEX, 500);
	//_test2 = IMAGEMANAGER->addImage("����", "test2.bmp", 70, 80, true, RGB(255, 0, 255));
	_test3 = IMAGEMANAGER->addImage("ĳ����", "test3.bmp", 30, 34, true, RGB(255, 0, 255));
	//�ε��� �ʱ�ȭ
	_loadingBar = new progressBar;
	_loadingBar->init("test", "loadingBarBack", 100, 500, 600, 20);

	_loadingBar->setGauge(0, 0);
	//���� ������ �ʱ�ȭ
	_currentGauge = 0;

	return S_OK;
}

void loading::release(void)
{
	//�ε��� ����
	SAFE_DELETE(_loadingBar);
}

void loading::update(void)
{
	//�ε��� ������Ʈ
	_loadingBar->update();
	//_test2->setX(_loadingBar->_progressBarBack->getX()+_loadingBar->_width-25);
	//_test2->setY(_loadingBar->_progressBarBack->getY()-33);	
}

void loading::render(void)
{
	HFONT font;
	HFONT o_font;
	font = CreateFont(20, 0, 0, 0, FW_NORMAL, 0, 0, 0, ANSI_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT("IMPACT"));
	o_font = (HFONT)SelectObject(getMemDC(), font);
	SetTextColor(getMemDC(), RGB(255, 255, 255));
	SetBkMode(getMemDC(), TRANSPARENT);
	//��׶��� ����
	_background->render(getMemDC());



	//�ε��� ����
	_loadingBar->render();
	_test3->render(getMemDC(), 90, WINSIZEY - 105);

	//_test2->render(getMemDC(), _test2->getX(), _test2->getY());


	SetBkMode(getMemDC(), TRANSPARENT);
	SetTextColor(getMemDC(), RGB(255, 255, 255));
	TextOut(getMemDC(), _loadingBar->getRect().left + 100, _loadingBar->getRect().top + 40, path, lstrlen(path));
	/*TextOut(getMemDC(), _test2->getX()+30, _test2->getY()+35, perCent, lstrlen(perCent));*/


	if (loadingDone() == true)
	{
		wsprintf(enter, TEXT("%s"), "PRESS ENTER TO START!");
		TextOut(getMemDC(), 350, 498, enter, lstrlen(enter));
	}

}

void loading::loadImage(string strKey, int width, int height)
{
	loadItem* item = new loadItem;
	item->init(strKey, width, height);
	_vLoadItem.push_back(item);
}

void loading::loadImage(string strKey, const char * fileName, int width, int height, BOOL isTrans, COLORREF transColor)
{
	loadItem* item = new loadItem;
	item->init(strKey, fileName, width, height, isTrans, transColor);
	_vLoadItem.push_back(item);
}

void loading::loadImage(string strKey, const char * fileName, float x, float y, int width, int height, BOOL isTrans, COLORREF transColor)
{
	loadItem* item = new loadItem;
	item->init(strKey, fileName, x, y, width, height, isTrans, transColor);
	_vLoadItem.push_back(item);
}

void loading::loadFrameImage(string strKey, const char * fileName, int width, int height, int maxFrameX, int maxFrameY, BOOL isTrans, COLORREF transColor)
{
	loadItem* item = new loadItem;
	item->init(strKey, fileName, width, height, maxFrameX, maxFrameY, isTrans, transColor);
	_vLoadItem.push_back(item);
}

void loading::loadFrameImage(string strKey, const char * fileName, float x, float y, int width, int height, int maxFrameX, int maxFrameY, BOOL isTrans, COLORREF transColor)
{
	loadItem* item = new loadItem;
	item->init(strKey, fileName, x, y, width, height, maxFrameX, maxFrameY, isTrans, transColor);
	_vLoadItem.push_back(item);
}

BOOL loading::loadingDone(void)
{
	//�ε��� �Ϸ��
	if (_currentGauge >= _vLoadItem.size())
	{
		return TRUE;
	}

	loadItem* item = _vLoadItem[_currentGauge];

	switch (item->getLoadingKind())
	{
	case LOAD_KIND_IMAGE_0:
	{
		tagImageResource img = item->getImageResource();
		IMAGEMANAGER->addImage(img.keyName, img.width, img.height);
	}
	break;

	case LOAD_KIND_IMAGE_1:
	{
		tagImageResource img = item->getImageResource();
		IMAGEMANAGER->addImage(img.keyName, img.fileName, img.width, img.height, img.trans, img.transColor);
	}
	break;

	case LOAD_KIND_IMAGE_2:
	{
		tagImageResource img = item->getImageResource();
		IMAGEMANAGER->addImage(img.keyName, img.fileName, img.x, img.y, img.width, img.height, img.trans, img.transColor);
	}
	break;

	case LOAD_KIND_FRAMEIMAGE_0:
	{
		tagImageResource img = item->getImageResource();
		IMAGEMANAGER->addFrameImage(img.keyName, img.fileName, img.width, img.height, img.frameX, img.frameY, img.trans, img.transColor);
	}
	break;

	case LOAD_KIND_FRAMEIMAGE_1:
	{
		tagImageResource img = item->getImageResource();
		IMAGEMANAGER->addFrameImage(img.keyName, img.fileName, img.x, img.y, img.width, img.height, img.frameX, img.frameY, img.trans, img.transColor);
	}
	break;
	//���߿� ���� ���� ���� �˾Ƽ�...
	case LOAD_KIND_SOUND:
		break;
	}

	GetCurrentDirectory(256, path);
	sprintf(buffer, "\\%s.bmp", _vLoadItem[_currentGauge]->getImageResource().keyName.c_str());
	//sprintf(buffer, "\\%s.bmp", _vLoadItem[_currentGauge]->getImageResource().fileName);
	strcat(path, buffer);
	wsprintf(perCent, TEXT("%d%c"), (_currentGauge - 2) / 5, '%');



	//��������� ����
	_currentGauge++;

	//�ε��� �̹��� ����
	_loadingBar->setGauge(_currentGauge, _vLoadItem.size());

	return FALSE;
}

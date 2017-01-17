#include "stdafx.h"
#include "progressBar.h"

HRESULT progressBar::init(char * frontImageKey, char * backImageKey, int x, int y, int width, int height)
{
	//체력바 위치 초기화
	_x = x;
	_y = y;

	//체력바 가로, 세로길이 초기화
	_width = width;
	_height = height;

	//체력바 렉트 위치 및 크기 초기화
	_rcProgress = RectMake(x, y, width, height);

	//키값으로 이미지이름(~.bmp)을 바로 초기화
	char frontImage[128];
	char backImage[128];
	//메모리 깔끔하게 밀어주기
	ZeroMemory(frontImage, sizeof(frontImage));
	ZeroMemory(backImage, sizeof(backImage));
	//~.bmp로 만들기
	sprintf(frontImage, "%s.bmp", frontImageKey);
	sprintf(backImage, "%s.bmp", backImageKey);

	//체력바 이미지 초기화
	_progressBarFront = IMAGEMANAGER->addImage(frontImageKey, frontImage, x, y, width, height, true, RGB(255, 0, 255));
	_progressBarBack = IMAGEMANAGER->addImage(backImageKey, backImage, x, y, width, height, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("숫자", "isaacNumber.bmp", x, y - 50, 140, 19, true, RGB(128, 128, 255));
	IMAGEMANAGER->addImage("퍼센트", "per.bmp", x, y - 50, 24, 19, true, RGB(128, 128, 255));
	return S_OK;
}

void progressBar::release(void)
{
}

void progressBar::update(void)
{
	_rcProgress = RectMake(_x, _y, _progressBarBack->getWidth(), _progressBarBack->getHeight());
}

void progressBar::render(void)
{
	//렌더링 되는 순서의 의해서 렌더가 되니까 피통부터 렌더 시킨다
	//_progressBarBack->render(getMemDC(), _rcProgress.left, _y);
	//앞에 보여지는 체력바 이미지
	_progressBarFront->render(getMemDC(), _rcProgress.left, _y,
		0, 0, _width, _progressBarFront->getHeight());

	IMAGEMANAGER->render("숫자", getMemDC(), _rcProgress.left + 535, _y - 25, ((int)_width / 6) / 10 * 14, 0, 14, 19);
	IMAGEMANAGER->render("숫자", getMemDC(), _rcProgress.left + 550, _y - 25, ((int)_width / 6) % 10 * 14, 0, 14, 19);
	IMAGEMANAGER->render("퍼센트", getMemDC(), _rcProgress.left + 570, _y - 25);
	if ((int)_width == 600)
	{
		IMAGEMANAGER->render("숫자", getMemDC(), _rcProgress.left + 520, _y - 25, 14, 0, 14, 19);
		IMAGEMANAGER->render("숫자", getMemDC(), _rcProgress.left + 535, _y - 25, 0, 0, 14, 19);
	}

}
//체력바 게이지 세팅하기
void progressBar::setGauge(float currentHp, float maxHp)
{
	_width = (currentHp / maxHp) * _progressBarBack->getWidth();
}

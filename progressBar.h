#pragma once
#include "gameNode.h"
//=============================================================
//	## progressBar ## (���α׷����� = ü�¹�)
//=============================================================

class progressBar : public gameNode
{
private:
	RECT _rcProgress;			//ü�¹� ��Ʈ
	int _x, _y;					//ü�¹� ��ġ ��ǥ
					//ü�¹� ���α���
	float _height;				//ü�¹� ���α���(���߿� �ʿ��ϸ� �����ϱ�)

	

public:
	image* _progressBarFront;	//ü�¹� �� �̹���
	image* _progressBarBack;		//ü�¹� �� �̹���
	float _width;

	//ü�¹� �ʱ�ȭ(���̹���Ű,���̹���Ű, x, y, ���α���, ���α���)
	HRESULT init(char* frontImageKey, char* backImageKey, int x, int y, int width, int height);
	void release(void);
	void update(void);
	void render(void);

	//ü�¹� ������ �����ϱ�
	void setGauge(float currentHp, float maxHp);

	//ü�¹� ��ġ ��ǥ �����ϱ�
	void setX(int x) { _x = x; }
	void setY(int y) { _y = y; }
	//ü�¹� ��Ʈ ��������
	RECT getRect(void) { return _rcProgress; }
	int getX() { return _x; }
	int getY() { return _y; }

	progressBar() {}
	~progressBar() {}
};

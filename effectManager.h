#pragma once
#include "singletonBase.h"

struct tagEffect
{
	image* img;
	int destX;
	int destY;
	int currentFrameX;
	int maxFrameX;
	int time;
};

class effectManager :
	public singletonBase<effectManager>
{
	vector<tagEffect*> _vEffect;
	

public:

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(HDC hdc);

	void addEffect(string effectName, float centerX, float centerY);



	effectManager() {};
	~effectManager() {};
};


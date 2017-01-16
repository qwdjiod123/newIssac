#include "stdafx.h"
#include "effectManager.h"

HRESULT effectManager::init(void)
{
	return S_OK;
}

void effectManager::release(void)
{
}

void effectManager::update(void)
{
	for (int i = 0; i < _vEffect.size(); i++)
	{
		if (_vEffect[i]->time % 3 == 0)
		{
			if (_vEffect[i]->currentFrameX < _vEffect[i]->maxFrameX)
			{
				_vEffect[i]->currentFrameX++;
			}
			else
			{
				_vEffect.erase(_vEffect.begin() + i);
				break;
			}
		}
		else
		{
			(_vEffect[i]->time)++;
		}
		
	}
}

void effectManager::render(HDC hdc)
{
	for (int i = 0; i < _vEffect.size(); i++)
	{
		_vEffect[i]->img->frameRender(hdc, _vEffect[i]->destX, _vEffect[i]->destY, _vEffect[i]->currentFrameX, 0);
	}
}

void effectManager::addEffect(string effectName, float centerX, float centerY)
{
	tagEffect* temp = new tagEffect;
	temp->img = IMAGEMANAGER->findImage(effectName);
	temp->destX = centerX - (temp->img->getFrameWidth() / 2);
	temp->destY = centerY - (temp->img->getFrameHeight() / 2);
	temp->currentFrameX = 0;
	temp->maxFrameX = temp->img->getMaxFrameX();
	temp->time = 0;
	_vEffect.push_back(temp);
}

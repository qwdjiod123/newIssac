#include "stdafx.h"
#include "cItemManager.h"
#include "cPlayer.h"
#include "cSceneManager.h"
#include "enemyManager.h"

HRESULT cItemManager::init(void)
{
	IsPlayerDamaged = false;
	IsChange = false;
	mapRC.x = WINSIZEX / 2;
	mapRC.y = WINSIZEY / 2 + 50;
	mapRC.rc = RectMakeCenter(mapRC.x, mapRC.y, 650, 400);
	return S_OK;
}

void cItemManager::release(void)
{


}

void cItemManager::update(void)
{

	//==================================================================
	//		## ��������ӷ����� AnimCount�� ���ϴ�. ##
	//==================================================================
	AnimCount++;
	if (AnimCount>500)
	{
		AnimCount = 0;
	}

	//==================================================================
	//		## �������۵��� ���ͼ��Ϳ� ���� �ֱ����� IsChage������ ���ϴ�. ##
	//==================================================================
	if (IsChange == true)
	{
		int static nCount = 0;
		nCount++;
		if (nCount>100)
		{
			IsChange = false;
			nCount = 0;
		}
	}
	//==================================================================
	//		## ������ ���� ##
	//==================================================================

	ItemSetting();

	ItemUpdate(������);
	ItemUpdate(ù��°��);
	ItemUpdate(�ι�°��);
	ItemUpdate(�׹�°��);
	ItemUpdate(�ټ���°��);
	ItemUpdate(������°��);
	ItemUpdate(�ϰ���°��);

	NewItemUpdate(������);
	NewItemUpdate(ù��°��);
	NewItemUpdate(�ι�°��);
	NewItemUpdate(�׹�°��);
	NewItemUpdate(�ټ���°��);
	NewItemUpdate(������°��);
	NewItemUpdate(�ϰ���°��);



	StoreUpdate();
	MissileControl();
	Collision();

	ItemRectCollision(������);
	//==================================================================
	//		## �𷡽ð� ������� ##
	//==================================================================
	if (IsTime == true)
	{
		int static nCount = 0;
		nCount++;
		if (nCount<100)
		{
			for (int p = 0; p < _enemy->getVMinion().size(); p++)
			{
				_enemy->getVMinionPt()->at(p)->setSpeed(0);       
			}
		}
		if (nCount>100)
		{
			nCount = 0;
			IsTime = false;
		}
	}

	//�׽�Ʈ
	if (KEYMANAGER->isOnceKeyDown(VK_F1))
	{
		_player->SetHp(_player->GetHp() - 1);
	}
}

void cItemManager::render(void)
{
	//==================================================================
	//		## ������ ���� ##
	//==================================================================



	if (_sm->GetdoorChangeFrame()==300)
	{
		ItemRender(������);
		ItemRender(ù��°��);
		ItemRender(�ι�°��);
		ItemRender(�׹�°��);
		ItemRender(�ټ���°��);
		ItemRender(������°��);
		ItemRender(�ϰ���°��);

		NewItemRender(������);
		NewItemRender(ù��°��);
		NewItemRender(�ι�°��);
		NewItemRender(�׹�°��);
		NewItemRender(�ټ���°��);
		NewItemRender(������°��);
		NewItemRender(�ϰ���°��);
	}
	

	StoreRener();

	MissileRender();

	//�׽�Ʈ�Դϴ�.
	/*wsprintf(buffer, TEXT("HP:%d"), _player->GetHp());
	TextOut(getMemDC(), 200, 200, buffer, lstrlen(buffer));*/
	//RectangleMake(getMemDC(), mapRC.rc);

}

void cItemManager::ItemSetting()
{
	// �ʿ������� ����
	if (_sm->GetCurrentMap() == ������&&ItemSetOnce[������] == false)
	{
		/*ItemMapSet(100, 400, ��ź, ������);
		ItemMapSet(200, 400, ����, ������);
		ItemMapSet(300, 400, ����1, ������);
		ItemMapSet(400, 400, ����99, ������);
		ItemMapSet(500, 400, ��������, ������);
		ItemMapSet(600, 400, ������Ʈ, ������);
		ItemMapSet(700, 400, ������Ʈ��, ������);
		ItemMapSet(100, 200, �������, ������);
		ItemMapSet(200, 200, ���������Ǳ���, ������);
		ItemMapSet(300, 200, �ڻ���������, ������);
		ItemMapSet(400, 200, �𷡽ð�, ������);
		ItemMapSet(500, 200, ī��, ������);
		ItemMapSet(600, 200, ��Ȳ, ������);*/

		ItemSetOnce[������] = true;
	}
	if (_sm->GetCurrentMap() == ù��°��&&ItemSetOnce[ù��°��] == false)
	{
		ItemMapSet(100, 450, ����, ù��°��);
		ItemMapSet(150, 450, ����, ù��°��);
		ItemMapSet(200, 450, ����, ù��°��);
		ItemMapSet(250, 450, ����, ù��°��);
		ItemMapSet(300, 450, ����, ù��°��);
		ItemMapSet(350, 450, ����, ù��°��);
		ItemMapSet(400, 450, ����, ù��°��);
		ItemMapSet(450, 450, ����, ù��°��);
		ItemMapSet(500, 450, ����, ù��°��);
		ItemMapSet(550, 450, ����, ù��°��);
		ItemMapSet(600, 450, ����, ù��°��);
		ItemMapSet(650, 450, ����, ù��°��);
		ItemMapSet(700, 450, ����, ù��°��);

		ItemSetOnce[ù��°��] = true;
	}
	if (_sm->GetCurrentMap() == �ι�°��&&ItemSetOnce[�ι�°��] == false)
	{
		StoreSetting(�ι�°��);
		ItemMapSet(400, 350, ��Ȳ, �ι�°��);
		ItemMapSet(400, 390, ������, �ι�°��);
		ItemSetOnce[�ι�°��] = true;
	}
	if (_sm->GetCurrentMap() == �׹�°��&&ItemSetOnce[�׹�°��] == false)
	{
		ItemMapSet(300, 350, ������Ʈ, �׹�°��);
		ItemMapSet(500, 350, ��ź, �׹�°��);
		ItemSetOnce[�׹�°��] = true;
	}
	if (_sm->GetCurrentMap() == �ټ���°��&&ItemSetOnce[�ټ���°��] == false)
	{
		ItemMapSet(100, 200, ����, �ټ���°��);
		ItemMapSet(100, 500, ��������, �ټ���°��);
		ItemMapSet(400, 300, �������, �ټ���°��);
		ItemMapSet(395, 340, ������, �ټ���°��);
		ItemSetOnce[�ټ���°��] = true;
	}
	if (_sm->GetCurrentMap() == ������°��&&ItemSetOnce[������°��] == false)
	{
		ItemMapSet(480, 350, ����1, ������°��);
		ItemMapSet(430, 350, ����1, ������°��);
		ItemMapSet(380, 350, ����1, ������°��);
		ItemMapSet(330, 350, ����1, ������°��);
		ItemSetOnce[������°��] = true;
	}
	if (_sm->GetCurrentMap() == �ϰ���°��&&ItemSetOnce[�ϰ���°��] == false)
	{
		ItemMapSet(300, 400, �𷡽ð�, �ϰ���°��);
		ItemMapSet(500, 400, �ڻ���������, �ϰ���°��);
		ItemMapSet(300, 440, ������, �ϰ���°��);
		ItemMapSet(500, 440, ������, �ϰ���°��);

		ItemMapSet(250, 150, ����ĳ����, �ϰ���°��);
		ItemMapSet(300, 200, ����99, �ϰ���°��);
		ItemMapSet(400, 200, ī��, �ϰ���°��);
		ItemMapSet(400, 240, ����2, �ϰ���°��);
		ItemMapSet(500, 200, ���������Ǳ���, �ϰ���°��);
		ItemMapSet(500, 240, ����3, �ϰ���°��);
		ItemSetOnce[�ϰ���°��] = true;
	}
}

void cItemManager::ItemMapSet(float _x, float _y, int _state, int _currentmap)
{
	tag_Item item;
	item.IsBomb = false;
	item.moveSpeed = 0.0f;
	item.x = _x;
	item.y = _y;
	item.state = _state;
	item.currentmap = _currentmap;

	if (_state == ��������)
	{
		item.RectSize = �������ڷ�Ʈ;
	}
	if (_state == ��ź)
	{
		item.RectSize = ��ź��Ʈ;
	}
	if (_state == ����)
	{
		item.RectSize = ���跺Ʈ;
	}
	if (_state == ������Ʈ��)
	{
		item.RectSize = ������Ʈ�ݷ�Ʈ;
	}
	if (_state == ������Ʈ)
	{
		item.RectSize = ������Ʈ��Ʈ;
	}
	if (_state == ����1)
	{
		item.RectSize = ����1��Ʈ;
	}
	if (_state == ����99)
	{
		item.RectSize = ����99��Ʈ;
	}
	if (_state == �������)
	{
		item.RectSize = ������ⷺƮ;
	}
	if (_state == ī��)
	{
		item.RectSize = ī�巺Ʈ;
	}
	if (_state == ��Ȳ)
	{
		item.RectSize = ��Ȳ��Ʈ;
	}
	if (_state == ���������Ǳ���)
	{
		item.RectSize = ���������Ǳ��ַ�Ʈ;
	}
	if (_state == �𷡽ð�)
	{
		item.RectSize = �𷡽ð跺Ʈ;
	}
	if (_state == �ڻ���������)
	{
		item.RectSize = �ڻ������ⷺƮ;
	}
	if (_state == ������)
	{
		item.RectSize = 50;
	}
	if (_state == ����ĳ����)
	{
		item.RectSize = 100;
	}
	if (_state == ����2)
	{
		item.RectSize = 40;
	}
	if (_state == ����3)
	{
		item.RectSize = 40;
	}
	if (_state == ����)
	{
		item.RectSize = 50;
	}

	item.rc = RectMakeCenter(item.x, item.y, item.RectSize, item.RectSize);
	vItem.push_back(item);
}

void cItemManager::ItemUse(int _item)
{
	if (_item == ��ź)
	{
		_player->SetBomb(_player->GetBomb() - 1);
		tag_Item item;
		item.x = _player->GetX();
		item.y = _player->GetY();
		item.IsBomb = true;
		item.state = ��ź;
		item.currentmap = _sm->GetCurrentMap();
		item.AnimX = 0;
		//item.rc = RectMakeCenter(10, 10, 100, 100); // ��ź�� ������ ��Ʈ������ update()����ó����
		vNewItem.push_back(item);
	}
	if (_item == �ڻ���������)
	{
		missileBomb.IsBomb = true;
	}
	if (_item == �𷡽ð�)
	{
		IsTime = true;
	}
	if (_item == ī��)
	{

	}


}

void cItemManager::ItemMake(float _x, float _y, int _state, int _currentmap, bool _IsMove)
{
	tag_Item item;
	item.IsBomb = false;
	item.IsMove = _IsMove;
	item.moveSpeed = 5.0f;
	item.angle = RND->getFromFloatTo(0, 2 * PI);
	item.x = _x;
	item.y = _y;
	item.state = _state;
	item.currentmap = _currentmap;
	if (_state == ��������)
	{
		item.RectSize = �������ڷ�Ʈ;
	}
	if (_state == ��ź)
	{
		item.RectSize = ��ź��Ʈ;
	}
	if (_state == ����)
	{
		item.RectSize = ���跺Ʈ;
	}
	if (_state == ������Ʈ��)
	{
		item.RectSize = ������Ʈ�ݷ�Ʈ;
	}
	if (_state == ������Ʈ)
	{
		item.RectSize = ������Ʈ��Ʈ;
	}
	if (_state == ����1)
	{
		item.RectSize = ����1��Ʈ;
	}
	if (_state == ����99)
	{
		item.RectSize = ����99��Ʈ;
	}
	if (_state == �������)
	{
		item.RectSize = ������ⷺƮ;
	}
	if (_state == ī��)
	{
		item.RectSize = ī�巺Ʈ;
	}
	if (_state == ��Ȳ)
	{
		item.RectSize = ��Ȳ��Ʈ;
	}
	if (_state == ���������Ǳ���)
	{
		item.RectSize = ���������Ǳ��ַ�Ʈ;
	}
	if (_state == �𷡽ð�)
	{
		item.RectSize = �𷡽ð跺Ʈ;
	}
	if (_state == �ڻ���������)
	{
		item.RectSize = �ڻ������ⷺƮ;
	}

	item.rc = RectMakeCenter(item.x, item.y, item.RectSize, item.RectSize);

	vNewItem.push_back(item);
}

void cItemManager::DeleteItem(int index)
{

	for (int i = 0; i < vItem.size(); i++)
	{
		vItem.erase(vItem.begin() + index);
		break;
	}
}

void cItemManager::DeleteNewItem(int index)
{
	for (int i = 0; i < vNewItem.size(); i++)
	{
		vNewItem.erase(vNewItem.begin() + index);
		break;
	}
}

void cItemManager::ItemUpdate(int _currentmap)
{
	if (_sm->GetCurrentMap() == _currentmap)
	{
		for (int i = 0; i < vItem.size(); i++)
		{
			if (vItem[i].currentmap == _currentmap)
			{
				//////////////////////////////////////////////////////////////////////
				//��Ʈ�� ���� Ǯ�϶� �ȸ԰��ϱ����� ������					
				if (vItem[i].IsBomb == false)
				{
					if (vItem[i].moveSpeed>0.0f)
					{
						vItem[i].moveSpeed -= 0.1f;
						vItem[i].x += cosf(vItem[i].angle)*vItem[i].moveSpeed;
						vItem[i].y += -sinf(vItem[i].angle)*vItem[i].moveSpeed;
						vItem[i].rc = RectMakeCenter(vItem[i].x, vItem[i].y, vItem[i].RectSize, vItem[i].RectSize);
					}
				}
				/////////////////////////////////////////////////////////////////�浹
				if (IntersectRect(&temp, &_player->GetRC(), &vItem[i].rc))
				{
					if (_player->GetKey()>0 && vItem[i].state == ��������)
					{
						IsChange = true;
						int static nCount = 0;
						nCount++;
						if (nCount>20)
						{
							nCount = 0;
							ItemMake(vItem[i].x, vItem[i].y, ������Ʈ��, vItem[i].currentmap, true);
							_player->SetKey(_player->GetKey() - 1);
							DeleteItem(i);
						}
						break;
					}
					if (_player->GetKey() <= 0 && vItem[i].state == ��������)
					{
						float distance = getDistance(vItem[i].x, vItem[i].y, _player->GetX(), _player->GetY());
						if (distance<75)
						{
							vItem[i].angle = getAngle(_player->GetX(), _player->GetY(), vItem[i].x, vItem[i].y);
							vItem[i].moveSpeed = ITEMMOVETIME;
						}
					}
					if (vItem[i].state == ����)
					{
						_player->SetKey(_player->GetKey() + 1);
						DeleteItem(i);
						break;
					}
					if (vItem[i].state == ��ź)
					{
						_player->SetBomb(_player->GetBomb() + 1);
						DeleteItem(i);
						break;
					}
					if (vItem[i].state == ������Ʈ��)
					{
						if (_player->GetHp() + 1>_player->GetmaxHp())
						{
							float distance = getDistance(vItem[i].x, vItem[i].y, _player->GetX(), _player->GetY());
							if (distance<75)
							{
								vItem[i].angle = getAngle(_player->GetX(), _player->GetY(), vItem[i].x, vItem[i].y);
								vItem[i].moveSpeed = ITEMMOVETIME;
							}
						}
						else if (_player->GetHp() + 1 <= _player->GetmaxHp())
						{
							_player->SetHp(_player->GetHp() + 1);
							DeleteItem(i);
							break;
						}
					}
					if (vItem[i].state == ������Ʈ)
					{
						if (_player->GetHp() == _player->GetmaxHp())
						{
							float distance = getDistance(vItem[i].x, vItem[i].y, _player->GetX(), _player->GetY());
							if (distance<75)
							{
								vItem[i].angle = getAngle(_player->GetX(), _player->GetY(), vItem[i].x, vItem[i].y);
								vItem[i].moveSpeed = ITEMMOVETIME;
							}
							break;
						}
						if (_player->GetHp() + 2 <= _player->GetmaxHp())
						{
							_player->SetHp(_player->GetHp() + 2);
							DeleteItem(i);
							break;
						}
						else if (_player->GetHp() + 2 > _player->GetmaxHp())
						{
							_player->SetHp(_player->GetHp() + 1);
							DeleteItem(i);
							break;
						}
					}
					if (vItem[i].state == ����1)
					{
						if (_player->GetMoney() == 99)
						{
							float distance = getDistance(vItem[i].x, vItem[i].y, _player->GetX(), _player->GetY());
							if (distance<75)
							{
								vItem[i].angle = getAngle(_player->GetX(), _player->GetY(), vItem[i].x, vItem[i].y);
								vItem[i].moveSpeed = ITEMMOVETIME;
							}
						}
						if (_player->GetMoney()<99)
						{
							_player->SetMoney(_player->GetMoney() + 1);
							DeleteItem(i);
							break;
						}
					}
					if (vItem[i].state == ����99)
					{
						_player->SetMoney(99);
						DeleteItem(i);
						break;
					}
					if (vItem[i].state == �������)
					{
						_player->SetAnimState(ETC);
						_player->SetmaxHp(_player->GetmaxHp() + 2);
						_player->SetHp(_player->GetHp() + 2);
						_player->addInVentory(�������);
						DeleteItem(i);
						break;
					}
					if (vItem[i].state == ī��)
					{
						if (_player->GetMoney() >= 2)
						{
							_player->SetMoney(_player->GetMoney() - 2);
							_player->SetRange(500);
							_player->SetBulletSpeed(5);
							_player->SetAnimState(CARD);
							_player->addInVentory(ī��);
							DeleteItem(i);
							break;
						}
					}
					if (vItem[i].state == ��Ȳ)
					{
						_player->SetAnimState(ETC);
						_player->SetArrow(��Ȳ);
						_player->addInVentory(��Ȳ);
						DeleteItem(i);
						break;
					}
					if (vItem[i].state == ���������Ǳ���)
					{
						if (_player->GetMoney() >= 7)
						{
							_player->SetMoney(_player->GetMoney() - 7);
							_player->SetAnimState(ETC);
							_player->addInVentory(���������Ǳ���);
							_player->SetIsFly(true);
							DeleteItem(i);
							break;
						}

					}
					if (vItem[i].state == �ڻ���������&&IsChange == false)
					{
						if (_player->GetSpace() == ����)
						{

						}
						else
						{
							ItemMake(vItem[i].x, 400, �𷡽ð�, _currentmap, false);
						}
						IsChange = true;
						_player->SetSpace(�ڻ���������);
						DeleteItem(i);
						_player->SetAnimState(ETC);
						break;
					}
					if (vItem[i].state == �𷡽ð�&&IsChange == false)
					{
						if (_player->GetSpace() == ����)
						{

						}
						else
						{
							ItemMake(vItem[i].x, 400, �ڻ���������, _currentmap, false);
						}
						IsChange = true;
						_player->SetSpace(�𷡽ð�);
						_player->SetAnimState(ETC);
						DeleteItem(i);
						break;
					}
				}

				/////////////////////////////////////////////////////////////////���Ʒ�
				if (vItem[i].state == ������� || vItem[i].state == ��Ȳ || vItem[i].state == ���������Ǳ��� || vItem[i].state == �ڻ��������� || vItem[i].state == �𷡽ð�)
				{
					if (vItem[i].gravity>3.8f)
					{
						vItem[i].gravity = 0.0f;
					}
					vItem[i].gravity += 0.1f;
					vItem[i].y += -sinf(PI / 2) * 2 + vItem[i].gravity;
					vItem[i].rc = RectMakeCenter(vItem[i].x, vItem[i].y, vItem[i].RectSize, vItem[i].RectSize);
				}
			}
		}
	}
}

void cItemManager::NewItemUpdate(int _currentmap)
{
	if (_sm->GetCurrentMap() == _currentmap)
	{
		for (int i = 0; i < vNewItem.size(); i++)
		{
			if (vNewItem[i].currentmap == _currentmap)
			{
				//==================================================================
				//		## �����ۿ����̴·��� ## �������� Ƣ����¾ֵ�
				//==================================================================	
				if (vNewItem[i].IsBomb == false && vNewItem[i].IsMove == true)
				{
					if (vNewItem[i].moveSpeed>0.0f)
					{
						vNewItem[i].moveSpeed -= 0.1f;
						vNewItem[i].x += cosf(vNewItem[i].angle)*vNewItem[i].moveSpeed;
						vNewItem[i].y += -sinf(vNewItem[i].angle)*vNewItem[i].moveSpeed;
						vNewItem[i].rc = RectMakeCenter(vNewItem[i].x, vNewItem[i].y, vNewItem[i].RectSize, vNewItem[i].RectSize);
					}
				}

				if (IntersectRect(&temp, &_player->GetRC(), &vNewItem[i].rc))
				{
					if (vNewItem[i].state == ����&&IsChange == false)
					{
						_player->SetKey(_player->GetKey() + 1);
						DeleteNewItem(i);
						break;
					}
					if (vNewItem[i].state == ������Ʈ��&&IsChange == false)
					{
						if (_player->GetHp() + 1>_player->GetmaxHp())
						{
							float distance = getDistance(vNewItem[i].x, vNewItem[i].y, _player->GetX(), _player->GetY());
							if (distance<75)
							{
								vNewItem[i].angle = getAngle(_player->GetX(), _player->GetY(), vNewItem[i].x, vNewItem[i].y);
								vNewItem[i].moveSpeed = ITEMMOVETIME;
							}
						}
						else if (_player->GetHp() + 1 <= _player->GetmaxHp())
						{
							_player->SetHp(_player->GetHp() + 1);
							DeleteNewItem(i);
							break;
						}
					}
					if (vNewItem[i].state == ������Ʈ&&IsChange == false)
					{
						if (_player->GetHp() == _player->GetmaxHp())
						{
							float distance = getDistance(vNewItem[i].x, vNewItem[i].y, _player->GetX(), _player->GetY());
							if (distance<75)
							{
								vNewItem[i].angle = getAngle(_player->GetX(), _player->GetY(), vNewItem[i].x, vNewItem[i].y);
								vNewItem[i].moveSpeed = ITEMMOVETIME;
							}
							break;
						}
						if (_player->GetHp() + 2 <= _player->GetmaxHp())
						{
							_player->SetHp(_player->GetHp() + 2);
							DeleteNewItem(i);
							break;
						}
						else if (_player->GetHp() + 2 > _player->GetmaxHp())
						{
							_player->SetHp(_player->GetHp() + 1);
							DeleteNewItem(i);
							break;
						}
					}
					if (vNewItem[i].state == ����1&&IsChange == false)
					{
						_player->SetMoney(_player->GetMoney() + 1);
						DeleteNewItem(i);
						break;
					}
					if (vNewItem[i].state == ����99&&IsChange == false)
					{
						_player->SetMoney(99);
						DeleteNewItem(i);
						break;
					}
					if (vNewItem[i].state == �ڻ���������&&IsChange == false)
					{
						if (_player->GetSpace() == ����)
						{

						}
						else
						{
							ItemMake(vNewItem[i].x, 400, �𷡽ð�, _currentmap, false);
						}
						IsChange = true;
						_player->SetSpace(�ڻ���������);
						DeleteNewItem(i);
						_player->SetAnimState(ETC);
						break;
					}
					if (vNewItem[i].state == �𷡽ð�&&IsChange == false)
					{
						if (_player->GetSpace() == ����)
						{

						}
						else
						{
							ItemMake(vNewItem[i].x, 400, �ڻ���������, _currentmap, false);
						}
						IsChange = true;
						_player->SetSpace(�𷡽ð�);
						DeleteNewItem(i);
						_player->SetAnimState(ETC);
						break;
					}
					if (vNewItem[i].state == ��ź&&vNewItem[i].IsBomb == false && IsChange == false)
					{
						_player->SetBomb(_player->GetBomb() + 1);
						DeleteNewItem(i);
						break;
					}
				}

				if (vNewItem[i].state == ��ź&&vNewItem[i].IsBomb == true)
				{
					vNewItem[i].contdown++;  // �����ϱ� 100����						
					if (100<vNewItem[i].contdown&& vNewItem[i].contdown<130) // ���� 20�ʵ���
					{
						vNewItem[i].rc = RectMakeCenter(vNewItem[i].x, vNewItem[i].y, BOMBSIZE, BOMBSIZE);
					}
					if (vNewItem[i].contdown>130)
					{
						vNewItem[i].contdown = 0; // ��� �����൵�Ǵµ� �����ؼ� �׳���
						DeleteNewItem(i);   // ������ ����	
						IsPlayerDamaged = false;
						break;
					}
				}

				if (vNewItem[i].state == �ڻ��������� || vNewItem[i].state == �𷡽ð�)
				{
					if (vNewItem[i].gravity>3.8f)
					{
						vNewItem[i].gravity = 0.0f;
					}
					vNewItem[i].gravity += 0.1f;
					vNewItem[i].y += -sinf(PI / 2) * 2 + vNewItem[i].gravity;
					vNewItem[i].rc = RectMakeCenter(vNewItem[i].x, vNewItem[i].y, vNewItem[i].RectSize, vNewItem[i].RectSize);
				}

			}
		}
	}

}

void cItemManager::ItemRender(int _currentmap)
{
	//SetTextColor(getMemDC(), RGB(0, 0, 0));
	if (_sm->GetCurrentMap() == _currentmap)
	{
		for (int i = 0; i < vItem.size(); i++)
		{
			if (vItem[i].currentmap == _currentmap)
			{
				if (vItem[i].state == ������)
				{
					//TextOut(getMemDC(), vItem[i].rc.left, vItem[i].rc.top, TEXT("������"), lstrlen(TEXT("������")));
					IMAGEMANAGER->render("������", getMemDC(), vItem[i].rc.left, vItem[i].rc.top, 0, 0, 50, 40);

				}
				if (vItem[i].state == ����)
				{
					if (AnimCount %����ī��Ʈ == 0)
					{
						vItem[i].AnimX += 1;
						if (vItem[i].AnimX>6)
						{
							vItem[i].AnimX = 0;
						}
					}
					//RectangleMake(getMemDC(), vItem[i].rc);
					IMAGEMANAGER->frameRender("����", getMemDC(), vItem[i].rc.left, vItem[i].rc.top, vItem[i].AnimX, IMAGEMANAGER->findImage("����")->getFrameY());
					//TextOut(getMemDC(), vItem[i].rc.left, vItem[i].rc.top, TEXT("����"), lstrlen(TEXT("����")));
				}
				if (vItem[i].state == ��ź)
				{
					//RectangleMake(getMemDC(), vItem[i].rc);
					IMAGEMANAGER->render("��ź", getMemDC(), vItem[i].rc.left, vItem[i].rc.top, 0, 0, 40, 40);
				}
				if (vItem[i].state == ������Ʈ��)
				{
					//TextOut(getMemDC(), vItem[i].rc.left, vItem[i].rc.top, TEXT("������Ʈ��"), lstrlen(TEXT("������Ʈ��")));
					//RectangleMake(getMemDC(), vItem[i].rc);
					IMAGEMANAGER->render("��Ʈ", getMemDC(), vItem[i].rc.left, vItem[i].rc.top, 0, 0, 35, 30);
				}
				if (vItem[i].state == ������Ʈ)
				{
					//TextOut(getMemDC(), vItem[i].rc.left, vItem[i].rc.top, TEXT("������Ʈ"), lstrlen(TEXT("������Ʈ")));					
					//RectangleMake(getMemDC(), vItem[i].rc);
					IMAGEMANAGER->render("��Ʈ2", getMemDC(), vItem[i].rc.left, vItem[i].rc.top, 0, 0, 35, 30);
				}
				if (vItem[i].state == ����1)
				{
					//TextOut(getMemDC(), vItem[i].rc.left, vItem[i].rc.top, TEXT("����1"), lstrlen(TEXT("����1")));
					if (AnimCount %����1ī��Ʈ == 0)
					{
						vItem[i].AnimX += 1;
						if (vItem[i].AnimX>7)
						{
							vItem[i].AnimX = 0;
						}
					}
					//RectangleMake(getMemDC(), vItem[i].rc);
					IMAGEMANAGER->frameRender("����1", getMemDC(), vItem[i].rc.left, vItem[i].rc.top, vItem[i].AnimX, IMAGEMANAGER->findImage("����1")->getFrameY());
				}
				if (vItem[i].state == ����99)
				{
					//TextOut(getMemDC(), vItem[i].rc.left, vItem[i].rc.top, TEXT("����99"), lstrlen(TEXT("����99")));
					//RectangleMake(getMemDC(), vItem[i].rc);
					IMAGEMANAGER->render("����99", getMemDC(), vItem[i].rc.left, vItem[i].rc.top, 0, 0, 40, 40);
				}
				if (vItem[i].state == ��Ȳ)
				{
					//TextOut(getMemDC(), vItem[i].rc.left, vItem[i].rc.top, TEXT("��Ȳ"), lstrlen(TEXT("��Ȳ")));
					//RectangleMake(getMemDC(), vItem[i].rc);
					IMAGEMANAGER->render("��Ȳ", getMemDC(), vItem[i].rc.left, vItem[i].rc.top, 0, 0, 40, 40);
				}
				if (vItem[i].state == ���������Ǳ���)
				{
					//TextOut(getMemDC(), vItem[i].rc.left, vItem[i].rc.top, TEXT("���������Ǳ���"), lstrlen(TEXT("���������Ǳ���")));
					//RectangleMake(getMemDC(), vItem[i].rc);
					IMAGEMANAGER->render("���������Ǳ���", getMemDC(), vItem[i].rc.left, vItem[i].rc.top, 0, 0, 40, 40);
				}
				if (vItem[i].state == �������)
				{
					//TextOut(getMemDC(), vItem[i].rc.left, vItem[i].rc.top, TEXT("�������"), lstrlen(TEXT("�������")));
					//RectangleMake(getMemDC(), vItem[i].rc);
					IMAGEMANAGER->render("�������", getMemDC(), vItem[i].rc.left, vItem[i].rc.top, 0, 0, 40, 40);
				}
				if (vItem[i].state == ī��)
				{
					//TextOut(getMemDC(), vItem[i].rc.left, vItem[i].rc.top, TEXT("ī��"), lstrlen(TEXT("ī��")));
					//RectangleMake(getMemDC(), vItem[i].rc);
					IMAGEMANAGER->render("ī��", getMemDC(), vItem[i].rc.left, vItem[i].rc.top, 0, 0, 30, 35);
				}
				if (vItem[i].state == �ڻ���������)
				{
					//TextOut(getMemDC(), vItem[i].rc.left, vItem[i].rc.top, TEXT("�ڻ���������"), lstrlen(TEXT("�ڻ���������")));
					//RectangleMake(getMemDC(), vItem[i].rc);
					IMAGEMANAGER->render("�ڻ���������", getMemDC(), vItem[i].rc.left, vItem[i].rc.top, 0, 0, 40, 40);
				}
				if (vItem[i].state == �𷡽ð�)
				{
					//TextOut(getMemDC(), vItem[i].rc.left, vItem[i].rc.top, TEXT("�𷡽ð�"), lstrlen(TEXT("�𷡽ð�")));
					//RectangleMake(getMemDC(), vItem[i].rc);
					IMAGEMANAGER->render("�𷡽ð�", getMemDC(), vItem[i].rc.left, vItem[i].rc.top, 0, 0, 40, 40);
				}
				if (vItem[i].state == ��������)
				{
					//TextOut(getMemDC(), vItem[i].rc.left, vItem[i].rc.top, TEXT("��������"), lstrlen(TEXT("��������")));
					//RectangleMake(getMemDC(), vItem[i].rc);
					if (IsChange == false)
					{
						IMAGEMANAGER->render("��������", getMemDC(), vItem[i].rc.left, vItem[i].rc.top, 0, 0, 50, 50);
					}
					if (IsChange == true)
					{
						IMAGEMANAGER->render("��������2", getMemDC(), vItem[i].rc.left, vItem[i].rc.top, 0, 0, 50, 50);
					}
				}
				if (vItem[i].state == ����ĳ����)
				{
					IMAGEMANAGER->render("����ĳ����", getMemDC(), vItem[i].rc.left, vItem[i].rc.top, 0, 0, 50, 100);
				}
				if (vItem[i].state == ����2)
				{
					IMAGEMANAGER->render("����2", getMemDC(), vItem[i].rc.left, vItem[i].rc.top, 0, 0, 40, 40);
				}
				if (vItem[i].state == ����3)
				{
					IMAGEMANAGER->render("����3", getMemDC(), vItem[i].rc.left, vItem[i].rc.top, 0, 0, 40, 40);
				}
				if (vItem[i].state == ����)
				{
					IMAGEMANAGER->render("����", getMemDC(), vItem[i].rc.left, vItem[i].rc.top, 0, 0, 50, 50);
				}
				//RectangleMake(getMemDC(), vItem[i].rc);
			}
		}
	}
}

void cItemManager::NewItemRender(int _currentmap)
{
	if (_sm->GetCurrentMap() == _currentmap)
	{
		for (int i = 0; i < vNewItem.size(); i++)
		{
			if (vNewItem[i].currentmap == _currentmap)
			{
				if (vNewItem[i].state == ����)
				{
					if (AnimCount %����ī��Ʈ == 0)
					{
						vNewItem[i].AnimX += 1;
						if (vNewItem[i].AnimX>6)
						{
							vNewItem[i].AnimX = 0;
						}
					}
					//TextOut(getMemDC(), vNewItem[i].rc.left, vNewItem[i].rc.top, TEXT("����"), lstrlen(TEXT("����")));
					//RectangleMake(getMemDC(), vNewItem[i].rc);
					IMAGEMANAGER->frameRender("����", getMemDC(), vNewItem[i].rc.left, vNewItem[i].rc.top, vNewItem[i].AnimX, IMAGEMANAGER->findImage("����")->getFrameY());
				}
				if (vNewItem[i].state == ��ź&&vNewItem[i].IsBomb == false)
				{
					//RectangleMake(getMemDC(), vNewItem[i].rc);
					IMAGEMANAGER->render("��ź", getMemDC(), vNewItem[i].rc.left, vNewItem[i].rc.top, 0, 0, 40, 40);
				}
				if (vNewItem[i].state == ��ź&&vNewItem[i].IsBomb == true)
				{
					if (100>vNewItem[i].contdown)
					{
						if (AnimCount % ��źī��Ʈ == 0)
						{
							vNewItem[i].AnimX++;
							if (vNewItem[i].AnimX >= 2)
							{
								vNewItem[i].AnimX = 0;
							}
						}
						IMAGEMANAGER->frameRender("��ź2", getMemDC(), vNewItem[i].x, vNewItem[i].y, vNewItem[i].AnimX, 0);
					}
					if (100<vNewItem[i].contdown&& vNewItem[i].contdown<130) // ���� 20�ʵ���
					{
						if (AnimCount % 1 == 0)
						{
							vNewItem[i].AnimX++;
							if (vNewItem[i].AnimX >= 22)
							{
								vNewItem[i].AnimX = 22;
							}
						}
						//RectangleMake(getMemDC(), vNewItem[i].rc);
						IMAGEMANAGER->frameRender("��ź3", getMemDC(), vNewItem[i].rc.left - 30, vNewItem[i].rc.top - 50, vNewItem[i].AnimX, 0);
					}
					if (vNewItem[i].contdown>130)
					{
					}
				}
				if (vNewItem[i].state == ������Ʈ��)
				{
					//TextOut(getMemDC(), vNewItem[i].rc.left, vNewItem[i].rc.top, TEXT("������Ʈ��"), lstrlen(TEXT("������Ʈ��")));					
					//RectangleMake(getMemDC(), vNewItem[i].rc);
					IMAGEMANAGER->render("��Ʈ", getMemDC(), vNewItem[i].rc.left, vNewItem[i].rc.top, 0, 0, 35, 30);
				}
				if (vNewItem[i].state == ������Ʈ)
				{
					//TextOut(getMemDC(), vNewItem[i].rc.left, vNewItem[i].rc.top, TEXT("������Ʈ"), lstrlen(TEXT("������Ʈ")));
					//RectangleMake(getMemDC(), vNewItem[i].rc);
					IMAGEMANAGER->render("��Ʈ2", getMemDC(), vNewItem[i].rc.left, vNewItem[i].rc.top, 0, 0, 35, 30);
				}
				if (vNewItem[i].state == ����1)
				{
					//RectangleMake(getMemDC(), vNewItem[i].rc);
					//TextOut(getMemDC(), vNewItem[i].rc.left, vNewItem[i].rc.top, TEXT("����1"), lstrlen(TEXT("����1")));
					if (AnimCount % ����1ī��Ʈ == 0)
					{
						vNewItem[i].AnimX += 1;
						if (vNewItem[i].AnimX>7)
						{
							vNewItem[i].AnimX = 0;
						}
					}
					//RectangleMake(getMemDC(), vNewItem[i].rc);
					IMAGEMANAGER->frameRender("����1", getMemDC(), vNewItem[i].rc.left, vNewItem[i].rc.top, vNewItem[i].AnimX, IMAGEMANAGER->findImage("����1")->getFrameY());
				}
				if (vNewItem[i].state == ����99)
				{
					//TextOut(getMemDC(), vNewItem[i].rc.left, vNewItem[i].rc.top, TEXT("����99"), lstrlen(TEXT("����99")));
					//RectangleMake(getMemDC(), vNewItem[i].rc);
					IMAGEMANAGER->render("����99", getMemDC(), vNewItem[i].rc.left, vNewItem[i].rc.top, 0, 0, 40, 40);
				}
				if (vNewItem[i].state == �ڻ���������)
				{
					//TextOut(getMemDC(), vNewItem[i].rc.left, vNewItem[i].rc.top, TEXT("�ڻ���������"), lstrlen(TEXT("�ڻ���������")));
					//RectangleMake(getMemDC(), vNewItem[i].rc);
					IMAGEMANAGER->render("�ڻ���������", getMemDC(), vNewItem[i].rc.left, vNewItem[i].rc.top, 0, 0, 40, 40);
				}
				if (vNewItem[i].state == �𷡽ð�)
				{
					//TextOut(getMemDC(), vNewItem[i].rc.left, vNewItem[i].rc.top, TEXT("�𷡽ð�"), lstrlen(TEXT("�𷡽ð�")));
					//RectangleMake(getMemDC(), vNewItem[i].rc);
					IMAGEMANAGER->render("�𷡽ð�", getMemDC(), vNewItem[i].rc.left, vNewItem[i].rc.top, 0, 0, 40, 40);
				}

			}
		}
	}
}

void cItemManager::Collision()
{
	//��ź�� �����浹
	for (int i = 0; i < vNewItem.size(); i++)
	{
		if (vNewItem[i].state == ��ź&&vNewItem[i].IsBomb == true)
		{
			for (int p = 0; p < _enemy->getVMinion().size(); p++)
			{

				if (IntersectRect(&temp, &vNewItem[i].rc, &_enemy->getVMinion()[p]->getRect()) && IsChange == false)
				{
					IsChange = true;
					_enemy->getVMinion()[p]->setHP(_enemy->getVMinion()[p]->getHP() - 50);
					break;
				}
			}
		}
	}

	//�ڻ���������� �����浹
	if (missileBomb.IsBomb == true)
	{
		for (int p = 0; p < _enemy->getVMinion().size(); p++)
		{
			if (IntersectRect(&temp, &missileBomb.rcBomb, &_enemy->getVMinion()[p]->getRect()))
			{				
				_enemy->getVMinion()[p]->setHP(_enemy->getVMinion()[p]->getHP() - 50);				
			}
		}
	}

	// �÷��̾�� ���� ��ź���浹����
	for (int i = 0; i < vNewItem.size(); i++)
	{
		if (vNewItem[i].state == ��ź&&vNewItem[i].IsBomb == true)
		{
			if (IntersectRect(&temp, &vNewItem[i].rc, &store.rc))
			{
				store.IsLive = false;
				break;
			}
			if (IntersectRect(&temp, &vNewItem[i].rc, &_player->GetRC()) && IsPlayerDamaged == false)
			{
				_player->SetHp(_player->GetHp() - 2);
				_player->SetAngle(getAngle(vNewItem[i].x, vNewItem[i].y, _player->GetX(), _player->GetY()));
				_player->SetAnimState(DAMAGE);
				IsPlayerDamaged = true;
				break;
			}
		}
	} // 

	  //��ź�� �⺻������ �浹�Ҷ� �з���
	for (int i = 0; i < vNewItem.size(); i++)
	{
		if (vNewItem[i].state == ��ź&&vNewItem[i].IsBomb == true)
		{
			for (int p = 0; p < vItem.size(); p++)
			{
				if (IntersectRect(&temp, &vItem[p].rc, &vNewItem[i].rc))
				{
					vItem[p].angle = getAngle(vNewItem[i].x, vNewItem[i].y, vItem[p].x, vItem[p].y);
					vItem[p].moveSpeed = ITEMMOVETIME;
					break;
				}
			}
		}
	}

	//��ź�� �������� �浹�Ҷ� �з���
	for (int i = 0; i < vNewItem.size(); i++)
	{
		if (vNewItem[i].state == ��ź&&vNewItem[i].IsBomb == true)
		{
			for (int p = 0; p < vNewItem.size(); p++)
			{
				if (IntersectRect(&temp, &vNewItem[p].rc, &vNewItem[i].rc))
				{
					vNewItem[p].angle = getAngle(vNewItem[i].x, vNewItem[i].y, vNewItem[p].x, vNewItem[p].y);
					vNewItem[p].moveSpeed = ITEMMOVETIME;
					break;
				}
			}
		}
	}


	
	//�������浹ó��
	for (int i = 0; i < vItem.size(); i++)
	{
		if (_player->GetIsFly() == false)
		{
			if (_sm->GetCurrentMap() == vItem[i].currentmap)
			{
				if (vItem[i].state == ����)
				{
					if (_player->GetRC().bottom > vItem[i].rc.top)
					{
						_player->SetY(vItem[i].y - 40);
						break;
					}
				}
			}
		}
	}
}

void cItemManager::ItemRectCollision(int _currentmap)
{
	//ȭ�� �⺻�����۵� �Ѿ��������


	for (int i = 0; i < vItem.size(); i++)
	{
		if (vItem[i].state == ����ĳ����)
		{
			continue;
		}
		if (vItem[i].rc.bottom>mapRC.rc.bottom)
		{
			vItem[i].angle = getAngle(vItem[i].x, vItem[i].y, mapRC.x, mapRC.y);
			vItem[i].moveSpeed = ITEMMOVETIME;
			break;
		}
		if (vItem[i].rc.left<mapRC.rc.left)
		{
			vItem[i].angle = getAngle(vItem[i].x, vItem[i].y, mapRC.x, mapRC.y);
			vItem[i].moveSpeed = ITEMMOVETIME;
			break;
		}
		if (vItem[i].rc.top<mapRC.rc.top)
		{
			vItem[i].angle = getAngle(vItem[i].x, vItem[i].y, mapRC.x, mapRC.y);
			vItem[i].moveSpeed = ITEMMOVETIME;
			break;
		}
		if (vItem[i].rc.right>mapRC.rc.right)
		{
			vItem[i].angle = getAngle(vItem[i].x, vItem[i].y, mapRC.x, mapRC.y);
			vItem[i].moveSpeed = ITEMMOVETIME;
			break;
		}

	}



	//ȭ�� �������۵� �Ѿ��������

	for (int i = 0; i < vNewItem.size(); i++)
	{
		if (vNewItem[i].rc.bottom>mapRC.rc.bottom)
		{
			vNewItem[i].angle = getAngle(vNewItem[i].x, vNewItem[i].y, mapRC.x, mapRC.y);
			vNewItem[i].moveSpeed = ITEMMOVETIME;
			break;
		}
		if (vNewItem[i].rc.left<mapRC.rc.left)
		{
			vNewItem[i].angle = getAngle(vNewItem[i].x, vNewItem[i].y, mapRC.x, mapRC.y);
			vNewItem[i].moveSpeed = ITEMMOVETIME;
			break;
		}
		if (vNewItem[i].rc.top<mapRC.rc.top)
		{
			vNewItem[i].angle = getAngle(vNewItem[i].x, vNewItem[i].y, mapRC.x, mapRC.y);
			vNewItem[i].moveSpeed = ITEMMOVETIME;
			break;
		}
		if (vNewItem[i].rc.right>mapRC.rc.right)
		{
			vNewItem[i].angle = getAngle(vNewItem[i].x, vNewItem[i].y, mapRC.x, mapRC.y);
			vNewItem[i].moveSpeed = ITEMMOVETIME;
			break;
		}
	}


}

void cItemManager::MissileControl()
{
	if (missileBomb.IsBomb == true)
	{
		missileBomb.nCount++;
		if (missileBomb.nCount<150)
		{
			missileBomb.rc = RectMakeCenter(missileBomb.x, missileBomb.y, �ڻ������������ذ�, �ڻ������������ذ�);
			if (KEYMANAGER->isStayKeyDown(VK_NUMPAD8))
			{
				missileBomb.y -= �̻��Ͻ��ǵ�;
			}
			if (KEYMANAGER->isStayKeyDown(VK_NUMPAD5))
			{
				missileBomb.y += �̻��Ͻ��ǵ�;
			}
			if (KEYMANAGER->isStayKeyDown(VK_NUMPAD4))
			{
				missileBomb.x -= �̻��Ͻ��ǵ�;
			}
			if (KEYMANAGER->isStayKeyDown(VK_NUMPAD6))
			{
				missileBomb.x += �̻��Ͻ��ǵ�;
			}
		}
		if (150<missileBomb.nCount&& missileBomb.nCount<200)
		{

		}
		if (200<missileBomb.nCount&& missileBomb.nCount<230)
		{
			missileBomb.rcBomb = RectMakeCenter(missileBomb.x, missileBomb.y, �ڻ�������������, �ڻ�������������);
		}
		if (missileBomb.nCount>230)
		{
			missileBomb.nCount = 0;
			missileBomb.IsBomb = false;
			missileBomb.rc = RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2, 0, 0);
			missileBomb.rcBomb = RectMakeCenter(-100, -100, 0, 0);
			missileBomb.AnimX = 0;
			missileBomb.AnimY = 300;
		}
	}
}

void cItemManager::MissileRender()
{
	if (missileBomb.IsBomb == true)
	{
		if (missileBomb.nCount<150)
		{
			//RectangleMake(getMemDC(), missileBomb.rc);
			IMAGEMANAGER->render("�ڻ���������2", getMemDC(), missileBomb.rc.left, missileBomb.rc.top, 0, 0, 50, 50);
		}
		if (150<missileBomb.nCount&& missileBomb.nCount<200)
		{
			missileBomb.AnimY -= 5;

			if (missileBomb.AnimY<0)
			{
				missileBomb.AnimY = 0;
			}
			IMAGEMANAGER->render("�ڻ���������3", getMemDC(), missileBomb.rc.left, missileBomb.rc.top - missileBomb.AnimY, 0, 0, 100, 200);
		}
		if (200<missileBomb.nCount&& missileBomb.nCount<230)
		{
			if (AnimCount % 1 == 0)
			{
				missileBomb.AnimX++;
				if (missileBomb.AnimX >= 22)
				{
					missileBomb.AnimX = 22;
				}
			}
			//RectangleMake(getMemDC(), missileBomb.rcBomb);
			IMAGEMANAGER->frameRender("��ź3", getMemDC(), missileBomb.rcBomb.left - 50, missileBomb.rcBomb.top - 50, missileBomb.AnimX, 0);
		}
	}
}

void cItemManager::StoreSetting(int _currentmap)
{
	store.x = 200;
	store.y = 250;
	store.StartX = store.x;
	store.StartY = store.y;
	store.angle = PI;
	store.AnimX = 0;
	store.IsLive = true;
	store.IsMove = false;
	store.currentmap = _currentmap;
	store.rc = RectMakeCenter(store.x, store.y, 100, 100);
}

void cItemManager::StoreUpdate()
{
	if (store.currentmap == _sm->GetCurrentMap() && store.IsLive == true)
	{
		float distance = getDistance(store.x, store.y, _player->GetX(), _player->GetY());
		if (80<distance)
		{
			distanceX = abs(_player->GetX() - store.x);
			if (distanceX>50)
			{
				IsLR = true;
			}
			else
			{
				IsLR = false;
			}
		}
		if (store.IsMove == false)
		{
			if (IntersectRect(&temp, &_player->GetRC(), &store.rc))
			{
				if (_player->GetMoney()>0)
				{
					if (distance<75 && IsChange == false)
					{
						store.angle = getAngle(_player->GetX(), _player->GetY(), store.x, store.y);
						store.IsMove = true;
						ItemMake(store.x, store.y, RND->getFromIntTo(��ź, ����1), store.currentmap, true);
						IsChange = true;
						_player->SetMoney(_player->GetMoney() - 1);
					}
				}
				if (IsLR == true)
				{
					if (_player->GetX()<store.x)//���ʿ����浹
					{
						_player->SetX(store.x - 65);
					}
					if (_player->GetX()>store.x)//�����ʿ����浹
					{
						_player->SetX(store.x + 65);
					}
				}
				if (IsLR == false)
				{
					if (_player->GetRC().top<store.rc.top)//���ʿ����浹
					{
						_player->SetY(store.y - 65);
					}
					if (_player->GetRC().bottom	>store.rc.bottom)//�Ʒ��ʿ����浹
					{
						_player->SetY(store.y + 65);
					}

				}
			}
		}
		if (store.IsMove == true)
		{
			store.nCount++;
			if (store.nCount<10)
			{
				store.x += cosf(store.angle) * 2;
				store.y += -sinf(store.angle) * 2;
				store.rc = RectMakeCenter(store.x, store.y, 100, 100);
			}
			if (store.nCount>10)
			{
				store.nCount = 0;
				store.x = store.StartX;
				store.y = store.StartY;
				store.rc = RectMakeCenter(store.x, store.y, 100, 100);
				store.IsMove = false;
			}
			if (IsLR == true)
			{
				if (_player->GetX()<store.x)//���ʿ����浹
				{
					_player->SetX(store.x - 65);
				}
				if (_player->GetX()>store.x)//�����ʿ����浹
				{
					_player->SetX(store.x + 65);
				}
			}
			if (IsLR == false)
			{
				if (_player->GetRC().top<store.rc.top)//���ʿ����浹
				{
					_player->SetY(store.y - 65);
				}
				if (_player->GetRC().bottom	>store.rc.bottom)//�Ʒ��ʿ����浹
				{
					_player->SetY(store.y + 65);
				}
			}
		}
	}


	if (store.currentmap == _sm->GetCurrentMap() && store.IsLive == false)
	{
		float distance = getDistance(store.x, store.y, _player->GetX(), _player->GetY());
		if (80<distance)
		{
			distanceX = abs(_player->GetX() - store.x);
			if (distanceX>50)
			{
				IsLR = true;
			}
			else
			{
				IsLR = false;
			}
		}
		if (store.IsMove == false)
		{
			if (IntersectRect(&temp, &_player->GetRC(), &store.rc))
			{
				if (IsLR == true)
				{
					if (_player->GetX()<store.x)//���ʿ����浹
					{
						_player->SetX(store.x - 65);
					}
					if (_player->GetX()>store.x)//�����ʿ����浹
					{
						_player->SetX(store.x + 65);
					}
				}
				if (IsLR == false)
				{
					if (_player->GetRC().top<store.rc.top)//���ʿ����浹
					{
						_player->SetY(store.y - 65);
					}
					if (_player->GetRC().bottom	>store.rc.bottom)//�Ʒ��ʿ����浹
					{
						_player->SetY(store.y + 65);
					}
				}
			}
		}
	}

}

void cItemManager::StoreRener()
{
	if (store.currentmap == _sm->GetCurrentMap() && store.IsLive == true)
	{
		if (IsChange == false)
		{
			IMAGEMANAGER->findImage("����")->setFrameX(0);
		}
		if (IsChange == true)
		{
			if (AnimCount % 6 == 0)
			{
				IMAGEMANAGER->findImage("����")->setFrameX(IMAGEMANAGER->findImage("����")->getFrameX() + 1);
				if (IMAGEMANAGER->findImage("����")->getFrameX() == IMAGEMANAGER->findImage("����")->getMaxFrameX())
				{
					IMAGEMANAGER->findImage("����")->setFrameX(1);
				}
			}
		}

		//RectangleMake(getMemDC(), store.rc);
		IMAGEMANAGER->frameRender("����", getMemDC(), store.rc.left, store.rc.top, IMAGEMANAGER->findImage("����")->getFrameX(), IMAGEMANAGER->findImage("����")->getFrameY());
	}

	if (store.currentmap == _sm->GetCurrentMap() && store.IsLive == false)
	{
		IMAGEMANAGER->frameRender("����", getMemDC(), store.rc.left, store.rc.top, IMAGEMANAGER->findImage("����")->getMaxFrameX(), IMAGEMANAGER->findImage("����")->getFrameY());
	}
}
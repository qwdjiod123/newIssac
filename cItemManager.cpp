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
	//		## 모든프레임렌더는 AnimCount를 씁니다. ##
	//==================================================================
	AnimCount++;
	if (AnimCount>500)
	{
		AnimCount = 0;
	}

	//==================================================================
	//		## 모든아이템들은 인터섹터에 텀을 주기위해 IsChage변수를 씁니다. ##
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
	//		## 아이템 셋팅 ##
	//==================================================================

	ItemSetting();

	ItemUpdate(정보방);
	ItemUpdate(첫번째방);
	ItemUpdate(두번째방);
	ItemUpdate(네번째방);
	ItemUpdate(다섯번째방);
	ItemUpdate(여섯번째방);
	ItemUpdate(일곱번째방);

	NewItemUpdate(정보방);
	NewItemUpdate(첫번째방);
	NewItemUpdate(두번째방);
	NewItemUpdate(네번째방);
	NewItemUpdate(다섯번째방);
	NewItemUpdate(여섯번째방);
	NewItemUpdate(일곱번째방);



	StoreUpdate();
	MissileControl();
	Collision();

	ItemRectCollision(정보방);
	//==================================================================
	//		## 모래시계 전용로직 ##
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

	//테스트
	if (KEYMANAGER->isOnceKeyDown(VK_F1))
	{
		_player->SetHp(_player->GetHp() - 1);
	}
}

void cItemManager::render(void)
{
	//==================================================================
	//		## 아이템 렌더 ##
	//==================================================================



	if (_sm->GetdoorChangeFrame()==300)
	{
		ItemRender(정보방);
		ItemRender(첫번째방);
		ItemRender(두번째방);
		ItemRender(네번째방);
		ItemRender(다섯번째방);
		ItemRender(여섯번째방);
		ItemRender(일곱번째방);

		NewItemRender(정보방);
		NewItemRender(첫번째방);
		NewItemRender(두번째방);
		NewItemRender(네번째방);
		NewItemRender(다섯번째방);
		NewItemRender(여섯번째방);
		NewItemRender(일곱번째방);
	}
	

	StoreRener();

	MissileRender();

	//테스트입니다.
	/*wsprintf(buffer, TEXT("HP:%d"), _player->GetHp());
	TextOut(getMemDC(), 200, 200, buffer, lstrlen(buffer));*/
	//RectangleMake(getMemDC(), mapRC.rc);

}

void cItemManager::ItemSetting()
{
	// 맵에아이템 셋팅
	if (_sm->GetCurrentMap() == 정보방&&ItemSetOnce[정보방] == false)
	{
		/*ItemMapSet(100, 400, 폭탄, 정보방);
		ItemMapSet(200, 400, 열쇠, 정보방);
		ItemMapSet(300, 400, 동전1, 정보방);
		ItemMapSet(400, 400, 동전99, 정보방);
		ItemMapSet(500, 400, 보물상자, 정보방);
		ItemMapSet(600, 400, 빨간하트, 정보방);
		ItemMapSet(700, 400, 빨간하트반, 정보방);
		ItemMapSet(100, 200, 썩은고기, 정보방);
		ItemMapSet(200, 200, 구렁텅이의군주, 정보방);
		ItemMapSet(300, 200, 박사의조정기, 정보방);
		ItemMapSet(400, 200, 모래시계, 정보방);
		ItemMapSet(500, 200, 카드, 정보방);
		ItemMapSet(600, 200, 유황, 정보방);*/

		ItemSetOnce[정보방] = true;
	}
	if (_sm->GetCurrentMap() == 첫번째방&&ItemSetOnce[첫번째방] == false)
	{
		ItemMapSet(100, 450, 벽돌, 첫번째방);
		ItemMapSet(150, 450, 벽돌, 첫번째방);
		ItemMapSet(200, 450, 벽돌, 첫번째방);
		ItemMapSet(250, 450, 벽돌, 첫번째방);
		ItemMapSet(300, 450, 벽돌, 첫번째방);
		ItemMapSet(350, 450, 벽돌, 첫번째방);
		ItemMapSet(400, 450, 벽돌, 첫번째방);
		ItemMapSet(450, 450, 벽돌, 첫번째방);
		ItemMapSet(500, 450, 벽돌, 첫번째방);
		ItemMapSet(550, 450, 벽돌, 첫번째방);
		ItemMapSet(600, 450, 벽돌, 첫번째방);
		ItemMapSet(650, 450, 벽돌, 첫번째방);
		ItemMapSet(700, 450, 벽돌, 첫번째방);

		ItemSetOnce[첫번째방] = true;
	}
	if (_sm->GetCurrentMap() == 두번째방&&ItemSetOnce[두번째방] == false)
	{
		StoreSetting(두번째방);
		ItemMapSet(400, 350, 유황, 두번째방);
		ItemMapSet(400, 390, 돌맹이, 두번째방);
		ItemSetOnce[두번째방] = true;
	}
	if (_sm->GetCurrentMap() == 네번째방&&ItemSetOnce[네번째방] == false)
	{
		ItemMapSet(300, 350, 빨간하트, 네번째방);
		ItemMapSet(500, 350, 폭탄, 네번째방);
		ItemSetOnce[네번째방] = true;
	}
	if (_sm->GetCurrentMap() == 다섯번째방&&ItemSetOnce[다섯번째방] == false)
	{
		ItemMapSet(100, 200, 열쇠, 다섯번째방);
		ItemMapSet(100, 500, 보물상자, 다섯번째방);
		ItemMapSet(400, 300, 썩은고기, 다섯번째방);
		ItemMapSet(395, 340, 돌맹이, 다섯번째방);
		ItemSetOnce[다섯번째방] = true;
	}
	if (_sm->GetCurrentMap() == 여섯번째방&&ItemSetOnce[여섯번째방] == false)
	{
		ItemMapSet(480, 350, 동전1, 여섯번째방);
		ItemMapSet(430, 350, 동전1, 여섯번째방);
		ItemMapSet(380, 350, 동전1, 여섯번째방);
		ItemMapSet(330, 350, 동전1, 여섯번째방);
		ItemSetOnce[여섯번째방] = true;
	}
	if (_sm->GetCurrentMap() == 일곱번째방&&ItemSetOnce[일곱번째방] == false)
	{
		ItemMapSet(300, 400, 모래시계, 일곱번째방);
		ItemMapSet(500, 400, 박사의조정기, 일곱번째방);
		ItemMapSet(300, 440, 돌맹이, 일곱번째방);
		ItemMapSet(500, 440, 돌맹이, 일곱번째방);

		ItemMapSet(250, 150, 상점캐릭터, 일곱번째방);
		ItemMapSet(300, 200, 동전99, 일곱번째방);
		ItemMapSet(400, 200, 카드, 일곱번째방);
		ItemMapSet(400, 240, 상점2, 일곱번째방);
		ItemMapSet(500, 200, 구렁텅이의군주, 일곱번째방);
		ItemMapSet(500, 240, 상점3, 일곱번째방);
		ItemSetOnce[일곱번째방] = true;
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

	if (_state == 보물상자)
	{
		item.RectSize = 보물상자렉트;
	}
	if (_state == 폭탄)
	{
		item.RectSize = 폭탄렉트;
	}
	if (_state == 열쇠)
	{
		item.RectSize = 열쇠렉트;
	}
	if (_state == 빨간하트반)
	{
		item.RectSize = 빨간하트반렉트;
	}
	if (_state == 빨간하트)
	{
		item.RectSize = 빨간하트렉트;
	}
	if (_state == 동전1)
	{
		item.RectSize = 동전1렉트;
	}
	if (_state == 동전99)
	{
		item.RectSize = 동전99렉트;
	}
	if (_state == 썩은고기)
	{
		item.RectSize = 썩은고기렉트;
	}
	if (_state == 카드)
	{
		item.RectSize = 카드렉트;
	}
	if (_state == 유황)
	{
		item.RectSize = 유황렉트;
	}
	if (_state == 구렁텅이의군주)
	{
		item.RectSize = 구렁텅이의군주렉트;
	}
	if (_state == 모래시계)
	{
		item.RectSize = 모래시계렉트;
	}
	if (_state == 박사의조정기)
	{
		item.RectSize = 박사조정기렉트;
	}
	if (_state == 돌맹이)
	{
		item.RectSize = 50;
	}
	if (_state == 상점캐릭터)
	{
		item.RectSize = 100;
	}
	if (_state == 상점2)
	{
		item.RectSize = 40;
	}
	if (_state == 상점3)
	{
		item.RectSize = 40;
	}
	if (_state == 벽돌)
	{
		item.RectSize = 50;
	}

	item.rc = RectMakeCenter(item.x, item.y, item.RectSize, item.RectSize);
	vItem.push_back(item);
}

void cItemManager::ItemUse(int _item)
{
	if (_item == 폭탄)
	{
		_player->SetBomb(_player->GetBomb() - 1);
		tag_Item item;
		item.x = _player->GetX();
		item.y = _player->GetY();
		item.IsBomb = true;
		item.state = 폭탄;
		item.currentmap = _sm->GetCurrentMap();
		item.AnimX = 0;
		//item.rc = RectMakeCenter(10, 10, 100, 100); // 폭탄이 터질때 랙트생성함 update()에서처리함
		vNewItem.push_back(item);
	}
	if (_item == 박사의조정기)
	{
		missileBomb.IsBomb = true;
	}
	if (_item == 모래시계)
	{
		IsTime = true;
	}
	if (_item == 카드)
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
	if (_state == 보물상자)
	{
		item.RectSize = 보물상자렉트;
	}
	if (_state == 폭탄)
	{
		item.RectSize = 폭탄렉트;
	}
	if (_state == 열쇠)
	{
		item.RectSize = 열쇠렉트;
	}
	if (_state == 빨간하트반)
	{
		item.RectSize = 빨간하트반렉트;
	}
	if (_state == 빨간하트)
	{
		item.RectSize = 빨간하트렉트;
	}
	if (_state == 동전1)
	{
		item.RectSize = 동전1렉트;
	}
	if (_state == 동전99)
	{
		item.RectSize = 동전99렉트;
	}
	if (_state == 썩은고기)
	{
		item.RectSize = 썩은고기렉트;
	}
	if (_state == 카드)
	{
		item.RectSize = 카드렉트;
	}
	if (_state == 유황)
	{
		item.RectSize = 유황렉트;
	}
	if (_state == 구렁텅이의군주)
	{
		item.RectSize = 구렁텅이의군주렉트;
	}
	if (_state == 모래시계)
	{
		item.RectSize = 모래시계렉트;
	}
	if (_state == 박사의조정기)
	{
		item.RectSize = 박사조정기렉트;
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
				//하트나 돈이 풀일때 안먹게하기위한 움직임					
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
				/////////////////////////////////////////////////////////////////충돌
				if (IntersectRect(&temp, &_player->GetRC(), &vItem[i].rc))
				{
					if (_player->GetKey()>0 && vItem[i].state == 보물상자)
					{
						IsChange = true;
						int static nCount = 0;
						nCount++;
						if (nCount>20)
						{
							nCount = 0;
							ItemMake(vItem[i].x, vItem[i].y, 빨간하트반, vItem[i].currentmap, true);
							_player->SetKey(_player->GetKey() - 1);
							DeleteItem(i);
						}
						break;
					}
					if (_player->GetKey() <= 0 && vItem[i].state == 보물상자)
					{
						float distance = getDistance(vItem[i].x, vItem[i].y, _player->GetX(), _player->GetY());
						if (distance<75)
						{
							vItem[i].angle = getAngle(_player->GetX(), _player->GetY(), vItem[i].x, vItem[i].y);
							vItem[i].moveSpeed = ITEMMOVETIME;
						}
					}
					if (vItem[i].state == 열쇠)
					{
						_player->SetKey(_player->GetKey() + 1);
						DeleteItem(i);
						break;
					}
					if (vItem[i].state == 폭탄)
					{
						_player->SetBomb(_player->GetBomb() + 1);
						DeleteItem(i);
						break;
					}
					if (vItem[i].state == 빨간하트반)
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
					if (vItem[i].state == 빨간하트)
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
					if (vItem[i].state == 동전1)
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
					if (vItem[i].state == 동전99)
					{
						_player->SetMoney(99);
						DeleteItem(i);
						break;
					}
					if (vItem[i].state == 썩은고기)
					{
						_player->SetAnimState(ETC);
						_player->SetmaxHp(_player->GetmaxHp() + 2);
						_player->SetHp(_player->GetHp() + 2);
						_player->addInVentory(썩은고기);
						DeleteItem(i);
						break;
					}
					if (vItem[i].state == 카드)
					{
						if (_player->GetMoney() >= 2)
						{
							_player->SetMoney(_player->GetMoney() - 2);
							_player->SetRange(500);
							_player->SetBulletSpeed(5);
							_player->SetAnimState(CARD);
							_player->addInVentory(카드);
							DeleteItem(i);
							break;
						}
					}
					if (vItem[i].state == 유황)
					{
						_player->SetAnimState(ETC);
						_player->SetArrow(유황);
						_player->addInVentory(유황);
						DeleteItem(i);
						break;
					}
					if (vItem[i].state == 구렁텅이의군주)
					{
						if (_player->GetMoney() >= 7)
						{
							_player->SetMoney(_player->GetMoney() - 7);
							_player->SetAnimState(ETC);
							_player->addInVentory(구렁텅이의군주);
							_player->SetIsFly(true);
							DeleteItem(i);
							break;
						}

					}
					if (vItem[i].state == 박사의조정기&&IsChange == false)
					{
						if (_player->GetSpace() == 없음)
						{

						}
						else
						{
							ItemMake(vItem[i].x, 400, 모래시계, _currentmap, false);
						}
						IsChange = true;
						_player->SetSpace(박사의조정기);
						DeleteItem(i);
						_player->SetAnimState(ETC);
						break;
					}
					if (vItem[i].state == 모래시계&&IsChange == false)
					{
						if (_player->GetSpace() == 없음)
						{

						}
						else
						{
							ItemMake(vItem[i].x, 400, 박사의조정기, _currentmap, false);
						}
						IsChange = true;
						_player->SetSpace(모래시계);
						_player->SetAnimState(ETC);
						DeleteItem(i);
						break;
					}
				}

				/////////////////////////////////////////////////////////////////위아래
				if (vItem[i].state == 썩은고기 || vItem[i].state == 유황 || vItem[i].state == 구렁텅이의군주 || vItem[i].state == 박사의조정기 || vItem[i].state == 모래시계)
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
				//		## 아이템움직이는로직 ## 상점에서 튀어나오는애들
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
					if (vNewItem[i].state == 열쇠&&IsChange == false)
					{
						_player->SetKey(_player->GetKey() + 1);
						DeleteNewItem(i);
						break;
					}
					if (vNewItem[i].state == 빨간하트반&&IsChange == false)
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
					if (vNewItem[i].state == 빨간하트&&IsChange == false)
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
					if (vNewItem[i].state == 동전1&&IsChange == false)
					{
						_player->SetMoney(_player->GetMoney() + 1);
						DeleteNewItem(i);
						break;
					}
					if (vNewItem[i].state == 동전99&&IsChange == false)
					{
						_player->SetMoney(99);
						DeleteNewItem(i);
						break;
					}
					if (vNewItem[i].state == 박사의조정기&&IsChange == false)
					{
						if (_player->GetSpace() == 없음)
						{

						}
						else
						{
							ItemMake(vNewItem[i].x, 400, 모래시계, _currentmap, false);
						}
						IsChange = true;
						_player->SetSpace(박사의조정기);
						DeleteNewItem(i);
						_player->SetAnimState(ETC);
						break;
					}
					if (vNewItem[i].state == 모래시계&&IsChange == false)
					{
						if (_player->GetSpace() == 없음)
						{

						}
						else
						{
							ItemMake(vNewItem[i].x, 400, 박사의조정기, _currentmap, false);
						}
						IsChange = true;
						_player->SetSpace(모래시계);
						DeleteNewItem(i);
						_player->SetAnimState(ETC);
						break;
					}
					if (vNewItem[i].state == 폭탄&&vNewItem[i].IsBomb == false && IsChange == false)
					{
						_player->SetBomb(_player->GetBomb() + 1);
						DeleteNewItem(i);
						break;
					}
				}

				if (vNewItem[i].state == 폭탄&&vNewItem[i].IsBomb == true)
				{
					vNewItem[i].contdown++;  // 폭발하기 100초전						
					if (100<vNewItem[i].contdown&& vNewItem[i].contdown<130) // 폭발 20초동안
					{
						vNewItem[i].rc = RectMakeCenter(vNewItem[i].x, vNewItem[i].y, BOMBSIZE, BOMBSIZE);
					}
					if (vNewItem[i].contdown>130)
					{
						vNewItem[i].contdown = 0; // 얘는 안해줘도되는데 찜찜해서 그냥함
						DeleteNewItem(i);   // 폭발후 삭제	
						IsPlayerDamaged = false;
						break;
					}
				}

				if (vNewItem[i].state == 박사의조정기 || vNewItem[i].state == 모래시계)
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
				if (vItem[i].state == 돌맹이)
				{
					//TextOut(getMemDC(), vItem[i].rc.left, vItem[i].rc.top, TEXT("돌맹이"), lstrlen(TEXT("돌맹이")));
					IMAGEMANAGER->render("돌맹이", getMemDC(), vItem[i].rc.left, vItem[i].rc.top, 0, 0, 50, 40);

				}
				if (vItem[i].state == 열쇠)
				{
					if (AnimCount %열쇠카운트 == 0)
					{
						vItem[i].AnimX += 1;
						if (vItem[i].AnimX>6)
						{
							vItem[i].AnimX = 0;
						}
					}
					//RectangleMake(getMemDC(), vItem[i].rc);
					IMAGEMANAGER->frameRender("열쇠", getMemDC(), vItem[i].rc.left, vItem[i].rc.top, vItem[i].AnimX, IMAGEMANAGER->findImage("열쇠")->getFrameY());
					//TextOut(getMemDC(), vItem[i].rc.left, vItem[i].rc.top, TEXT("열쇠"), lstrlen(TEXT("열쇠")));
				}
				if (vItem[i].state == 폭탄)
				{
					//RectangleMake(getMemDC(), vItem[i].rc);
					IMAGEMANAGER->render("폭탄", getMemDC(), vItem[i].rc.left, vItem[i].rc.top, 0, 0, 40, 40);
				}
				if (vItem[i].state == 빨간하트반)
				{
					//TextOut(getMemDC(), vItem[i].rc.left, vItem[i].rc.top, TEXT("빨간하트반"), lstrlen(TEXT("빨간하트반")));
					//RectangleMake(getMemDC(), vItem[i].rc);
					IMAGEMANAGER->render("하트", getMemDC(), vItem[i].rc.left, vItem[i].rc.top, 0, 0, 35, 30);
				}
				if (vItem[i].state == 빨간하트)
				{
					//TextOut(getMemDC(), vItem[i].rc.left, vItem[i].rc.top, TEXT("빨간하트"), lstrlen(TEXT("빨간하트")));					
					//RectangleMake(getMemDC(), vItem[i].rc);
					IMAGEMANAGER->render("하트2", getMemDC(), vItem[i].rc.left, vItem[i].rc.top, 0, 0, 35, 30);
				}
				if (vItem[i].state == 동전1)
				{
					//TextOut(getMemDC(), vItem[i].rc.left, vItem[i].rc.top, TEXT("동전1"), lstrlen(TEXT("동전1")));
					if (AnimCount %동전1카운트 == 0)
					{
						vItem[i].AnimX += 1;
						if (vItem[i].AnimX>7)
						{
							vItem[i].AnimX = 0;
						}
					}
					//RectangleMake(getMemDC(), vItem[i].rc);
					IMAGEMANAGER->frameRender("동전1", getMemDC(), vItem[i].rc.left, vItem[i].rc.top, vItem[i].AnimX, IMAGEMANAGER->findImage("동전1")->getFrameY());
				}
				if (vItem[i].state == 동전99)
				{
					//TextOut(getMemDC(), vItem[i].rc.left, vItem[i].rc.top, TEXT("동전99"), lstrlen(TEXT("동전99")));
					//RectangleMake(getMemDC(), vItem[i].rc);
					IMAGEMANAGER->render("동전99", getMemDC(), vItem[i].rc.left, vItem[i].rc.top, 0, 0, 40, 40);
				}
				if (vItem[i].state == 유황)
				{
					//TextOut(getMemDC(), vItem[i].rc.left, vItem[i].rc.top, TEXT("유황"), lstrlen(TEXT("유황")));
					//RectangleMake(getMemDC(), vItem[i].rc);
					IMAGEMANAGER->render("유황", getMemDC(), vItem[i].rc.left, vItem[i].rc.top, 0, 0, 40, 40);
				}
				if (vItem[i].state == 구렁텅이의군주)
				{
					//TextOut(getMemDC(), vItem[i].rc.left, vItem[i].rc.top, TEXT("구렁텅이의군주"), lstrlen(TEXT("구렁텅이의군주")));
					//RectangleMake(getMemDC(), vItem[i].rc);
					IMAGEMANAGER->render("구렁텅이의군주", getMemDC(), vItem[i].rc.left, vItem[i].rc.top, 0, 0, 40, 40);
				}
				if (vItem[i].state == 썩은고기)
				{
					//TextOut(getMemDC(), vItem[i].rc.left, vItem[i].rc.top, TEXT("썩은고기"), lstrlen(TEXT("썩은고기")));
					//RectangleMake(getMemDC(), vItem[i].rc);
					IMAGEMANAGER->render("썩은고기", getMemDC(), vItem[i].rc.left, vItem[i].rc.top, 0, 0, 40, 40);
				}
				if (vItem[i].state == 카드)
				{
					//TextOut(getMemDC(), vItem[i].rc.left, vItem[i].rc.top, TEXT("카드"), lstrlen(TEXT("카드")));
					//RectangleMake(getMemDC(), vItem[i].rc);
					IMAGEMANAGER->render("카드", getMemDC(), vItem[i].rc.left, vItem[i].rc.top, 0, 0, 30, 35);
				}
				if (vItem[i].state == 박사의조정기)
				{
					//TextOut(getMemDC(), vItem[i].rc.left, vItem[i].rc.top, TEXT("박사의조정기"), lstrlen(TEXT("박사의조정기")));
					//RectangleMake(getMemDC(), vItem[i].rc);
					IMAGEMANAGER->render("박사의조정기", getMemDC(), vItem[i].rc.left, vItem[i].rc.top, 0, 0, 40, 40);
				}
				if (vItem[i].state == 모래시계)
				{
					//TextOut(getMemDC(), vItem[i].rc.left, vItem[i].rc.top, TEXT("모래시계"), lstrlen(TEXT("모래시계")));
					//RectangleMake(getMemDC(), vItem[i].rc);
					IMAGEMANAGER->render("모래시계", getMemDC(), vItem[i].rc.left, vItem[i].rc.top, 0, 0, 40, 40);
				}
				if (vItem[i].state == 보물상자)
				{
					//TextOut(getMemDC(), vItem[i].rc.left, vItem[i].rc.top, TEXT("보물상자"), lstrlen(TEXT("보물상자")));
					//RectangleMake(getMemDC(), vItem[i].rc);
					if (IsChange == false)
					{
						IMAGEMANAGER->render("보물상자", getMemDC(), vItem[i].rc.left, vItem[i].rc.top, 0, 0, 50, 50);
					}
					if (IsChange == true)
					{
						IMAGEMANAGER->render("보물상자2", getMemDC(), vItem[i].rc.left, vItem[i].rc.top, 0, 0, 50, 50);
					}
				}
				if (vItem[i].state == 상점캐릭터)
				{
					IMAGEMANAGER->render("상점캐릭터", getMemDC(), vItem[i].rc.left, vItem[i].rc.top, 0, 0, 50, 100);
				}
				if (vItem[i].state == 상점2)
				{
					IMAGEMANAGER->render("상점2", getMemDC(), vItem[i].rc.left, vItem[i].rc.top, 0, 0, 40, 40);
				}
				if (vItem[i].state == 상점3)
				{
					IMAGEMANAGER->render("상점3", getMemDC(), vItem[i].rc.left, vItem[i].rc.top, 0, 0, 40, 40);
				}
				if (vItem[i].state == 벽돌)
				{
					IMAGEMANAGER->render("벽돌", getMemDC(), vItem[i].rc.left, vItem[i].rc.top, 0, 0, 50, 50);
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
				if (vNewItem[i].state == 열쇠)
				{
					if (AnimCount %열쇠카운트 == 0)
					{
						vNewItem[i].AnimX += 1;
						if (vNewItem[i].AnimX>6)
						{
							vNewItem[i].AnimX = 0;
						}
					}
					//TextOut(getMemDC(), vNewItem[i].rc.left, vNewItem[i].rc.top, TEXT("열쇠"), lstrlen(TEXT("열쇠")));
					//RectangleMake(getMemDC(), vNewItem[i].rc);
					IMAGEMANAGER->frameRender("열쇠", getMemDC(), vNewItem[i].rc.left, vNewItem[i].rc.top, vNewItem[i].AnimX, IMAGEMANAGER->findImage("열쇠")->getFrameY());
				}
				if (vNewItem[i].state == 폭탄&&vNewItem[i].IsBomb == false)
				{
					//RectangleMake(getMemDC(), vNewItem[i].rc);
					IMAGEMANAGER->render("폭탄", getMemDC(), vNewItem[i].rc.left, vNewItem[i].rc.top, 0, 0, 40, 40);
				}
				if (vNewItem[i].state == 폭탄&&vNewItem[i].IsBomb == true)
				{
					if (100>vNewItem[i].contdown)
					{
						if (AnimCount % 폭탄카운트 == 0)
						{
							vNewItem[i].AnimX++;
							if (vNewItem[i].AnimX >= 2)
							{
								vNewItem[i].AnimX = 0;
							}
						}
						IMAGEMANAGER->frameRender("폭탄2", getMemDC(), vNewItem[i].x, vNewItem[i].y, vNewItem[i].AnimX, 0);
					}
					if (100<vNewItem[i].contdown&& vNewItem[i].contdown<130) // 폭발 20초동안
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
						IMAGEMANAGER->frameRender("폭탄3", getMemDC(), vNewItem[i].rc.left - 30, vNewItem[i].rc.top - 50, vNewItem[i].AnimX, 0);
					}
					if (vNewItem[i].contdown>130)
					{
					}
				}
				if (vNewItem[i].state == 빨간하트반)
				{
					//TextOut(getMemDC(), vNewItem[i].rc.left, vNewItem[i].rc.top, TEXT("빨간하트반"), lstrlen(TEXT("빨간하트반")));					
					//RectangleMake(getMemDC(), vNewItem[i].rc);
					IMAGEMANAGER->render("하트", getMemDC(), vNewItem[i].rc.left, vNewItem[i].rc.top, 0, 0, 35, 30);
				}
				if (vNewItem[i].state == 빨간하트)
				{
					//TextOut(getMemDC(), vNewItem[i].rc.left, vNewItem[i].rc.top, TEXT("빨간하트"), lstrlen(TEXT("빨간하트")));
					//RectangleMake(getMemDC(), vNewItem[i].rc);
					IMAGEMANAGER->render("하트2", getMemDC(), vNewItem[i].rc.left, vNewItem[i].rc.top, 0, 0, 35, 30);
				}
				if (vNewItem[i].state == 동전1)
				{
					//RectangleMake(getMemDC(), vNewItem[i].rc);
					//TextOut(getMemDC(), vNewItem[i].rc.left, vNewItem[i].rc.top, TEXT("동전1"), lstrlen(TEXT("동전1")));
					if (AnimCount % 동전1카운트 == 0)
					{
						vNewItem[i].AnimX += 1;
						if (vNewItem[i].AnimX>7)
						{
							vNewItem[i].AnimX = 0;
						}
					}
					//RectangleMake(getMemDC(), vNewItem[i].rc);
					IMAGEMANAGER->frameRender("동전1", getMemDC(), vNewItem[i].rc.left, vNewItem[i].rc.top, vNewItem[i].AnimX, IMAGEMANAGER->findImage("동전1")->getFrameY());
				}
				if (vNewItem[i].state == 동전99)
				{
					//TextOut(getMemDC(), vNewItem[i].rc.left, vNewItem[i].rc.top, TEXT("동전99"), lstrlen(TEXT("동전99")));
					//RectangleMake(getMemDC(), vNewItem[i].rc);
					IMAGEMANAGER->render("동전99", getMemDC(), vNewItem[i].rc.left, vNewItem[i].rc.top, 0, 0, 40, 40);
				}
				if (vNewItem[i].state == 박사의조정기)
				{
					//TextOut(getMemDC(), vNewItem[i].rc.left, vNewItem[i].rc.top, TEXT("박사의조정기"), lstrlen(TEXT("박사의조정기")));
					//RectangleMake(getMemDC(), vNewItem[i].rc);
					IMAGEMANAGER->render("박사의조정기", getMemDC(), vNewItem[i].rc.left, vNewItem[i].rc.top, 0, 0, 40, 40);
				}
				if (vNewItem[i].state == 모래시계)
				{
					//TextOut(getMemDC(), vNewItem[i].rc.left, vNewItem[i].rc.top, TEXT("모래시계"), lstrlen(TEXT("모래시계")));
					//RectangleMake(getMemDC(), vNewItem[i].rc);
					IMAGEMANAGER->render("모래시계", getMemDC(), vNewItem[i].rc.left, vNewItem[i].rc.top, 0, 0, 40, 40);
				}

			}
		}
	}
}

void cItemManager::Collision()
{
	//폭탄과 적들충돌
	for (int i = 0; i < vNewItem.size(); i++)
	{
		if (vNewItem[i].state == 폭탄&&vNewItem[i].IsBomb == true)
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

	//박사의조정기와 적들충돌
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

	// 플레이어와 상점 폭탄과충돌로직
	for (int i = 0; i < vNewItem.size(); i++)
	{
		if (vNewItem[i].state == 폭탄&&vNewItem[i].IsBomb == true)
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

	  //폭탄과 기본아이템 충돌할때 밀려라
	for (int i = 0; i < vNewItem.size(); i++)
	{
		if (vNewItem[i].state == 폭탄&&vNewItem[i].IsBomb == true)
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

	//폭탄과 뉴아이템 충돌할때 밀려라
	for (int i = 0; i < vNewItem.size(); i++)
	{
		if (vNewItem[i].state == 폭탄&&vNewItem[i].IsBomb == true)
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


	
	//벽돌과충돌처리
	for (int i = 0; i < vItem.size(); i++)
	{
		if (_player->GetIsFly() == false)
		{
			if (_sm->GetCurrentMap() == vItem[i].currentmap)
			{
				if (vItem[i].state == 벽돌)
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
	//화면 기본아이템들 넘어가지마세요


	for (int i = 0; i < vItem.size(); i++)
	{
		if (vItem[i].state == 상점캐릭터)
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



	//화면 뉴아이템들 넘어가지마세요

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
			missileBomb.rc = RectMakeCenter(missileBomb.x, missileBomb.y, 박사의조정기조준경, 박사의조정기조준경);
			if (KEYMANAGER->isStayKeyDown(VK_NUMPAD8))
			{
				missileBomb.y -= 미사일스피드;
			}
			if (KEYMANAGER->isStayKeyDown(VK_NUMPAD5))
			{
				missileBomb.y += 미사일스피드;
			}
			if (KEYMANAGER->isStayKeyDown(VK_NUMPAD4))
			{
				missileBomb.x -= 미사일스피드;
			}
			if (KEYMANAGER->isStayKeyDown(VK_NUMPAD6))
			{
				missileBomb.x += 미사일스피드;
			}
		}
		if (150<missileBomb.nCount&& missileBomb.nCount<200)
		{

		}
		if (200<missileBomb.nCount&& missileBomb.nCount<230)
		{
			missileBomb.rcBomb = RectMakeCenter(missileBomb.x, missileBomb.y, 박사의조정기폭발, 박사의조정기폭발);
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
			IMAGEMANAGER->render("박사의조정기2", getMemDC(), missileBomb.rc.left, missileBomb.rc.top, 0, 0, 50, 50);
		}
		if (150<missileBomb.nCount&& missileBomb.nCount<200)
		{
			missileBomb.AnimY -= 5;

			if (missileBomb.AnimY<0)
			{
				missileBomb.AnimY = 0;
			}
			IMAGEMANAGER->render("박사의조정기3", getMemDC(), missileBomb.rc.left, missileBomb.rc.top - missileBomb.AnimY, 0, 0, 100, 200);
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
			IMAGEMANAGER->frameRender("폭탄3", getMemDC(), missileBomb.rcBomb.left - 50, missileBomb.rcBomb.top - 50, missileBomb.AnimX, 0);
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
						ItemMake(store.x, store.y, RND->getFromIntTo(폭탄, 동전1), store.currentmap, true);
						IsChange = true;
						_player->SetMoney(_player->GetMoney() - 1);
					}
				}
				if (IsLR == true)
				{
					if (_player->GetX()<store.x)//왼쪽에서충돌
					{
						_player->SetX(store.x - 65);
					}
					if (_player->GetX()>store.x)//오른쪽에서충돌
					{
						_player->SetX(store.x + 65);
					}
				}
				if (IsLR == false)
				{
					if (_player->GetRC().top<store.rc.top)//위쪽에서충돌
					{
						_player->SetY(store.y - 65);
					}
					if (_player->GetRC().bottom	>store.rc.bottom)//아래쪽에서충돌
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
				if (_player->GetX()<store.x)//왼쪽에서충돌
				{
					_player->SetX(store.x - 65);
				}
				if (_player->GetX()>store.x)//오른쪽에서충돌
				{
					_player->SetX(store.x + 65);
				}
			}
			if (IsLR == false)
			{
				if (_player->GetRC().top<store.rc.top)//위쪽에서충돌
				{
					_player->SetY(store.y - 65);
				}
				if (_player->GetRC().bottom	>store.rc.bottom)//아래쪽에서충돌
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
					if (_player->GetX()<store.x)//왼쪽에서충돌
					{
						_player->SetX(store.x - 65);
					}
					if (_player->GetX()>store.x)//오른쪽에서충돌
					{
						_player->SetX(store.x + 65);
					}
				}
				if (IsLR == false)
				{
					if (_player->GetRC().top<store.rc.top)//위쪽에서충돌
					{
						_player->SetY(store.y - 65);
					}
					if (_player->GetRC().bottom	>store.rc.bottom)//아래쪽에서충돌
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
			IMAGEMANAGER->findImage("슬롯")->setFrameX(0);
		}
		if (IsChange == true)
		{
			if (AnimCount % 6 == 0)
			{
				IMAGEMANAGER->findImage("슬롯")->setFrameX(IMAGEMANAGER->findImage("슬롯")->getFrameX() + 1);
				if (IMAGEMANAGER->findImage("슬롯")->getFrameX() == IMAGEMANAGER->findImage("슬롯")->getMaxFrameX())
				{
					IMAGEMANAGER->findImage("슬롯")->setFrameX(1);
				}
			}
		}

		//RectangleMake(getMemDC(), store.rc);
		IMAGEMANAGER->frameRender("슬롯", getMemDC(), store.rc.left, store.rc.top, IMAGEMANAGER->findImage("슬롯")->getFrameX(), IMAGEMANAGER->findImage("슬롯")->getFrameY());
	}

	if (store.currentmap == _sm->GetCurrentMap() && store.IsLive == false)
	{
		IMAGEMANAGER->frameRender("슬롯", getMemDC(), store.rc.left, store.rc.top, IMAGEMANAGER->findImage("슬롯")->getMaxFrameX(), IMAGEMANAGER->findImage("슬롯")->getFrameY());
	}
}
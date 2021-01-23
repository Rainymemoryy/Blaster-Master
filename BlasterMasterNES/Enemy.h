#pragma once
#include "GameObject.h"
#include "Utils.h"
#include <cstdlib>
#include "Item.h"
#include "ItemHp.h"
#include "ItemH.h"
class CEnemy :public CGameObject
{
public:
	float hp;
	float damage=10;
	bool visible = true;
	vector<LPGAMEOBJECT> *listObj;
	vector<LPGAMEOBJECT>* coObjects;
	CGameObject *targerBullet3 = NULL;
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom) {}
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL, vector<LPGAMEOBJECT> *listObj = NULL) {}
	virtual void Render() {}
	virtual void SetState(int state) {}
	virtual void LastUpdate() {}
	void DropItem() {

		//srand(time(NULL));

		
		int n= rand() % 4 + 0;
		if (!n) {
			DebugOut(L"[Enemy] Drop item: %d\n", dropItem);
			CGameObject *obj;
			float ix, iy;
			this->TinhTam(ix, iy);
			switch (dropItem)
			{
			case Item_HP:
				obj = new CItemHp(ix-8, iy-8);
				listObj->push_back(obj);
				break;
			
			case Item_H:
				obj = new CItemH(ix - 8, iy - 8);
				listObj->push_back(obj);
				break;
			default:
				break;
			}
		}
	}
	virtual float GetDamage() { return damage; }
	
	void SetTargetBullet3(CGameObject *target) { targerBullet3 = target; }
};

#pragma once
#include "GameObject.h"
#include "Utils.h"
#include <cstdlib>


class CEnemy :public CGameObject
{
public:
	float hp;
	float damage=10;

	int dropItem = -1;
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom) {}
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL, vector<LPGAMEOBJECT> *listObj = NULL) {}
	virtual void Render() {}
	virtual void SetState(int state) {}
	virtual void LastUpdate() {}

	void DropItem() {

		srand(time(NULL));
		int n= rand() % 2 + 0;
		if (n) {
			DebugOut(L"[Enemy] Drop item: %d\n", dropItem);
			
		}
	}

	virtual float GetDamage() { return damage; }
};

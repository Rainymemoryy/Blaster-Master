#pragma once
#include "GameObject.h"
#include "Utils.h"

class CEnemy :public CGameObject
{
public:
	float hp;
	float damage=10;


	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom) {}
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL, vector<LPGAMEOBJECT> *listObj = NULL) {}
	virtual void Render() {}
	virtual void SetState(int state) {}
	virtual void LastUpdate() {}

	virtual float GetDamage() { return damage; }
};

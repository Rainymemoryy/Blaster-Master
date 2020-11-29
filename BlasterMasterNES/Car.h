#pragma once
#include "GameObject.h"
class CCar : public CGameObject
{
	vector<LPGAMEOBJECT> *listObj;
public:
	virtual void Render();
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects = NULL, vector<LPGAMEOBJECT> *listObj = NULL);
};

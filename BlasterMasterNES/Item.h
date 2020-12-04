#pragma once
#include "GameObject.h"


#define Item_HP	201


class CItem :public CGameObject
{
public:
	virtual void Render() {}
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b) {}
};


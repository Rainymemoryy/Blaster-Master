#pragma once
#include "GameObject.h"


#define Item_HP	201
#define Item_1	203
#define Item_2	204
#define Item_3	205
#define Item_H	206
#define Item_Bous	207



class CItem :public CGameObject
{
public:
	virtual void Render() {}
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b) {}
};


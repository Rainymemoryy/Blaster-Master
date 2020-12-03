#pragma once
#include "GameObject.h"
#include "Brick.h"
class CStair:public CGameObject
{
	float r, b;
public:
	CStair(float l, float t, float r, float b) {
		this->x = l;
		this->y = t;
		this->r = r;
		this->b = b;
	};
	virtual void Render();
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	

};


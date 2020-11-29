#pragma once
#include "GameObject.h"

#define BRICK_DAMAGE 0.1f
class CBrick : public CGameObject
{
	float r, b;

public:
	virtual void Render();
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	void SetRB(float a, float b);
};
#pragma once
#include "GameObject.h"


class CBlock1 : public CGameObject
{
protected:
	float r, b;
	float damage = 0;
public:

	CBlock1(float x, float y);

	virtual void Render();
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	virtual float GetDamage() { return damage; };

};
#pragma once
#include "GameObject.h"


class CBrick : public CGameObject
{
protected:
	
	float damage=0;
public:
	float r, b;
	CBrick(float l, float t, float r, float b);

	virtual void Render();
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	virtual float GetDamage() { return damage; };

};
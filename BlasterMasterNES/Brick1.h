#pragma once
#include "GameObject.h"
#include "Brick.h"


#define Brick1_Damage 0.1f


class CBrick1 : public CBrick
{
public:
	CBrick1(float l, float t, float r, float b) : CBrick(l, t, r, b) {
		damage = Brick1_Damage;
	};
};
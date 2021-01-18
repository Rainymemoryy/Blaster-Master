#pragma once
#include "GameObject.h"
#include "Brick.h"


#define Brick221_Damage 0.6f


class COvhAlert : public CBrick
{
public:
	COvhAlert(float l, float t, float r, float b) : CBrick(l, t, r, b) {
		damage = Brick221_Damage;
	};
	//void getpot(float l, float t, float r, float b) {l=this->x};
};
#include "Credit.h"

CCredit::CCredit(int type,float x, float y, float vx, float vy)
{
	this->x = x;
	this->y = y;
	this->vx = vx;
	this->vy = vy;
	this->type = type;
}
void CCredit::Render(int dt)
{
	x += vx * dt;
	y += vy * dt;

	if (type == Credit_Type_Ani) {
		ani->Render(round(x), round(y), 255, -1);
	}
	else if (type == Credit_Type_String) {
		for (int i = 0; i < listSprite->size(); i++) {

			listSprite->at(i)->Draw(round(x+8*i), round(y), 255);
		}
	}
}

void CCredit::SetSpeed(float vx, float vy)
{
	this->vx = vx;
	this->vy = vy;
}



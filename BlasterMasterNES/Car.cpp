#include "Car.h"

void CCar::Render()
{
	
	if (nx >= 0)animation_set->at(0)->Render(round(x), round(y), 255, 0);
	else
		animation_set->at(0)->Render(round(x), round(y), 255, 1);
	listObj->at(0)->Render();
	//RenderBoundingBox();
}

void CCar::GetBoundingBox(float & l, float & t, float & r, float & b)
{
	l = x;
	t = y;
	r = x + 26;
	b = y + 26;
}

void CCar::Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects, vector<LPGAMEOBJECT>* listObj)
{
	this->listObj = listObj;
}
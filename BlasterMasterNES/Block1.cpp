#include "Block1.h"


CBlock1::CBlock1(float x, float y)
{
	this->x = x - 2;
	this->y = y-2;
	this->r = x+ 2;
	this->b = y+2;

}

void CBlock1::Render()
{
	//RenderBoundingBox();
}

void CBlock1::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = x;
	t = y;
	r = this->r;
	b = this->b;
}

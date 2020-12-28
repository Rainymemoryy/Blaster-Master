#include "Brick.h"

CBrick::CBrick(float l, float t, float r, float b)
{
	this->x = l;
	this->y = t; 
	this->r = r;
	this->b = b;
	
}

void CBrick::Render()
{
	//RenderBoundingBox();
}

void CBrick::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = x;
	t = y;
	r = this->r;
	b = this->b;
}

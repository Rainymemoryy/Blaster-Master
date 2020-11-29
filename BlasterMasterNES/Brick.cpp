#include "Brick.h"

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

void CBrick::SetRB(float a, float b)
{
	this->r = a;
	this->b = b;
}
#include "Stair.h"




void CStair::Render()
{
//	RenderBoundingBox();
}

void CStair::GetBoundingBox(float & l, float & t, float & r, float & b)
{
	l = x;
	t = y;
	r = this->r;
	b = this->b;
}

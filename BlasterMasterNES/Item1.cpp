#include "Item1.h"

void CItem1::Render()
{
	//RenderBoundingBox();
	animation_set->at(0)->Render(round(x), round(y), 255, -1);
}

void CItem1::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + Item1_Box_Width;
	b = y + Item1_Box_Height;
}

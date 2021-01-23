#include "Item2.h"

void CItem2::Render()
{
	//RenderBoundingBox();
	animation_set->at(0)->Render(round(x), round(y), 255, -1);
}

void CItem2::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + Item2_Box_Width;
	b = y + Item2_Box_Height;
}

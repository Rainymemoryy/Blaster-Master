#include "Item3.h"

void CItem3::Render()
{
	//RenderBoundingBox();
	animation_set->at(0)->Render(round(x), round(y), 255, -1);
}

void CItem3::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + Item3_Box_Width;
	b = y + Item3_Box_Height;
}

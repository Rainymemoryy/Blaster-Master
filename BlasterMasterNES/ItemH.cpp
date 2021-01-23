#include "ItemH.h"

void CItemH::Render()
{
	//RenderBoundingBox();
	animation_set->at(0)->Render(round(x), round(y), 255, -1);
}

void CItemH::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + ItemH_Box_Width;
	b = y + ItemH_Box_Height;
}

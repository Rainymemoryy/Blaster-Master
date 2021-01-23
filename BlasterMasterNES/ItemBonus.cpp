#include "ItemBonus.h"

void CItemBonus::Render()
{
	//RenderBoundingBox();
	animation_set->at(0)->Render(round(x), round(y), 255, -1);
}

void CItemBonus::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + ItemBonus_Box_Width;
	b = y + ItemBonus_Box_Height;
}

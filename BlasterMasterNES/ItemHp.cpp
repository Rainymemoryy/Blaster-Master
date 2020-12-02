#include "ItemHp.h"

void CItemHp::Render()
{
	//RenderBoundingBox();
	animation_set->at(0)->Render(round(x), round(y), 255, -1);
}

void CItemHp::GetBoundingBox(float & l, float & t, float & r, float & b)
{
	l = x;
	t = y;
	r = x+ ItemHP_Box_Width;
	b = y + ItemHP_Box_Height;
}

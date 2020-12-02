#include "Brick2.h"

void CBrick2::Render()
{
	animation_set->at(0)->Render(round(x), round(y), 255, -1);
}

#pragma once
#include "Item.h" 

#define Item3_HP			20
#define Item3_Box_Height	16
#define Item3_Box_Width	16

#define Item3_AniSet		905
class CItem3 : public  CItem
{
public:
	CItem3(float x, float y) {
		this->SetAnimationSet(CAnimationSets::GetInstance()->Get(Item3_AniSet));
		this->x = x;
		this->y = y;
	}

	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	//float Get1() { return Item1_HP; }
};


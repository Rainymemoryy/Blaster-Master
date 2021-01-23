#pragma once
#include "Item.h" 

#define Item1_HP			20
#define Item1_Box_Height	16
#define Item1_Box_Width	16

#define Item1_AniSet		903
class CItem1 : public  CItem
{
public:
	CItem1(float x, float y) {
		this->SetAnimationSet(CAnimationSets::GetInstance()->Get(Item1_AniSet));
		this->x = x;
		this->y = y;
	}

	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	//float Get1() { return Item1_HP; }
};


#pragma once
#include "Item.h" 

#define ItemBonus_HP			20
#define ItemBonus_Box_Height	13
#define ItemBonus_Box_Width	16

#define ItemBonus_AniSet		907
class CItemBonus : public  CItem
{
public:
	CItemBonus(float x, float y) {
		this->SetAnimationSet(CAnimationSets::GetInstance()->Get(ItemBonus_AniSet));
		this->x = x;
		this->y = y;
	}

	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	//float Get1() { return Item1_HP; }
};


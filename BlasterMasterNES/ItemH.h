#pragma once
#include "Item.h" 

#define ItemH_HP			20
#define ItemH_Box_Height	16
#define ItemH_Box_Width	16

#define ItemH_AniSet		906
class CItemH : public  CItem
{
public:
	CItemH(float x, float y) {
		this->SetAnimationSet(CAnimationSets::GetInstance()->Get(ItemH_AniSet));
		this->x = x;
		this->y = y;
	}

	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	//float Get1() { return Item1_HP; }
};


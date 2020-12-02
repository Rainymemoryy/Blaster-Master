#pragma once
#include "Item.h" 

#define ItemHP_HP			20
#define ItemHP_Box_Height	16
#define ItemHP_Box_Width	16

#define ItemHP_AniSet		902
class CItemHp : public  CItem
{
public :
	CItemHp(float x, float y) { 
		this->SetAnimationSet(CAnimationSets::GetInstance()->Get(ItemHP_AniSet));
		this->x = x;
		this->y = y;
	}

	virtual void Render();
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	float GetHP() { return ItemHP_HP; }
};


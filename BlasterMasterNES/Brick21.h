#pragma once
#pragma once
#include "GameObject.h"
#include "Brick.h"

#define Brick21_AniSet	1001

class CBrick21 : public CBrick
{
public:


	CBrick21(float l, float t, float r, float b) : CBrick(l, t, r, b)
	{
		this->SetAnimationSet(CAnimationSets::GetInstance()->Get(Brick21_AniSet));
	};

	virtual void Render();
};
#pragma once
#include "GameObject.h"
#include "Brick.h"

#define Brick2_AniSet	913

class CBrick2 : public CBrick
{
public:

	
	CBrick2(float l, float t, float r, float b) : CBrick(l, t, r, b) {
		this->SetAnimationSet(CAnimationSets::GetInstance()->Get(Brick2_AniSet));
	};

	virtual void Render();
};
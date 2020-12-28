#pragma once

#include "Sprites.h"
#include "Animations.h"

#define Credit_Type_Ani		1
#define Credit_Type_String	2

class CCredit
{
protected:
	int type = Credit_Type_Ani;



	float x=0, y=0;
	float vx=0, vy=0;
	int dt;

	CAnimation* ani;
	vector<CSprite * > *listSprite = new vector<CSprite *>();

	

public:
	CCredit(int type, float x, float y, float vx, float vy);
	void Render(int dt);
	void SetSpeed(float vx,float vy);


	void SetAni(LPANIMATION ani) {
		this->ani = ani;
	}
	void SetSpriteString(vector<CSprite * > *listSprite) {
		this->listSprite = listSprite;
	}
	
};


#pragma once
#include "GameObject.h"
#include "Brick.h"
#include "Utils.h"
#include "Car.h"
#include "Bullet.h"
#include "Enemy.h"

#define Enemy2_Box_Height		16
#define Enemy2_Box_Width		18
#define Enemy2_HP				100
#define Enemy2_VX				0.05f
#define Enemy2_VY				0.05f
#define Enemy2_TimeBanDan		2000
#define Enemy2_TimeAniBanDan	300
#define Enemy2_AniSet			802
#define Enemy2_Ani_Left			0
#define Enemy2_Ani_Right		1

#define Enemy2_Damge		25.f

class CEnemy2 : public CEnemy
{
	int timeBanDan = 0;
	bool isBanDan = false;
	int timeAniBanDan=-1;
	
	//vector<LPGAMEOBJECT> *listObj;
public:
	CEnemy2(float x, float y);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects = NULL, vector<LPGAMEOBJECT> *listObj = NULL);
	virtual void Render();
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void LastUpdate();
	virtual float GetDamge() { return 20.f; };

	void BanDan();
};

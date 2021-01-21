#pragma once
#include "GameObject.h"
#include "Brick.h"
#include "Utils.h"
#include "Car.h"
#include "Bullet.h"
#include "Enemy.h"

#define Enemy9_Box_Height		21
#define Enemy9_Box_Width		18
#define Enemy9_HP				100
#define Enemy9_VX				0.15f
#define Enemy9_VY				0.05f
#define Enemy9_TimeNgungBanDan		2000
#define Enemy9_TimeAniBanDan	300
#define Enemy9_AniSet			809
#define Enemy9_Ani_Left			0
#define Enemy9_Ani_Right		1

#define Enemy9_Damge		25.f

#define Enemy9_Delay		1000

class CEnemy9 : public CEnemy
{
	int timeBanDan = 0;
	bool isBanDan = false;
	int timeAniBanDan = -1;
	int timeNgungBanDan = -1;

	//vector<LPGAMEOBJECT> *listObj;
public:
	CEnemy9(float x, float y);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects = NULL, vector<LPGAMEOBJECT> *listObj = NULL);
	virtual void Render();
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void LastUpdate();
	virtual float GetDamge() { return 20.f; };

	void BanDan();
};

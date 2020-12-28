#pragma once
#include "GameObject.h"
#include "Brick.h"
#include "Utils.h"
#include "Car.h"
#include "Bullet.h"
#include "Enemy.h"

#define Enemy7_Box_Width	26
#define Enemy7_Box_Height	18

#define Enemy7_HP			100
#define Enemy7_AY			0.014f
#define Enemy7_VX			0.05f
#define Enemy7_VY			0.25f

#define Enemy7_AniSet		807
#define Enemy7_Ani_Left		0
#define Enemy7_Ani_Right	1

#define Enemy7_Damge		25.f
#define Enemy7_NgungTimeBanDan	1500
#define Enemy7_Time1LanBanDan	200
#define Enemy7_SoLanBanDan	4

class CEnemy7:public CEnemy
{
	float max_x, min_x;
	int timeBanDan = 0;
	int lastBanDan = 0;
	int soLanBanDan = Enemy7_SoLanBanDan;


public:
	CEnemy7(float x, float y, float min_x, float max_x);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects = NULL, vector<LPGAMEOBJECT> *listObj = NULL);
	virtual void Render();
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void LastUpdate();

	virtual float GetDamge() { return Enemy7_Damge; };
	void BanDan();
};


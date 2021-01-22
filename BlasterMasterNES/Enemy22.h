#pragma once
#include "GameObject.h"
#include "Brick.h"
#include "Utils.h"
#include "Car.h"
#include "Bullet.h"

#include "Enemy.h"

#define Enemy22_Box_Width	16
#define Enemy22_Box_Height	16

#define Enemy22_HP			100
#define Enemy22_AY			0.014f
#define Enemy22_VX			0.1f
#define Enemy22_VY			0.05f

#define Enemy22_AniSet		302
#define Enemy22_Ani_Left		0
#define Enemy22_Ani_Right	1

#define Enemy22_Damge		25.f
#define Enemy22_Damge_Bullet		20.f

#define Enemy22_TimeBanDan	1500
#define Enemy22_Time1LanBanDan	1500
#define Enemy22_TimeDiChuyen	1500

#define Enemy22_SoLanBanDan	4

class CEnemy22 :public CEnemy
{
	float max_x, min_x;
	int timeNgungBanDan = 0;
	int time1LanBanDan = 200;
	int soLanBanDan = Enemy22_SoLanBanDan;
	float timeDiChuyen;

public:
	int i;
	int j;

	CEnemy22(float x, float y);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects = NULL, vector<LPGAMEOBJECT> *listObj = NULL);
	virtual void Render();
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void LastUpdate();

	virtual float GetDamge() { return Enemy22_Damge; };
	void BanDan();
};


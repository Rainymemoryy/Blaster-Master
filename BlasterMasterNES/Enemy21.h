#pragma once
#include "GameObject.h"
#include "Brick.h"
#include "Utils.h"
#include "Car.h"
#include "Bullet.h"

#include "Enemy.h"

#define Enemy21_Box_Width	26
#define Enemy21_Box_Height	26

#define Enemy21_HP			100
#define Enemy21_AY			0.014f
#define Enemy21_VX			0.05f
#define Enemy21_VY			0.25f

#define Enemy21_AniSet		301
#define Enemy21_Ani_Left		0
#define Enemy21_Ani_Right	1

#define Enemy21_Damge		25.f
#define Enemy21_Damge_Bullet		20.f

#define Enemy21_TimeBanDan	1500
#define Enemy21_Time1LanBanDan	1500
#define Enemy21_SoLanBanDan	4

class CEnemy21 :public CEnemy
{
	float max_x, min_x;
	int timeNgungBanDan = 0;
	int time1LanBanDan = 200;
	int soLanBanDan = Enemy21_SoLanBanDan;


public:
	int i;
	CEnemy21(float x, float y);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects = NULL, vector<LPGAMEOBJECT> *listObj = NULL);
	virtual void Render();
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void LastUpdate();

	virtual float GetDamge() { return Enemy21_Damge; };
	void BanDan();
};


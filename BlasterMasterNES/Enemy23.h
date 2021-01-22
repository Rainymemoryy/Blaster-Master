#pragma once
#pragma once
#include "GameObject.h"
#include "Brick.h"
#include "Utils.h"
#include "Car.h"
#include "Bullet.h"

#include "Enemy.h"

#define Enemy23_Box_Width	24
#define Enemy23_Box_Height	32

#define Enemy23_HP			100
#define Enemy23_AY			0.014f
#define Enemy23_VX			0.25f
#define Enemy23_VY			0.25f

#define Enemy23_AniSet		303
#define Enemy23_Ani_Left		0
#define Enemy23_Ani_Right	1

#define Enemy23_Damge		25.f
#define Enemy23_Damge_Bullet		20.f

#define Enemy23_TimeBanDan	1500
#define Enemy23_Time1LanBanDan	1500
#define Enemy23_TimeDiChuyen	1500

#define Enemy23_SoLanBanDan	4

class CEnemy23 :public CEnemy
{
	float max_x, min_x;
	int timeNgungBanDan = 0;
	int time1LanBanDan = 200;
	float timeDiChuyen = 0;
	int soLanBanDan = Enemy23_SoLanBanDan;
	//float timeDiChuyen;

public:
	int i=0;
	int j;

	CEnemy23(float x, float y);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects = NULL, vector<LPGAMEOBJECT> *listObj = NULL);
	virtual void Render();
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void LastUpdate();

	virtual float GetDamge() { return Enemy23_Damge; };
	void BanDan();
};


#pragma once
#include "GameObject.h"
#include "Brick.h"
#include "Utils.h"
#include "Car.h"
#include "Bullet.h"
#include "Enemy.h"

#define Enemy6_Box_Width	16
#define Enemy6_Box_Height	26

#define Enemy6_HP			100
#define Enemy6_AY			0.014f
#define Enemy6_VX			0.05f
#define Enemy6_VY			0.25f

#define Enemy6_AniSet		806
#define Enemy6_Ani_Left		0
#define Enemy6_Ani_Right	1

#define Enemy6_Damge		25.f
#define Enemy6_TimeDiTrenMatDat	2000

class CEnemy6:public CEnemy
{
	float max_x, min_x;
	int timeDiTrenMatDat= Enemy6_TimeDiTrenMatDat;
	int soLanNhay = 2;
	
public :
	CEnemy6(float x, float y, float min_x, float max_x);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects = NULL, vector<LPGAMEOBJECT> *listObj = NULL);
	virtual void Render();
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void LastUpdate();

	virtual float GetDamge() { return Enemy6_Damge; };
};


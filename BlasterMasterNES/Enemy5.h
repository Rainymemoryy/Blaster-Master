#pragma once
#include "GameObject.h"
#include "Brick.h"
#include "Utils.h"
#include "Car.h"
#include "Bullet.h"
#include "Enemy.h"

#define Enemy5_Box_Height	18
#define Enemy5_Box_Width	18
#define Enemy5_HP			100
#define Enemy5_AY			0.0005f
#define Enemy5_VX			0.05f
#define Enemy5_VY			0.05f

#define Enemy5_MaxD			100.f


#define Enemy5_AniSet		805
#define Enemy5_Ani_Left		0
#define Enemy5_Ani_Right	1

#define Enemy5_Damge		25.f
#define Enemy5_Jump			0.2f

#define Enemy5_TimeDoiHuong	3000

class CEnemy5 : public CEnemy
{
	int timeDoiHuong = -1;
	bool followHero = false;
public:

	CEnemy5(float x, float y);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects = NULL, vector<LPGAMEOBJECT> *listObj = NULL);
	virtual void Render();
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);

	virtual void LastUpdate();
	virtual float GetDamge() { return Enemy5_Damge; };
};

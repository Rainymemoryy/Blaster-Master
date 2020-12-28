#pragma once
#include "GameObject.h"
#include "Brick.h"
#include "Utils.h"
#include "Car.h"
#include "Bullet.h"
#include "Enemy.h"


#define Enemy1_Box_Height	10
#define Enemy1_Box_Width	18
#define Enemy1_HP			100
#define Enemy1_AY			0.0015f
#define Enemy1_VX			0.05f
#define Enemy1_VY			0.1f

#define Enemy1_AniSet		801
#define Enemy1_Ani_Left		0
#define Enemy1_Ani_Right	1

#define Enemy1_Damge       25.f
#define Enemy1_Jump			0.2f


class CEnemy1 : public CEnemy
{
public:

	CEnemy1(float x, float y);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects = NULL, vector<LPGAMEOBJECT> *listObj = NULL);
	virtual void Render();
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void LastUpdate();
	virtual float GetDamge() { return Enemy1_Damge; };

};

#pragma once
#include "GameObject.h"
#include "Brick.h"
#include "Utils.h"
#include "Car.h"
#include "Bullet.h"
#include "Enemy.h"

#define Enemy3_Box_Height	18
#define Enemy3_Box_Width	18
#define Enemy3_HP			100
#define Enemy3_AY			0.0005f
#define Enemy3_VX			0.05f
#define Enemy3_VY			0.0f

#define Enemy3_AniSet		801
#define Enemy3_Ani_Left		0
#define Enemy3_Ani_Right	1

#define Enemy3_Damge       25.f
#define Enemy3_Jump			0.2f


class CEnemy3 : public CEnemy
{
	float px, f, py;
public:
	CEnemy3();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects = NULL, vector<LPGAMEOBJECT> *listObj = NULL);
	virtual void Render();
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void LastUpdate();
	virtual float GetDamge() { return 0.f; };


};

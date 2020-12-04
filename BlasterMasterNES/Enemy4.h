#pragma once
#include "GameObject.h"
#include "Brick.h"
#include "Utils.h"
#include "Car.h"
#include "Bullet.h"
#include "Enemy.h"

#define Enemy4_Box_Height	18
#define Enemy4_Box_Width	18
#define Enemy4_HP			100
#define Enemy4_AY			0.000025f
#define Enemy4_VX			0.02f
#define Enemy4_VY			0.04f

#define Enemy4_AniSet		804
#define Enemy4_Ani_Left		0
#define Enemy4_Ani_Right	1

#define Enemy4_Damge		25.f
#define Enemy4_TimeJump		3000

class CEnemy4 : public CEnemy
{

protected:
	int timeJump = -1;

	float s1, s2;
public:
	CEnemy4(float x, float y);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects = NULL, vector<LPGAMEOBJECT> *listObj = NULL);
	virtual void Render();
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);

	virtual void LastUpdate();
	virtual float GetDamge() { return 10.f; };
};

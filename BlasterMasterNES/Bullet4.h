#pragma once
#include "Bullet.h"
#include "GameObject.h"

#define Bullet4_Box_Width	8
#define Bullet4_Box_Height	8

#define Bullet4_AniSet		704

#define Bullet4_Damage_DF	30

#define Bullet4_Ani_Left	0
#define Bullet4_Ani_Right	1

#define Bullet4_AY			0.0002f
#define Bullet4_VY			0.06f
#define Bullet4_VX			0.06f


class CBullet4 : public CBullet
{
public:
	CBullet4();

	virtual void LastUpdate();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects = NULL, vector<LPGAMEOBJECT> *listObj = NULL);
	virtual void Render();
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
};

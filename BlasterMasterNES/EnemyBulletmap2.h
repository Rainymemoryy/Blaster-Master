#pragma once
#pragma once
#include "Bullet.h"
#include "GameObject.h"

#define Bullet1_Box_Width	8
#define Bullet1_Box_Height	8

#define Bullet1_AniSet		711

#define Bullet1_Damage_DF	20

#define Bullet1_V_DF		0.3


class CBulleteny1 : public CBullet
{
public:
	CBulleteny1();

	virtual void LastUpdate();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects = NULL, vector<LPGAMEOBJECT> *listObj = NULL);
	virtual void Render();
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);



};

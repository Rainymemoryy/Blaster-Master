#pragma once
#include "Bullet.h"
#include "GameObject.h"

#define Bullet1_Box_Width	4
#define Bullet1_Box_Height	4

#define Bullet1_AniSet		701

#define Bullet1_Damage_DF	30

#define Bullet1_V_DF		0.3


class CBullet1 : public CBullet
{
public:
	CBullet1();

	virtual void LastUpdate();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects = NULL, vector<LPGAMEOBJECT> *listObj = NULL);
	virtual void Render();
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);

	

};

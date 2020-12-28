#pragma once
#include "Bullet.h"
#include "GameObject.h"

#define Bullet3_Box_Width	7
#define Bullet3_Box_Height	7

#define Bullet3_AniSet		703

#define Bullet3_Damage_DF	120

#define Bullet3_V_DF		0.3


class CBullet3 : public CBullet
{
	
public:
	CGameObject *target;
	CBullet3();

	virtual void LastUpdate();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects = NULL, vector<LPGAMEOBJECT> *listObj = NULL);
	virtual void Render();
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);

	void SetTarget(CGameObject *obj);


};

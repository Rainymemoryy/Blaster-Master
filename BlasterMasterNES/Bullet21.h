#pragma once
#include "Bullet.h"
#include "GameObject.h"

#define Bullet2_Box_A		22
#define Bullet2_Box_B		6

#define Bullet2_AniSet		702

#define Bullet21_AniSet		7021


#define Bullet2_Damage_DF	60

#define Bullet2_V_DF		0.3


class CBullet21 : public CBullet
{
public:
	vector<LPGAMEOBJECT>* listObj;
	CBullet21();
	virtual void LastUpdate();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects = NULL, vector<LPGAMEOBJECT> *listObj = NULL);
	virtual void Render();
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	


};

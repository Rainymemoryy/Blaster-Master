#pragma once
#include "Bullet.h"
#include "GameObject.h"

#define Bullet6_Box_Width	7
#define Bullet6_Box_Height	7

#define Bullet6_AniSet		703

#define Bullet6_Damage_DF	120

#define Bullet6_V_DF		0.15


class CBullet6 : public CBullet
{
	float maxD1;
	int x1, y1, x2, y2;
public:

	CBullet6(int x1, int y1, int x2, int y2);
	virtual void LastUpdate();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL, vector<LPGAMEOBJECT>* listObj = NULL);
	virtual void Render();
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};

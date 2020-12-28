#pragma once
#include "Bullet.h"
#include "GameObject.h"

#define Bullet5_Box_Width	8
#define Bullet5_Box_Height	8
#define Bullet5_AniSet		705
#define Bullet5_Damage_DF	30

#define Bullet5_Ani_Left	0
#define Bullet5_Ani_Right	1

#define Bullet5_AY			0.0002f
#define Bullet5_NayLen		0.08f
#define Bullet5_TimeTuHuy		2000
class CBullet5 : public CBullet
{
	float nayLen= Bullet5_NayLen;
	int timeTuHuy= Bullet5_TimeTuHuy;
	bool duoiTheoHero = false;
public:
	CBullet5();

	virtual void LastUpdate();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects = NULL, vector<LPGAMEOBJECT> *listObj = NULL);
	virtual void Render();
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
};

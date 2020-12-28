#pragma once
#include "GameObject.h"
#include "Brick.h"
#include "Utils.h"
#include "Car.h"
#include "Bullet.h"
#include "Enemy.h"


#define Enemy8_Box_Height	10
#define Enemy8_Box_Width	16
#define Enemy8_HP			100

#define Enemy8_AniSet		808
#define Enemy8_Damge       25.f



class CEnemy8 : public CEnemy
{
public:

	CEnemy8(float x, float y);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects = NULL, vector<LPGAMEOBJECT> *listObj = NULL);
	virtual void Render();
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void LastUpdate();
	virtual float GetDamge() { return Enemy8_Damge; };

	void BanDan();
};

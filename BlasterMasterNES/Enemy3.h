#pragma once
#include "GameObject.h"
#include "Brick.h"
#include "Utils.h"
#include "Car.h"
#include "Bullet.h"
#include "Enemy.h"


#define Enemy3_Box_Height	16
#define Enemy3_Box_Width	16
#define Enemy3_HP			100
#define Enemy3_AY			0.0015f
#define Enemy3_V			0.04f

#define Enemy3_AniSet		803
#define Enemy3_Damge       25.f



class CEnemy3 : public CEnemy
{
	bool followHero = false;
public:

	CEnemy3(float x, float y, int nx, int ny, int vx, int vy);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects = NULL, vector<LPGAMEOBJECT> *listObj = NULL);
	virtual void Render();
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void LastUpdate();
	virtual float GetDamge() { return Enemy3_Damge; };

};

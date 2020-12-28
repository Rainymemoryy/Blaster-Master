#pragma once
#include "GameObject.h"
#include "Brick.h"
#include "Utils.h"
#include "Car.h"
#include "Bullet.h"
#include "Enemy.h"


#define Enemy10_Box_Height	18
#define Enemy10_Box_Width	18
#define Enemy10_HP			100
#define Enemy10_AY			0.0015f
#define Enemy10_V			0.1f

#define Enemy10_AniSet		810
#define Enemy10_Damge       25.f



class CEnemy10 : public CEnemy
{
	
public:

	CEnemy10(float x, float y);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects = NULL, vector<LPGAMEOBJECT> *listObj = NULL);
	virtual void Render();
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void LastUpdate();
	virtual float GetDamge() { return Enemy10_Damge; };

};



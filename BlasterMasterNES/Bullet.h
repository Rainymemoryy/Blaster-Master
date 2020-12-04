#pragma once
#include "GameObject.h"
#include "Brick.h"
#include "Utils.h"
#include "Car.h"
#include  "Hero.h"

#define Bullet_Hero		0
#define Bullet_Enemy	1

class CBullet : public CGameObject
{
protected:
	float damage;
	bool isPhatNo = false;
	float maxD;
	int timeDelete = 145;
public:
	
	virtual void LastUpdate() {};
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL, vector<LPGAMEOBJECT> *listObj = NULL) {};
	virtual void Render() {};
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom) {};

	void SetDamage(float dmg) { this->damage = dmg; };
	float GetDamage() { return damage; };

	void SetmaxD(float maxD) { this->maxD = maxD;};

};

#include "BossArm.h"

void BossArm::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + 16;
	bottom = y + 32;
	damage = 20;
}
void BossArm::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects, vector<LPGAMEOBJECT>* listObj)
{
	this->listObj = listObj;
	CGameObject::Update(dt);
	coEvents->clear();
	
	vector<LPGAMEOBJECT>* tmp = new vector<LPGAMEOBJECT>();
	for (int i = 0; i < coObjects->size(); i++)
		if (coObjects->at(i)->isTouthtable) tmp->push_back(coObjects->at(i));
	CalcPotentialCollisions(tmp, *coEvents);
	delete tmp;
}

void BossArm::LastUpdate()
{
	if (this->type == TYPE_LEFT_CLAW)
	{
		float x_, y_;
		Boss->getLeftClawPos(x_, y_);
		this->x = x_;
		this->y = y_;
	}
	else if (this->type == TYPE_RIGHT_CLAW)
	{
		float x_, y_;
		Boss->getRightClawPos(x_, y_);
		this->x = x_;
		this->y = y_;
	}

	if (Boss->visible == false) visible = false;
}

void BossArm::Render()
{
	//RenderBoundingBox();
}

BossArm::BossArm(CBoss* boss, int _type)
{
	type = _type;
	//isEnemy = true;
	damage = 1;
	hp = 10000;
	this->Boss = boss;
	x = Boss->x;
	y = Boss->y;
	visible = true;

}

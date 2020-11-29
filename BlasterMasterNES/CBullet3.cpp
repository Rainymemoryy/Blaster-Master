#include "Bullet3.h"

CBullet3::CBullet3()
{
	//this->SetAnimationSet(CAnimationSets::GetInstance()->Get(Bullet3_AniSet));
	damage = Bullet3_Damage_DF;
	

}

void CBullet3::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects, vector<LPGAMEOBJECT>* listObj)
{
	if (isPhatNo)return;

	float target_x=-1, target_y=-1;
	target->GetPosition(target_x, target_y);

	if (abs(target_x - x) > abs(target_y - y))
	{
		if (target_x - x > 0) {
			vx = Bullet3_V_DF;
			vy = 0;
		}
		else {
			vx =- Bullet3_V_DF;
			vy = 0;
		}
	}
	else {
		if (target_y - y > 0) {
			vx = 0;
			vy = Bullet3_V_DF;
		}
		else {
			vx =-0;
			vy = -Bullet3_V_DF;
		}
	}

	
	CGameObject::Update(dt);
	coEvents.clear();

	vector<LPGAMEOBJECT> *TmpCoo = new vector<LPGAMEOBJECT>();

	for (int i = 0; i < coObjects->size(); i++) {
		LPGAMEOBJECT e = coObjects->at(i);
		if (e->isTouthtable)
		{
			if (dynamic_cast<CEnemy*>(e)) {
				if (GetState() == Bullet_Hero) TmpCoo->push_back(e);
			}
		}
	}

	CalcPotentialCollisions(TmpCoo, coEvents);

}

void CBullet3::LastUpdate()
{
	
	if (isPhatNo)  timeDelete -= dt;
	else {
		if (coEvents.size() == 0)
		{
			x += dx;
			y += dy;
		}
		else
		{
			float min_tx, min_ty, nx = 0, ny;
			float rdx = 0;
			float rdy = 0;
			vector<LPCOLLISIONEVENT> coEventsResult;
			FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);
			x += min_tx * dx + nx * 0.001f;
			y += min_ty * dy + ny * 0.001f;
			isPhatNo = true;
			isTouthtable = false;

			for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
		}
	}

	if (timeDelete <= 0) isDelete = true;

}

void CBullet3::Render()
{
	RenderBoundingBox();
	/*if (isPhatNo) {
		animation_set->at(1)->Render(round(x - 6), round(y - 6), 255, -1);
	}
	else animation_set->at(0)->Render(round(x), round(y), 255, -1);*/

}

void CBullet3::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	right = x + Bullet3_Box_Width;
	top = y;
	bottom = y + Bullet3_Box_Height;
}

void CBullet3::SetTarget(CGameObject * obj)
{
	this->target = obj;
}

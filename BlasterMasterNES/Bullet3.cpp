#include "Bullet3.h"

CBullet3::CBullet3()
{
	this->SetAnimationSet(CAnimationSets::GetInstance()->Get(Bullet3_AniSet));
	damage = Bullet3_Damage_DF;
	vx = 0; vy = 0;
}

void CBullet3::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects, vector<LPGAMEOBJECT>* listObj)
{
	if (isPhatNo)return;
	CGameObject::Update(dt);
	for (int i = 0; i < listObj->size(); i++) {
		if (target == listObj->at(i))
		{
			if (this->IsScopeWith(target)) {
				isPhatNo = true;
				vx = 0; vy = 0;
				return;
			}
			coEvents->clear();
			vector<LPGAMEOBJECT> * tmpObj = new vector<LPGAMEOBJECT>();
			tmpObj->push_back(target);
			CalcPotentialCollisions(tmpObj, *coEvents);
			return;
		}
	}
	isPhatNo = true;

	
}

void CBullet3::LastUpdate()
{

	if (isPhatNo) {
		timeDelete -= dt;
		isTouthtable = false;
		DebugOut(L"[Bullet3] timeDelete: %d\n", timeDelete);
	}
	else {
		if (coEvents->size() == 0)
		{
			x += dx;
			y += dy;
		}
		else
		{
			float min_tx, min_ty, nx = 0, ny;
			float rdx = 0;
			float rdy = 0;
			vector<LPCOLLISIONEVENT> *coEventsResult=new vector<LPCOLLISIONEVENT>();
			

			FilterCollision(*coEvents, *coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);
			x += min_tx * dx + nx * 0.001f;
			y += min_ty * dy + ny * 0.001f;
			isPhatNo = true;
			isTouthtable = false;
			
			delete coEventsResult;
			for (UINT i = 0; i < coEvents->size(); i++) delete coEvents->at(i);
		}

		if (true) {
			float target_x = -1, target_y = -1;
			target->TinhTam(target_x, target_y);
			float x, y;
			TinhTam(x, y);

			if (abs(target_x - x) > abs(target_y - y))
			{
				if (target_x - x > 0) {
					vx = Bullet3_V_DF;
					vy = 0;
				}
				else {
					vx = -Bullet3_V_DF;
					vy = 0;
				}
			}
			else {
				if (target_y - y > 0) {
					vx = 0;
					vy = Bullet3_V_DF;
				}
				else {
					vx = 0;
					vy = -Bullet3_V_DF;
				}
			}
		}
	}

	

	if (timeDelete <= 0) isDelete = true;

}

void CBullet3::Render()
{
	

	if (isPhatNo) {
		animation_set->at(5)->Render(round(x - 6), round(y - 6), 255, -1);
	}
	else {
		int ani = -1;
		if (vy == 0) {
			if (vx < 0) {
				animation_set->at(0)->Render(round(x), round(y), 255, 0);
				animation_set->at(1)->Render(round(x) + 9, round(y), 255, -1);
			}
			if (vx > 0) {
				animation_set->at(0)->Render(round(x), round(y), 255, 1);
				animation_set->at(2)->Render(round(x) - 16, round(y), 255, -1);
			}
		}
		if (vx == 0) {
			if (vy < 0) {
				animation_set->at(0)->Render(round(x), round(y), 255, 2);
				animation_set->at(3)->Render(round(x), round(y) + 9, 255, -1);
			}
			if (vy > 0) {
				animation_set->at(0)->Render(round(x), round(y), 255, 3);
				animation_set->at(4)->Render(round(x), round(y) - 16, 255, -1);
			}
		}
	}
	
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

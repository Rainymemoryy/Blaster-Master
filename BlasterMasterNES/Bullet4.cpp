#include "Bullet4.h"

CBullet4::CBullet4()
{
	this->SetAnimationSet(CAnimationSets::GetInstance()->Get(Bullet4_AniSet));
	damage = Bullet4_Damage_DF;
	maxD = 100;
	vx = 0.03f;
	vy = -Bullet4_VY;
}

void CBullet4::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects, vector<LPGAMEOBJECT>* listObj)
{

	if (isPhatNo)return;
	CGameObject::Update(dt);
	coEvents->clear();
	CalcPotentialCollisions(coObjects, *coEvents);

}

void CBullet4::LastUpdate()
{
	
	if (isPhatNo)  timeDelete -= dt;
	else {
		if (coEvents->size() == 0)
		{
			if (maxD - sqrt(dx*dx + dy * dy) > 0)
			{
				x += dx;
				y += dy;
				maxD -= sqrt(dx*dx + dy * dy);
			}
			else if (maxD >= 0) {
				float t = maxD / sqrt(dx*dx + dy * dy);
				x += t * dx;
				y += t * dy;
				maxD = -1;
			}
			else
			{
				isPhatNo = true;
				isTouthtable = false;
			}
		}
		else
		{
			float min_tx, min_ty, nx = 0, ny;
			float rdx = 0;
			float rdy = 0;
			vector<LPCOLLISIONEVENT> *coEventsResult = new vector<LPCOLLISIONEVENT>();
			vector<LPCOLLISIONEVENT> *tmpCoo = new vector<LPCOLLISIONEVENT>();

			for (int i = 0; i < coEvents->size(); i++)
			{
				CGameObject *obj = coEvents->at(i)->obj;
				if (dynamic_cast<CHero*>(obj)) {
					if (GetState() != Bullet_Hero) tmpCoo->push_back(coEvents->at(i));
				}
				if (dynamic_cast<CEnemy*>(obj)) {
					if (GetState() != Bullet_Enemy) tmpCoo->push_back(coEvents->at(i));
				}
			}

			FilterCollision(*tmpCoo, *coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);

			x += min_tx * dx + nx * 0.001f;
			y += min_ty * dy + ny * 0.001f;



			if (coEventsResult->size() != 0) {
				isPhatNo = true;
				isTouthtable = false;
				vx = 0; vy = 0;
				
			}
			delete coEventsResult;
			delete tmpCoo;
			for (UINT i = 0; i < coEvents->size(); i++) delete coEvents->at(i);
		}

		if (true) {
			vy += Bullet4_AY * dt;
		}
		
	}

	if (timeDelete <= 0) isDelete = true;
}

void CBullet4::Render()
{
	//RenderBoundingBox();
	if (isPhatNo) {
		animation_set->at(1)->Render(round(x - 4), round(y - 4), 255, -1);
		vx = 0; vy = 0;
	}
	else {
		if(vx>0)animation_set->at(0)->Render(round(x), round(y), 255, 1);
		else animation_set->at(0)->Render(round(x), round(y), 255, 0);
	}
}

void CBullet4::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	right = x + Bullet4_Box_Width;
	top = y;
	bottom = y + Bullet4_Box_Height;
}

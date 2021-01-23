#include "Bullet2.h"

#include "Brick2.h"
#include "Sound.h"

CBullet2::CBullet2(bool c)
{
	this->SetAnimationSet(CAnimationSets::GetInstance()->Get(Bullet2_AniSet));
	damage = Bullet2_Damage_DF;
	this->upgrade = c;
	maxD = 200;
}

void CBullet2::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects, vector<LPGAMEOBJECT>* listObj)
{
	if (isPhatNo)return;
	CGameObject::Update(dt);
	coEvents->clear();
	CalcPotentialCollisions(coObjects, *coEvents);

	//Vieets them
	
}

void CBullet2::LastUpdate()
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
				if (dynamic_cast<CBrick *>(obj)) {
					if (this->IsScopeWith(obj)) {
						isPhatNo = true;
						isTouthtable = false;
					}
					tmpCoo->push_back(coEvents->at(i));
				}
				if (dynamic_cast<CHero*>(obj)) {
					if (this->IsScopeWith(obj)) {
						isPhatNo = true;
						isTouthtable = false;
					}
					if (GetState() != Bullet_Hero) tmpCoo->push_back(coEvents->at(i));
				}
				if (dynamic_cast<CEnemy*>(obj)) {
					if (this->IsScopeWith(obj)) {
						isPhatNo = true;
						isTouthtable = false;
					}
					if (GetState() != Bullet_Enemy) tmpCoo->push_back(coEvents->at(i));
				}


			}

			FilterCollision(*tmpCoo, *coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);

			x += min_tx * dx + nx * 0.001f;
			y += min_ty * dy + ny * 0.001f;


			for (int i = 0; i < coEventsResult->size(); i++) {

				LPGAMEOBJECT e = coEventsResult->at(i)->obj;
				if (dynamic_cast<CBrick2 *>(e))
					if(upgrade){
					Sound::GetInstance()->Play("PlayerBulletHitBrick", 0, 1);
					e->SetDelete(true);
				}
				isPhatNo = true;
				isTouthtable = false;
			}
			delete coEventsResult;
			delete tmpCoo;
			for (UINT i = 0; i < coEvents->size(); i++) delete coEvents->at(i);
		}
	}
	if (timeDelete <= 0) isDelete = true;
}

void CBullet2::Render()
{
	
	if (isPhatNo) {
		if (vy != 0)
			animation_set->at(1)->Render(round(x-5), round(y-8), 255, -1);
		else
			if (vx >= 0)  animation_set->at(1)->Render(round(x+14), round(y-5), 255,-1);
			else  animation_set->at(1)->Render(round(x-8), round(y-5), 255, -1);
		
	}
	else {
		if (vy != 0)
			animation_set->at(0)->Render(round(x), round(y), 255, 2);
		else
			if (vx >= 0)  animation_set->at(0)->Render(round(x), round(y), 255, 1);
			else  animation_set->at(0)->Render(round(x), round(y), 255, 0);
	}
}

void CBullet2::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	// Ban ken troi
	if (vy != 0) {
		left = x;
		right = x + Bullet2_Box_B;
		top = y;
		bottom = y + Bullet2_Box_A;
	}
	else {
		left = x;
		right = x + Bullet2_Box_A;
		top = y;
		bottom = y + Bullet2_Box_B;
	}
}

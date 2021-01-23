#include "Bullet21.h"
#include "OvhAlert.h"
#include "Brick21.h"
#include "Boss.h"
#include "Sound.h"
#include "Item1.h"
#include "Item3.h"

#include "Item2.h"

#include "ItemH.h"

CBullet21::CBullet21()
{
	this->SetAnimationSet(CAnimationSets::GetInstance()->Get(Bullet21_AniSet));
	damage = Bullet2_Damage_DF;
	maxD = 200;
}

void CBullet21::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects, vector<LPGAMEOBJECT>* listObj)
{
	this->listObj = listObj;
	if (isPhatNo)return;
	CGameObject::Update(dt);
	coEvents->clear();
	CalcPotentialCollisions(coObjects, *coEvents);
	
}

void CBullet21::LastUpdate()
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
					tmpCoo->push_back(coEvents->at(i));
				}
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


			for (int i = 0; i < coEventsResult->size(); i++) {

				LPGAMEOBJECT e = coEventsResult->at(i)->obj;
				if (dynamic_cast<CBrick21 *>(e)) 
				{
					Sound::GetInstance()->Play("PlayerBulletHitBrick", 0, 1);
					e->SetDelete(true);
					int n = rand() % 4 + 0;
					if (!n) 
					{
						DebugOut(L"[Enemy] Drop item: %d\n", 1);
						CGameObject* obj;
						float ix, iy;
						int m = rand() % 5 + 0;
						this->TinhTam(ix, iy);
						switch (m)
						{
						case 1:
							obj = new CItemHp(ix , iy );
							listObj->push_back(obj);
							break;
							
						case 2:
							obj = new CItem1(ix , iy );
							listObj->push_back(obj);
							break;
						case 3:
							obj = new CItem2(ix, iy);
							listObj->push_back(obj);
							break;
						case 4:
							obj = new CItem3(ix, iy );
							listObj->push_back(obj);
						case 5:
							obj = new CItemH(ix, iy );
							listObj->push_back(obj);
							break;
							break;
						default:
							break;
						}
					}
				}
				
				if (dynamic_cast <CBoss*>(e))
				{
					dynamic_cast <CBoss*>(e)->SetState(BOSS_STATE_INJURED);
					dynamic_cast <CBoss*>(e)->hp-=100;
				}
				if (dynamic_cast<COvhAlert *>(e)) {
					x += dx;
					y += dy;
				}
				else{
					isPhatNo = true;
					isTouthtable = false;
				}
			}
			delete coEventsResult;
			delete tmpCoo;
			for (UINT i = 0; i < coEvents->size(); i++) delete coEvents->at(i);
		}
	}
	if (timeDelete <= 0) isDelete = true;
}

void CBullet21::Render()
{

	if (isPhatNo) {
		Sound::GetInstance()->Play("EnemyBulletBang", 0, 1);
		if (vy != 0)
			animation_set->at(1)->Render(round(x - 5), round(y - 8), 255, -1);
		else
			if (vx >= 0)  animation_set->at(1)->Render(round(x + 14), round(y - 5), 255, -1);
			else  animation_set->at(1)->Render(round(x - 8), round(y - 5), 255, -1);

	}
	else {
		if (vy != 0)
		{
			if (vy>=0)
			animation_set->at(0)->Render(round(x), round(y), 255, 3);
			else 
				animation_set->at(0)->Render(round(x), round(y), 255, 2);

		}
		else
			if (vx >= 0)  animation_set->at(0)->Render(round(x), round(y), 255, 1);
			else  animation_set->at(0)->Render(round(x), round(y), 255, 0);
	}
}

void CBullet21::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	// Ban ken troi
	if (vy != 0) {
		if (vy > 0)
		{
			left = x;
			right = x + Bullet2_Box_B;
			top = y;
			bottom = y + Bullet2_Box_A - 16;
		}
		else 
		{
			left = x;
			right = x + Bullet2_Box_B;
			top = y;
			bottom = y + Bullet2_Box_A;
		}
	}
	else {
		left = x;
		right = x + Bullet2_Box_A;
		top = y;
		bottom = y + Bullet2_Box_B;
	}
}

#include "Enemy3.h"
#include "Hero.h"
#include "PlayScence.h"
#include "Block1.h"

#include "Bullet.h"
#include "Bullet3.h"

#include "Item.h"



CEnemy3::CEnemy3(float x, float y, int nx, int ny, int vx, int vy)
{
	this->SetAnimationSet(CAnimationSets::GetInstance()->Get(Enemy3_AniSet));
	this->x = x;
	this->y = y;

	this->nx = nx;
	this->ny = ny;

	this->vx = vx * Enemy3_V;
	this->vy = vy * Enemy3_V;

	//vx = Enemy3_V;


	hp = Enemy3_HP;
	dropItem = Item_HP;
}

void CEnemy3::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects, vector<LPGAMEOBJECT>* listObj)
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

void CEnemy3::LastUpdate()
{

	if (coEvents->size() == 0) {
		x += dx;
		y += dy;
	}
	else
	{
		if (true) {
			float min_tx, min_ty, nx = 0, ny = 0;
			float rdx = 0;
			float rdy = 0;
			vector<LPCOLLISIONEVENT> coEvents_Block_Brick;
			vector<LPCOLLISIONEVENT> coEventsResult_Block_Brick;

			for (int i = 0; i < coEvents->size(); i++) {
				LPCOLLISIONEVENT e = coEvents->at(i);
				if (dynamic_cast<CBrick *>(e->obj))
					coEvents_Block_Brick.push_back(e);
				if (dynamic_cast<CBlock1 *>(e->obj))
					coEvents_Block_Brick.push_back(e);
			}
			FilterCollision(coEvents_Block_Brick, coEventsResult_Block_Brick, min_tx, min_ty, nx, ny, rdx, rdy);

			x += min_tx * dx + nx * 0.001f;
			y += min_ty * dy + ny * 0.001f;



			/*if (nx != 0)vx = 0;
			if (ny != 0)vy = 0;*/



			for (int i = 0; i < coEventsResult_Block_Brick.size(); i++) {
				LPCOLLISIONEVENT e = coEventsResult_Block_Brick[i];
				DebugOut(L"nx:  %f   ny:  %f\n", e->nx, e->ny);

				if (dynamic_cast<CBrick *>(e->obj)) {
					if (e->nx > 0) {
						this->nx = 1;
						this->ny = 0;
						this->vy = -Enemy3_V;
						this->vx = 0;
						followHero = false;
					}
					else if (e->nx < 0) {
						this->nx = -1;
						this->ny = 0;
						this->vy = Enemy3_V;
						this->vx = 0;
						followHero = false;
					}
					else if (e->ny > 0) {
						this->nx = 0;
						this->ny = 1;
						this->vx = Enemy3_V;
						this->vy = 0;
						followHero = false;
					}
					else if (e->ny < 0) {
						this->nx = 0;
						this->ny = -1;
						this->vx = -Enemy3_V;
						this->vy = 0;
						followHero = false;
					}
				}

				if (dynamic_cast<CBlock1 *>(e->obj)) {

					if (!followHero) {
						if (e->nx < 0) {
							this->nx = 1;
							this->ny = 0;
							x += Enemy3_Box_Width;
							y -= Enemy3_Box_Height;
							vy = -Enemy3_V;
							vx = 0;
							x += 2;
						}
						else if (e->ny > 0) {
							this->nx = 0;
							this->ny = -1;
							x -= Enemy3_Box_Width;
							y -= Enemy3_Box_Height;
							vx = -Enemy3_V;
							vy = 0;
							y -= 2;
						}
						else if (e->nx > 0) {
							this->nx = -1;
							this->ny = 0;
							x -= Enemy3_Box_Width;
							y += Enemy3_Box_Height;
							vy = Enemy3_V;
							vx = 0;
							x -= 2;
						}
						else if (e->ny < 0) {
							this->nx = 0;
							this->ny = 1;
							x += Enemy3_Box_Width;
							y += Enemy3_Box_Height;
							vx = Enemy3_V;
							vy = 0;
							y += 2;
						}
					}
					else {
						x += -(min_tx * dx + nx * 0.001f) + dx;
						y += -(min_ty * dy + ny * 0.001f) + dy;
					}

				}
			}


		}

		if (true) {
			for (int i = 0; i < coEvents->size(); i++) {
				CGameObject* e = coEvents->at(i)->obj;

				if (dynamic_cast<CBullet3 *>(e))
				{
					CBullet3 *tmpBullet3 = (CBullet3*)(e);
					if (tmpBullet3->target == this) hp -= tmpBullet3->GetDamage();
				}
				else if (dynamic_cast<CBullet *>(e) && e->GetState() != Bullet_Enemy)
				{
					CBullet *tmpBullet = (CBullet*)(e);
					hp -= tmpBullet->GetDamage();
				}

			}
			if (hp <= 0) {
				isDelete = true;
				DropItem();
			}

		}
		for (UINT i = 0; i < coEvents->size(); i++) delete coEvents->at(i);
	}



	if (true) {
		CHero*hero = ((CPlayScene*)(CGame::GetInstance()->GetCurrentScene()))->GetPlayer();
		float x1, y1, x2, y2;

		this->TinhTam(x1, y1);
		hero->TinhTam(x2, y2);

		if (x1 - 5 < x2&&x1 + 5 > x2) {
			if (y1 < y2&&ny>0) {
				vy = 3 * Enemy3_V;
				vx = 0;
				followHero = true;
			}
			if (y1 > y2&&ny < 0) {
				vy = -3 * Enemy3_V;
				vx = 0;
				followHero = true;
			}
		}
		if (y1 - 5 < y2&&y1 + 5 > y2) {
			if (x1 < x2&&nx>0) {
				vy = 0;
				vx = 3 * Enemy3_V;
				followHero = true;
			}
			if (x1 > x2&&nx < 0) {
				vy = 0;
				vx = -3 * Enemy3_V;
				followHero = true;
			}
		}
	}
}



void CEnemy3::Render()
{
	//RenderBoundingBox();

	if (nx < 0) animation_set->at(1)->Render(round(x), round(y), 255, -1);
	else if (nx > 0)animation_set->at(3)->Render(round(x), round(y), 255, -1);
	else if (ny > 0)animation_set->at(2)->Render(round(x), round(y), 255, -1);
	else if (ny < 0)animation_set->at(0)->Render(round(x), round(y), 255, -1);


}

void CEnemy3::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	right = x + Enemy3_Box_Width;
	top = y;
	bottom = y + Enemy3_Box_Height;
}
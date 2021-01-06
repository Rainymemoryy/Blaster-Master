#include "Enemy1.h"
#include "Hero.h"
#include "PlayScence.h"


#include "Bullet.h"
#include "Bullet3.h"

#include "Item.h"



CEnemy1::CEnemy1(float x, float y)
{
	this->SetAnimationSet(CAnimationSets::GetInstance()->Get(Enemy1_AniSet));
	this->x = x;
	this->y = y;

	vx = -Enemy1_VX;
	vy = Enemy1_VY;;
	hp = Enemy1_HP;

	dropItem = Item_HP;
}

void CEnemy1::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects, vector<LPGAMEOBJECT>* listObj)
{
	this->listObj = listObj;
	this->coObjects = coObjects;
	CGameObject::Update(dt);
	coEvents->clear();

	vector<LPGAMEOBJECT>* tmp = new vector<LPGAMEOBJECT>();
	for (int i = 0; i < coObjects->size(); i++)
		if (coObjects->at(i)->isTouthtable) tmp->push_back(coObjects->at(i));
	CalcPotentialCollisions(tmp, *coEvents);
	delete tmp;
}

void CEnemy1::LastUpdate()
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
			vector<LPCOLLISIONEVENT> coEvents_Brick;
			vector<LPCOLLISIONEVENT> coEventsResult_Brick;

			for (int i = 0; i < coEvents->size(); i++) {
				LPCOLLISIONEVENT e = coEvents->at(i);
				if (dynamic_cast<CBrick *>(e->obj))
					coEvents_Brick.push_back(e);
			}
			FilterCollision(coEvents_Brick, coEventsResult_Brick, min_tx, min_ty, nx, ny, rdx, rdy);

			x += min_tx * dx + nx * 0.001f;
			y += min_ty * dy + ny * 0.001f;


			if (nx != 0) vx = -vx;
			if (ny != 0) vy = 0;


			if (nx != 0 && ny <0)vy = -0.045;
		}

		if (true) {
			//va cham
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

			//nam trong
			for (int i = 0; i < coObjects->size(); i++) {
				CGameObject* e = coObjects->at(i);

				if (this->IsScopeWith(e)) {
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
			}

			if (hp <= 0) {
				isDelete = true;
				DropItem();
			}

		}
		for (UINT i = 0; i < coEvents->size(); i++) delete coEvents->at(i);
	}

	if (true) {
		vy += Enemy1_AY;
		float hero_t, hero_l, hero_r, hero_b;
		((CPlayScene*)(CGame::GetInstance()->GetCurrentScene()))->GetPlayer()->GetBoundingBox(hero_l, hero_t, hero_r, hero_b);
		float t, l, r, b;
		GetBoundingBox(l, t, r, b);
		float herox = (hero_l + hero_r) / 2,
			x = (l + r) / 2;
		if (x > herox + 25) vx = -Enemy1_VX;
		if (x < herox - 25)  vx = Enemy1_VX;
	}

}



void CEnemy1::Render()
{
	//RenderBoundingBox();
	if (vx < 0) animation_set->at(Enemy1_Ani_Left)->Render(round(x), round(y), 255, -1);
	else animation_set->at(Enemy1_Ani_Right)->Render(round(x), round(y), 255, -1);
}

void CEnemy1::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	right = x + Enemy1_Box_Width;
	top = y;
	bottom = y + Enemy1_Box_Height;
}
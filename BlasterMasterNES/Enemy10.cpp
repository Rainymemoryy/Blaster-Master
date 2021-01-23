#include "Enemy10.h"
#include "Hero.h"
#include "PlayScence.h"
#include "Block1.h"

#include "Bullet.h"
#include "Bullet3.h"

#include "Item.h"



CEnemy10::CEnemy10(float x, float y)
{
	this->SetAnimationSet(CAnimationSets::GetInstance()->Get(Enemy5_AniSet));
	this->x = x;
	this->y = y;

	nx = 0;
	ny = 0;
	vx = Enemy10_V;
	hp = Enemy10_HP;
	dropItem = Item_HP;
}

void CEnemy10::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects, vector<LPGAMEOBJECT>* listObj)
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

void CEnemy10::LastUpdate()
{
	thoiGianDoiHuong -= dt;

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
			}
			FilterCollision(coEvents_Block_Brick, coEventsResult_Block_Brick, min_tx, min_ty, nx, ny, rdx, rdy);

			x += min_tx * dx + nx * 0.001f;
			y += min_ty * dy + ny * 0.001f;
			if (nx != 0)vx = -vx;
			if (ny != 0)vy = 0;
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



void CEnemy10::Render()
{

	animation_set->at(0)->Render(round(x), round(y), 255, -1);
}

void CEnemy10::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	right = x + Enemy10_Box_Width;
	top = y;
	bottom = y + Enemy10_Box_Height;
}
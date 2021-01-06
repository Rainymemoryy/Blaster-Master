#include "Enemy2.h"
#include "Hero.h"
#include "PlayScence.h"
#include "Bullet.h"
#include "Bullet1.h"
#include "Item.h"
#include "Bullet3.h"

CEnemy2::CEnemy2(float x, float y)
{
	this->SetAnimationSet(CAnimationSets::GetInstance()->Get(Enemy2_AniSet));

	this->x = x;
	this->y = y;
	vx = Enemy2_VX;
	vy = Enemy2_VY;
	hp = Enemy2_HP;

	dropItem = Item_HP;
}

void CEnemy2::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects, vector<LPGAMEOBJECT>* listObj)
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

void CEnemy2::LastUpdate()
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
			if (ny != 0) vy = -vy;
		}

		if (true) {
			for (int i = 0; i < coEvents->size(); i++) {
				CGameObject* e = coEvents->at(i)->obj;

				if (dynamic_cast<CBullet3 *>(e))
				{
					CBullet3 *tmpBullet3 = (CBullet3*)(e);
					if (tmpBullet3->target == this) hp -= tmpBullet3->GetDamage();
				}
				else if (dynamic_cast<CBullet *>(e))
				{
					CBullet *tmpBullet = (CBullet*)(e);
					hp -= tmpBullet->GetDamage();
				}
			}
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
		CHero * hero = ((CPlayScene*)(CGame::GetInstance()->GetCurrentScene()))->GetPlayer();
		float kc = this->TinhKhoangCach(hero);
		timeBanDan += dt;
		timeAniBanDan = timeAniBanDan < 0 ? -1 : timeAniBanDan + dt;
		if (timeBanDan >= Enemy2_TimeBanDan && kc <= 100 && kc >= 30) {
			timeBanDan = 0;
			timeAniBanDan = 0;
			isBanDan = true;

			BanDan();

		}
	}
}

void CEnemy2::Render()
{
	
	if (timeAniBanDan>=0)
	{
		if (vx < 0) animation_set->at(Enemy2_Ani_Left)->Render(round(x), round(y), 255, 0);
		else animation_set->at(Enemy2_Ani_Right)->Render(round(x), round(y), 255, 0);
		
	}
	else {
		if (vx < 0) animation_set->at(Enemy2_Ani_Left)->Render(round(x), round(y), 255, 1);
		else animation_set->at(Enemy2_Ani_Right)->Render(round(x), round(y), 255, 1);
	}
	timeAniBanDan = timeAniBanDan >= Enemy2_TimeAniBanDan ? -1: timeAniBanDan;


}

void CEnemy2::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	right = x + Enemy2_Box_Width;
	top = y;
	bottom = y + Enemy2_Box_Height;
}

void CEnemy2::BanDan()
{
	CGameObject *tmpTarget = ((CPlayScene*)(CGame::GetInstance()->GetCurrentScene()))->GetPlayer();
	float a1, b1, a2, b2;

	CBullet1*obj = new CBullet1();
	obj->SetPosition(x + 7, y + 18);
	obj->SetmaxD(100);
	tmpTarget->TinhTam(a1, b1);
	obj->TinhTam(a2, b2);
	obj->SetState(Bullet_Enemy);
	obj->SetSpeed(0.1*(a1 - a2) / tmpTarget->TinhKhoangCach(obj), 0.1*(b1 - b2) / tmpTarget->TinhKhoangCach(obj));
	listObj->push_back(obj);

}



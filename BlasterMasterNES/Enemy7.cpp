#include "Enemy7.h"
#include <cstdlib>
#include "Bullet3.h"
#include "Item.h"
#include "PlayScence.h"
#include "Bullet1.h"

CEnemy7::CEnemy7(float x, float y, float min_x, float max_x)
{
	this->x = x;
	this->y = y;
	this->min_x = min_x;
	this->max_x = max_x;

	vy = 0;
	vx = -Enemy7_VX;
	dropItem = Item_H;
	hp = Enemy7_HP;

	this->SetAnimationSet(CAnimationSets::GetInstance()->Get(Enemy7_AniSet));
}

void CEnemy7::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects, vector<LPGAMEOBJECT>* listObj)
{
	this->dt = dt;
	this->listObj = listObj;
	CGameObject::Update(dt);
	coEvents->clear();

	vector<LPGAMEOBJECT>* tmp = new vector<LPGAMEOBJECT>();
	for (int i = 0; i < coObjects->size(); i++)
		if (coObjects->at(i)->isTouthtable) tmp->push_back(coObjects->at(i));
	CalcPotentialCollisions(tmp, *coEvents);
	delete tmp;

}

void CEnemy7::LastUpdate()
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
		if (x < min_x)vx = Enemy7_VX;
		if (x > max_x)vx = -Enemy7_VX;
	}

	if (true) {
		timeBanDan -= dt;
		timeBanDan = timeBanDan <= -Enemy7_NgungTimeBanDan ? (Enemy7_SoLanBanDan+1) * Enemy7_Time1LanBanDan -5 : timeBanDan;
		if (timeBanDan / Enemy7_Time1LanBanDan > 0 && timeBanDan / Enemy7_Time1LanBanDan != lastBanDan) {

			BanDan();
		}
		lastBanDan = timeBanDan / Enemy7_Time1LanBanDan;
	}

}

void CEnemy7::BanDan()
{
	
		CGameObject *tmpTarget = ((CPlayScene*)(CGame::GetInstance()->GetCurrentScene()))->GetPlayer();
		float a1, b1, a2, b2;
		CBullet1*obj = new CBullet1();
		obj->SetPosition(x + 7, y + 18);
		obj->SetmaxD(1000);
		tmpTarget->TinhTam(a1, b1);
		obj->TinhTam(a2, b2);
		obj->SetState(Bullet_Enemy);
		obj->SetSpeed(0.1*(a1 - a2) / tmpTarget->TinhKhoangCach(obj), 0.1*(b1 - b2) / tmpTarget->TinhKhoangCach(obj));
		listObj->push_back(obj);
}

void CEnemy7::Render()
{
	//RenderBoundingBox();
	if (vx <= 0) animation_set->at(Enemy7_Ani_Left)->Render(round(x), round(y), 255, -1);
	else animation_set->at(Enemy7_Ani_Right)->Render(round(x), round(y), 255, -1);
}

void CEnemy7::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + Enemy7_Box_Width;
	bottom = y + Enemy7_Box_Height;
}



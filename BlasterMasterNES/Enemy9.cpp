#include "Enemy9.h"
#include "Hero.h"
#include "PlayScence.h"
#include "Bullet.h"
#include "Bullet1.h"
#include "Item.h"
#include "Bullet3.h"
#include "Bullet5.h"


CEnemy9::CEnemy9(float x, float y)
{
	this->SetAnimationSet(CAnimationSets::GetInstance()->Get(Enemy9_AniSet));

	this->x = x;
	this->y = y;

	vx = -Enemy9_VX;
	vy = 0;
	hp = Enemy9_HP;
	dropItem = Item_HP;
}

void CEnemy9::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects, vector<LPGAMEOBJECT>* listObj)
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

void CEnemy9::LastUpdate()
{
	if (timeNgungBanDan >= 0) timeNgungBanDan -= dt;
	timeAniBanDan -= dt;
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

			if (nx != 0) vx = 0;
			if (ny != 0) {
				vy = 0;
				vx = 0;
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
				else if (dynamic_cast<CBullet *>(e))
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


	// Tinhs van toc, di chuyen
	if (true) {
		CHero * hero = ((CPlayScene*)(CGame::GetInstance()->GetCurrentScene()))->GetPlayer();
		float tamHero_X, tamHero_Y;
		hero->TinhTam(tamHero_X, tamHero_Y);
		float tam_X, tam_Y;
		TinhTam(tam_X, tam_Y);
		if (tamHero_X - 10 < tam_X&& tamHero_X + 10 > tam_X) {
			{

				if (timeNgungBanDan < 0)
				{
					vy = -3;
					timeNgungBanDan = Enemy9_TimeNgungBanDan;
					BanDan();
					timeAniBanDan = Enemy9_TimeAniBanDan;
				}
			}
		}
	}
}

void CEnemy9::Render()
{


	if (timeAniBanDan >= 0)
	{
		if (vx < 0) animation_set->at(Enemy9_Ani_Left)->Render(round(x), round(y), 255, 1);
		else animation_set->at(Enemy9_Ani_Right)->Render(round(x), round(y), 255, 1);


	}
	else {
		if (vx < 0) animation_set->at(Enemy9_Ani_Left)->Render(round(x), round(y), 255, 0);
		else animation_set->at(Enemy9_Ani_Right)->Render(round(x), round(y), 255, 0);
	}




}

void CEnemy9::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	right = x + Enemy9_Box_Width;
	top = y;
	bottom = y + Enemy9_Box_Height;
}

void CEnemy9::BanDan()
{
	CGameObject *tmpTarget = ((CPlayScene*)(CGame::GetInstance()->GetCurrentScene()))->GetPlayer();
	float a1, b1, a2, b2;

	this->TinhTam(a1, b1);
	tmpTarget->TinhTam(a2, b2);

	CBullet5 *obj = new CBullet5();
	obj->SetPosition(x + 5, y + 5);
	obj->SetState(Bullet_Enemy);



	listObj->push_back(obj);

}


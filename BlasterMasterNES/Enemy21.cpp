#include "Enemy21.h"
#include <cstdlib>
#include "EnemyBulletmap2.h"
#include "Item.h"
#include "PlayScence.h"
#include "Bullet21.h"

CEnemy21::CEnemy21(float x, float y)
{
	this->x = x;
	this->y = y;
	//this->min_x = min_x;
	//this->max_x = max_x;
	vy = 0;
	vx = 0;
	dropItem = Item_HP;
	hp = Enemy21_HP;
	this->SetAnimationSet(CAnimationSets::GetInstance()->Get(Enemy21_AniSet));
}

void CEnemy21::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects, vector<LPGAMEOBJECT>* listObj)
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

void CEnemy21::LastUpdate()
{
	if (coEvents->size() == 0) {
		x += dx;
		y += dy;
	}
	else
	{

		/*if (true) {
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

		}*/

		if (true) {
			for (int i = 0; i < coEvents->size(); i++) {
				CGameObject* e = coEvents->at(i)->obj;

				if (dynamic_cast<CBullet21 *>(e))
				{
					CBullet21 *tmpBullet21 = (CBullet21*)(e);
					/*if (tmpBullet3->target == this)*/ hp -= tmpBullet21->GetDamage();
				}
				/*else if (dynamic_cast<CBullet *>(e) && e->GetState() != Bullet_Enemy)
				{
					CBullet *tmpBullet = (CBullet*)(e);
					hp -= tmpBullet->GetDamage();
				}*/

			}
			if (hp <= 0) {
				isDelete = true;
				DropItem();
			}

		}
		for (UINT i = 0; i < coEvents->size(); i++) delete coEvents->at(i);
	}

	//vy += Enemy21_AY;
	//if (x < min_x)vx = Enemy21_VX;
	//if (x > max_x)vx = -Enemy21_VX;

	timeNgungBanDan -= dt;
	if (timeNgungBanDan <= 0) {
		// = Enemy21_SoLanBanDan;
		timeNgungBanDan = 1000;
		i = (i + 1) % 2;
		BanDan();
	}
}

void CEnemy21::BanDan()
{

	//CGameObject *tmpTarget = ((CPlayScene*)(CGame::GetInstance()->GetCurrentScene()))->GetPlayer();
	float a1, b1, a2, b2;
	CBulleteny1*obj = new CBulleteny1();
	CBulleteny1*obj2 = new CBulleteny1();

	obj->SetmaxD(200);
	obj2->SetmaxD(200);

	//tmpTarget->TinhTam(a1, b1);
	//obj->TinhTam(a2, b2);
	obj->SetState(Bullet_Enemy);
	obj2->SetState(Bullet_Enemy);

	if (i == 0)
	{
		obj->SetSpeed(Bullet1_V_DF, 0);
		obj->SetPosition(x + 26, y + 10);
		obj->SetDamage(Enemy21_Damge_Bullet);
		obj2->SetSpeed(-Bullet1_V_DF, 0);
		obj2->SetPosition(x, y + 10);
		obj2->SetDamage(Enemy21_Damge_Bullet);

	}
	else {
		obj->SetSpeed(0, Bullet1_V_DF);		obj->SetPosition(x + 10, y + 26);
		obj2->SetSpeed(0, -Bullet1_V_DF);		obj2->SetPosition(x + 10, y );
	}
	listObj->push_back(obj);
	listObj->push_back(obj2);

}

void CEnemy21::Render()
{

	if (i <= 0) animation_set->at(Enemy21_Ani_Left)->Render(round(x), round(y), 255, -1);
	else animation_set->at(Enemy21_Ani_Right)->Render(round(x), round(y), 255, -1);
}

void CEnemy21::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + Enemy21_Box_Width;
	bottom = y + Enemy21_Box_Height;
}



#include "Enemy6.h"
#include <cstdlib>
#include "Bullet3.h"
#include "Item.h"

CEnemy6::CEnemy6(float x, float y, float min_x, float max_x)
{
	this->x = x;
	this->y = y;
	this->min_x = min_x;
	this->max_x = max_x;
	vy = 0;
	vx = -Enemy6_VX;

	dropItem = Item_HP;

	hp = Enemy6_HP;

	this->SetAnimationSet(CAnimationSets::GetInstance()->Get(Enemy6_AniSet));
}

void CEnemy6::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects, vector<LPGAMEOBJECT>* listObj)
{


	this->listObj = listObj;
	if (soLanNhay == 0) {
		timeDiTrenMatDat -= dt;
		if (timeDiTrenMatDat < 0) {
			soLanNhay = rand() % 4 + 1;
			DebugOut(L"[Enenmy6] so lan nhay %d\n", soLanNhay);
		}
	}
	else timeDiTrenMatDat = Enemy6_TimeDiTrenMatDat;


	//CGameObject::Update(dt);

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

void CEnemy6::LastUpdate()
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

			if (soLanNhay > 0) {
				if (ny < 0) {
					vy = -Enemy6_VY; soLanNhay--;
				}
			}
			else {
				if (ny != 0) vy = 0;
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

	vy += Enemy6_AY;
	if (x < min_x)vx = Enemy6_VX;
	if (x > max_x)vx = -Enemy6_VX;
}

void CEnemy6::Render()
{

	if (vx <= 0) animation_set->at(Enemy6_Ani_Left)->Render(round(x), round(y), 255, -1);
	else animation_set->at(Enemy6_Ani_Right)->Render(round(x), round(y), 255, -1);
}

void CEnemy6::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + Enemy6_Box_Width;
	bottom = y + Enemy6_Box_Height;
}



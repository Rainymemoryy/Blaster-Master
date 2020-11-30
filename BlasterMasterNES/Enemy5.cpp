#include "Enemy5.h"
#include "Hero.h"
#include "PlayScence.h"
#include "Bullet.h"


CEnemy5::CEnemy5()
{
	this->SetAnimationSet(CAnimationSets::GetInstance()->Get(Enemy5_AniSet));

	x = 100;
	y = 100;
	vx = -Enemy5_VX;
	vy = 0;
	hp = Enemy5_HP;
}

void CEnemy5::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects, vector<LPGAMEOBJECT>* listObj)
{
	
	CHero *hero = ((CPlayScene*)(CGame::GetInstance()->GetCurrentScene()))->GetPlayer();
	if (this->TinhKhoangCach(hero) <= Enemy5_MaxD) {
		float a1, b1, a2, b2;

		hero->TinhTam(a1, b1);
		this->TinhTam(a2, b2);
		vx = 3*Enemy5_VX*(a1 - a2) / hero->TinhKhoangCach(this);
		vy = 3*Enemy5_VY *(b1 - b2) / hero->TinhKhoangCach(this);
		followHero = true;

	}
	else {
		
		timeDoiHuong -= dt;
		if (timeDoiHuong <= 0) {
			vx = -vx;
			timeDoiHuong += Enemy5_TimeDoiHuong;
		}
		followHero = false;
	}
	
	CGameObject::Update(dt);
	coEvents.clear();

	vector<LPGAMEOBJECT> *TmpCoo = new vector<LPGAMEOBJECT>();
	for (int i = 0; i < coObjects->size(); i++) {
		LPGAMEOBJECT e = coObjects->at(i);
		if (dynamic_cast<CBrick *>(e)) {
			TmpCoo->push_back(e);
		}
		if (dynamic_cast<CHero *>(e)) {
			TmpCoo->push_back(e);
		}
		if (dynamic_cast<CBullet *>(e) && e->isTouthtable) {
			if (e->GetState() != Bullet_Enemy)
				TmpCoo->push_back(e);
		}
	}
	CalcPotentialCollisions(TmpCoo, coEvents);
	
}

void CEnemy5::LastUpdate()
{
	
	if (coEvents.size() == 0) {
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

			for (int i = 0; i < coEvents.size(); i++) {
				LPCOLLISIONEVENT e = coEvents[i];
				if (dynamic_cast<CBrick *>(e->obj))
					coEvents_Brick.push_back(e);
			}
			FilterCollision(coEvents_Brick, coEventsResult_Brick, min_tx, min_ty, nx, ny, rdx, rdy);

			x += min_tx * dx + nx * 0.001f;
			y += min_ty * dy + ny * 0.001f;

			if (nx != 0) {
				vx = -vx;
				timeDoiHuong = Enemy5_TimeDoiHuong;
			}
			if (ny != 0) vy = 0;
		}

		if (true) {
			for (int i = 0; i < coEvents.size(); i++) {
				LPCOLLISIONEVENT e = coEvents[i];
				if ((dynamic_cast<CBullet *>(e->obj))) {
					hp -= (dynamic_cast<CBullet *>(e->obj))->GetDamage();
					if (hp <= 0) isDelete = true;
				}
				if ((dynamic_cast<CHero *>(e->obj))) {
					isDelete = true;
				}
			}
		}

		
		for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
	}



}

void CEnemy5::Render()
{
	RenderBoundingBox();
	if(followHero)
	animation_set->at(1)->Render(round(x), round(y), 255, -1);
	else animation_set->at(0)->Render(round(x), round(y), 255, -1);
	
}

void CEnemy5::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	right = x + Enemy5_Box_Width;
	top = y;
	bottom = y + Enemy5_Box_Height;
}


#include "Enemy4.h"
#include "Hero.h"
#include "PlayScence.h"
#include "Bullet.h"


CEnemy4::CEnemy4()
{
	this->SetAnimationSet(CAnimationSets::GetInstance()->Get(Enemy4_AniSet));
	x = 100;
	y = 100;
	vy = 0;
	vx = -Enemy4_VX;
	hp = Enemy4_HP;
	
}

void CEnemy4::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects, vector<LPGAMEOBJECT>* listObj)
{
	vy += Enemy4_AY*dt;


	timeJump -= dt;
	if (timeJump <= 0) {
		vy = -Enemy4_VY;
		timeJump += Enemy4_TimeJump;
	}

	CGameObject::Update(dt);
	coEvents.clear();

	vector<LPGAMEOBJECT> *TmpCoo = new vector<LPGAMEOBJECT>();
	for (int i = 0; i < coObjects->size(); i++) {
		LPGAMEOBJECT e = coObjects->at(i);
		if (dynamic_cast<CBrick *>(e)) {
			TmpCoo->push_back(e);
		}
		if (dynamic_cast<CBullet *>(e) && e->isTouthtable) {
			if (e->GetState() != Bullet_Enemy)
				TmpCoo->push_back(e);
		}
	}
	CalcPotentialCollisions(TmpCoo, coEvents);
	
}

void CEnemy4::LastUpdate()
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

			if (nx != 0) vx = -vx;
			if (ny > 0) vy = 0.5;
			if (ny < 0) {
				vy = -Enemy4_VY;
				timeJump = Enemy4_TimeJump;
			}
		}

		if (true) {
			for (int i = 0; i < coEvents.size(); i++) {
				LPCOLLISIONEVENT e = coEvents[i];
				if ((dynamic_cast<CBullet *>(e->obj))) {
					hp -= (dynamic_cast<CBullet *>(e->obj))->GetDamage();
					if (hp <= 0) isDelete = true;
				}
			}
		}
		for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
	}



}

void CEnemy4::Render()
{
	RenderBoundingBox();
	
	if (vx < 0) animation_set->at(Enemy4_Ani_Left)->Render(round(x), round(y), 255, -1);
	else animation_set->at(Enemy4_Ani_Right)->Render(round(x), round(y), 255, -1);
}

void CEnemy4::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	right = x + Enemy4_Box_Width;
	top = y;
	bottom = y + Enemy4_Box_Height;
}


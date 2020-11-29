#include "Enemy3.h"
#include "Hero.h"
#include "PlayScence.h"
#include "Bullet.h"


CEnemy3::CEnemy3()
{
	this->SetAnimationSet(CAnimationSets::GetInstance()->Get(Enemy1_AniSet));
	px = -1;
	py = 0;
	f = -1;

	x = 100;
	y = 100;
	vx = -Enemy1_VX;
	vy = -50;
	hp = Enemy1_HP;
}

void CEnemy3::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects, vector<LPGAMEOBJECT>* listObj)
{
	CGameObject::Update(dt);
	coEvents.clear();
	vector<LPGAMEOBJECT> *TmpCoo = new vector<LPGAMEOBJECT>();
	for (int i = 0; i < coObjects->size(); i++) {
		LPGAMEOBJECT e = coObjects->at(i);
		if ((dynamic_cast<CBrick *>(e) || dynamic_cast<CBullet *>(e)&&e->isTouthtable)) {
			TmpCoo->push_back(e);
		}
	}
	CalcPotentialCollisions(TmpCoo, coEvents);
}
void CEnemy3::Render()
{
	RenderBoundingBox();
	
}

void CEnemy3::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	right = x + Enemy3_Box_Width;
	top = y;
	bottom = y + Enemy3_Box_Height;
}

void CEnemy3::LastUpdate()
{
	
	if (coEvents.size() == 0) {
		x += dx;
		y += dy;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;
		float rdx = 0;
		float rdy = 0;
		vector<LPCOLLISIONEVENT> coEventsResult;
		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);
		x += min_tx * dx + nx * 0.001f;
		y += min_ty * dy + ny * 0.001f;


		for (int i = 0; i < coEventsResult.size(); i++) {
			LPCOLLISIONEVENT e = coEventsResult[i];
			if ((dynamic_cast<CBrick *>(e->obj))) {

				
			}
			else if ((dynamic_cast<CBullet *>(e->obj))) {

				hp -= (dynamic_cast<CBullet *>(e->obj))->GetDamage();
				if (hp <= 0) isDelete = true;
			}
		}

		for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
	}

}


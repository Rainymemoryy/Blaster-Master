#include "Bullet6.h"

CBullet6::CBullet6(int x1, int y1, int x2, int y2)
{
	this->SetAnimationSet(CAnimationSets::GetInstance()->Get(Bullet6_AniSet));
	damage = Bullet6_Damage_DF;
	vx = 0; vy = 0;
	this->x1 = x1;
	this->y1 = y1;
	this->x2 = x2;
	this->y2 = y2;

	vx = x1 * Bullet6_V_DF;
	vy = y1 * Bullet6_V_DF;

	maxD = 100;
	maxD1 = 40;
}

void CBullet6::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects, vector<LPGAMEOBJECT>* listObj)
{
	if (isPhatNo)return;
	CGameObject::Update(dt);
	coEvents->clear();

	vector<LPGAMEOBJECT>* tmpCoo = new vector<LPGAMEOBJECT>();
	for (int i = 0; i < coObjects->size(); i++) {
		if (dynamic_cast<CEnemy*>(coObjects->at(i)))
			tmpCoo->push_back(coObjects->at(i));

	}
	CalcPotentialCollisions(tmpCoo, *coEvents);
	delete tmpCoo;
}

void CBullet6::LastUpdate()
{

	if (isPhatNo) {
		timeDelete -= dt;
		isTouthtable = false;

	}
	else {
		if (coEvents->size() == 0)
		{


			if (maxD1 - Bullet6_V_DF * dt > 0)
			{
				x += dx;
				y += dy;
				maxD1 -= Bullet6_V_DF * dt;
			}
			else if (maxD1 >= 0) {
				float t = maxD1 / (Bullet6_V_DF * dt);
				x += t * dx;
				y += t * dy;
				maxD1 = -1;
			}
			else
			{
				vx = x2 * Bullet6_V_DF;
				vy = y2 * Bullet6_V_DF;

				if (maxD - sqrt(dx * dx + dy * dy) > 0)
				{
					x += dx;
					y += dy;
					maxD -= sqrt(dx * dx + dy * dy);
				}
				else if (maxD >= 0) {
					float t = maxD / sqrt(dx * dx + dy * dy);
					x += t * dx;
					y += t * dy;
					maxD = -1;
				}
				else
				{
					vx = 0;
					vy = 0;
					isPhatNo = true;
					isTouthtable = false;
				}
			}
		}
		else
		{
			float min_tx, min_ty, nx = 0, ny;
			float rdx = 0;
			float rdy = 0;
			vector<LPCOLLISIONEVENT>* coEventsResult = new vector<LPCOLLISIONEVENT>();


			FilterCollision(*coEvents, *coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);
			x += min_tx * dx + nx * 0.001f;
			y += min_ty * dy + ny * 0.001f;
			isPhatNo = true;
			isTouthtable = false;

			delete coEventsResult;
			for (UINT i = 0; i < coEvents->size(); i++) delete coEvents->at(i);
		}
	}

	if (timeDelete <= 0) isDelete = true;

}

void CBullet6::Render()
{


	if (isPhatNo) {
		animation_set->at(5)->Render(round(x - 6), round(y - 6), 255, -1);
	}
	else {
		int ani = -1;
		if (x1 == x2) {
			if (vx < 0) {
				animation_set->at(0)->Render(round(x), round(y), 255, 0);
				animation_set->at(1)->Render(round(x) + 9, round(y), 255, -1);
			}
			if (vx > 0) {
				animation_set->at(0)->Render(round(x), round(y), 255, 1);
				animation_set->at(2)->Render(round(x) - 16, round(y), 255, -1);
			}


		}

		if (y1 == y2) {
			if (vy < 0) {
				animation_set->at(0)->Render(round(x), round(y), 255, 2);
				animation_set->at(3)->Render(round(x), round(y) + 9, 255, -1);
			}
			if (vy > 0) {
				animation_set->at(0)->Render(round(x), round(y), 255, 3);
				animation_set->at(4)->Render(round(x), round(y) - 16, 255, -1);
			}
		}

	}
}

void CBullet6::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	right = x + Bullet6_Box_Width;
	top = y;
	bottom = y + Bullet6_Box_Height;
}



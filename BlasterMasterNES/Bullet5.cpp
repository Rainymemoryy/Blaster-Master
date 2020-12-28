#include "Bullet5.h"
#include "PlayScence.h"
CBullet5::CBullet5()
{
	this->SetAnimationSet(CAnimationSets::GetInstance()->Get(Bullet5_AniSet));
	damage = Bullet5_Damage_DF;
	
	vy = 0.1;
}

void CBullet5::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects, vector<LPGAMEOBJECT>* listObj)
{

	if (isPhatNo)return;
	CGameObject::Update(dt);
	coEvents->clear();
	CalcPotentialCollisions(coObjects, *coEvents);

}

void CBullet5::LastUpdate()
{
	timeTuHuy -= dt;
	if (isPhatNo)  timeDelete -= dt;
	else {
		if (coEvents->size() == 0)
		{
			x += dx;
			y += dy;
		}
		else
		{
			if (true) {
				float min_tx, min_ty, nx = 0, ny;
				float rdx = 0;
				float rdy = 0;
				vector<LPCOLLISIONEVENT> *coEventsResult = new vector<LPCOLLISIONEVENT>();
				vector<LPCOLLISIONEVENT> *coTmp = new vector<LPCOLLISIONEVENT>();

				for (int i = 0; i < coEvents->size(); i++)
				{
					CGameObject *obj = coEvents->at(i)->obj;
					if (dynamic_cast<CBrick*>(obj)) {
						coTmp->push_back(coEvents->at(i));
					}
					if (dynamic_cast<CHero*>(obj)) {
						coTmp->push_back(coEvents->at(i));
					}
				}

				FilterCollision(*coTmp, *coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);

				x += min_tx * dx + nx * 0.001f;
				y += min_ty * dy + ny * 0.001f;



				for (int i = 0; i < coEventsResult->size(); i++) {
					CGameObject *obj = coEventsResult->at(i)->obj;
					if (dynamic_cast<CBrick*>(obj)) {

						if (coEventsResult->at(i)->nx != 0)vx = 0;

						if (coEventsResult->at(i)->ny != 0) {
							vy = -nayLen;
							nayLen /= 2;
							duoiTheoHero = true;
						}
					
						
					}
					if (dynamic_cast<CHero*>(obj)) {
						isPhatNo = true;
					}
				}
				delete coEventsResult;
				delete coTmp;
			}
			for (UINT i = 0; i < coEvents->size(); i++) delete coEvents->at(i);
		}
		if (true) {
			vy += Bullet5_AY * dt;
		}

	}

	if (duoiTheoHero) {
		CHero * hero = ((CPlayScene*)(CGame::GetInstance()->GetCurrentScene()))->GetPlayer();
		float a1, b1, a2, b2;
		TinhTam(a1, b1);
		hero->TinhTam(a2, b2);
		if (a1 < a2) vx = SLOC_VX;
		else vx = -SLOC_VX;
	}

	if (timeTuHuy <= 0) isPhatNo = true;
	if (timeDelete <= 0) isDelete = true;

	
}

void CBullet5::Render()
{
	
	if (isPhatNo) {
		animation_set->at(1)->Render(round(x - 4), round(y - 4), 255, -1);
		vx = 0; vy = 0;
		
	}
	else {
		if (vx > 0)animation_set->at(0)->Render(round(x), round(y), 255, 1);
		else animation_set->at(0)->Render(round(x), round(y), 255, 0);
	}
}

void CBullet5::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	right = x + Bullet5_Box_Width;
	top = y;
	bottom = y + Bullet5_Box_Height;
}

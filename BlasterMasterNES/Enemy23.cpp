#include "Enemy23.h"
#include <cstdlib>
#include "Bullet21.h"
#include "Item.h"
#include "PlayScence.h"
#include "EnemyBulletmap2.h"

CEnemy23::CEnemy23(float x, float y)
{
	this->x = x;
	this->y = y;
	vy = Enemy23_VY;
	vx = -Enemy23_VX;
	dropItem = Item_HP;
	hp = Enemy23_HP;
	this->SetAnimationSet(CAnimationSets::GetInstance()->Get(Enemy23_AniSet));
}

void CEnemy23::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects, vector<LPGAMEOBJECT>* listObj)
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

void CEnemy23::LastUpdate()
{
	if (coEvents->size() == 0) {
		if (i%3 == 1)
		{
			x += dx;
			y += dy;
		}
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

				if (dynamic_cast<CBullet21 *>(e))
				{
					CBullet21*tmpBullet21 = (CBullet21*)(e);
					hp -= tmpBullet21->GetDamage();
				}

			}
			if (hp <= 0) {
				isDelete = true;
				DropItem();
			}

		}
		for (UINT i = 0; i < coEvents->size(); i++) delete coEvents->at(i);
	}
	
	//vy += Enemy23_AY;
	/*if (x < min_x)vx = Enemy23_VX;
	if (x > max_x)vx = -Enemy23_VX;*/
	timeDiChuyen -= dt;
	timeNgungBanDan -= dt;
	if (timeNgungBanDan <= 0) {
		// = Enemy23_SoLanBanDan;
		timeNgungBanDan = 250;
		i = (i + 1) ;
		srand(time(NULL));
		int res = rand() % (4 - 1 + 1)+1 ;
		vx = 0;
		vy = 0;
		switch (res)
		{
		case 1:
			/*if (nx != 0)*/ vx = Enemy23_VX;
			/*if (ny != 0)*/ vy = 0;
			break;
		case 2:
			/*if (nx != 0)*/ vx = -Enemy23_VX;
			/*if (ny != 0)*/ vy = 0;
			break;
		case 3:
			/*if (nx != 0)*/ vx = 0;
			/*if (ny != 0)*/ vy = Enemy23_VY;
			break;
		case 4:
			/*if (nx != 0)*/ vx = 0;
			/*if (ny != 0)*/ vy = -Enemy23_VY;
			break;

		}
		if(i%3==0)
		BanDan();
		if (i > 10)
			i = 0;
	}
	
}

void CEnemy23::BanDan()
{

	CGameObject *tmpTarget = ((CPlayScene*)(CGame::GetInstance()->GetCurrentScene()))->GetPlayer();
	float a1, b1, a2, b2;
	CBulleteny1*obj = new CBulleteny1();
	obj->SetPosition(x + 7, y + 18);
	obj->SetmaxD(1000);
	tmpTarget->TinhTam(a1, b1);
	obj->TinhTam(a2, b2);
	obj->SetState(Bullet_Enemy);
	obj->SetSpeed(0.09*(a1 - a2) / tmpTarget->TinhKhoangCach(obj), 0.09*(b1 - b2) / tmpTarget->TinhKhoangCach(obj));
	listObj->push_back(obj);
}

void CEnemy23::Render()
{
	//RenderBoundingBox();
	if (i <= 3) animation_set->at(0)->Render(round(x), round(y), 255, -1);
	if ( i < 7 && i>3) animation_set->at(1)->Render(round(x), round(y), 255, -1);
	if (i>=7) 	animation_set->at(2)->Render(round(x), round(y), 255, -1);

}

void CEnemy23::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + Enemy23_Box_Width;
	bottom = y + Enemy23_Box_Height;
}



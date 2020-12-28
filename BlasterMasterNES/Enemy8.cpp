#include "Enemy8.h"
#include "Hero.h"
#include "PlayScence.h"
#include "Bullet.h"
#include "Bullet3.h"
#include "Bullet4.h"
#include "Item.h"



CEnemy8::CEnemy8(float x, float y)
{
	this->SetAnimationSet(CAnimationSets::GetInstance()->Get(Enemy8_AniSet));
	this->x = x;
	this->y = y;
	dropItem = Item_HP;
}

void CEnemy8::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects, vector<LPGAMEOBJECT>* listObj)
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

void CEnemy8::LastUpdate()
{

	if (coEvents->size() != 0) {
		if (true) {

			if (true) {
				for (int i = 0; i < coEvents->size(); i++)
				{
					CGameObject* e = coEvents->at(i)->obj;

					if (dynamic_cast<CHero*>(coEvents->at(i)->obj))
					{
						isDelete = true;
						DropItem();
						BanDan();
						break;
					}
					else
						if (dynamic_cast<CBullet3 *>(e))
						{
							CBullet3 *tmpBullet3 = (CBullet3*)(e);
							if (tmpBullet3->target == this) {
								isDelete = true;
								DropItem();
								BanDan();
								break;
							}
						}
						else
							if (dynamic_cast<CBullet *>(e) && e->GetState() != Bullet_Enemy)
							{
								isDelete = true;
								DropItem();
								BanDan();
								break;
							}

				}


			}
			for (UINT i = 0; i < coEvents->size(); i++) delete coEvents->at(i);
		}
	}
}



void CEnemy8::Render()
{
	
	animation_set->at(0)->Render(round(x), round(y), 255, -1);
}

void CEnemy8::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	right = x + Enemy8_Box_Width;
	top = y;
	bottom = y + Enemy8_Box_Height;
}


void CEnemy8::BanDan()
{
	int soLuongDan = rand() % 3 + 2;
	for (int i = 0; i < soLuongDan; i++) {
		int detal = rand() % 17 + -8;

		CBullet4 *bullet4 = new CBullet4();
		bullet4->SetPosition(x + 4, y);
		bullet4->SetSpeed(Bullet4_VX*detal / 10.f, -Bullet4_VY);
		bullet4->SetState(Bullet_Enemy);
		//DebugOut(L"%f\n", Bullet4_VX*detal / 10.f);

		listObj->push_back(bullet4);
	}

}

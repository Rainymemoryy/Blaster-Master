#include "Bullet.h"
#include "Enemy1.h"

void CBullet::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects, vector<LPGAMEOBJECT>* listObj)
{


	if (isPhatNo)return;
	CGameObject::Update(dt);
	coEvents.clear();
	
	vector<LPGAMEOBJECT> *TmpCoo = new vector<LPGAMEOBJECT>();
	for (int i = 0; i < coObjects->size(); i++) {
		LPGAMEOBJECT e = coObjects->at(i);


		if (e->isTouthtable)
		{
			if (dynamic_cast<CBrick *>(e)) {
				TmpCoo->push_back(e);
			}
			if (dynamic_cast<CHero*>(e)) {
				if (GetState() != Bullet_Hero) TmpCoo->push_back(e);
			}
			if (dynamic_cast<CEnemy*>(e)) {
				if (GetState() != Bullet_Enemy) TmpCoo->push_back(e);
			}
		}
	}
	CalcPotentialCollisions(TmpCoo, coEvents);
	TmpCoo->clear();
	delete TmpCoo;
}

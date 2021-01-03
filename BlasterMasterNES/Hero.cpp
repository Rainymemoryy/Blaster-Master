#include "Hero.h"
#include "Enemy1.h"
#include "Enemy2.h"
#include "Enemy3.h"
#include "Enemy4.h"
#include "Enemy5.h"


#include "Bullet.h"
#include "Bullet1.h"
#include "Bullet2.h"
#include "Bullet3.h"


#include "Item.h"
#include "ItemHp.h"


#include "Stair.h"

#include "PlayScence.h"

CHero::CHero(float x, float y) : CGameObject()
{
	level = LEVEL_SLOC;
	untouchable = 0;
	SetState(STATE_SLDF_DUNGYEN);
	SetState(STATE_SLOC_DUNGYEN);
	start_x = x;
	start_y = y;
	this->x = x;
	this->y = y;

	if(false){
		LSLOC a = new SLOC();
		a->width = 26;
		a->height = 18;
		a->indexAni = 10;
		sloc_ani_box.push_back(a);

		LSLOC b = new SLOC();
		b->width = 26;
		b->height = 26;
		b->indexAni = 11;
		sloc_ani_box.push_back(b);

		LSLOC c = new SLOC();
		c->width = 26;
		c->height = 28;
		c->indexAni = 12;
		sloc_ani_box.push_back(c);

		LSLOC d = new SLOC();
		d->width = 26;
		d->height = 30;
		d->indexAni = 13;
		sloc_ani_box.push_back(d);

		LSLOC f = new SLOC();
		f->width = 26;
		f->height = 34;
		f->indexAni = 14;
		sloc_ani_box.push_back(f);
	}
	if (true) {
		LSLOC a = new SLOC();
		a->width = 26;
		a->height = 18;
		a->indexAni = 10;
		sloc_ani_box.push_back(a);

		LSLOC b = new SLOC();
		b->width = 26;
		b->height = 18;
		b->indexAni = 11;
		sloc_ani_box.push_back(b);

		LSLOC c = new SLOC();
		c->width = 26;
		c->height = 18;
		c->indexAni = 12;
		sloc_ani_box.push_back(c);

		LSLOC d = new SLOC();
		d->width = 26;
		d->height = 18;
		d->indexAni = 13;
		sloc_ani_box.push_back(d);

		LSLOC f = new SLOC();
		f->width = 26;
		f->height = 18;
		f->indexAni = 14;
		sloc_ani_box.push_back(f);
	}
}

void CHero::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects, vector<LPGAMEOBJECT> *listObj)
{
	if (typeMap_isSL) {
		
			if (true) {
				if (isDeath)return;

				CGameObject::Update(dt);

				this->listObj = listObj;
				this->coObjects = coObjects;

				sldf_coTheVaoXe = false;
				sloc_ix = sloc_ix >= 400 ? sloc_ix - 400 : sloc_ix;
				sloc_iy -= dt;
				sloc_iy = sloc_iy >= 400 ? 400 : sloc_iy;
				sloc_iy = sloc_iy <= 0 ? 0 : sloc_iy;

				if (level == LEVEL_SLDF) {
					vy += SLDF_AY * dt;
					if (car != NULL) {
						int xx = x + currentWidth / 2;
						int yy = y + currentWidth / 2;
						int xxx = car->x + 26 / 2;
						int yyy = car->y + 16 / 2;
						float d = abs(sqrt((xx - xxx)*(xx - xxx) + (yy - yyy)*(yy - yyy)));
						if (d < 26) {
							sldf_coTheVaoXe = true;
						}
						else sldf_coTheVaoXe = false;
					}
				}
				else {
					vy += SLOC_AY * dt;
					lastWidth = currentWidth;
					lastHeight = currentHeight;
					currentWidth = sloc_ani_box.at(sloc_iy / 100)->width;
					currentHeight = sloc_ani_box.at(sloc_iy / 100)->height;
				}

				x = x + lastWidth - (currentWidth + lastWidth) / 2;
				y = y + lastHeight - currentHeight;
			}

		if (true) {
			coEvents->clear();
			CalcPotentialCollisions(coObjects, *coEvents);
		}
	}


}

void CHero::LastUpdate()
{
	if (typeMap_isSL) {
		if (isDeath)return;
		untouchable -= dt;

		sldf_oGanCauThang = false;
		sldf_oTrenCauThang = false;

		//Tinh toan va cham
		if (coEvents->size() == 0)
		{
			x += dx;
			y += dy;

		}
		else
		{
			//Va cham vs gach
			if (true) {
				float min_tx, min_ty, nx = 0, ny;
				float rdx = 0;
				float rdy = 0;
				vector<LPCOLLISIONEVENT> *coEventsBrick = new vector<LPCOLLISIONEVENT>();
				vector<LPCOLLISIONEVENT> *coEventsResultBrick = new vector<LPCOLLISIONEVENT>();


				for (int i = 0; i < coEvents->size(); i++)
				{
					if (dynamic_cast<CBrick *>(coEvents->at(i)->obj))
						coEventsBrick->push_back(coEvents->at(i));
					if (dynamic_cast<CStair *>(coEvents->at(i)->obj))
					{
						cauThang = coEvents->at(i)->obj;
						if (coEvents->at(i)->ny < 0) {
							sldf_oGanCauThang = true;
							coEventsBrick->push_back(coEvents->at(i));
						}

					}
				}

				FilterCollision(*coEventsBrick, *coEventsResultBrick, min_tx, min_ty, nx, ny, rdx, rdy);

				x += min_tx * dx + nx * 0.001f;
				y += min_ty * dy + ny * 0.001f;

				if (nx != 0)vx = 0;
				if (ny != 0)vy = 0;

				for (UINT i = 0; i < coEventsResultBrick->size(); i++)
				{
					LPCOLLISIONEVENT e = coEventsResultBrick->at(i);
					if (dynamic_cast<CBrick *>(e->obj)) {
						int a = 1;
						if (ny > 0) a = 10;

						if (level == LEVEL_SLDF) {
							if (ny < 0) sldf_coTheNhay = true;
							else {
								sldf_coTheNhay = false;
								dangNhay = false;
							}
							if (ny < 0)	sldf_coTheNamXuong = true;
							else sldf_coTheNamXuong = false;
							sldf_hp -= ((CBrick*)(e->obj))->GetDamage() * dt*a;

						}
						else {
							if (ny < 0) sloc_coTheNhay = true;
							else {
								sloc_coTheNhay = false;
								dangNhay = false;
							}
							sloc_hp -= ((CBrick*)(e->obj))->GetDamage() * dt*a;

						}
						sldf_oTrenCauThang = false;
					}
					if (dynamic_cast<CStair *>(e->obj)) {
						sldf_oTrenCauThang = true;
						sldf_coTheNamXuong = false;
					}
				}
			}

			//Va cham vs quai, dan
			if (true) {

				float min_tx, min_ty, nx = 0, ny;
				float rdx = 0;
				float rdy = 0;
				vector<LPCOLLISIONEVENT> *coEventsEnemy_Bullet = new vector<LPCOLLISIONEVENT>();
				vector<LPCOLLISIONEVENT> *coEventsResultEnemy_Bullet = new vector<LPCOLLISIONEVENT>();

				for (int i = 0; i < coEvents->size(); i++)
				{
					LPCOLLISIONEVENT e = coEvents->at(i);
					if (dynamic_cast<CEnemy *>(e->obj))
						coEventsEnemy_Bullet->push_back(coEvents->at(i));
					if (dynamic_cast<CBullet *>(e->obj) && e->obj->isTouthtable)
						if (e->obj->GetState() != Bullet_Hero)
							coEventsEnemy_Bullet->push_back(coEvents->at(i));
				}
				FilterCollision(*coEventsEnemy_Bullet, *coEventsResultEnemy_Bullet, min_tx, min_ty, nx, ny, rdx, rdy);

				for (UINT i = 0; i < coEventsResultEnemy_Bullet->size(); i++)
				{
					LPCOLLISIONEVENT e = coEventsResultEnemy_Bullet->at(i);
					if (untouchable <= 0) {

						if (dynamic_cast<CEnemy*>(e->obj)) {


							untouchable = HERO_UNTOUCHABLE_TIME;
							if (level == LEVEL_SLOC)
								sloc_hp -= dynamic_cast<CEnemy*>(e->obj)->GetDamage();
							if (level == LEVEL_SLDF)
								sldf_hp -= dynamic_cast<CEnemy*>(e->obj)->GetDamage();
						}
						if (dynamic_cast<CBullet*>(e->obj)) {

							untouchable = HERO_UNTOUCHABLE_TIME;
							if (level == LEVEL_SLOC)
								sloc_hp -= dynamic_cast<CBullet*>(e->obj)->GetDamage();
							if (level == LEVEL_SLDF)
								sldf_hp -= dynamic_cast<CBullet*>(e->obj)->GetDamage();


						}

					}
				}
			}

			//va cham voi item, cong dich chuyen
			if (true) {
				for (int i = 0; i < coEvents->size(); i++) {
					if (dynamic_cast<CPortal *>(coEvents->at(i)->obj))
					{
						/*CPortal *portal = (CPortal *)(coEvents->at(i)->obj);
						((CPlayScene*)(CGame::GetInstance()->GetCurrentScene()))->SetIdArea(portal->GetSceneId());
						x += portal->GetSumX();
						y += portal->GetSumY();
						vy = 0;
						vx = 0;*/
						CGame::GetInstance()->SwitchScene(4);
					}
					if (dynamic_cast<CItemHp *>(coEvents->at(i)->obj))
					{
						CItemHp *itemhp = (CItemHp *)(coEvents->at(i)->obj);
						if (level == LEVEL_SLDF) {
							sldf_hp += itemhp->GetHP();
						}
						if (level == LEVEL_SLOC) {
							sloc_hp += itemhp->GetHP();
						}
						itemhp->SetDelete(true);
					}
				}

			}

			for (UINT i = 0; i < coEvents->size(); i++) delete coEvents->at(i);
		}

		//Dieu kien leo cau thang
		if (true) {

			if (level == LEVEL_SLDF) {
				for (int i = 0; i < listObj->size(); i++) {
					if (dynamic_cast<CStair *>(listObj->at(i)))
					{
						cauThang = listObj->at(i);
						float l1, t1, r1, b1, l2, t2, r2, b2;
						this->GetBoundingBox(l1, t1, r1, b1);
						listObj->at(i)->GetBoundingBox(l2, t2, r2, b2);
						if (CGame::GetInstance()->ChongLenNhau(l1, t1, r1, b1, l2, t2, r2, b2))
						{
							sldf_oGanCauThang = true;
							break;
						}
					}
				}
			}
			sldf_oGanCauThang = sldf_oTrenCauThang ? true : sldf_oGanCauThang;
			sldf_leoCauThang = sldf_oGanCauThang ? sldf_leoCauThang : false;

		}

		UpdateHP();
	}
	
}

void CHero::Render()
{
	if (typeMap_isSL) {
		untouchable_nhapnhay -= dt;
		int untouchable_alpha = 255;
		if (untouchable > 0 && untouchable_nhapnhay > 0) {
			untouchable_alpha = 50;
		}
		untouchable_nhapnhay = untouchable_nhapnhay <= -100 ? 100 : untouchable_nhapnhay;

		if (level == LEVEL_SLDF)
		{
			int ani = -1;
			if (isDeath) {
				if (nx >= 0)ani = Ani_Sldf_ChetBenPhai;
				else ani = ANI_SLDF_CHETBENTRAI;
			}
			else

				if (sldf_leoCauThang) {
					ani = Ani_Sldf_LeoCauThang;
					if (ny == 0) animation_set->at(ani)->IsStop(true);
					else animation_set->at(ani)->IsStop(false);
				}
				else if (nx < 0) {
					if (vx == 0) {
						if (sldf_namXuong == true) ani = ANI_SLDF_NAMBENTRAI;
						else ani = ANI_SLDF_NHINTRAI;
					}
					else {
						if (sldf_namXuong) ani = ANI_SLDF_BOBENTRAI;
						else ani = ANI_SLDF_DIBENTRAI;
					}
				}
				else {
					if (vx == 0) {
						if (sldf_namXuong == true) ani = ANI_SLDF_NAMBENPHAI;
						else ani = ANI_SLDF_NHINPHAI;
					}
					else {
						if (sldf_namXuong) ani = ANI_SLDF_BOBENPHAI;
						else ani = ANI_SLDF_DIBENPHAI;
					}
				}
			if (ani != -1)
				animation_set->at(ani)->Render(round(x), round(y), untouchable_alpha, -1);
		}
		else {
			if (isDeath) {
				animation_set->at(15)->Render(round(x), round(y), 255, -1);
			}
			else {
				int j = sloc_iy / 100;
				int i = sloc_ix / 100;
				if (nx > 0) i = i + 4;

				int t;
				switch (j)
				{
				case 0:
					t = 0;
					break;
				case 1:
					t = 8;
					break;
				case 2:
					t = 10;
					break;
				case 3:
					t = 12;
					break;
				case 4:
					t = 16;
					break;
				default:
					break;
				}

				animation_set->at(sloc_ani_box.at(j)->indexAni)->Render(round(x), round(y) - t, untouchable_alpha, i);

			}
		}
		RenderHP();
	}
	
}

void CHero::Reset()
{
	if (typeMap_isSL) {
		SetLevel(LEVEL_SLOC);
		SetState(STATE_SLOC_DUNGYEN);

		SetPosition(start_x, start_y);
		SetSpeed(0, 0);

		sloc_hp = 160;
		sldf_hp = 80;
	}
}

void CHero::RenderHP()
{
	if (typeMap_isSL) {
		float camx, camy;
		CGame::GetInstance()->GetCamPos(camx, camy);
		int i = 0;
		if (level == LEVEL_SLDF) {
			i = sldf_hp / 10;
		}
		if (level == LEVEL_SLOC) {
			i = sloc_hp / 20;
		}
		CAnimationSets::GetInstance()->Get(901)->at(0)->Render(round(camx + 10), round(camy + CGame::GetInstance()->GetScreenHeight() - 70), 255, i);
	}
}

void CHero::UpdateHP()
{
	if (typeMap_isSL)
	{
		sloc_hp = sloc_hp >= SLOC_MAXHP ? SLOC_MAXHP : sloc_hp;
		sloc_hp = sloc_hp <= 0 ? 0 : sloc_hp;

		sldf_hp = sldf_hp >= SLDF_MAXHP ? SLDF_MAXHP : sldf_hp;
		sldf_hp = sldf_hp <= 0 ? 0 : sldf_hp;

		if (sldf_hp <= 0 || sloc_hp <= 0) isDeath = true;
	}
}

void CHero::NhayVaoXe()
{
	if (typeMap_isSL)
		if (sldf_coTheVaoXe) {
			nx = 1;
			for (int i = 0; i < listObj->size(); i++)
			{
				if (car == listObj->at(i)) {
					lastHeight = currentHeight;
					lastWidth = currentWidth;
					currentWidth = 26;
					currentHeight = 18;
					x = car->x;
					y = car->y + lastHeight - currentHeight;
					nx = car->nx;
					car = NULL;
					listObj->erase(listObj->begin() + i);
					break;
				}
			}

			level = LEVEL_SLOC;
			SetState(STATE_SLOC_DUNGYEN);
		}
}

void CHero::RaKhoiXe()
{
	if (typeMap_isSL)
		if (vy < 0.1&&sloc_coTheNhay)
		{
			level = LEVEL_SLDF;
			SetState(STATE_SLDF_DUNGYEN);
			if (car == NULL) {
				CGameObject *obj = new CCar();
				car = obj;
				obj->SetPosition(x + lastWidth - (26 + lastWidth) / 2, y + lastHeight - 26);
				obj->SetAnimationSet(CAnimationSets::GetInstance()->Get(2));
				obj->nx = nx;
				listObj->push_back(obj);

			}
		}
}

void CHero::SpecialSkill(int tag)
{
	CPlayScene * playScene = (CPlayScene *)(CGame::GetInstance()->GetCurrentScene());
	if (tag == 1&& playScene->GetIsChoseItem()==1)
		for (int i = 0; i < coObjects->size(); i++) {
			CGameObject *e = coObjects->at(i);

			if (dynamic_cast<CEnemy*>(e) && !this->IsScopeWith(e)) {


				CBullet3 *obj = new CBullet3();

				float ix, iy;
				this->TinhTam(ix, iy);
				obj->SetPosition(ix - 3, iy - 3);
				obj->SetState(Bullet_Hero);
				obj->SetTarget(e);

				listObj->push_back(obj);
				playScene->Set_iItem1(playScene->Get_iItem1() - 1);
			}
		}
}

void CHero::SetState(int state)
{
	CPlayScene * playScene = (CPlayScene*)(CGame::GetInstance()->GetCurrentScene());

	CGameObject::SetState(state);

	if (typeMap_isSL) {

		if (isDeath) return;

		if (state == Bullet3 && level == LEVEL_SLOC && playScene->Get_iItem1()>0) {

			for (int i = 0; i < coObjects->size(); i++) {
				CGameObject *e = coObjects->at(i);

				if (dynamic_cast<CEnemy*>(e) && !this->IsScopeWith(e)) {


					CBullet3 *obj = new CBullet3();

					float ix, iy;
					this->TinhTam(ix, iy);
					obj->SetPosition(ix - 3, iy - 3);
					obj->SetState(Bullet_Hero);
					obj->SetTarget(e);

					listObj->push_back(obj);
					playScene->Set_iItem1(playScene->Get_iItem1() - 1);
				}
			}

		}

		if (state == STATE_VAOXE) {
			NhayVaoXe();
			return;
		}
		if (state == STATE_NHAYKHOIXE) {
			RaKhoiXe();
			return;
		}

		if (level == LEVEL_SLDF) {
			if (state == STATE_SLDF_BANDANDON && !sldf_leoCauThang) {
				CGameObject *tmpObj = new CBullet1();
				if (nx > 0) {
					tmpObj->SetPosition(x + currentWidth / 2 - 2, y + currentHeight / 2 - 2);
					tmpObj->SetSpeed(Bullet1_V_DF, 0);

				}
				else {

					tmpObj->SetPosition(x + currentWidth / 2 - 2, y + currentHeight / 2 - 2);
					tmpObj->SetSpeed(-Bullet1_V_DF, 0);
				}
				tmpObj->SetState(Bullet_Hero);
				listObj->push_back(tmpObj);
			}

			switch (state)
			{
			case STATE_SLDF_DIBENPHAI:

				vx = SLDF_VX;
				nx = 1;
				lastWidth = currentWidth;
				lastHeight = currentHeight;
				currentWidth = BOX_SLDF_WIDTH_DI;
				currentHeight = BOX_SLDF_HEIGHT_DI;
				sldf_namXuong = false;
				break;
			case STATE_SLDF_DIBENTRAI:

				vx = -SLDF_VX;
				nx = -1;
				lastWidth = currentWidth;
				lastHeight = currentHeight;
				currentWidth = BOX_SLDF_WIDTH_DI;
				currentHeight = BOX_SLDF_HEIGHT_DI;
				sldf_namXuong = false;
				break;
			case STATE_SLDF_NHAY:
				if (sldf_coTheNhay) {
					if (vy < 0.1)
					{
						vy = -SLDF_VY;
						SetState(STATE_SLDF_DUNGYEN);
						sldf_coTheNhay = false;
						sldf_coTheNamXuong = false;
						sldf_oGanCauThang = false;
						sldf_leoCauThang = false;
					}
				}
				break;
			case STATE_SLDF_DUNGYEN:
				lastWidth = currentWidth;
				lastHeight = currentHeight;
				currentWidth = BOX_SLDF_WIDTH_DUNG;
				currentHeight = BOX_SLDF_HEIGHT_DUNG;
				vx = 0;
				sldf_namXuong = false;
				break;
			case STATE_SLDF_CHET:
				lastWidth = currentWidth;
				lastHeight = currentHeight;
				currentWidth = BOX_SLDF_WIDTH_CHET;
				currentHeight = BOX_SLDF_HEIGHT_CHET;
				x = x + lastWidth - (currentWidth + lastWidth) / 2;
				y = y + lastHeight - currentHeight;
				isDeath = true;
				break;
			case STATE_SLDF_NAMXUONG:
				if (sldf_coTheNamXuong) {
					if (vy < 0.1) {
						vx = 0;
						lastWidth = currentWidth;
						lastHeight = currentHeight;
						currentWidth = BOX_SLDF_WIDTH_NAMXUONG;
						currentHeight = BOX_SLDF_HEIGHT_NAMXUONG;
						sldf_namXuong = true;
					}
				}
				break;
			case STATE_SLDF_BOBENPHAI:
				vx = SLDF_VX / 2;
				nx = 1;
				sldf_namXuong = true;

				lastWidth = currentWidth;
				lastHeight = currentHeight;
				currentWidth = BOX_SLDF_WIDTH_NAMXUONG;
				currentHeight = BOX_SLDF_HEIGHT_NAMXUONG;
				break;
			case STATE_SLDF_BOBENTRAI:
				vx = -SLDF_VX / 2;
				nx = -1;
				sldf_namXuong = true;

				lastWidth = currentWidth;
				lastHeight = currentHeight;
				currentWidth = BOX_SLDF_WIDTH_NAMXUONG;
				currentHeight = BOX_SLDF_HEIGHT_NAMXUONG;
				break;
			case STATE_SLDF_LEOLENCAUTHANG:
				vy = -0.08;
				vx = 0;
				ny = -1;
				if (cauThang != NULL)
					x = cauThang->x + cauThang->GetWidth() / 2 - currentWidth / 2;
				lastWidth = currentWidth;
				lastHeight = currentHeight;
				currentWidth = BOX_DFMAP_WIDTH_LEOTHANG;
				currentHeight = BOX_DFMAP_HEIGHT_LEOTHANG;
				break;
			case STATE_SLDF_LEOXUONGCAUTHANG:
				vy = 0.08;
				vx = 0;
				ny = 1;
				if (cauThang != NULL)
					x = cauThang->x + cauThang->GetWidth() / 2 - currentWidth / 2;
				lastWidth = currentWidth;
				lastHeight = currentHeight;
				currentWidth = BOX_DFMAP_WIDTH_LEOTHANG;
				currentHeight = BOX_DFMAP_HEIGHT_LEOTHANG;
				break;
			case STATE_SLDF_DUNGTRENCAUTHANG:
				vy = 0;
				vx = 0;
				ny = 0;
				if (cauThang != NULL)
					x = cauThang->x + cauThang->GetWidth() / 2 - currentWidth / 2;
				lastWidth = currentWidth;
				lastHeight = currentHeight;
				currentWidth = BOX_DFMAP_WIDTH_LEOTHANG;
				currentHeight = BOX_DFMAP_HEIGHT_LEOTHANG;
				break;
			default:
				break;
			}
		}
		else {
			if (state == STATE_SLOC_BANDANDON) {
				CGameObject *tmpObj = new CBullet2();
				int j = sloc_iy / 100;
				int i = sloc_ix / 100;
				if (j == 4) {

					tmpObj->SetPosition(x + currentWidth / 2 - 3, y + currentHeight / 2 - 11);
					tmpObj->SetSpeed(0, -Bullet2_V_DF);
				}
				if (j == 0) {
					if (nx > 0) {

						tmpObj->SetPosition(x + currentWidth / 2 - 11, y);
						tmpObj->SetSpeed(Bullet2_V_DF, 0);
					}
					else {

						tmpObj->SetPosition(x + currentWidth / 2 - 11, y);
						tmpObj->SetSpeed(-Bullet2_V_DF, 0);
					}
				}
				tmpObj->SetState(Bullet_Hero);
				listObj->push_back(tmpObj);
			}

			switch (state)
			{
			case STATE_SLOC_CHAYBENTRAI:
				sloc_ix += dt;
				nx = -1;
				vx = -SLOC_VX;
				break;
			case STATE_SLOC_CHAYBENPHAI:
				sloc_ix += dt;
				nx = 1;
				vx = SLOC_VX;
				break;
			case STATE_SLOC_DUNGYEN:
				/*vx = 0;*/
				vx /= 1.2;
				break;
			case STATE_SLOC_NHAY:
				if (sloc_coTheNhay&&vy < 0.1) {
					vy = -SLOC_VY;
					sloc_coTheNhay = false;
					dangNhay = true;
				}
				break;
			case STATE_SLOC_CHET:
				lastWidth = currentWidth;
				lastHeight = currentHeight;
				currentWidth = BOX_SLOC_WIDTH_NOXE;
				currentHeight = BOX_SLOC_HEIGHT_NOXE;
				x = x + lastWidth - (currentWidth + lastWidth) / 2;
				y = y + lastHeight - currentHeight;
				isDeath = true;
				break;
			case STATE_SLOC_KEYUP:
				sloc_iy += 2 * dt;
				break;
			case STATE_SLOC_HIGHTJUMP:
				if (dangNhay&&vy < 0) {
					vy -= 0.00015*dt;
				}
				break;
			default:
				break;
			}
		}
	}
}

void CHero::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	if (typeMap_isSL) {
		left = x;
		top = y;
		right = x + currentWidth;
		bottom = y + currentHeight;
	}
}

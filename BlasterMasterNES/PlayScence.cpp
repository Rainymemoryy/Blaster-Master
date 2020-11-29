#include <iostream>
#include <fstream>

#include "PlayScence.h"
#include "Utils.h"
#include "Textures.h"
#include "Sprites.h"
#include "Portal.h"

using namespace std;

CPlayScene::CPlayScene(int id, LPCWSTR filePath) :
	CScene(id, filePath)
{
	key_handler = new CPlayScenceKeyHandler(this);
}

#define SCENE_SECTION_UNKNOWN -1
#define SCENE_SECTION_TEXTURES 2
#define SCENE_SECTION_SPRITES 3
#define SCENE_SECTION_ANIMATIONS 4
#define SCENE_SECTION_ANIMATION_SETS	5
#define SCENE_SECTION_OBJECTS	6
#define SCENE_SECTION_MAP	7

#define OBJECT_TYPE_MARIO	0
#define OBJECT_TYPE_BRICK	1
#define OBJECT_TYPE_GOOMBA	2
#define OBJECT_TYPE_KOOPAS	3

#define OBJECT_TYPE_PORTAL	50

#define MAX_SCENE_LINE 1024

void CPlayScene::_ParseSection_TEXTURES(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 5) return; // skip invalid lines

	int texID = atoi(tokens[0].c_str());
	wstring path = ToWSTR(tokens[1]);
	int R = atoi(tokens[2].c_str());
	int G = atoi(tokens[3].c_str());
	int B = atoi(tokens[4].c_str());

	CTextures::GetInstance()->Add(texID, path.c_str(), D3DCOLOR_XRGB(R, G, B), atoi(tokens[5].c_str()));
}

void CPlayScene::_ParseSection_SPRITES(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 6) return; // skip invalid lines

	int ID = atoi(tokens[0].c_str());
	int l = atoi(tokens[1].c_str());
	int t = atoi(tokens[2].c_str());
	int r = atoi(tokens[3].c_str());
	int b = atoi(tokens[4].c_str());
	int texID = atoi(tokens[5].c_str());

	LPDIRECT3DTEXTURE9 tex = CTextures::GetInstance()->Get(texID);
	if (tex == NULL)
	{
		DebugOut(L"[ERROR] Texture ID %d not found!\n", texID);
		return;
	}

	CSprites::GetInstance()->Add(ID, l, t, r, b, tex);
}

void CPlayScene::_ParseSection_ANIMATIONS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 3) return; // skip invalid lines - an animation must at least has 1 frame and 1 frame time

	//DebugOut(L"--> %s\n",ToWSTR(line).c_str());

	LPANIMATION ani = new CAnimation();

	int ani_id = atoi(tokens[0].c_str());
	for (int i = 1; i < tokens.size(); i += 2)	// why i+=2 ?  sprite_id | frame_time
	{
		int sprite_id = atoi(tokens[i].c_str());
		int frame_time = atoi(tokens[i + 1].c_str());
		ani->Add(sprite_id, frame_time);
	}

	CAnimations::GetInstance()->Add(ani_id, ani);
}

void CPlayScene::_ParseSection_ANIMATION_SETS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 2) return; // skip invalid lines - an animation set must at least id and one animation id

	int ani_set_id = atoi(tokens[0].c_str());

	LPANIMATION_SET s = new CAnimationSet();

	CAnimations *animations = CAnimations::GetInstance();

	for (int i = 1; i < tokens.size(); i++)
	{
		int ani_id = atoi(tokens[i].c_str());

		LPANIMATION ani = animations->Get(ani_id);
		s->push_back(ani);
	}

	CAnimationSets::GetInstance()->Add(ani_set_id, s);
}

void CPlayScene::_ParseSection_OBJECTS(string line)
{
	vector<string> tokens = split(line);

	//DebugOut(L"--> %s\n",ToWSTR(line).c_str());

	if (tokens.size() < 3) return; // skip invalid lines - an object set must have at least id, x, y

	int object_type = atoi(tokens[0].c_str());
	float x = atof(tokens[1].c_str());
	float y = atof(tokens[2].c_str());

	int ani_set_id = atoi(tokens[3].c_str());

	CAnimationSets * animation_sets = CAnimationSets::GetInstance();

	CGameObject *obj = NULL;

	switch (object_type)
	{
	case OBJECT_TYPE_MARIO:
		if (player != NULL)
		{
			DebugOut(L"[ERROR] MARIO object was created before!\n");
			return;
		}
		obj = new CHero(x, y);
		player = (CHero*)obj;
		obj->SetPosition(x, y);
		DebugOut(L"[INFO] Player object created!\n");
		break;

	case OBJECT_TYPE_BRICK:
		obj = new CBrick();
		obj->SetPosition(x*16.f, y*16.f);
		obj->state = atoi(tokens[6].c_str());
		((CBrick*)obj)->SetRB(atof(tokens[4].c_str()) * 16, atof(tokens[5].c_str()) * 16);

		break;

	case OBJECT_TYPE_PORTAL:
	{
		float r = atof(tokens[4].c_str());
		float b = atof(tokens[5].c_str());
		int scene_id = atoi(tokens[6].c_str());
		obj = new CPortal(x * 16, y * 16, r * 16, b * 16, scene_id);
	}
	break;
	default:
		DebugOut(L"[ERR] Invalid object type: %d\n", object_type);
		return;
	}

	LPANIMATION_SET ani_set = animation_sets->Get(ani_set_id);

	obj->SetAnimationSet(ani_set);
	objects.push_back(obj);
}

void CPlayScene::_ParseSeciton_MAP(string line)
{
	vector<string> tokens = split(line);
	if (tokens.size() < 6) return;
	float x = atof(tokens[0].c_str());
	float y = atof(tokens[1].c_str());
	float z = atof(tokens[2].c_str());
	float t = atof(tokens[3].c_str());
	float k = atof(tokens[4].c_str());
	float j = atof(tokens[5].c_str());
	wstring mt = ToWSTR(tokens[6].c_str());
	map = new Map(x, y, z, t, k, j);
	map->LoadMatrix(mt.c_str());
	map->CreateTilesFromTileSet();
	DebugOut(L"[INFO] ----------------------------------\n");
}

void CPlayScene::Load()
{
	DebugOut(L"[INFO] Start loading scene resources from : %s \n", sceneFilePath);

	ifstream f;
	f.open(sceneFilePath);

	int section = SCENE_SECTION_UNKNOWN;

	char str[MAX_SCENE_LINE];
	while (f.getline(str, MAX_SCENE_LINE))
	{
		string line(str);

		if (line[0] == '#') continue;
		if (line == "[TEXTURES]") { section = SCENE_SECTION_TEXTURES; continue; }
		if (line == "[SPRITES]") {
			section = SCENE_SECTION_SPRITES; continue;
		}
		if (line == "[ANIMATIONS]") {
			section = SCENE_SECTION_ANIMATIONS; continue;
		}
		if (line == "[ANIMATION_SETS]") {
			section = SCENE_SECTION_ANIMATION_SETS; continue;
		}
		if (line == "[OBJECTS]") {
			section = SCENE_SECTION_OBJECTS; continue;
		}
		if (line == "[MAP]") {
			section = SCENE_SECTION_MAP; continue;
		}
		if (line[0] == '[') { section = SCENE_SECTION_UNKNOWN; continue; }

		switch (section)
		{
		case SCENE_SECTION_TEXTURES: _ParseSection_TEXTURES(line); break;
		case SCENE_SECTION_SPRITES: _ParseSection_SPRITES(line); break;
		case SCENE_SECTION_ANIMATIONS: _ParseSection_ANIMATIONS(line); break;
		case SCENE_SECTION_ANIMATION_SETS: _ParseSection_ANIMATION_SETS(line); break;
		case SCENE_SECTION_OBJECTS: _ParseSection_OBJECTS(line); break;
		case SCENE_SECTION_MAP:_ParseSeciton_MAP(line); break;
		}
	}

	f.close();

	CTextures::GetInstance()->Add(ID_TEX_BBOX, L"textures\\bbox.png", D3DCOLOR_XRGB(255, 255, 255));

	DebugOut(L"[INFO] Done loading scene resources %s\n", sceneFilePath);
}

void CPlayScene::Update(DWORD dt)
{
	if (player == NULL) return;

	//Tính toán cx/cy
	player->GetPosition(cx, cy);
	CGame *game = CGame::GetInstance();
	cx -= game->GetScreenWidth() / 2;
	cy -= game->GetScreenHeight() / 2;
	cx = cx < 0 ? 0 : cx;
	cy = cy < 0 ? 0 : cy;
	cx = (cx + game->GetScreenWidth()) > map->GetMapWidth() ? cx = map->GetMapWidth() - game->GetScreenWidth() : cx;
	cy = (cy + game->GetScreenHeight()) > map->GetMapHeiht() ? cy = map->GetMapHeiht() - game->GetScreenHeight() : cy;

	float l1, t1, r1, b1;
	l1 = cx - 50;
	t1 = cy - 50;
	r1 = cx + game->GetScreenWidth() + 100;
	b1 = cy + game->GetScreenHeight() + 100;
	float l2, t2, r2, b2;



	

	for (int i = objects.size() - 1; i >= 0; i--) {
		if (objects[i]->isDelete)
		{
			delete objects[i];
			objects.erase(objects.begin() + i);
		}
		else {
			objects[i]->GetBoundingBox(l2, t2, r2, b2);
			if (game->IsScope(l1, t1, r1, b1, l2, t2, r2, b2) || game->IsScope(l2, t2, r2, b2, l1, t1, r1, b1))
				curObjects->push_back(objects[i]);
		}
	}

	for (size_t i = 0; i < curObjects->size(); i++) {
		curObjects->at(i)->Update(dt, curObjects, &objects);
	}
	for (size_t i = 0; i < curObjects->size(); i++) {
		curObjects->at(i)->LastUpdate();
	}


	
	player->GetPosition(cx, cy);
	cx -= game->GetScreenWidth() / 2;
	cy -= game->GetScreenHeight() / 2;
	cx = cx < 0 ? 0 : cx;
	cy = cy < 0 ? 0 : cy;
	cx = (cx + game->GetScreenWidth()) > map->GetMapWidth() ? cx = map->GetMapWidth() - game->GetScreenWidth() : cx;
	cy = (cy + game->GetScreenHeight()) > map->GetMapHeiht() ? cy = map->GetMapHeiht() - game->GetScreenHeight() : cy;
	CGame::GetInstance()->SetCamPos(round(cx), round(cy));
}

void CPlayScene::Render()
{
	if (map != NULL)
		map->Render(cx, cy);
	for (int i = 0; i < curObjects->size(); i++)
		curObjects->at(i)->Render();
	curObjects->clear();
	
}

void CPlayScene::Unload()
{
	for (int i = 0; i < objects.size(); i++)
		delete objects[i];

	objects.clear();
	player = NULL;

	DebugOut(L"[INFO] Scene %s unloaded! \n", sceneFilePath);
}

void CPlayScenceKeyHandler::OnKeyDown(int KeyCode)
{
	CHero *hero = ((CPlayScene*)scence)->GetPlayer();
	if (KeyCode == DIK_R)
		hero->SetState(AddEnemy);

	if (KeyCode == DIK_E) hero->SetState(Bullet3);

	if (hero->level == LEVEL_SLDF) {
		switch (KeyCode)
		{
		case DIK_SPACE:
			hero->SetState(STATE_SLDF_NHAY);
			break;
		case DIK_A:
			hero->Reset();
			break;
		case DIK_DOWN:
			hero->SetState(STATE_SLDF_NAMXUONG);
			break;
		case DIK_F:
			hero->SetState(STATE_VAOXE);
			break;
		case DIK_D:
			hero->SetState(STATE_SLDF_BANDANDON);
			break;
		default:
			break;
		}
	}
	else
	{
		switch (KeyCode)
		{
		case DIK_A:
			hero->Reset();
			break;
		case DIK_SPACE:
			hero->SetState(STATE_SLOC_NHAY);
			break;
		case DIK_F:
			hero->SetState(STATE_NHAYKHOIXE);
			break;
		case DIK_D:
			hero->SetState(STATE_SLOC_BANDANDON);
			break;
		default:
			break;
		}
	}
}

void CPlayScenceKeyHandler::KeyState(BYTE *states)
{
	CGame *game = CGame::GetInstance();
	CHero *hero = ((CPlayScene*)scence)->GetPlayer();

	if (hero->level == LEVEL_SLDF) {
		if (hero->GetState() == STATE_SLDF_CHET) return;
		if (game->IsKeyDown(DIK_RIGHT))
		{
			if (!hero->sldf_namXuong)
				hero->SetState(STATE_SLDF_DIBENPHAI);
			else
				hero->SetState(STATE_SLDF_BOBENPHAI);
		}
		else
			if (game->IsKeyDown(DIK_LEFT))
			{
				if (!hero->sldf_namXuong)
					hero->SetState(STATE_SLDF_DIBENTRAI);
				else
					hero->SetState(STATE_SLDF_BOBENTRAI);
			}
			else
				if (hero->sldf_namXuong)
					hero->SetState(STATE_SLDF_NAMXUONG);
				else hero->SetState(STATE_SLDF_DUNGYEN);

		if (game->IsKeyDown(DIK_UP))
		{
			if (hero->sldf_namXuong) {
				hero->SetState(STATE_SLDF_DUNGYEN);
			}
		}
	}
	else {
		if (game->IsKeyDown(DIK_LEFT)) {
			hero->SetState(STATE_SLOC_CHAYBENTRAI);

			if (game->IsKeyDown(DIK_UP)) {
				hero->SetState(STATE_SLOC_KEYUP);
			}
		}
		else
			if (game->IsKeyDown(DIK_RIGHT)) {
				hero->SetState(STATE_SLOC_CHAYBENPHAI);

				if (game->IsKeyDown(DIK_UP)) {
					hero->SetState(STATE_SLOC_KEYUP);
				}
			}
			else
				if (game->IsKeyDown(DIK_UP)) {
					hero->SetState(STATE_SLOC_KEYUP);

					if (game->IsKeyDown(DIK_RIGHT)) {
						hero->SetState(STATE_SLOC_CHAYBENPHAI);
					}
					else
						if (game->IsKeyDown(DIK_LEFT)) {
							hero->SetState(STATE_SLOC_CHAYBENTRAI);
						}
						else
						{
							hero->SetState(STATE_SLOC_DUNGYEN);
						}
				}
				else
				{
					hero->SetState(STATE_SLOC_DUNGYEN);
				}
	}
}
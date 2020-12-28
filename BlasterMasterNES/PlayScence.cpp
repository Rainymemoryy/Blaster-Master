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
#define Scene_Section_Objects	6
#define Scene_Section_Map	7
#define Scene_Section_AreaOnMap	8


#define OBJECT_TYPE_MARIO	0
#define OBJECT_TYPE_BRICK	1
#define OBJECT_TYPE_GOOMBA	2
#define OBJECT_TYPE_KOOPAS	3

#define OBJECT_TYPE_PORTAL	50

#define MAX_SCENE_LINE 1024

void CPlayScene::_ParseSection_TEXTURES(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 5) return; 
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

	if (tokens.size() < 6) return; 

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

	if (tokens.size() < 3) return; 
	LPANIMATION ani = new CAnimation();

	int ani_id = atoi(tokens[0].c_str());
	for (int i = 1; i < tokens.size(); i += 2)
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

	if (tokens.size() < 2) return;

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
	if (tokens.size() < 3) return; 

	int object_type = atoi(tokens[0].c_str());
	float x = atof(tokens[1].c_str());
	float y = atof(tokens[2].c_str());
	int ani_set_id = atoi(tokens[3].c_str());

	if (player == NULL)
	{
		player = new CHero(x, y);
	}
	player->SetPosition(x, y);
	CAnimationSets * animation_sets = CAnimationSets::GetInstance();
	LPANIMATION_SET ani_set = animation_sets->Get(ani_set_id);
	player->SetAnimationSet(ani_set);
	
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

void CPlayScene::_ParseSeciton_AreaOnMap(string line)
{
	vector<string> tokens = split(line);
	if (tokens.size() < 2) return;
	int index = atoi(tokens[0].c_str());
	LPCWSTR path = ToLPCWSTR(tokens[1]);
	CAreaOnMap * areaOnMap = new CAreaOnMap(index, path);
	areaOnMap->GetAreaOnMap_Load();
	listAreaOnMap[index] = areaOnMap;
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
			section = Scene_Section_Objects; continue;
		}
		if (line == "[MAP]") {
			section = Scene_Section_Map; continue;
		}
		if (line == "[AREAONMAP]"){
			section = Scene_Section_AreaOnMap; continue;
		}

		if (line[0] == '[') { section = SCENE_SECTION_UNKNOWN; continue; }


		switch (section)
		{
		case SCENE_SECTION_TEXTURES: _ParseSection_TEXTURES(line); break;
		case SCENE_SECTION_SPRITES: _ParseSection_SPRITES(line); break;
		case SCENE_SECTION_ANIMATIONS: _ParseSection_ANIMATIONS(line); break;
		case SCENE_SECTION_ANIMATION_SETS: _ParseSection_ANIMATION_SETS(line); break;
		case Scene_Section_Objects: _ParseSection_OBJECTS(line); break;
		case Scene_Section_Map:_ParseSeciton_MAP(line); break;
		case Scene_Section_AreaOnMap: _ParseSeciton_AreaOnMap(line); break;
		}
	}

	f.close();

	CTextures::GetInstance()->Add(ID_TEX_BBOX, L"textures\\bbox.png", D3DCOLOR_XRGB(255, 255, 255));

	DebugOut(L"[INFO] Done loading scene resources %s\n", sceneFilePath);
}

void CPlayScene::Update(DWORD dt)
{
	if (isStopGame) return;

	if (player == NULL) return;

	CAreaOnMap *curAreaOnMap = listAreaOnMap[indexAreaOnMap];

	curObjects->clear();
	curObjects->push_back(player);
	objects = curAreaOnMap->GetAreaOnMap_ListObj();


	GetCam(cx, cy);
	float l1, t1, r1, b1, l2, t2, r2, b2;
	l1 = cx;
	t1 = cy;
	r1 = cx+CGame::GetInstance()->GetScreenWidth();
	b1 = cy+CGame::GetInstance()->GetScreenHeight();

	//DebugOut(L"++++++++++++++size %d\n", objects->size());

	for (int i = objects->size() - 1; i >= 0; i--) {
		if (objects->at(i)->isDelete)
		{
			CGameObject *tmp = objects->at(i);
			objects->erase(objects->begin() + i);
			delete tmp;
		}
		else {
			if(dynamic_cast<CBrick*>(objects->at(i))) curObjects->push_back(objects->at(i));
			else {
				objects->at(i)->GetBoundingBox(l2, t2, r2, b2);
				if(!(l1 > r2 || r1 < l2 || t1 > b2 || b1 < t2))
					curObjects->push_back(objects->at(i));
			}
		
		}
	}

	//DebugOut(L"-------------size %d\n", objects->size());

	for (size_t i = 0; i < curObjects->size(); i++) {
		curObjects->at(i)->Update(dt, curObjects, objects);
	}
	for (size_t i = 0; i < curObjects->size(); i++) {
		curObjects->at(i)->LastUpdate();
	}



	//DebugOut(L"%d\n", curObjects->size());

	GetCam(cx, cy);
	CGame::GetInstance()->SetCamPos(round(cx), round(cy));
}

void CPlayScene::Render()
{
	if (!isStopGame) {
		GetCam(cx, cy);
		if (map != NULL)
			map->Render(cx, cy);

		for (int i = 0; i < curObjects->size(); i++)
			curObjects->at(i)->Render();
		player->Render();
	}
}

void CPlayScene::Unload()
{
	/*for (int i = 0; i < objects.size(); i++)
		delete objects[i];

	objects.clear();
	player = NULL;

	DebugOut(L"[INFO] Scene %s unloaded! \n", sceneFilePath);*/
}

void CPlayScene::GetCam(float & cx, float & cy)
{
	CGame *game = CGame::GetInstance();
	CAreaOnMap *curAreaOnMap = listAreaOnMap[indexAreaOnMap];

	float l = curAreaOnMap->GetAreaOnMap_X(), t = curAreaOnMap->GetAreaOnMap_Y(), r = curAreaOnMap->GetAreaOnMap_Right(), b = curAreaOnMap->GetAreaOnMap_Bottom();

	player->TinhTam(cx, cy);
	cx -= game->GetScreenWidth() / 2;
	cy -= game->GetScreenHeight() / 2;
	cx = cx < l ? l : cx;
	cy = cy < t ? t : cy;
	cx = (cx + game->GetScreenWidth()) > r ? r - game->GetScreenWidth() : cx;
	cy = (cy + game->GetScreenHeight()) > b ? b - game->GetScreenHeight() : cy;
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
			if (hero->sldf_oTrenCauThang) {
				hero->sldf_leoCauThang = true;
				hero->y += 1;
			}
			else {
				hero->SetState(STATE_SLDF_NAMXUONG);
			}
			break;
		case DIK_F:
			hero->SetState(STATE_VAOXE);
			break;
		case DIK_D:
			hero->SetState(STATE_SLDF_BANDANDON);
			break;
		case DIK_UP:
			if (hero->sldf_oGanCauThang) hero->sldf_leoCauThang = true;
			else
				if (hero->sldf_namXuong) {
					hero->SetState(STATE_SLDF_DUNGYEN);
				}
			break;
		case DIK_ESCAPE:
			((CPlayScene*)scence)->StopOrResumeGame();
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
		case DIK_ESCAPE:
			((CPlayScene*)scence)->StopOrResumeGame();
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
	if (hero->GetState() == STATE_SLDF_CHET) return;


	if (hero->level == LEVEL_SLDF) {
		if (!hero->sldf_leoCauThang)
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
		else
			if (game->IsKeyDown(DIK_UP))
				hero->SetState(STATE_SLDF_LEOLENCAUTHANG);
			else
				if (game->IsKeyDown(DIK_DOWN))
					hero->SetState(STATE_SLDF_LEOXUONGCAUTHANG);
				else
					hero->SetState(STATE_SLDF_DUNGTRENCAUTHANG);
	}
	else {

		if (game->IsKeyDown(DIK_SPACE))
			hero->SetState(STATE_SLOC_HIGHTJUMP);

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
		

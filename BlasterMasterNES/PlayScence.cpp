#include <iostream>
#include <fstream> 
#include <string>  
#include "PlayScence.h"
#include "Utils.h"
#include "Textures.h"
#include "Sprites.h"
#include "Portal.h"
#include "Sound.h"


using namespace std;

CPlayScene::CPlayScene(int id, LPCWSTR filePath) :
	CScene(id, filePath)
{
	key_handler = new CPlayScenceKeyHandler(this);
	
}

#pragma region Load
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
	float x = atof(tokens[1].c_str())*16;
	float y = atof(tokens[2].c_str())*16;
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
		if (line == "[AREAONMAP]") {
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
	//Sound::GetInstance()->Play("Area2", 1, 1);
}
#pragma endregion

bool haveboss = false;
int BossAppearCount=0;
void CPlayScene::Update(DWORD dt)
{
	if(!haveboss)
		Sound::GetInstance()->Play("Area2", 1, 1);
	this->dt = dt;

	if (isStopGame) return;
	if (isChoseItem) return;

	if (player == NULL) return;
	CGame::GetInstance()->SetIsStopRender(false);

	CAreaOnMap *curAreaOnMap = listAreaOnMap[indexAreaOnMap];
	objects = curAreaOnMap->GetAreaOnMap_ListObj();
	curObjects->clear();
	curObjects->push_back(player);
	
	/*if (player->isDeath <= 0)
		Unload();*/
	


	GetCam(cx, cy);
	float l1, t1, r1, b1, l2, t2, r2, b2;
	l1 = cx;
	t1 = cy;
	r1 = cx+CGame::GetInstance()->GetScreenWidth();
	b1 = cy+CGame::GetInstance()->GetScreenHeight();
	if (player->x >= 305*16 && player->y < 172*16 && player->x < 321*16 && player->y>158*16)
		haveboss = true;
	//DebugOut(L"++++++++++++++size %d\n", objects->size());
	if(!haveboss)
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
	else
		if (BossAppearCount>200)
		
		for (int i = objects->size() - 1; i >= 0; i--) 
		{
			/*if (dynamic_cast<CBoss*>(objects->at(i)))
				if (objects->at(i)->hp)*/
			if (objects->at(i)->isDelete)
			{
				CGameObject* tmp = objects->at(i);
				objects->erase(objects->begin() + i);
				delete tmp;
			}
			else {
				if (dynamic_cast<CBrick*>(objects->at(i))) curObjects->push_back(objects->at(i));
				else {
					objects->at(i)->GetBoundingBox(l2, t2, r2, b2);
					if (!(l1 > r2 || r1 < l2 || t1 > b2 || b1 < t2))
						curObjects->push_back(objects->at(i));
				}
			}
			/*if (dynamic_cast<CBoss*>(objects->at(i)))
				curObjects->push_back(objects->at(i));
			if (dynamic_cast<BossArm*>(objects->at(i)))
				curObjects->push_back(objects->at(i));*/
		}
		else {
			for (int i = objects->size() - 1; i >= 0; i--)
			{
				if (dynamic_cast<CBrick*>(objects->at(i))) curObjects->push_back(objects->at(i));
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
int al=255;
float renderleftttt = true;
void CPlayScene::Render()
{
	if (heroChet) {
		if (soMangTrongGame-1 > 0) {
			int t = soMangTrongGame;
			ReLoad();
			soMangTrongGame =  t-1;

		}
		else {
			Sound::GetInstance()->StopAll();
			CGame::GetInstance()->SwitchScene(4);
		}
		heroChet = false;

		return;
	}

	if ((haveboss)&&(BossAppearCount<=201))
	{
		BossAppearCount++;
		if (BossAppearCount == 1)
		{
			Sound::GetInstance()->Stop("Area2");
			Sound::GetInstance()->Play("BossIntro", 1, 100000);
		}
		if (BossAppearCount <= 200) {
			if (BossAppearCount % 10 < 5)
				al = 100;
			else
				al = 255;
			if (map != NULL)
				map->Render(cx, cy, al);
		}
		else
		{
			Sound::GetInstance()->Stop("BossIntro");
			Sound::GetInstance()->Play("Boss", 1, 100000);
			al =0;
			map->Render(cx, cy, al);
			//BossAppearCount = 0;
			/*CGame::GetInstance()->SetCamPos(32, 0);
			player->SetPosition(148, 192);*/
		}

		GetCam(cx, cy);
		if (map != NULL)
			map->Render(cx, cy, al);
		for (int i = 0; i < curObjects->size(); i++)
			curObjects->at(i)->Render();
		player->Render();
		/*if (player->isDeath)
			if(renderleftttt)
			timeRenderLeft = TimeRenderLeft;
	*/	RenderLeft(); //render so mang nhan vat
		player->RenderHP();

	}
	else
	{
		GetCam(cx, cy);
		if (map != NULL)
			map->Render(cx, cy, al);
		for (int i = 0; i < curObjects->size(); i++)
			curObjects->at(i)->Render();
		player->Render();
		if(!haveboss)
		if (player->x > 256 * 16)
			if (player->y > 140 * 16)
			{
				if (map != NULL)
					map->Render2(cx, cy);
			}
			else
			{
				CAreaOnMap* curAreaOnMap = listAreaOnMap[indexAreaOnMap];
				if (player->y > curAreaOnMap->GetAreaOnMap_Bottom() - 95)
					map->Render2(cx, cy);
			}
		//if (player->isDeath)
		//	if (renderleftttt)
		//	{
		//		timeRenderLeft = TimeRenderLeft;
		//		renderleftttt = false;
		//	}
		RenderLeft();
		 //render so mang nhan vat
		player->RenderHP();

		if (isChoseItem) {
			RenderSelectMenu();
		}
		else
			if (isStopGame) {
				CGame::GetInstance()->SetIsStopRender(true);
				RederStopGame();
			}

		if (nextScene != -100) {
			CGame::GetInstance()->SwitchScene(4);
		}
		if (fireworks.size() != 0) {
			for (int i = 0; i < fireworks.size(); i++)
				fireworks.at(i)->Render();
		}
	}
}


void CPlayScene::GetCam(float & cx, float & cy)
{
	CGame *game = CGame::GetInstance();
	CAreaOnMap *curAreaOnMap = listAreaOnMap[indexAreaOnMap];

	int l, t, r, b;

	player->TinhTam(cx, cy);
	if ((cx > 256 * 16) && (cy > 126 * 16))
	{
		l = ((int)cx)/16;
		if (l <= 270)
		{
			l = curAreaOnMap->GetAreaOnMap_X();
			r=l+ 18 * 16;
		}
		else
		{
			while ((l-14) % 16 != 0)
				l--;
			l = l * 16;

			r = l + 20 * 16;
		}
		
		
		t = ((int)cy-16)/16;
		
		while ((t-12) % 16 != 0)
			t--;
		t = t * 16;
		b = t + 20 * 16;
		
		
	}
	else
	{
		l = curAreaOnMap->GetAreaOnMap_X(), t = curAreaOnMap->GetAreaOnMap_Y(), r = curAreaOnMap->GetAreaOnMap_Right(), b = curAreaOnMap->GetAreaOnMap_Bottom();
	}
	cx -= game->GetScreenWidth() / 2;
	cy -= game->GetScreenHeight() / 2;
	cx = cx < l ? l : cx;
	cy = cy < t ? t : cy;
	cx = (cx + game->GetScreenWidth()) > r ? r - game->GetScreenWidth() : cx;
	cy = (cy + game->GetScreenHeight()) > b ? b - game->GetScreenHeight() : cy;
}

#define SpritePause	101
void CPlayScene::RederStopGame()
{
	GetCam(cx, cy);
	CSprites::GetInstance()->Get(SpritePause)->Draw(round(cx),round(cy), 200);
	
}


#define SpriteLeft	201
#define SpriteLeft_X	102
#define SpriteLeft_Y	106
void CPlayScene::RenderLeft()
{
	if (timeRenderLeft <= 0) 
		return;
	/*if (timeRenderLeft < 3000)
		if(player->isDeath&&!renderleftttt)
	{
		player->Reset();
		renderleftttt = true;
		soMangTrongGame -= 1;
	}*/

	GetCam(cx, cy);
	float _x = cx + SpriteLeft_X, _y = cy + SpriteLeft_Y;
	CSprites::GetInstance()->Get(SpriteLeft)->Draw(round(_x), round(_y), 255);
	string str = to_string(soMangTrongGame);
	_x += 35; _y += 1;

	std::list<char> chars;
	for (char c : str)
		chars.push_back(c);
	for (char c : chars)
	{
		int i = (int)c;
		CSprites::GetInstance()->Get(i)->Draw(round(_x), round(_y), 255);
		_x += 7;
		
	}
	timeRenderLeft -= dt;	
	DebugOut(L"time %d\n", timeRenderLeft);
}

#define SpriteSelectMenu	301
#define AniSelectMenu		302
#define Item_1	1
#define Item_2	2
#define Item_3	3
#define Item_1_X	80
#define Item_1_Y	167
#define Item_2_X	112
#define Item_2_Y	167
#define Item_3_X	144
#define Item_3_Y	137

#define Item_1_IX	96
#define Item_2_IX	128	
#define Item_3_IX	160
#define Item_IY		183
void CPlayScene::RenderSelectMenu()
{
	GetCam(cx, cy);
	CSprites::GetInstance()->Get(SpriteSelectMenu)->Draw(round(cx), round(cy), 255);
	
	switch (selectItem)
	{
	case Item_1:
		CAnimations::GetInstance()->Get(AniSelectMenu)->Render(round(cx + Item_1_X), round(cy + Item_1_Y), 255);
		break;
	case Item_2:
		CAnimations::GetInstance()->Get(AniSelectMenu)->Render(round(cx + Item_2_X), round(cy + Item_1_Y), 255);
		break;
	case Item_3:
		CAnimations::GetInstance()->Get(AniSelectMenu)->Render(round(cx + Item_3_X), round(cy + Item_1_Y), 255);
		break;
	default:
		break;
	}


	if (true)
	{
		string str = to_string(player->Get_iItem1());
		std::list<char> chars;
		for (char c : str)
			chars.push_back(c);
		float _x = cx+ Item_1_IX, _y = cy+ Item_IY;
		_x -= 7 * chars.size()/2+1;
		for (char c : chars)
		{
			int i = (int)c;
			CSprites::GetInstance()->Get(i)->Draw(round(_x), round(_y), 255);
			_x += 7;
		}
	}
	
	if (true)
	{
		string str = to_string(player->Get_iItem2());
		std::list<char> chars;
		for (char c : str)
			chars.push_back(c);
		float _x = cx + Item_2_IX, _y = cy + Item_IY;
		_x -= 7 * chars.size() / 2 + 1;
		for (char c : chars)
		{
			int i = (int)c;
			CSprites::GetInstance()->Get(i)->Draw(round(_x), round(_y), 255);
			_x += 7;
		}
	}

	if (true)
	{
		string str = to_string(player->Get_iItem3());
		std::list<char> chars;
		for (char c : str)
			chars.push_back(c);
		float _x = cx + Item_3_IX, _y = cy + Item_IY;
		_x -= 7 * chars.size() / 2 + 1;
		for (char c : chars)
		{
			int i = (int)c;
			CSprites::GetInstance()->Get(i)->Draw(round(_x), round(_y), 255);
			_x += 7;
		}
	}

}

void CPlayScene::SelectItemLeft()
{
	selectItem--;
	selectItem = selectItem < Item_1 ? Item_1 : selectItem;
}

void CPlayScene::SelectItemRight()
{
	selectItem++;
	selectItem = selectItem > Item_3 ? Item_3 : selectItem;
}
void CPlayScene::ReLoad()
{
	if (true) {

		player = new CHero();
		indexAreaOnMap = InDexArea_Start;
		cx = 0, cy = 0;
		last_cx = 0, last_cy = 0;
		isStopGame = false;
		soMangTrongGame = SoMangMacDinh;
		timeHienThiSoMangTrongGame = TimeHienThiSoMangTrongGame;
		timeRenderLeft = TimeRenderLeft;
		selectItem = 1;
		isChoseItem = false;

	
		listAreaOnMap.clear();

		//Danh sách đối tượng
		objects = new vector<LPGAMEOBJECT>();
		curObjects = new vector<LPGAMEOBJECT>();

	}
	if (true) {
		DebugOut(L"[INFO] Start re loading scene resources from : %s \n", sceneFilePath);

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
			if (line == "[AREAONMAP]") {
				section = Scene_Section_AreaOnMap; continue;
			}

			if (line[0] == '[') { section = SCENE_SECTION_UNKNOWN; continue; }


			switch (section)
			{

			case Scene_Section_Objects: _ParseSection_OBJECTS(line); break;
			case Scene_Section_AreaOnMap: _ParseSeciton_AreaOnMap(line); break;
			}
		}

		f.close();

		DebugOut(L"[INFO] Done re loading scene resources %s\n", sceneFilePath);
	}

}

void CPlayScene::Unload()
{
	CAreaOnMap* curAreaOnMap = listAreaOnMap[indexAreaOnMap];
	objects = curAreaOnMap->GetAreaOnMap_ListObj();
	for (int i = 0; i < objects->size(); i++)
		delete objects->at(i);

	objects->clear();
	player = NULL;

	DebugOut(L"[INFO] Scene %s unloaded! \n", sceneFilePath);
}

#pragma region KeyBorad
void CPlayScenceKeyHandler::OnKeyDown(int KeyCode)
{
	CPlayScene* playScene = (CPlayScene*)scence;
	CHero *hero = playScene->GetPlayer();
	if (KeyCode == DIK_Q)
	{
		hero->Reset();
		hero->timeNgapChet = Time_NgapChet;
	}
	if (hero->level == LEVEL_OVH)
	{

		if (KeyCode == DIK_D)
			hero->shoot = true;
		else hero->shoot = false;
		if (KeyCode == DIK_A)
			playScene->ReLoad();
			//hero->Reset();
		//if (playScene->GetIsStopGame()) {
			if (KeyCode == DIK_ESCAPE)
				((CPlayScene*)scence)->StopOrResumeGame();
		

	}
	else
	if (playScene->GetIsChoseItem()) {
		switch (KeyCode)
		{
		case DIK_RIGHT:
			playScene->SelectItemRight();
			break;
		case DIK_LEFT:
			playScene->SelectItemLeft();
			break;
		case DIK_ESCAPE:
			playScene->SetIsChoseItem(false);
			break;
		case 28: //enter
			playScene->SetIsChoseItem(false);
			break;
		default:
			
			break;
		}
	}
	else
		if (playScene->GetIsStopGame()) {
			if(KeyCode==DIK_ESCAPE)
				((CPlayScene*)scence)->StopOrResumeGame();
		}
		else {

			switch (KeyCode)
			{

			case DIK_TAB:
				playScene->SetIsChoseItem(true);
				break;
			case DIK_ESCAPE:
				playScene->StopOrResumeGame();
				break;
			case DIK_A:
				playScene->ReLoad();;
				break;
			case DIK_E:
				if (hero->level == LEVEL_SLOC)
					hero->SetState(SLOC_Special_Skill);
				break;
			case DIK_SPACE:
				if (hero->level == LEVEL_SLDF)
					hero->SetState(STATE_SLDF_NHAY);
				else
					hero->SetState(STATE_SLOC_NHAY);
				break;
			case DIK_DOWN:
				if (hero->level == LEVEL_SLDF) {
					if (hero->sldf_oTrenCauThang) {
						hero->sldf_leoCauThang = true;
						hero->y += 1;
					}
					else {
						hero->SetState(STATE_SLDF_NAMXUONG);
					}
				}
				break;
			case DIK_F:
				if (hero->level == LEVEL_SLDF)
					hero->SetState(STATE_VAOXE);
				else
					hero->SetState(STATE_NHAYKHOIXE);
				break;
			case DIK_D:
				if (hero->level == LEVEL_SLDF)
					hero->SetState(STATE_SLDF_BANDANDON);
				else
					hero->SetState(STATE_SLOC_BANDANDON);
				break;
			case DIK_C:
				hero->SetState(STATE_SLOC_BANDANCHUM);
				break;
			case DIK_UP:
				if (hero->level == LEVEL_SLDF) {
					if (hero->sldf_oGanCauThang) hero->sldf_leoCauThang = true;
					else
						if (hero->sldf_namXuong) {
							hero->SetState(STATE_SLDF_DUNGYEN);
						}
				}
				break;
			default:
				break;
			}
		}
}

void CPlayScenceKeyHandler::KeyState(BYTE *states)
{

	CGame *game = CGame::GetInstance();
	CPlayScene* playScene = (CPlayScene*)scence;
	CHero *hero = playScene->GetPlayer();
	
	if (hero->level == LEVEL_OVH)
	{
		if (game->IsKeyDown(DIK_UP))
		{
			hero->SetState(STATE_SLDF_OVH_DITREN);
		}
		else
			if (game->IsKeyDown(DIK_DOWN))
			{
				hero->SetState(STATE_SLDF_OVH_DIDUOI);
			}
			else
				if (game->IsKeyDown(DIK_LEFT))
				{
					hero->SetState(STATE_SLDF_OVH_DITRAI);
				}
				else
					if (game->IsKeyDown(DIK_RIGHT))
					{
						hero->SetState(STATE_SLDF_OVH_DIPHAI);
					}
					else
					{
						if (hero->state > STATE_SLDF_OVH_PHAI)
							hero->SetState(hero->state - 4);
						if (hero->state < STATE_SLDF_OVH_TREN)
							hero->SetState(STATE_SLDF_OVH_PHAI);
					}
	}
	else

	if (playScene->GetIsChoseItem()) {

	}
	else
		if (playScene->GetIsStopGame()) {

		}
		else {
			if (hero->GetState() == STATE_SLDF_CHET) return;


			if (true) {
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
								else
									hero->SetState(STATE_SLDF_DUNGYEN);
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
					{
						hero->SetState(STATE_SLOC_HIGHTJUMP);
						//Sound::GetInstance()->Play("PlayerJump", 0, 1);
					}
					if (game->IsKeyDown(DIK_UP)) {
						hero->SetState(STATE_SLOC_KEYUP);
					}

					if (game->IsKeyDown(DIK_LEFT))
						hero->SetState(STATE_SLOC_CHAYBENTRAI);
					else
						if (game->IsKeyDown(DIK_RIGHT)) 
							hero->SetState(STATE_SLOC_CHAYBENPHAI);
						else
							hero->SetState(STATE_SLOC_DUNGYEN);

				}
			}

			if (false) {
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
								else
									hero->SetState(STATE_SLDF_DUNGYEN);
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
					{
						hero->SetState(STATE_SLOC_HIGHTJUMP);
						//Sound::GetInstance()->Play("PlayerJump", 0, 1);
					}
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
								if (game->IsKeyDown(DIK_RIGHT))
									hero->SetState(STATE_SLOC_CHAYBENPHAI);
								else
									if (game->IsKeyDown(DIK_LEFT))
										hero->SetState(STATE_SLOC_CHAYBENTRAI);
									else
										hero->SetState(STATE_SLOC_DUNGYEN);
							}
							else
								hero->SetState(STATE_SLOC_DUNGYEN);

				}
			}
			
		}
}
#pragma endregion

		

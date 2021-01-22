#include "OpeningScene.h"
#include <iostream>
#include <fstream>
#include "PlayScence.h"
#include "Utils.h"
#include "Textures.h"
#include "Sprites.h"
#include "Portal.h"
#include "Sound.h"

using namespace std;

COpeningScene::COpeningScene(int id, LPCWSTR filePath) :
	CScene(id, filePath)
{
	key_handler = new COpeningScenceKeyHandler(this);
	CGame::GetInstance()->SetCamPos(0, 0);
}

#define SCENE_SECTION_UNKNOWN			-1
#define SCENE_SECTION_TEXTURES			2
#define SCENE_SECTION_SPRITES			3
#define SCENE_SECTION_ANIMATIONS		4
#define SCENE_SECTION_ANIMATION_SETS	5

#define MAX_SCENE_LINE 1024

void COpeningScene::_ParseSection_TEXTURES(string line)
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

void COpeningScene::_ParseSection_SPRITES(string line)
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

void COpeningScene::_ParseSection_ANIMATIONS(string line)
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

void COpeningScene::_ParseSection_ANIMATION_SETS(string line)
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

void COpeningScene::Load()
{
	DebugOut(L"[Opening scene] -----------------------------------\n" );
	DebugOut(L"[INFO] Start loading scene resources from : %s \n", sceneFilePath);

	ifstream f;
	f.open(sceneFilePath);

	int section = SCENE_SECTION_UNKNOWN;

	char str[MAX_SCENE_LINE];
	while (f.getline(str, MAX_SCENE_LINE))
	{
		string line(str);

		if (line[0] == '#') continue;
		if (line == "[TEXTURES]") {
			section = SCENE_SECTION_TEXTURES; continue; 
		}
		if (line == "[SPRITES]") {
			section = SCENE_SECTION_SPRITES; continue;
		}
		if (line == "[ANIMATIONS]") {
			section = SCENE_SECTION_ANIMATIONS; continue;
		}
		if (line == "[ANIMATION_SETS]") {
			section = SCENE_SECTION_ANIMATION_SETS; continue;
		}
		if (line[0] == '[') { section = SCENE_SECTION_UNKNOWN; continue; }


		switch (section)
		{
			case SCENE_SECTION_TEXTURES: _ParseSection_TEXTURES(line); break;
			case SCENE_SECTION_SPRITES: _ParseSection_SPRITES(line); break;
			case SCENE_SECTION_ANIMATIONS: _ParseSection_ANIMATIONS(line); break;
			case SCENE_SECTION_ANIMATION_SETS: _ParseSection_ANIMATION_SETS(line); break;
		}
	}

	f.close();
	CTextures::GetInstance()->Add(ID_TEX_BBOX, L"textures\\bbox.png", D3DCOLOR_XRGB(255, 255, 255));
	DebugOut(L"[INFO] Done loading scene resources %s\n", sceneFilePath);
	ani_set = CAnimationSets::GetInstance()->Get(AniSetOpening);
	Sound::GetInstance()->Play("Opening", 1, 1);
}

void COpeningScene::Update(DWORD dt)
{
	timeLine += dt;
	DebugOut(L"%d\n", timeLine);
	
	if (timeLine >= OP_TimeLine)
	{
		Sound::GetInstance()->Stop("Opening");
		CGame::GetInstance()->SwitchScene(GetNextScene());
		if (this->id == 1)
			Sound::GetInstance()->Play("CarBackground", 0, 1);
	}
	
}
void COpeningScene::Render()
{
	ani_set->at(0)->Render(0, 0, 255, -1);
}

void COpeningScene::Unload()
{
	delete ani_set;
	//Sound::GetInstance()->StopAll();
}

void COpeningScenceKeyHandler::OnKeyDown(int KeyCode)
{
	if (KeyCode == DIK_SPACE || KeyCode == DIK_ESCAPE)
	if (this->scence->id == 1)
	{
		Sound::GetInstance()->Stop("Opening");
		CGame::GetInstance()->SwitchScene(CGame::GetInstance()->GetCurrentScene()->GetNextScene());		
		Sound::GetInstance()->Play("CarBackground", 0, 1);
	}
}

void COpeningScenceKeyHandler::KeyState(BYTE *states)
{
	return;
}


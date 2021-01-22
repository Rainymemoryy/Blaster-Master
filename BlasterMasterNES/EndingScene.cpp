#include "EndingScene.h"
#include <iostream>
#include <fstream>
#include "PlayScence.h"
#include "Utils.h"
#include "Textures.h"
#include "Sprites.h"
#include "Portal.h"
#include "Sound.h"

using namespace std;

CEndingScene::CEndingScene(int id, LPCWSTR filePath) :
	CScene(id, filePath)
{
	key_handler = new CEndingScenceKeyHandler(this);
	CGame::GetInstance()->SetCamPos(cam_x, cam_y);
}


#pragma region Load
#define SCENE_SECTION_UNKNOWN			-1
#define SCENE_SECTION_TEXTURES			2
#define SCENE_SECTION_SPRITES			3
#define SCENE_SECTION_ANIMATIONS		4
#define SCENE_SECTION_CREDIT			5


#define MAX_SCENE_LINE 1024

void CEndingScene::_ParseSection_TEXTURES(string line)
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

void CEndingScene::_ParseSection_SPRITES(string line)
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

void CEndingScene::_ParseSection_ANIMATIONS(string line)
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


void CEndingScene::_ParseSection_CREDIT(string line)
{

	vector<string> tokens = split(line);
	if (tokens.size() < 2) return;

	int credit_type = atoi(tokens[0].c_str());
	int x = atoi(tokens[2].c_str());
	int y = atoi(tokens[3].c_str());
	float vx = atof(tokens[4].c_str());
	float vy = atof(tokens[5].c_str());

	if (credit_type == Credit_Type_Ani) {
		CCredit *credit = new CCredit(Credit_Type_Ani, x, y, vx, vy);
		credit->SetAni(CAnimations::GetInstance()->Get(atoi(tokens[1].c_str())));
		listCredit_Ani->push_back(credit);
	}
	else
		if (credit_type == Credit_Type_String) {

			vector<CSprite * > *listSprite = new vector<CSprite *>();
			std::list<char> chars;
			for (char c : tokens[1])
				chars.push_back(c);
			for (char c : chars)
			{
				int i = (int)c;
				DebugOut(L"%d\n", i);
				if (i >= 65 && i <= 90)
					listSprite->push_back(CSprites::GetInstance()->Get(i));
				else if (i == 46 || i == 45 || i == 33) {
					listSprite->push_back(CSprites::GetInstance()->Get(i));
				}
				else if (i >= 48 & i <= 57) {
					listSprite->push_back(CSprites::GetInstance()->Get(i));
				}
				else
					listSprite->push_back(CSprites::GetInstance()->Get(-1));
			}

			CCredit *credit = new CCredit(Credit_Type_String, x, y, vx, vy);
			credit->SetSpriteString(listSprite);

			listCredit_String->push_back(credit);
		}


}

void CEndingScene::Load()
{
	DebugOut(L"[Ending scene] -----------------------------------\n");
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
		if (line == "[CREDIT]") {
			section = SCENE_SECTION_CREDIT; continue;
		}
		if (line[0] == '[') { section = SCENE_SECTION_UNKNOWN; continue; }


		switch (section)
		{
		case SCENE_SECTION_TEXTURES: _ParseSection_TEXTURES(line); break;
		case SCENE_SECTION_SPRITES: _ParseSection_SPRITES(line); break;
		case SCENE_SECTION_ANIMATIONS: _ParseSection_ANIMATIONS(line); break;
		case SCENE_SECTION_CREDIT: _ParseSection_CREDIT(line); break;
		}
	}

	f.close();
	CTextures::GetInstance()->Add(ID_TEX_BBOX, L"textures\\bbox.png", D3DCOLOR_XRGB(255, 255, 255));

	nuiLua = listCredit_Ani->at(0);

	DebugOut(L"[INFO] Done loading scene resources %s\n", sceneFilePath);
}
#pragma endregion

#define MiniScece1_Background_Width	254
void CEndingScene::Update(DWORD dt)
{

	this->dt = dt;
	timeLine += dt;
	DebugOut(L"TimeLine: %d\n", timeLine);
	if (timeLine < ED_TimeLine_NuiLuaBatDauHoatDong)//Nui lua chua hoat dong
	{
		CGame::GetInstance()->SetCamPos(round(cam_x), round(cam_y));
		
	}
	else
		if (timeLine < ED_TimeLine_NuiLuaNgungHoatDong) //Nui lua dang hoat dong
		{
			Sound::GetInstance()->Play("Mountain", 1, 1);
			nuiLua->SetSpeed(0, 0.0055);
			int n = rand() % 6 + -3;
			CGame::GetInstance()->SetCamPos(round(cam_x), round(cam_y + n));
		}
		else
			if (timeLine < ED_TimeLine_KetThucMiniScene_1) //Di chuyen camera
			{
				Sound::GetInstance()->Stop("Mountain");
				Sound::GetInstance()->Play("Ending", 1, 1);

				cam_x += dt * cam_vx;
				cam_x = cam_x >= MiniScece1_Background_Width ? MiniScece1_Background_Width : cam_x;
				CGame::GetInstance()->SetCamPos(round(cam_x), round(cam_y));

			}
			else
				if (timeLine < ED_TimeLine_KetThucCredit_Scene2)//Mini scene 2 chay credit tac gia
				{
				
					//Sound::GetInstance()->Play("Ending", 1, 1);



					if (indexCredit < listCredit_String->size()) {
						is_mini_scene1 = false;
						is_mini_scene2 = true;
						cam_x = 0;
						cam_y = 0;
						CGame::GetInstance()->SetCamPos(round(cam_x), round(cam_y));
						nextRowCredit -= dt;
						if (nextRowCredit <= 0) {
							nextRowCredit = ED_NextRound_Credit;
							listCredit_String_Load->push_back(listCredit_String->at(indexCredit));
							indexCredit++;
						}
					}
					
				}
				else {

				}

}

#define BackGround_miniScene1_1 1011
#define BackGround_miniScene1_2 1012
#define BackGround_miniScene2	1021
void CEndingScene::Render()
{
	if (is_mini_scene1) {
		//Vẽ nền
		CSprites::GetInstance()->Get(BackGround_miniScene1_1)->Draw(0, 0);

		//Vẽ đối tượng
		for (int i = 0; i < listCredit_Ani->size(); i++)
			listCredit_Ani->at(i)->Render(dt);

		//Vẽ lại nền
		CSprites::GetInstance()->Get(BackGround_miniScene1_2)->Draw(0, 136);
	}
	else
		if (is_mini_scene2)
		{
			CSprites::GetInstance()->Get(BackGround_miniScene2)->Draw(0, 0);
			for (int i = 0; i < listCredit_String_Load->size(); i++) {
				listCredit_String_Load->at(i)->Render(dt);
			}
		}

}

void CEndingScene::Unload()
{
	delete ani_set;
	for (int i = 0; i < listCredit_String->size(); i++) {
		delete listCredit_String->at(i);
	}
	for (int i = 0; i < listCredit_Ani->size(); i++) {
		delete listCredit_Ani->at(i);
	}

}


#pragma region KeyBoard
void CEndingScenceKeyHandler::OnKeyDown(int KeyCode)
{
	return;
}

void CEndingScenceKeyHandler::KeyState(BYTE *states)
{
	return;
}

#pragma endregion



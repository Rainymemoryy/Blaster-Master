#pragma once
#include "Game.h"
#include "Textures.h"
#include "Scence.h"
#include "GameObject.h"
#include "Brick.h"
#include "Hero.h"
#include "Map.h"

#include "Credit.h"


#define Time_Ending	10000
#define ED_Cam_VX	0.08f

#define ED_NextRound_Credit	1500


#define ED_TimeLine_NuiLuaBatDauHoatDong	3000
#define ED_TimeLine_NuiLuaNgungHoatDong		6300
#define ED_TimeLine_KetThucMiniScene_1		13000
#define ED_TimeLine_KetThucCredit_Scene2	100000

class CEndingScene : public CScene
{
protected:


	float cam_x=0, cam_y=0;
	float cam_vx = ED_Cam_VX;
	int dt;

	bool is_mini_scene1 = true;
	bool is_mini_scene2 = false;

	void _ParseSection_TEXTURES(string line);
	void _ParseSection_SPRITES(string line);
	void _ParseSection_ANIMATIONS(string line);
	void _ParseSection_CREDIT(string line);
	LPANIMATION_SET ani_set;


	int timeLine = ED_NextRound_Credit;
	

	//miniScene1 
	vector<CCredit * > *listCredit_Ani = new vector<CCredit *>();
	CCredit *nuiLua;

	//miniScene2
	vector<CCredit * > *listCredit_String = new vector<CCredit *>();
	vector<CCredit * > *listCredit_String_Load = new vector<CCredit *>();
	int nextRowCredit = ED_NextRound_Credit;
	int indexCredit = 0;


public:
	CEndingScene(int id, LPCWSTR filePath);
	virtual void Load();
	virtual void Update(DWORD dt);
	virtual void Render();
	virtual void Unload();
};



class CEndingScenceKeyHandler : public CScenceKeyHandler
{
public:
	virtual void KeyState(BYTE *states);
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode) {};
	CEndingScenceKeyHandler(CScene *s) :CScenceKeyHandler(s) {};
};

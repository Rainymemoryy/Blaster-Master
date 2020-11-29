#pragma once
#include "Game.h"
#include "Textures.h"
#include "Scence.h"
#include "GameObject.h"
#include "Brick.h"
#include "Hero.h"

#include "Map.h"

class CPlayScene : public CScene
{
protected:
	CHero *player;					// A play scene has to have player, right?
	Map *map;

	vector<LPGAMEOBJECT> objects;
	vector<LPGAMEOBJECT> *curObjects=new vector<LPGAMEOBJECT>();

	float cx = 0, cy = 0;
	float last_cx = 0, last_cy = 0;


	void _ParseSection_TEXTURES(string line);
	void _ParseSection_SPRITES(string line);
	void _ParseSection_ANIMATIONS(string line);
	void _ParseSection_ANIMATION_SETS(string line);
	void _ParseSection_OBJECTS(string line);
	void CPlayScene::_ParseSeciton_MAP(string line);

	int a = 0, b = 0;

public:
	CPlayScene(int id, LPCWSTR filePath);
	virtual void Load();
	virtual void Update(DWORD dt);
	virtual void Render();
	virtual void Unload();

	CHero * GetPlayer() { return player; }

	//friend class CPlayScenceKeyHandler;
};

class CPlayScenceKeyHandler : public CScenceKeyHandler
{
public:
	virtual void KeyState(BYTE *states);
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode) {};
	CPlayScenceKeyHandler(CScene *s) :CScenceKeyHandler(s) {};
};
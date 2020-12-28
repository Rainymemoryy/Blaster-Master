#pragma once
#include "Game.h"
#include "Textures.h"
#include "Scence.h"
#include "GameObject.h"
#include "Brick.h"
#include "Hero.h"
#include "Map.h"

#define AniSetOpening	1
#define OP_TimeLine	25000




class COpeningScene : public CScene
{
	
protected:

	int timeLine = 0;


	void _ParseSection_TEXTURES(string line);
	void _ParseSection_SPRITES(string line);
	void _ParseSection_ANIMATIONS(string line);
	void _ParseSection_ANIMATION_SETS(string line);

	LPANIMATION_SET ani_set;
public:
	COpeningScene(int id, LPCWSTR filePath);
	virtual void Load();
	virtual void Update(DWORD dt);
	virtual void Render();
	virtual void Unload();

};

class COpeningScenceKeyHandler : public CScenceKeyHandler
{
public:
	virtual void KeyState(BYTE *states);
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode) {};
	COpeningScenceKeyHandler(CScene *s) :CScenceKeyHandler(s) {};
};

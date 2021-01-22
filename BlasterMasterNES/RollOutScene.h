#pragma once
#include "Game.h"
#include "Textures.h"
#include "Scence.h"
#include "GameObject.h"
#include "Brick.h"
#include "Hero.h"
#include "Map.h"

#define AniSetRollOut	1

#define RO_TimeLine_1	2500
#define RO_TimeLine_2	4000

class CRollOutScene : public CScene
{



protected:

	int timeLine = 0;


	void _ParseSection_TEXTURES(string line);
	void _ParseSection_SPRITES(string line);
	void _ParseSection_ANIMATIONS(string line);
	void _ParseSection_ANIMATION_SETS(string line);

	LPANIMATION_SET ani_set;
public:
	CRollOutScene(int id, LPCWSTR filePath);
	virtual void Load();
	virtual void Update(DWORD dt);
	virtual void Render();
	virtual void Unload();

};

class CRollOutScenceKeyHandler : public CScenceKeyHandler
{
public:
	virtual void KeyState(BYTE *states);
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode) {};
	CRollOutScenceKeyHandler(CScene *s) :CScenceKeyHandler(s) {};
};

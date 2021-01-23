#pragma once
#include "Game.h"
#include "Textures.h"
#include "Scence.h"
#include "GameObject.h"
#include "Brick.h"
#include "Hero.h"
#include "Map.h"
#include "AreaOnMap.h"


//-------------------------------------
#include "Firework.h"






#define InDexArea_Start 101

#define TimeHienThiSoMangTrongGame 2000
#define SoMangMacDinh	2
#define TimeRenderLeft	4000
class CPlayScene : public CScene
{
protected:
	
	//dt
	int dt;

	//Nhân vật
	CHero *player;	

	//Map dùng để hiển thị lên hệ thống
	Map *map;

	//Khu vực chơi
	unordered_map<int, CAreaOnMap*> listAreaOnMap;
	int indexAreaOnMap = InDexArea_Start;

	//Danh sách đối tượng
	vector<LPGAMEOBJECT> *objects= new vector<LPGAMEOBJECT>();
	vector<LPGAMEOBJECT> *curObjects=new vector<LPGAMEOBJECT>();

	//Camera
	float cx = 0, cy = 0;
	float last_cx = 0, last_cy = 0;

	//Trạng thái dừng game
	bool isStopGame = false;

	//Số mạng của nhân vật
	int soMangTrongGame = SoMangMacDinh;
	int timeHienThiSoMangTrongGame = TimeHienThiSoMangTrongGame;
	int timeRenderLeft = TimeRenderLeft;


	//Select item
	int selectItem = 1;
	bool isChoseItem = false;
	int iItem_1 = 9;
	int iItem_2 = 99;
	int iItem_3 = 99;

	//Hàm đọc dữ liệu
	void _ParseSection_TEXTURES(string line);
	void _ParseSection_SPRITES(string line);
	void _ParseSection_ANIMATIONS(string line);
	void _ParseSection_ANIMATION_SETS(string line);
	void _ParseSection_OBJECTS(string line);
	void _ParseSeciton_MAP(string line);
	void _ParseSeciton_AreaOnMap(string line);
	

	int  nextScene = -100;

	//--------------------------------------------
	vector <Firework*> fireworks;

	bool heroChet = false;

public:
	CPlayScene(int id, LPCWSTR filePath);
	virtual void Load();
	virtual void Update(DWORD dt);
	virtual void Render();
	virtual void Unload();
	virtual void ReLoad();
	CHero * GetPlayer() { return player; }
	void SetIdArea(int idArea) {
		this->indexAreaOnMap = idArea;
	}
	float GetMapHeight() { return map->GetMapHeight(); }
	float GetMapWidth() { return map->GetMapWidth(); }
	void SetCam(float cx, float cy) { this->cx=cx; this->cy = cy; }
	void GetCam(float &cx, float& cy);
	void StopOrResumeGame() { isStopGame = !isStopGame; }
	bool GetIsStopGame() { return isStopGame; }
	void RederStopGame();
	void RenderLeft(); // mang trong game

	void RenderSelectMenu();
	void SelectItemLeft();
	void SelectItemRight();
	bool GetIsChoseItem() { return isChoseItem; }
	void SetIsChoseItem(bool b) { this->isChoseItem = b; }
	int GetSelectItem(){ return selectItem; }



	void SetNextScene(int k) { nextScene = k; }

	/*void Set_iItem1(int n) { iItem_1 = n; }
	void Set_iItem2(int n) { iItem_2 = n; }
	void Set_iItem3(int n) { iItem_3 = n; }
	int Get_iItem1() { return iItem_1; }
	int Get_iItem2() { return iItem_2; }
	int Get_iItem3() { return iItem_3; }*/




	void AddFirework(Firework* firework) { fireworks.push_back(firework); };
	void ClearFireworks() { fireworks.clear(); };
	void SetHeroChet(bool b) { this->heroChet = b; }
	
};

class CPlayScenceKeyHandler : public CScenceKeyHandler
{
public:
	virtual void KeyState(BYTE *states);
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode) {};
	CPlayScenceKeyHandler(CScene *s) :CScenceKeyHandler(s) {};
};

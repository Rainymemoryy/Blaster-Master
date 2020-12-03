#pragma once
#include	"GameObject.h"
#include	<algorithm>
#include	<assert.h>
#include	"Utils.h"
#include	"Car.h"
#include	"Game.h"
#include	"Brick.h"
#include	"Goomba.h"
#include	"Portal.h"
#include	"Bullet.h"
#include	"Enemy1.h"

#define AddEnemy	1010014
#define Bullet3		1010015



#define	LEVEL_SLDF		211
#define	LEVEL_SLOC		212

#define HERO_UNTOUCHABLE_TIME	2000

#define STATE_NHAYKHOIXE		1201
#define STATE_VAOXE				1202

#define ANI_HP					16
#define Hero_Sldf_AniSet			101
#define Hero_Sloc_AniSet			102


#pragma region SLDF
#define SLDF_VX		0.08f
#define SLDF_VY		0.2f
#define SLDF_AY		0.0005f
#define SLDF_MAXHP	80.f

#define STATE_SLDF_DUNGYEN			1101
#define STATE_SLDF_DIBENPHAI		1102
#define STATE_SLDF_DIBENTRAI		1103
#define STATE_SLDF_NHAY				1104
#define STATE_SLDF_CHET				1105
#define STATE_SLDF_BOBENTRAI		1106
#define STATE_SLDF_BOBENPHAI		1107
#define STATE_SLDF_NAMXUONG			1108
#define STATE_SLDF_BANDANDON		1109
#define STATE_SLDF_BANDANCHUM		1110
#define STATE_SLDF_LEOLENCAUTHANG	1111
#define STATE_SLDF_LEOXUONGCAUTHANG	1112
#define STATE_SLDF_DUNGTRENCAUTHANG	1113

#define ANI_SLDF_NHINTRAI				0
#define ANI_SLDF_NHINPHAI				1
#define ANI_SLDF_DIBENTRAI				2
#define ANI_SLDF_DIBENPHAI				3
#define ANI_SLDF_BOBENTRAI				4
#define ANI_SLDF_BOBENPHAI				5
#define ANI_SLDF_NAMBENTRAI				6
#define ANI_SLDF_NAMBENPHAI				7
#define ANI_SLDF_CHETBENTRAI			8
#define Ani_Sldf_ChetBenPhai			9
#define Ani_Sldf_LeoCauThang			16
//10 11 12 13 14 15 da duoc xai

#define BOX_SLDF_WIDTH_DI				10
#define BOX_SLDF_HEIGHT_DI				17

#define BOX_SLDF_WIDTH_DUNG				10
#define BOX_SLDF_HEIGHT_DUNG			17

#define BOX_SLDF_WIDTH_NAMXUONG			16
#define BOX_SLDF_HEIGHT_NAMXUONG		10

#define BOX_SLDF_WIDTH_CHET				16
#define BOX_SLDF_HEIGHT_CHET			16

#define BOX_DFMAP_WIDTH_LEOTHANG		12
#define BOX_DFMAP_HEIGHT_LEOTHANG		16
#pragma endregion

#pragma region  SLOC
#define SLOC_AY		0.0005f
#define SLOC_VX		0.1f
#define SLOC_VY		0.215f
#define SLOC_MAXHP	160.f

#define STATE_SLOC_CHAYBENTRAI	1121
#define STATE_SLOC_CHAYBENPHAI	1122
#define STATE_SLOC_NHAY			1123
#define STATE_SLOC_NANGSUNG		1124
#define STATE_SLOC_DUNGYEN		1125
#define STATE_SLOC_BANDANDON	1126
#define STATE_SLOC_CHET			1127
#define STATE_SLOC_KEYUP		1130
#define	STATE_SLOC_HIGHTJUMP	1131

#define ANI_SLOC_NOXE			15
#define BOX_SLOC_WIDTH_NOXE		45
#define BOX_SLOC_HEIGHT_NOXE	40

#pragma endregion

struct SLOC
{
	int height, width; //Kích thước của sprite
	int indexAni; // Animation nào?
};

typedef SLOC*LSLOC;

class CHero : public CGameObject
{
public:
	int untouchable=0;
	int untouchable_nhapnhay =  100;


	float start_x;		
	float start_y;

	float delta_x, delta_y;

	int typeMap;
	int enviroment;


	int currentWidth = BOX_SLDF_WIDTH_DUNG;
	int currentHeight = BOX_SLDF_HEIGHT_DUNG;
	int lastWidth = BOX_SLDF_WIDTH_DUNG;
	int lastHeight = BOX_SLDF_HEIGHT_DUNG;

	vector<LPGAMEOBJECT> *listObj;
	vector<LPGAMEOBJECT> *coObjects;
	

	CGameObject *car = NULL;

	int level = LEVEL_SLOC;
	bool oTrongXe = true;
	bool isDeath = false;

	float sldf_hp = SLDF_MAXHP;
	bool sldf_coTheNhay = false;
	bool sldf_namXuong = false;
	bool sldf_coTheNamXuong = false;
	bool sldf_coTheVaoXe = false;
	bool sldf_oGanCauThang = false;
	bool sldf_oTrenCauThang = false;
	bool sldf_leoCauThang = false;

	CGameObject *cauThang = NULL;


	vector<LSLOC> sloc_ani_box;
	bool sloc_coTheNhay = false;
	float sloc_hp = SLOC_MAXHP;
	int sloc_ix = 0;
	int sloc_iy = 0;

	bool dangNhay = false;

	float lastX, lastY;

public:
	CHero(float x = 0.0f, float y = 0.0f);

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects = NULL, vector<LPGAMEOBJECT> *listObj = NULL);
	virtual void Render();
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void LastUpdate();



	void SetState(int state);
	void SetLevel(int l) { level = l; }
	
	void Reset();

	int GetCurrentHeight() { return currentHeight; }
	int GetCurrentWidth() { return currentWidth; }

	void RenderHP();
	void UpdateHP();
};
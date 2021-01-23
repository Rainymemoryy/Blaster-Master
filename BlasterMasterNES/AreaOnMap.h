#pragma once
#include <iostream>
#include <fstream>
#include "Utils.h"

#include "Portal.h"
#include "GameObject.h"


#include "Brick.h"
#include "Brick1.h"
#include "Brick2.h"
#include "Stair.h"
#include "Block1.h"
#include "Brick21.h"
#include "OvhAlert.h"


#include "Enemy1.h"
#include "Enemy2.h"
#include "Enemy3.h"
#include "Enemy4.h"
#include "Enemy5.h"
#include "Enemy6.h"
#include "Enemy7.h"
#include "Enemy8.h"
#include "Enemy9.h"
#include "Enemy10.h"
#include "Enemy21.h"
#include "Enemy22.h"
#include "Enemy23.h"

#include "Boss.h"
#include "BossArm.h"

#include "Item.h"
#include "ItemHp.h"
#include "ItemH.h"
#include "Item1.h"
#include "Item2.h"
#include "Item3.h"
#include "ItemBonus.h"






#define AreaOnMap_UnKnown	0
#define AreaOnMap_LoadInfo	1
#define AreaOnMap_LoadObj	2


#define AreaOnMap_Type_BrickDf	0
#define AreaOnMap_Type_Brick1	1
#define AreaOnMap_Type_Brick2	2
#define AreaOnMap_Type_Stair	3
#define AreaOnMap_Type_Block1	4

#define OvhMap_Type_Alert		21
#define AreaOnMap_Type_Brick21	22

#define AreaOnMap_Type_Portal	20

#define AreaOnMap_Type_Enemy1	101
#define AreaOnMap_Type_Enemy2	102
#define AreaOnMap_Type_Enemy3	103
#define AreaOnMap_Type_Enemy4	104
#define AreaOnMap_Type_Enemy5	105
#define AreaOnMap_Type_Enemy6	106
#define AreaOnMap_Type_Enemy7	107
#define AreaOnMap_Type_Enemy8	108
#define AreaOnMap_Type_Enemy9	109
#define AreaOnMap_Type_Enemy10	110
#define AreaOnMap_Type_Enemy21	301
#define AreaOnMap_Type_Enemy22	302
#define AreaOnMap_Type_Enemy23	303
#define AreaOnMap_Type_BOSS	16



#define AreaOnMap_Type_ItemHP	201
#define AreaOnMap_Type_Item1	203
#define AreaOnMap_Type_Item2	204
#define AreaOnMap_Type_Item3	205
#define AreaOnMap_Type_ItemH	206
#define AreaOnMap_Type_ItemBonus	207



//typedef CAreaOnMap * LPAreaOnMap;

class CAreaOnMap
{
protected:
	int id;
	float map_t, map_l, map_r, map_b;
	bool isReload = false;
	LPCWSTR sceneFilePath;

	vector<LPGAMEOBJECT> *listObj;

public:
	CAreaOnMap(int id,LPCWSTR sceneFilePath)
	{
		this->id = id;
		this->sceneFilePath = sceneFilePath;
	}

	void GetAreaOnMap_Load() {
		listObj = new vector<LPGAMEOBJECT>();
		ifstream f;
		f.open(sceneFilePath);
		int section = AreaOnMap_UnKnown;
		char str[1024];

		while (f.getline(str, 1024))
		{
			string line(str);

			if (line[0] == '#') continue;
			if (line == "[INFO]") { section = AreaOnMap_LoadInfo; continue; }
			if (line == "[OBJECTS]") { section = AreaOnMap_LoadObj; continue; }
			if (line[0] == '[') { section = AreaOnMap_UnKnown; continue; }

			switch (section)
			{
			case AreaOnMap_LoadInfo: _ParseSection_Info(line); break;
			case AreaOnMap_LoadObj: _ParseSection_Objects(line); break;
			}
		}

		f.close();

		DebugOut(L"id: %d\t\tfile: %s\t\t\size :%d\n",id ,sceneFilePath, listObj->size());
	}

	void _ParseSection_Info(string line) {
		vector<string> tokens = split(line);
		map_l = atof(tokens[0].c_str());
		map_t = atof(tokens[1].c_str());
		map_r = atof(tokens[2].c_str());
		map_b = atof(tokens[3].c_str());
	}
	void _ParseSection_Objects(string line) {

		vector<string> tokens = split(line);
		if (tokens.size() < 3) return;

		int object_type = atoi(tokens[0].c_str());

		CGameObject *obj = NULL;
		switch (object_type)
		{
		case AreaOnMap_Type_BrickDf:
			obj = new CBrick(atof(tokens[1].c_str()) * 16, atof(tokens[2].c_str()) * 16, atof(tokens[3].c_str()) * 16, atof(tokens[4].c_str()) * 16);
			listObj->push_back(obj);
			break;
		case AreaOnMap_Type_Brick1:
			obj = new CBrick1(atof(tokens[1].c_str()) * 16, atof(tokens[2].c_str()) * 16, atof(tokens[3].c_str()) * 16, atof(tokens[4].c_str()) * 16);
			listObj->push_back(obj);
			break;
		case AreaOnMap_Type_Brick2:
			obj = new CBrick2(atof(tokens[1].c_str()) * 16, atof(tokens[2].c_str()) * 16, atof(tokens[3].c_str()) * 16, atof(tokens[4].c_str()) * 16);
			listObj->push_back(obj);
			break;
		case AreaOnMap_Type_Brick21:
			obj = new CBrick21(atof(tokens[1].c_str()) * 16, atof(tokens[2].c_str()) * 16, atof(tokens[3].c_str()) * 16, atof(tokens[4].c_str()) * 16);
			listObj->push_back(obj);
			break;
		case AreaOnMap_Type_Stair:
			obj = new CStair(atof(tokens[1].c_str()) * 16, atof(tokens[2].c_str()) * 16, atof(tokens[3].c_str()) * 16, atof(tokens[4].c_str()) * 16);
			listObj->push_back(obj);
			break;
		case OvhMap_Type_Alert:
			obj = new COvhAlert(atof(tokens[1].c_str()) * 16, atof(tokens[2].c_str()) * 16, atof(tokens[3].c_str()) * 16, atof(tokens[4].c_str()) * 16);
			listObj->push_back(obj);
			break;
		case AreaOnMap_Type_Block1:
			obj = new CBlock1(atof(tokens[1].c_str()) * 16, atof(tokens[2].c_str()) * 16);
			listObj->push_back(obj);
			break;
		case AreaOnMap_Type_ItemHP:
			obj = new CItemHp(atof(tokens[1].c_str()) * 16, atof(tokens[2].c_str()) * 16);
			listObj->push_back(obj);
			break;
		case AreaOnMap_Type_ItemH:
			obj = new CItemH(atof(tokens[1].c_str()) * 16, atof(tokens[2].c_str()) * 16);
			listObj->push_back(obj);
			break;
		case AreaOnMap_Type_Item1:
			obj = new CItem1(atof(tokens[1].c_str()) * 16, atof(tokens[2].c_str()) * 16);
			listObj->push_back(obj);
			break;
		case AreaOnMap_Type_Item2:
			obj = new CItem2(atof(tokens[1].c_str()) * 16, atof(tokens[2].c_str()) * 16);
			listObj->push_back(obj);
			break;
		case AreaOnMap_Type_Item3:
			obj = new CItem3(atof(tokens[1].c_str()) * 16, atof(tokens[2].c_str()) * 16);
			listObj->push_back(obj);
			break;
		case AreaOnMap_Type_ItemBonus:
			obj = new CItemBonus(atof(tokens[1].c_str()) * 16, atof(tokens[2].c_str()) * 16);
			listObj->push_back(obj);
			break;

		case AreaOnMap_Type_Enemy1:
			obj = new CEnemy1(atof(tokens[1].c_str()) * 16, atof(tokens[2].c_str()) * 16);
			listObj->push_back(obj);
			break;
		case AreaOnMap_Type_Enemy2:
			obj = new CEnemy2(atof(tokens[1].c_str()) * 16, atof(tokens[2].c_str()) * 16);
			listObj->push_back(obj);
			break;
		case AreaOnMap_Type_Enemy3:
			obj = new CEnemy3(atof(tokens[1].c_str()) * 16, atof(tokens[2].c_str()) * 16, atoi(tokens[3].c_str()), atoi(tokens[4].c_str()), atoi(tokens[5].c_str()), atoi(tokens[6].c_str()));
			listObj->push_back(obj);
			break;
		case AreaOnMap_Type_Enemy4:
			obj = new CEnemy4(atof(tokens[1].c_str()) * 16, atof(tokens[2].c_str()) * 16);
			listObj->push_back(obj);
			break;
		case AreaOnMap_Type_Enemy5:
			obj = new CEnemy5(atof(tokens[1].c_str()) * 16, atof(tokens[2].c_str()) * 16);
			listObj->push_back(obj);
			break;
		case AreaOnMap_Type_Enemy6:
			obj = new CEnemy6(atof(tokens[1].c_str()) * 16, atof(tokens[2].c_str()) * 16, atof(tokens[3].c_str()) * 16, atof(tokens[4].c_str()) * 16);
			listObj->push_back(obj);
			break;
		case AreaOnMap_Type_Enemy7:
			obj = new CEnemy7(atof(tokens[1].c_str()) * 16, atof(tokens[2].c_str()) * 16, atof(tokens[3].c_str()) * 16, atof(tokens[4].c_str()) * 16);
			listObj->push_back(obj);
			break;
		case AreaOnMap_Type_Enemy8:
			obj = new CEnemy8(atof(tokens[1].c_str()) * 16, atof(tokens[2].c_str()) * 16 + 6);
			listObj->push_back(obj);
			break;
		case AreaOnMap_Type_Enemy9:
			obj = new CEnemy9(atof(tokens[1].c_str()) * 16, atof(tokens[2].c_str()) * 16 + 6);
			listObj->push_back(obj);
			break;
		case AreaOnMap_Type_Enemy10:
			obj = new CEnemy10(atof(tokens[1].c_str()) * 16, atof(tokens[2].c_str()) * 16);
			listObj->push_back(obj);
			break;
	

		case AreaOnMap_Type_Enemy21:
			obj = new CEnemy21(atof(tokens[1].c_str()) * 16, atof(tokens[2].c_str()) * 16);
			listObj->push_back(obj);
			break;
		case AreaOnMap_Type_Enemy22:
			obj = new CEnemy22(atof(tokens[1].c_str()) * 16, atof(tokens[2].c_str()) * 16);
			listObj->push_back(obj);
			break;
		case AreaOnMap_Type_Enemy23:
			obj = new CEnemy23(atof(tokens[1].c_str()) * 16, atof(tokens[2].c_str()) * 16);
			listObj->push_back(obj);
			break;
		case AreaOnMap_Type_Portal:
			obj = new CPortal(atof(tokens[1].c_str()) * 16, atof(tokens[2].c_str()) * 16, atof(tokens[3].c_str()) * 16, atof(tokens[4].c_str()) * 16, atoi(tokens[5].c_str()), atof(tokens[6].c_str()) * 16, atof(tokens[7].c_str()) * 16);
			listObj->push_back(obj);
			break;


		case AreaOnMap_Type_BOSS:
		
			obj = new CBoss();
			dynamic_cast<CBoss*>(obj)->SetStartPosition(atof(tokens[1].c_str()) * 16, atof(tokens[2].c_str()) * 16);
			BossArm* left = new BossArm(dynamic_cast<CBoss*>(obj), TYPE_LEFT_CLAW);
			listObj->push_back(left);
			BossArm* right = new BossArm(dynamic_cast<CBoss*>(obj), TYPE_RIGHT_CLAW);
			listObj->push_back(right);
			listObj->push_back(obj);
			break;
					
		}
	}

	float GetAreaOnMap_Right() { return map_r*16; }
	float GetAreaOnMap_Bottom() { return map_b*16; }
	float GetAreaOnMap_X() { return map_l*16; }
	float GetAreaOnMap_Y() { return map_t*16; }


	vector<LPGAMEOBJECT> * GetAreaOnMap_ListObj() {
		return listObj;
	}
	void SetListObj(vector<LPGAMEOBJECT> * list) {
		listObj = list;
	}

	~CAreaOnMap() {
		for (int i = 0; i < listObj->size(); i++)
			delete listObj->at(i);
		listObj->clear();
	};


};


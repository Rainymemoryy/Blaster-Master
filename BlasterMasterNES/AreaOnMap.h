#pragma once
#include <iostream>
#include <fstream>
#include "Utils.h"

#include "GameObject.h"
#include "Brick.h"


#define AreaOnMap_UnKnown	0
#define AreaOnMap_LoadInfo	1
#define AreaOnMap_LoadObj	2


#define AreaOnMap_Type_Brick	0
#define AreaOnMap_Type_Enemy1	101
#define AreaOnMap_Type_Enemy2	102
#define AreaOnMap_Type_Enemy3	103
#define AreaOnMap_Type_Enemy4	104
#define AreaOnMap_Type_Enemy5	105
#define AreaOnMap_Type_Enemy6	106

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

		DebugOut(L"size :%d\n", listObj->size());
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
		case AreaOnMap_Type_Brick:
			obj = new CBrick(atof(tokens[1].c_str()) * 16, atof(tokens[2].c_str()) * 16, atof(tokens[3].c_str()) * 16, atof(tokens[4].c_str()) * 16);
			break;
		}
		listObj->push_back(obj);
	}

	float GetAreaOnMap_Height() { return map_b - map_t; }
	float GetAreaOnMap_Width() { return map_r - map_l; }
	float GetAreaOnMap_X() { return map_l; }
	float GetAreaOnMap_Y() { return map_t; }


	vector<LPGAMEOBJECT> * GetAreaOnMap_ListObj() {
		return listObj;
	}


	~CAreaOnMap() {
		for (int i = 0; i < listObj->size(); i++)
			delete listObj->at(i);
		listObj->clear();
	};


};


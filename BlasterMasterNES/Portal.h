#pragma once

#include "GameObject.h"

/*
	Object that triggers scene switching
*/
class CPortal : public CGameObject
{
	int scene_id;	// target scene to switch to
	float r, b;
	float sumX, sumY;

	int width;
	int height;
public:
	CPortal(float l, float t, float r, float b, int scene_id, float sumX, float sumY );
	virtual void Render();
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	int GetSceneId() { return scene_id; }
	float GetSumX() { return sumX; }
	float GetSumY() { return sumY; }
};
#include "Portal.h"



CPortal::CPortal(float l, float t, float r, float b, int scene_id, float sumX, float sumY)
{
	this->x = l;
	this->y = t;
	this->r = r;
	this->b = b;
	this->scene_id = scene_id;
	this->sumX = sumX;
	this->sumY = sumY;
}

void CPortal::Render()
{
	//RenderBoundingBox();
}

void CPortal::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = x;
	t = y;
	r = this->r;
	b = this->b;
}
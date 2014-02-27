#ifndef __MAPOBJ__H__
#define __MAPOBJ__H__

#include "Object.h"

#include <map>
#include <string>
using namespace std;

#include "HGEBase.h"
#include "hgeMap.h"
#include <hgesprite.h>
#include <hgefont.h>
#include <hgegui.h>

class CMapObj : public CObject  
{
public:
	bool RenderFunc();
	bool FrameFunc();
	CMapObj();
	virtual ~CMapObj();

private:
	hgeGUI *guiPlay;
	HTARGET MainTar;
	hgeSprite *MainSpr;
	hgeFont	  *font;

	hgeMap *map;

	//速度和摩擦力
	const int	speed;
	const float friction;
	float	slideX,slideY;
	//地图右上角在屏幕中的坐标
	float mapX,mapY;
	int	  mapCx, mapCy;

	int screenCx;
	int screenCy;
};

#endif __MAPOBJ__H__
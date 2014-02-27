// EditMap.h: interface for the CEditMap class.
//
//////////////////////////////////////////////////////////////////////

#ifndef _EDITMAP_H_
#define _EDITMAP_H_

#include "HGEBase.h"
#include "hgeMap.h"

class CEditMap : public CHGEBase  
{
public:
	bool ReRender();
	bool SaveMap();
	bool ReadMap();
	bool RenderFunc();
	bool FrameFunc();
	CEditMap();
	virtual ~CEditMap();

	hgeMap *map;

	//速度和摩擦力
	const int	speed;
	const float friction;
	float	slideX,slideY;
	//地图右上角在屏幕中的坐标
	float mapX,mapY;

	//地图的桌面
	HTARGET		tarMap;
	hgeSprite	*sprMap;
};

#endif

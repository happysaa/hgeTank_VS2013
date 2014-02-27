#ifndef __TANK_H__
#define __TANK_H__

#include "hgeMain.h"
#include "hgeMap.h"
#include "hgeanim.h"
#include "CRole.h"

class CTank : public CRole  
{
public:
	CTank();
	CTank(hgeMap *map);
	virtual ~CTank();

	bool FrameFunc();
	bool Render();

	bool CrashProc(float &dx, float &dy);
	bool KeyProc();


public:
	hgeMap	 *map;
	hgeSprite *spr;
	HTEXTURE  tex;

	hgeAnimation *aniWheels;
	HTEXTURE	  texWheels;

	bool	 IsMoveX, IsMoveY;
	float	 xPos, yPos;
	float	 xScreen, yScreen;
	float	 cxScreen, cyScreen;

	float	 dx,dy;
	float	 fMove;
	float	 dt;
	int		 speed;
	float	 friction;
	int		mapWidth, mapHeight;

	enum direct{stop, up,down,left,right};
	float  radian;
};

#endif // Tank.h

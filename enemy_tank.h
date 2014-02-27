#ifndef __ENEMY_TANK_H__
#define __ENEMY_TANK_H__ 

#include "CRole.h"
#include "hgeMap.h"
#include "hgeMain.h"
#include "Astar.h"
using namespace Astar;

class Cenemy_tank : public CRole  
{
public:
	static DWORD WINAPI PathProc(LPVOID lpParameter);
	bool FrameFunc();
	bool FrameFunc(float x, float y);
	bool Render();
	Cenemy_tank(hgeMap *map);

	virtual ~Cenemy_tank();

	CAstar<TILEINFO> *Astar;
	static Astar::PNODE	 nodePath;
	static HANDLE hMutex;
	hgeMap *map;

	HTEXTURE  tex;
	hgeSprite *spr;

	int mX;
	int mY;
};
#endif // enemy_tank.h



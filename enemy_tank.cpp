// enemy_tank.cpp: implementation of the Cenemy_tank class.
//
//////////////////////////////////////////////////////////////////////
#include "enemy_tank.h"
#include <windows.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Astar::PNODE Cenemy_tank::nodePath = NULL;
HANDLE Cenemy_tank::hMutex = NULL;


Cenemy_tank::Cenemy_tank(hgeMap *map):map(map)
,CRole(ROLEPICTUREVC() ,100, 200, 10, 1, 300, 300, 128, 128),mX(10),mY(10)
{
	tex = hge->Texture_Load("files\\tank11.png");
	spr = new hgeSprite(tex, 0, 0, 128, 128);
	Astar = new CAstar<TILEINFO>;
	HANDLE hThread = CreateThread(NULL, 0, PathProc, this, 0, 0);
}

Cenemy_tank::~Cenemy_tank()
{

}

bool Cenemy_tank::Render()
{
	spr->Render(m_fRoleX, m_fRoleY);
	return false;
}

bool Cenemy_tank::FrameFunc()
{
	return false;
}

bool Cenemy_tank::FrameFunc(float x, float y)
{
	mX = x;
	mY = y;
	if(nodePath != NULL)
	{
		float x = nodePath->pt.y*32-m_fRoleX;
		float y = nodePath->pt.x*32-m_fRoleY;
		if(x < 0) m_fRoleX -=0.5; else m_fRoleX += 0.5;
		if(y < 0) m_fRoleY -=0.5; else m_fRoleY += 0.5;
		if(abs(x) < 1 && abs(y) < 1)
		{
			if(nodePath != NULL)
			{
				nodePath = nodePath->preNode;
			}
		}
	}
	return false;
}

DWORD Cenemy_tank::PathProc(LPVOID lpParameter)
{
	using namespace Astar;
	using Astar::POINT;
	Cenemy_tank *lCenemyTank = (Cenemy_tank *)lpParameter;
	CAstar<TILEINFO> *Astar = lCenemyTank->Astar;

	while(1)
	{
		if(nodePath == NULL)
		{
			Astar->Release();
			Astar->SetPath(POINT(lCenemyTank->mY/32, lCenemyTank->mX/32), POINT(lCenemyTank->m_fRoleY/32, \
				lCenemyTank->m_fRoleX/32),lCenemyTank->map->mapTileInfo["1"], POINT(lCenemyTank->map->height,\
				lCenemyTank->map->width));

			Astar->GetPath();
			if(Astar->CloseList.empty())
			{
				nodePath = NULL;
			}
			else
			{
				nodePath = Astar->CloseList.back();
			}
		}
	}

	return 0;
}

// EditMap.cpp: implementation of the CEditMap class.
//
//////////////////////////////////////////////////////////////////////

#include "hgeMain.h"
#include "EditMap.h"
#include "hge.h"

extern HGE *hge;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CEditMap::CEditMap():speed(20),friction(0.98),mapX(0),mapY(0),slideX(0),slideY(0)
{
	//新建地图
	map = new hgeMap(hge->Resource_MakePath("tank.tmx"));

	//初始化地图窗口
	tarMap = hge->Target_Create(map->width*map->TileWidth, map->height*map->TileHeight, 0.5);
	HTEXTURE tex = hge->Target_GetTexture(tarMap);
	sprMap    = new hgeSprite(tex, 0, 0, screenCx, screenCy);
	sprMap->SetBlendMode(BLEND_COLORMUL | BLEND_ALPHAADD | BLEND_NOZWRITE);
	ReRender();
}

CEditMap::~CEditMap()
{

}

bool CEditMap::FrameFunc()
{
	float dt = hge->Timer_GetDelta();

//	if(hge->Input_GetKeyState(HGEK_ESCAPE))	SetFunc(hgeBase, hgeMenu);
	if(hge->Input_GetKeyState(HGEK_UP))		slideY += speed*dt;
	if(hge->Input_GetKeyState(HGEK_DOWN))	slideY -= speed*dt;
	if(hge->Input_GetKeyState(HGEK_LEFT))	slideX += speed*dt;
	if(hge->Input_GetKeyState(HGEK_RIGHT))	slideX -= speed*dt;

	//处理碰撞和摩擦力
	slideX *= friction; slideY *= friction;
 	if(mapX > 0 || mapX < screenCx-map->TileWidth*map->width)	slideX = -slideX;
 	if(mapY > 0 || mapY < screenCy-map->TileHeight*map->height) slideY = -slideY;
 	mapX += slideX; mapY += slideY;

	return false;
}

bool CEditMap::ReRender()
{
	hge->Gfx_BeginScene(tarMap);
	hge->Gfx_Clear(0);
	map->Render();
	hge->Gfx_EndScene();
	return true;
}

bool CEditMap::RenderFunc()
{
	hge->Gfx_BeginScene();
	hge->Gfx_Clear(0);
	sprMap->SetTextureRect(-mapX, -mapY, screenCx, screenCy, false);
	sprMap->Render(0, 0);
	hge->Gfx_EndScene();
	return false;
}

bool CEditMap::ReadMap()
{
	return true;
}

bool CEditMap::SaveMap()
{
	return true;
}

// BackgroundObj.cpp: implementation of the CMapObj class.
//
//////////////////////////////////////////////////////////////////////

#include "MapObj.h"
#include "hgeMain.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMapObj::CMapObj():speed(10),friction(0.98),mapX(0),mapY(0),slideX(0),slideY(0)
{
	//»ñÈ¡ÆÁÄ»¿í¸ß
	screenCx = hge->System_GetState(HGE_SCREENWIDTH);
	screenCy = hge->System_GetState(HGE_SCREENHEIGHT);

	guiPlay = new hgeGUI();
	guiPlay->SetCursor(new hgeSprite(hge->Texture_Load("files\\cursor.png"), 0, 0, 32, 32));

	font = new hgeFont("files\\font1.fnt");
	map = new hgeMap(hge->Resource_MakePath("tank.tmx"));
	mapCx = map->width*map->TileWidth;
	mapCy = map->height*map->TileHeight;
	//
	MainTar = hge->Target_Create(mapCx, mapCy, false);
	MainSpr = new hgeSprite(hge->Target_GetTexture(MainTar), 0, 0, screenCx, screenCy);
}

CMapObj::~CMapObj()
{

}

bool CMapObj::FrameFunc()
{
	float dt = hge->Timer_GetDelta();
	guiPlay->Update(dt);

	return false;
}

bool CMapObj::RenderFunc()
{
	hge->Gfx_BeginScene(0);
	MainSpr->SetTextureRect(mapX, mapY, screenCx, screenCy, false);
	MainSpr->Render(0, 0);

	map->RenderLayer("2", mapX, mapY, hge->System_GetState(HGE_SCREENWIDTH)/map->TileWidth,\
		hge->System_GetState(HGE_SCREENHEIGHT)/map->TileHeight);
	guiPlay->Render();
	hge->Gfx_EndScene();

	hge->Gfx_BeginScene(MainTar);
	map->RenderLayer("0");
	map->RenderLayer("1");
	hge->Gfx_EndScene();
	return false;
}

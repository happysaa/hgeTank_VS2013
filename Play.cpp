#include "Play.h"
#include "Tank.h"
#include "hgeMain.h"
#include "enemy_tank.h"

CPlay::CPlay():speed(10),friction(0.98),mapX(0),mapY(0),slideX(0),slideY(0)
{
	guiPlay = new hgeGUI();
	guiPlay->SetCursor(new hgeSprite(hge->Texture_Load("files\\cursor.png"), 0, 0, 32, 32));

	font = new hgeFont("files\\font1.fnt");
	map = new hgeMap(hge->Resource_MakePath("tank.tmx"));
	mapCx = map->width*map->TileWidth;
	mapCy = map->height*map->TileHeight;
	//
	MainTar = hge->Target_Create(mapCx, mapCy, false);
	MainSpr = new hgeSprite(hge->Target_GetTexture(MainTar), 0, 0, screenCx, screenCy);
	ReRend();
	//初始化自己的坦克
	MyTank = new CTank(map);
	eTank  = new Cenemy_tank(map);
}

CPlay::~CPlay()
{

}

bool CPlay::FrameFunc()
{
	float dt = hge->Timer_GetDelta();
	guiPlay->Update(dt);
	//if(hge->Input_GetKeyState(HGEK_ESCAPE))	SetFunc(hgeBase, hgeMenu);
	MyTank->FrameFunc();
	if(!MyTank->IsMoveX)
	{
		mapX += MyTank->dx;
	}
	if(!MyTank->IsMoveY)
	{
		mapY += MyTank->dy;
	}

	eTank->FrameFunc(MyTank->xPos, MyTank->yPos);
	return false;
}

bool CPlay::RenderFunc()
{
	hge->Gfx_BeginScene(0);
	MainSpr->SetTextureRect(mapX, mapY, screenCx, screenCy, false);
	MainSpr->Render(0, 0);


	map->RenderLayer("2", mapX, mapY, hge->System_GetState(HGE_SCREENWIDTH)/map->TileWidth,\
		hge->System_GetState(HGE_SCREENHEIGHT)/map->TileHeight);
	guiPlay->Render();
	
	hge->Gfx_EndScene();
	return false;
}

bool CPlay::ReRend()
{
	hge->Gfx_BeginScene(MainTar);
	map->RenderLayer("0");
	map->RenderLayer("1");
	hge->Gfx_EndScene();
	return true;
}

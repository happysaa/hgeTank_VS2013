#include "hgeMain.h"
#include "Scene.h"
#include "MenuScene.h"

CScene *hgeScene;

CHGEBase	 *hgeBase = 0;
CEditMap	 *hgeEditMap = 0;
CPlay		 *hgePlay = 0;
HGE *hge=0;

bool FrameFunc()
{
	return hgeScene ? hgeScene->FrameFunc() : true;
}

bool RenderFunc()
{
	return hgeScene ? hgeScene->RenderFunc() : true;
}

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	hge = hgeCreate(HGE_VERSION);

	//�����趨
	hge->System_SetState(HGE_LOGFILE, "hge_tank.log");
	hge->System_SetState(HGE_FRAMEFUNC, FrameFunc);
	hge->System_SetState(HGE_RENDERFUNC, RenderFunc);
	hge->System_SetState(HGE_TITLE, "HGE TANK");
	hge->System_SetState(HGE_WINDOWED, true);
	hge->System_SetState(HGE_SCREENWIDTH, 1366);
	hge->System_SetState(HGE_SCREENHEIGHT, 768);
	hge->System_SetState(HGE_SCREENBPP, 32);
	hge->System_SetState(HGE_USESOUND, true);

	//��ʼ��ϵͳ
	if(hge->System_Initiate())
	{
		//��ʼ����Ҫ��Դ
//		hgeEditMap  = new CEditMap();
		hgePlay		= new CPlay();
		//hgeBase		= hgeMenu;
		hgeScene = new CMenuScene();
		//��ʼ��Ϸ
		hge->System_Start();
	}
	else
	{
		MessageBox(NULL, hge->System_GetErrorMessage(), "Error", MB_OK);
	}
	
	//�ͷ���Դ
	hge->System_Shutdown();
	hge->Release();
	return 0;
}
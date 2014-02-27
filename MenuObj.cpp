// MenuObj.cpp: implementation of the CMenuObj class.
//
//////////////////////////////////////////////////////////////////////

#include "MenuObj.h"
#include "hgeMain.h"
#include <math.h>
#include "menuitem.h"
#include "PlayScene.h"


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMenuObj::CMenuObj()
{
	//初始化背景
	texBg = hge->Texture_Load("files\\bg.png");
	quadBg.tex = texBg;
	wBg = hge->Texture_GetWidth(texBg, true);
	hBg = hge->Texture_GetWidth(texBg, true);

	quadBg.blend = BLEND_ALPHABLEND | BLEND_COLORMUL | BLEND_NOZWRITE;
	for(int i=0;i<4;i++)
	{
		quadBg.v[i].z=0.5f;
		quadBg.v[i].col=0xFFFFFFFF;
	}
	quadBg.v[0].x=0;		quadBg.v[0].y=0; 
	quadBg.v[1].x=screenCx;	quadBg.v[1].y=0; 
	quadBg.v[2].x=screenCx;	quadBg.v[2].y=screenCy; 
	quadBg.v[3].x=0;		quadBg.v[3].y=screenCy;

	quadBg.v[0].tx = 0;				quadBg.v[0].ty = 0;
	quadBg.v[1].tx = screenCx/wBg;  quadBg.v[1].ty = 0;
	quadBg.v[2].tx = screenCx/wBg;  quadBg.v[2].ty = screenCy/hBg;
	quadBg.v[3].tx = 0;				quadBg.v[3].ty = screenCy/hBg;

	//加载菜单
	texCursor  = hge->Texture_Load("files\\cursor.png");
	fnt=new hgeFont("files\\font1.fnt");
	spr=new hgeSprite(texCursor,0,0,32,32);
	
	gui=new hgeGUI();
	gui->AddCtrl(new hgeGUIMenuItem(1,fnt,0,screenCx/2,screenCy/2-80,0.0f, "Play"));
	gui->AddCtrl(new hgeGUIMenuItem(2,fnt,0,screenCx/2,screenCy/2-40,0.1f, "Options"));
	gui->AddCtrl(new hgeGUIMenuItem(3,fnt,0,screenCx/2,screenCy/2,   0.2f, "EditMap"));
	gui->AddCtrl(new hgeGUIMenuItem(4,fnt,0,screenCx/2,screenCy/2+40,0.3f, "Exit"));
	
	gui->SetNavMode(HGEGUI_UPDOWN | HGEGUI_CYCLED);
	gui->SetCursor(spr);
	gui->SetFocus(1);
	gui->Enter();
}

CMenuObj::~CMenuObj()
{
	delete gui;
	delete fnt;
	delete spr;
}


bool CMenuObj::FrameFunc()
{
	float dt = hge->Timer_GetDelta();
	static float t=0.0f;
	float tx,ty;
	int id;
	static int lastid=0;

	id=gui->Update(dt);
	if(id == -1)
	{
		gui->SetFocus(1);
		gui->Enter();
		switch(lastid)
		{
			case 1:
				SetScene(new CPlayScene());
				SetFunc(hgeBase, hgePlay);
				break;
			case 2:
				break;
			case 3:
				SetFunc(hgeBase, hgeEditMap);
				break;
			case 4: return true;
		}
	}
	else if(id) { lastid=id; gui->Leave(); }
	// Here we update our background animation
	t+=dt;
	tx=50*cosf(t/60);
	ty=50*sinf(t/60);
	quadBg.v[0].tx=tx;			    quadBg.v[0].ty=ty;
	quadBg.v[1].tx=tx+screenCx/wBg;	quadBg.v[1].ty=ty;
	quadBg.v[2].tx=tx+screenCx/wBg; quadBg.v[2].ty=ty+screenCy/hBg;
	quadBg.v[3].tx=tx;				quadBg.v[3].ty=ty+screenCy/hBg;

	return false;
}


bool CMenuObj::RenderFunc()
{
	hge->Gfx_BeginScene();
	hge->Gfx_RenderQuad(&quadBg);
	gui->Render();
	fnt->SetColor(0xFFFFFFFF);
	fnt->printf(5, 5, HGETEXT_LEFT, "dt:%.3f\nFPS:%d", hge->Timer_GetDelta(), hge->Timer_GetFPS());
	hge->Gfx_EndScene();
	return false;
}

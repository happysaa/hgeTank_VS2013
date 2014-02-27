#include "Tank.h"
#include <math.h>

CTank::CTank(){}

CTank::CTank(hgeMap *map):map(map),
xPos(300.0), yPos(400.0), speed(40), tex(0), friction(0.90), dx(0), dy(0), radian(0.0)
{
	mapWidth	= map->width*map->TileWidth;
	mapHeight	= map->height*map->TileHeight;
	xScreen		= xPos;
	yScreen		= yPos;
	tex = hge->Texture_Load("files\\tank.png");
	spr = new hgeSprite(tex, 0, 0, 128, 128);
	spr->SetHotSpot(64,64);
	cxScreen = hge->System_GetState(HGE_SCREENWIDTH);
	cyScreen = hge->System_GetState(HGE_SCREENHEIGHT);

	texWheels = hge->Texture_Load("files\\wheel.png");
	aniWheels = new hgeAnimation(texWheels, 2, 10, 0, 0, 128,128);
	aniWheels->SetHotSpot(64,64);
}

CTank::~CTank()
{

}

bool CTank::Render()
{
	aniWheels->RenderEx(xScreen, yScreen, radian);
	spr->RenderEx(xScreen, yScreen, radian);
	return true;
}

bool CTank::FrameFunc()
{
	//按键处理
	KeyProc();

	//轮胎是否运动
	aniWheels->Update(dt);
	if(fMove < 1.0e-5 && aniWheels->IsPlaying())
	{
		aniWheels->Stop();
	}
	else if(fMove > 1.0e-5 && !aniWheels->IsPlaying())
	{
		aniWheels->Play();
	}
	//检测碰撞
	dx *= friction; dy *= friction; fMove *= friction;
	CrashProc(dx, dy);
	if(xPos + dx > 64 && xPos + dx < mapWidth - 64) 
	{
		//靠近边缘则拓展视野
		if(xScreen+dx > 128+64 && xScreen+dx < cxScreen-128-64)
		{
			xScreen += dx;
			IsMoveX = true;
		}
		else if(xPos < 128+64 || xPos > mapWidth - 128-64)
		{
			xScreen += dx;
			IsMoveX = true;
		}
		//到了屏幕末尾
		xPos += dx;
	}
	else
	{
		IsMoveX = true;
	}
	if(yPos + dy > 64 && yPos + dy < mapHeight - 64)
	{
		if(yScreen+dy > 128+64 && yScreen+dy < cyScreen-128-64)
		{
			yScreen += dy;
			IsMoveY = true;
		}
		else if(yPos < 128+64 || yPos > mapHeight - 128-64)
		{
			yScreen += dy;
			IsMoveY = true;
		}
		yPos += dy;
	}
	else
	{
		IsMoveY = true;
	}
	return true;
}

bool CTank::CrashProc(float &dx, float &dy)
{
	IsMoveX = false;
	IsMoveY = false;
	int x,y,i,sum;

	x = (yPos+dy)/map->TileHeight;
	y = (xPos)/map->TileWidth;
	if(x-2 >= 0)
	{
		sum = (*map->mapTileInfo["1"])[x-2][y-1] + (*map->mapTileInfo["1"])[x-2][y] + (*map->mapTileInfo["1"])[x-2][y+1];
		if(sum && dy < 0)
		{
			dy = 0;
		}
	}
	if(x+2 < map->height)
	{
		sum = (*map->mapTileInfo["1"])[x+2][y-1] + (*map->mapTileInfo["1"])[x+2][y] + (*map->mapTileInfo["1"])[x+2][y+1];
		if(sum && dy > 0)
		{
			dy = 0;
		}
	}


	x = (yPos)/map->TileHeight;
	y = (xPos + dx)/map->TileWidth;
	if(y-2 > 0)
	{
		sum = (*map->mapTileInfo["1"])[x-1][y-2] + (*map->mapTileInfo["1"])[x][y-2] + (*map->mapTileInfo["1"])[x+1][y-2];
		if(sum && dx < 0)
		{
			dx = 0;
		}
	}
	if(y+2 < map->width)
	{
		sum = (*map->mapTileInfo["1"])[x-1][y+2] + (*map->mapTileInfo["1"])[x][y+2] + (*map->mapTileInfo["1"])[x+1][y+2];
		if(sum && dx > 0)
		{
			dx = 0;
		}
	}
	
	return true;
}

bool CTank::KeyProc()
{
	dt = hge->Timer_GetDelta();
	if(hge->Input_GetKeyState(HGEK_UP))
	{
		dy -= speed*dt, fMove = speed*dt/10;
		radian += (M_PI-radian)/100;
	}
	if(hge->Input_GetKeyState(HGEK_DOWN))
	{
		dy += speed*dt, fMove = speed*dt/10;
		if(radian < M_PI)
		{
			radian += (0.0-radian)/100;
		}
		else
		{
			radian += (M_PI*2-radian)/100;
		}

	}
	if(hge->Input_GetKeyState(HGEK_LEFT))
	{
		dx -= speed*dt, fMove = speed*dt/10;
		if(radian < M_PI_2*3)
		{
			radian += (M_PI_2-radian)/100;
		}
		else
		{
			radian += (M_PI_2*5-radian)/100;
			if(radian > M_PI*2)
			{
				radian -= M_PI*2;
			}
		}
	}
	if(hge->Input_GetKeyState(HGEK_RIGHT))
	{
		dx += speed*dt, fMove = speed*dt/10;
		if(radian > M_PI_2)
		{
			radian += (M_PI_2*3-radian)/100;
		}
		else
		{
			radian += (-M_PI_2-radian)/100;
			if(radian < 0.0)
			{
				radian += M_PI*2;
			}
		}
	}
	return true;
}

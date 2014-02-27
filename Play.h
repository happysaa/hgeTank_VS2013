#ifndef __PLAY_H__
#define __PLAY_H__

#include <map>
#include <string>
using namespace std;

#include "HGEBase.h"
#include "hgeMap.h"
#include <hgesprite.h>
#include <hgefont.h>
#include <hgegui.h>

class Cenemy_tank;
class CTank;

class CPlay : public CHGEBase  
{
public:
	bool ReRend();
	bool RenderFunc();
	bool FrameFunc();
	CPlay();
	virtual ~CPlay();

	hgeGUI *guiPlay;
	HTARGET MainTar;
	hgeSprite *MainSpr;
	hgeFont	  *font;

	hgeMap *map;
	CTank *MyTank;
	Cenemy_tank *eTank;

	//�ٶȺ�Ħ����
	const int	speed;
	const float friction;
	float	slideX,slideY;
	//��ͼ���Ͻ�����Ļ�е�����
	float mapX,mapY;
	int	  mapCx, mapCy;
};

#endif // Play.h

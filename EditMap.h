// EditMap.h: interface for the CEditMap class.
//
//////////////////////////////////////////////////////////////////////

#ifndef _EDITMAP_H_
#define _EDITMAP_H_

#include "HGEBase.h"
#include "hgeMap.h"

class CEditMap : public CHGEBase  
{
public:
	bool ReRender();
	bool SaveMap();
	bool ReadMap();
	bool RenderFunc();
	bool FrameFunc();
	CEditMap();
	virtual ~CEditMap();

	hgeMap *map;

	//�ٶȺ�Ħ����
	const int	speed;
	const float friction;
	float	slideX,slideY;
	//��ͼ���Ͻ�����Ļ�е�����
	float mapX,mapY;

	//��ͼ������
	HTARGET		tarMap;
	hgeSprite	*sprMap;
};

#endif

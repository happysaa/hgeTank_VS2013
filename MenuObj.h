#ifndef __MENUOBJ__H__
#define __MENUOBJ__H__

#include "Object.h"
#include "HGEBase.h"
#include "hgegui.h"
#include "hge.h"
#include "hgefont.h"

class CMenuObj : public CObject, public CHGEBase
{
public:
	CMenuObj();
	virtual ~CMenuObj();

	bool FrameFunc();
	bool RenderFunc();

public:
	HTEXTURE texBg;
	hgeQuad quadBg;
	int		wBg;
	int		hBg;

	hgeGUI		*gui;
	HTEXTURE	texCursor;
	hgeFont		*fnt;
	hgeSprite	*spr;

};

#endif // __MENUOBJ__H__
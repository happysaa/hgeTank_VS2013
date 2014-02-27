// HGEBase.cpp: implementation of the CHGEBase class.
//
//////////////////////////////////////////////////////////////////////

#include "HGEBase.h"
#include <hge.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

extern HGE *hge;

int CHGEBase::screenCx = 0;
int CHGEBase::screenCy = 0;

CHGEBase::CHGEBase()
{
	//»ñÈ¡ÆÁÄ»¿í¸ß
	screenCx = hge->System_GetState(HGE_SCREENWIDTH);
	screenCy = hge->System_GetState(HGE_SCREENHEIGHT);
}

CHGEBase::~CHGEBase()
{

}

void CHGEBase::SetFunc(CHGEBase *&pBase, CHGEBase *pNewBase)
{
	pBase = pNewBase;
}

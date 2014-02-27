// HGEBase.h: interface for the CHGEBase class.
//
//////////////////////////////////////////////////////////////////////

#ifndef _HGEBASE_H_
#define _HGEBASE_H_


class CHGEBase  
{
public:
	CHGEBase();
	virtual ~CHGEBase();
	void SetFunc(CHGEBase *&pBase, CHGEBase *pNewBase);
	virtual bool FrameFunc() = 0;
	virtual bool RenderFunc() = 0;

	static int screenCx;
	static int screenCy;
};



#endif

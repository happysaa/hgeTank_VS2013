#ifndef __OBJECT__H__
#define __OBJECT__H__

class CScene;

class CObject  
{
public:
	void SetScene(CScene *scene);
	virtual bool RenderFunc() = 0;
	virtual bool FrameFunc() = 0;
	CObject();
	virtual ~CObject();

};

#endif // __OBJECT__H__
#ifndef __SCENE__H__
#define __SCENE__H__

#include <vector>
#include <map>

using namespace std;

class CObject;

typedef vector<CObject*> OBJECTS;
typedef map<int, OBJECTS *> OBJECTLAYER;

class CScene  
{
public:
	CScene();
	virtual ~CScene();

	bool FrameFunc();
	bool RenderFunc();

	void addChild(CObject *obj, int layer);
	void setScene(CScene *scene);

private:
	int screenCx;
	int screenCy;

	OBJECTLAYER mObjectLayer;
	int mMaxLayer;
};

#endif // __SCENE__H__
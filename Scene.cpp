#include "Scene.h"
#include "Object.h"

extern CScene *hgeScene;

CScene::CScene():mMaxLayer(0)
{
	
}

CScene::~CScene()
{

}

void CScene::addChild(CObject *obj, int layer)
{
	if(layer > mMaxLayer)
		mMaxLayer = layer;

	if(mObjectLayer.find(layer) != mObjectLayer.end())
	{
		mObjectLayer[layer]->push_back(obj);
	}
	else
	{
		OBJECTS *objs = new OBJECTS;
		objs->push_back(obj);
		mObjectLayer[layer] = objs;
	}
}

void CScene::setScene(CScene *scene)
{
	hgeScene = scene;
}

bool CScene::FrameFunc()
{
	for(int i = 0; i <= mMaxLayer; i++)
	{
		if(mObjectLayer.find(i) != mObjectLayer.end())
		{
			OBJECTS &objs = *mObjectLayer[i];
			for(OBJECTS::iterator iter = objs.begin(); iter != objs.end(); iter++)
			{
				(*iter)->FrameFunc();
			}
		}
	}
	return false;
}

bool CScene::RenderFunc()
{
	for(int i = 0; i <= mMaxLayer; i++)
	{
		if(mObjectLayer.find(i) != mObjectLayer.end())
		{
			OBJECTS &objs = *mObjectLayer[i];
			for(OBJECTS::iterator iter = objs.begin(); iter != objs.end(); iter++)
			{
				(*iter)->RenderFunc();
			}
		}
	}
	return false;
}
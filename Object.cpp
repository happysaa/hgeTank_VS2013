#include "Object.h"

extern CScene *hgeScene;

CObject::CObject()
{

}

CObject::~CObject()
{

}

void CObject::SetScene(CScene *scene)
{
	hgeScene = scene;
}

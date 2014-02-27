#ifndef __HGEMAP_H__
#define __HGEMAP_H__

#include <vector>
#include <map>
#include <string>
using namespace std;

#include "hge.h"
#include <hgesprite.h>
#include "tinyxml\tinyxml.h"


typedef vector<hgeSprite *> SPRITES;
typedef vector<int *> TILEINFO;
typedef map<string, TILEINFO *> MAPTILEINFO;

class hgeMap  
{
public:
	bool RenderLayer(string layer_name, float xPos = 0, float yPos = 0, int nxTile = 0, int nyTile = 0);
	bool Render();
	bool IsLoad;
	bool LoadResource();

	hgeMap(char* szMapFile);
	virtual ~hgeMap();

	HGE *hge;

	TiXmlDocument	*doc;
	TiXmlNode		*Node;
	TiXmlElement	*Elem;

	int TileWidth,TileHeight;//地图元素大小
	int width,height;//地图行列数


	//图片元素的纹理
	SPRITES sprs;
	TILEINFO tileInfo;

	MAPTILEINFO mapTileInfo;

};

#endif // hgeMap.h

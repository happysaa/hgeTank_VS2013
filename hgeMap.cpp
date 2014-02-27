#include "hgeMap.h"
#include "hgeMain.h"

hgeMap::hgeMap(char *szMapFile)
{
	hge = hgeCreate(HGE_VERSION);
	doc = new TiXmlDocument(szMapFile);
	IsLoad = doc->LoadFile(TIXML_ENCODING_UTF8);
	LoadResource();
	delete doc;
}

hgeMap::~hgeMap()
{
	//释放精灵
	for(SPRITES::iterator iter = sprs.begin(); iter != sprs.end(); iter++)
	{
		hge->Texture_Free((*iter)->GetTexture());
		delete *iter;
	}

	//释放mapTileInfo
	for(MAPTILEINFO::iterator mapiter = mapTileInfo.begin(); mapiter != mapTileInfo.end(); mapiter++)
	{
		for(TILEINFO::iterator iter = mapiter->second->begin(); iter != mapiter->second->end(); iter++)
		{
			delete [] *iter;
		}
		delete mapiter->second;
	}
}

bool hgeMap::LoadResource()
{
	Node = doc->FirstChild("map");

	//初始化地图元素的行列数以及元素宽高
	Node->ToElement()->Attribute("width", &width);
	Node->ToElement()->Attribute("height", &height);	
	Node->ToElement()->Attribute("tilewidth", &TileWidth);
	Node->ToElement()->Attribute("tileheight", &TileHeight);

	//获取image的source属性，得到图片地址
	sprs.push_back(new hgeSprite(0, 0, 0, 0, 0));
	for(Elem = Node->FirstChildElement("tileset"); Elem; Elem = Elem->NextSiblingElement("tileset"))
	{
		//加载图片的纹理
		const char *szImageName = Elem->FirstChildElement("image")->Attribute("source");
		HTEXTURE tex = hge->Texture_Load(hge->Resource_MakePath(szImageName));

		//获取图片宽高，循环截取元素,存放到sprite中
		int imageWidth  = hge->Texture_GetWidth(tex);
		int imageHeigth = hge->Texture_GetHeight(tex);
		for(int i = 0; i < imageHeigth/TileHeight; i++)
		{
			for(int j = 0; j < imageWidth/TileWidth; j++)
			{
				sprs.push_back(new hgeSprite(tex, j*TileHeight, i*TileWidth, TileWidth, TileHeight));
			}
		}
	}

	//读取地图信息到tileInfo
	for(Elem = Node->FirstChild("layer")->ToElement(); Elem; Elem = Elem->NextSiblingElement("layer"))
	{
		string layer_name = Elem->Attribute("name");
		mapTileInfo[layer_name] = new TILEINFO;

		TiXmlElement *tmpElem = Elem->FirstChildElement("data")->FirstChildElement("tile");
		for(int i = 0; i < height; i++)
		{
			(*mapTileInfo[layer_name]).push_back(new int[width]);
			memset((*mapTileInfo[layer_name])[i], 0, width);
			for(int j = 0; j< width; j++)
			{
				tmpElem->Attribute("gid", &(*mapTileInfo[layer_name])[i][j]);
				tmpElem = tmpElem->NextSiblingElement();
			}
		}
	}
	return true;
}

bool hgeMap::Render()
{
	for(MAPTILEINFO::iterator iter = mapTileInfo.begin(); iter != mapTileInfo.end(); iter++)
	{
		RenderLayer(iter->first);	
	}
	return false;
}

bool hgeMap::RenderLayer(string layer_name, float xPos, float yPos, int nxTile, int nyTile)
{
	int x = yPos/TileHeight;
	int y = xPos/TileWidth;
	if(nxTile == 0 || nyTile == 0)
	{
		nxTile = height;
		nyTile = width;
	}
	for(int i = x; i <= x + nyTile+1; i++)
	{
		for(int j = y; j <= y + nxTile + 1; j++)
		{
			if(i < height && j < width && i >= 0 && j >=0)
			{
				sprs[(*mapTileInfo[layer_name])[i][j]]->Render(j*TileWidth - xPos, i*TileHeight - yPos);
			}
		}
	}
	return true;
}

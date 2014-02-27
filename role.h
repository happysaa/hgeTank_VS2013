// C 运行时头文件
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <math.h>

// TODO: 在此处引用程序需要的其他头文件
#include <vector>
#include <list>
#include <string>
#include <stack>

#include <hge.h>
#include <hgesprite.h>
#include <hgeanim.h>
#include <hgerect.h>
#include <hgefont.h>

using namespace std ;

#define  CENGSHU 10 

#define  WINDOWWIDTH  1366
#define  WINDOWHEIGHT 768

#define  MAPWIDTH	2560
#define  MAPHEIGHT  2560

#define  ROLETANKWIDTH  128 
#define  ROLETANKHEIGHT 128


//小方块的宽和高 
#define  BOXWIDTH  32
#define  BOXHEIGHT 32


#define  BOXROWNUM 500
#define  BOXCOLNUM 500

//tank的速度和摩擦力
#define  ROLETANKSPEED 300
#define  FRICTION    0.5


#define  ROVESTOPR 800 
#define  ROVESTOPL 300 
#define  ROVESTOPU 200 
#define  ROVESTOPD 500

//石头状态
#define  ATTACKSTONSTATE 3 


typedef vector<HTEXTURE>  ROLEPICTUREVC , *PROLEPICTUREVC ;

enum DIRECTION{ DIRECTION_DOWN, DIRECTION_LEFTDOWN , DIRECTION_LEFT  ,DIRECTION_LEFTUP ,DIRECTION_UP  ,DIRECTION_RIGHTUP,
DIRECTION_RIGHT ,DIRECTION_RIGHTDOWN };

enum ACTIONSTATE{MOVE , STOP , FIRE };


//读写文件用的数据结构,对于读取文件显示用的
typedef struct tag_filestruct 
{
	int iCengshu ;
	int iSize ;

}FILESTRUCT , *PFILESTRUCT;

//地图上的贴图的信息，1.贴什么图，2。贴图的坐标
typedef struct tag_mapblockattribute
{
	int iTexture ;
	POINT point ;


}MAPBLOCKATTRIBUTE , *PMAPBLOCKATTRIBUTE;


//一副地图要用到的图元,先要进行加载 //背景图片的信息 背景的iChooseTexture = -1 ;
typedef struct tag_choosetextureattribute
{
	char szstrTextureFileName[MAX_PATH] ; 
	int iChooseTexture ;
	int fChooseTextureWidth ;
	int fChooseTextureHeight ;

}CHOOSETEXTUREATTRIBUTE , *PCHOOSETEXTUREATTRIBUTE, BACKGROUNDMAP;


typedef  struct tag_box 
{
	//是不是能通过
	int iIsgo ;
	//是否被攻击了
	//bool bIsAttack;
	//能被攻击几下
	//int iIsAttack ;

	

} BOX ,*PBOX;


typedef struct tag_mapattribute
{

	BOX (*pMapBox)[BOXCOLNUM];
	int iRowNum ;
	int iColNum ;
	int iCengshu ;

	//还有很多信息要进行添加，敌方坦克的位置什么的

}MAPATTRIBUTE,*PMAPATTRIBUTE;


typedef struct  tag_rolepicture 
{
	string strName ;
	vector<HTEXTURE> hTextureVC;

}ROLEPICTURE , *PROLEPICTURE;

typedef struct  tag_position 
{
	int iRow ;
	int iCol ;

}POSITION , *PPOSITION;


typedef struct tag_wayelem
{
	POSITION sPosition ;
	int iDir ;

}WAYELEM , *PWAYELEM;
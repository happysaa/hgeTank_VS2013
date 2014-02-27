// C ����ʱͷ�ļ�
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <math.h>

// TODO: �ڴ˴����ó�����Ҫ������ͷ�ļ�
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


//С����Ŀ�͸� 
#define  BOXWIDTH  32
#define  BOXHEIGHT 32


#define  BOXROWNUM 500
#define  BOXCOLNUM 500

//tank���ٶȺ�Ħ����
#define  ROLETANKSPEED 300
#define  FRICTION    0.5


#define  ROVESTOPR 800 
#define  ROVESTOPL 300 
#define  ROVESTOPU 200 
#define  ROVESTOPD 500

//ʯͷ״̬
#define  ATTACKSTONSTATE 3 


typedef vector<HTEXTURE>  ROLEPICTUREVC , *PROLEPICTUREVC ;

enum DIRECTION{ DIRECTION_DOWN, DIRECTION_LEFTDOWN , DIRECTION_LEFT  ,DIRECTION_LEFTUP ,DIRECTION_UP  ,DIRECTION_RIGHTUP,
DIRECTION_RIGHT ,DIRECTION_RIGHTDOWN };

enum ACTIONSTATE{MOVE , STOP , FIRE };


//��д�ļ��õ����ݽṹ,���ڶ�ȡ�ļ���ʾ�õ�
typedef struct tag_filestruct 
{
	int iCengshu ;
	int iSize ;

}FILESTRUCT , *PFILESTRUCT;

//��ͼ�ϵ���ͼ����Ϣ��1.��ʲôͼ��2����ͼ������
typedef struct tag_mapblockattribute
{
	int iTexture ;
	POINT point ;


}MAPBLOCKATTRIBUTE , *PMAPBLOCKATTRIBUTE;


//һ����ͼҪ�õ���ͼԪ,��Ҫ���м��� //����ͼƬ����Ϣ ������iChooseTexture = -1 ;
typedef struct tag_choosetextureattribute
{
	char szstrTextureFileName[MAX_PATH] ; 
	int iChooseTexture ;
	int fChooseTextureWidth ;
	int fChooseTextureHeight ;

}CHOOSETEXTUREATTRIBUTE , *PCHOOSETEXTUREATTRIBUTE, BACKGROUNDMAP;


typedef  struct tag_box 
{
	//�ǲ�����ͨ��
	int iIsgo ;
	//�Ƿ񱻹�����
	//bool bIsAttack;
	//�ܱ���������
	//int iIsAttack ;

	

} BOX ,*PBOX;


typedef struct tag_mapattribute
{

	BOX (*pMapBox)[BOXCOLNUM];
	int iRowNum ;
	int iColNum ;
	int iCengshu ;

	//���кܶ���ϢҪ������ӣ��з�̹�˵�λ��ʲô��

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
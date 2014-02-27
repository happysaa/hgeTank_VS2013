#ifndef CRole_H_H_H_H_H_H_H_H_H_H_H_H_H
#define CRole_H_H_H_H_H_H_H_H_H_H_H_H_H

#include <vector>
using namespace std;

#include <hge.h>
#include <hgesprite.h>

typedef vector<HTEXTURE>  ROLEPICTUREVC , *PROLEPICTUREVC ;
enum DIRECTION{ DIRECTION_DOWN , DIRECTION_LEFT , DIRECTION_UP, DIRECTION_RIGHT ,
DIRECTION_LEFTDOWN ,DIRECTION_RIGHTDOWN ,DIRECTION_LEFTUP ,DIRECTION_RIGHTUP};
enum ACTIONSTATE{MOVE , STOP , FIRE };

#define  BOXROWNUM 500
#define  BOXCOLNUM 500

typedef  struct tag_box 
{
	//是不是能通过
	int iIsgo ;
	//是不是能打破
	int iIsAttack ;
} BOX ,*PBOX;

typedef struct tag_mapattribute
{
	BOX (*pMapBox)[BOXCOLNUM];
	int iRowNum ;
	int iColNum ;
	int iCengshu ;
	//还有很多信息要进行添加，敌方坦克的位置什么的
}MAPBOXATTRIBUTE,*PMAPBOXATTRIBUTE;

class CRole
{
public:
	CRole();
	virtual ~CRole();

	virtual bool Render() =0 ;
	virtual bool FrameFunc() =0;
	void SetRolePos(float roleX, float roleY);

protected :
	//主角的地址
	float m_roleX , m_roleY ;
	//iCengshu为role所在的层数
	CRole(ROLEPICTUREVC &RolehTextureVC ,int iLife ,int iSpeed ,int iAttack, int iCengshu , float fRoleX, float fRoleY , 
		int iRoleWidth , int iRoleHeight );
	//role的属性

	static PMAPBOXATTRIBUTE m_Map;

	HGE *m_pHge ;
	vector<hgeSprite*> m_pRenderSpriteVC ;
	//所在层数
	int m_iCengshu ;
	int m_iSpeed ;
	//所在地图的坐标
	float m_fRoleX ,m_fRoleY ;
	//生命值当生命值为0的时候就灭亡
	int m_iLife;
	//攻击力 
	int m_iAttack ;
	int m_iRoleWidth , m_iRoleHeight ;
	
	DIRECTION m_Direction ;
	ACTIONSTATE  m_ActionState ; 
};

#endif



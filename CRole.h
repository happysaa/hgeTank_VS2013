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
	//�ǲ�����ͨ��
	int iIsgo ;
	//�ǲ����ܴ���
	int iIsAttack ;
} BOX ,*PBOX;

typedef struct tag_mapattribute
{
	BOX (*pMapBox)[BOXCOLNUM];
	int iRowNum ;
	int iColNum ;
	int iCengshu ;
	//���кܶ���ϢҪ������ӣ��з�̹�˵�λ��ʲô��
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
	//���ǵĵ�ַ
	float m_roleX , m_roleY ;
	//iCengshuΪrole���ڵĲ���
	CRole(ROLEPICTUREVC &RolehTextureVC ,int iLife ,int iSpeed ,int iAttack, int iCengshu , float fRoleX, float fRoleY , 
		int iRoleWidth , int iRoleHeight );
	//role������

	static PMAPBOXATTRIBUTE m_Map;

	HGE *m_pHge ;
	vector<hgeSprite*> m_pRenderSpriteVC ;
	//���ڲ���
	int m_iCengshu ;
	int m_iSpeed ;
	//���ڵ�ͼ������
	float m_fRoleX ,m_fRoleY ;
	//����ֵ������ֵΪ0��ʱ�������
	int m_iLife;
	//������ 
	int m_iAttack ;
	int m_iRoleWidth , m_iRoleHeight ;
	
	DIRECTION m_Direction ;
	ACTIONSTATE  m_ActionState ; 
};

#endif



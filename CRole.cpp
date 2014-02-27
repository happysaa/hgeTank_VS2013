#include "CRole.h"

CRole::CRole()
{
	
}

CRole::CRole( ROLEPICTUREVC &RolehTextureVC ,int iLife ,int iSpeed ,int iAttack , int iCengshu , float fRoleX, float fRoleY ,
			 int iRoleWidth , int iRoleHeight)
{
	m_pHge = hgeCreate(HGE_VERSION);
	m_iLife = iLife ;
	m_iSpeed = iSpeed ;
	m_iAttack = iAttack ;
	m_iCengshu = iCengshu ;
	m_fRoleX = fRoleX ;
	m_fRoleY = fRoleY ;
	m_iRoleWidth = iRoleWidth ;
	m_iRoleHeight = iRoleHeight ;


	hgeSprite *pTemsprite = NULL ;
	for (ROLEPICTUREVC::size_type i = 0 ; i != RolehTextureVC.size() ; ++i)
	{
		pTemsprite = NULL ;
		pTemsprite = new hgeSprite( RolehTextureVC[i] ,0,0, m_pHge->Texture_GetWidth(RolehTextureVC[i]) ,
			m_pHge->Texture_GetHeight(RolehTextureVC[i]) );
		m_pRenderSpriteVC.push_back(pTemsprite);
	}

}

CRole::~CRole()
{
	
	for (vector<hgeSprite*>::size_type i = 0 ; i != m_pRenderSpriteVC.size() ; ++i)
	{
		delete m_pRenderSpriteVC[i] ;
	}

	m_pHge->Release() ;
}


void CRole::SetRolePos(float roleX, float roleY)
{
	m_roleX = roleX;
	m_roleY = roleY;
}
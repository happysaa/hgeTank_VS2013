#ifndef __ASTAR_H__
#define __ASTAR_H__

#include <vector>
#include <list>
using namespace std;

namespace Astar
{

typedef struct stPOINT
{
	int x,y;	//����
	//���캯��
	stPOINT()			 :x(0),y(0){}
	stPOINT(int x, int y):x(x),y(y){}
}POINT, *PPOINT;

typedef struct stNode
{
	POINT	pt;		//���������
	int		f,g,h;	//f=g+h
	stNode *preNode;//���ڵ�
	//���캯��
	stNode(){}
	stNode(POINT pt, int f, int g, int h, stNode *preNode):pt(pt),f(f),g(g),h(h),preNode(preNode){}
}NODE, *PNODE;

template<class T>
class CAstar  
{
public:
	CAstar();
	~CAstar();

public:
	static const int H;		//	Ŀ��ķ�10
	static const int G_FAR;	//	�ԽǺķ�14
	static const int G_NEAR;//	���ںķ�10

	typedef list<NODE *>	nodeList;
	nodeList OpenList,CloseList;
	T *m_mapInfo;

	POINT m_ptStart;
	POINT m_ptEnd;
	POINT m_ptMap;

public:
	void  SetPath(POINT ptStart, POINT ptEnd, T *mapInfo, POINT ptRowCol);
	PNODE GetPath(POINT ptStart, POINT ptEnd, T *mapInfo, POINT ptRowCol);
	PNODE GetPath();
	void Release();
private:
	bool Search();					//��ʼ����·����true��ʾ�ɹ���false��ʾʧ��
	void InitList(POINT ptStart);	//��ʼ��������	
	NODE *FindMinFNode();			//�ҵ���СF�ڵ�
	void CheckAroundPt(NODE *preNode);
	bool CheckPt(POINT pt, int G, NODE* preNode);
	
	bool IsBlock(POINT pt);
	bool IsInClose(POINT pt);
	NODE *IsInOpen(POINT pt);
};

#include "Astar.inl"

}
#endif // Astar.h
#ifndef __ASTAR_H__
#define __ASTAR_H__

#include <vector>
#include <list>
using namespace std;

namespace Astar
{

typedef struct stPOINT
{
	int x,y;	//行列
	//构造函数
	stPOINT()			 :x(0),y(0){}
	stPOINT(int x, int y):x(x),y(y){}
}POINT, *PPOINT;

typedef struct stNode
{
	POINT	pt;		//土块的坐标
	int		f,g,h;	//f=g+h
	stNode *preNode;//父节点
	//构造函数
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
	static const int H;		//	目标耗费10
	static const int G_FAR;	//	对角耗费14
	static const int G_NEAR;//	相邻耗费10

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
	bool Search();					//开始搜索路径，true表示成功，false表示失败
	void InitList(POINT ptStart);	//初始化出发点	
	NODE *FindMinFNode();			//找到最小F节点
	void CheckAroundPt(NODE *preNode);
	bool CheckPt(POINT pt, int G, NODE* preNode);
	
	bool IsBlock(POINT pt);
	bool IsInClose(POINT pt);
	NODE *IsInOpen(POINT pt);
};

#include "Astar.inl"

}
#endif // Astar.h
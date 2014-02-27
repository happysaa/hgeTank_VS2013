template<class T>
int const CAstar<T>::H		= 10;
template<class T>
int const CAstar<T>::G_FAR  = 14;
template<class T>
int const CAstar<T>::G_NEAR = 10;

template<class T>
CAstar<T>::CAstar()
{

}

template<class T>
CAstar<T>::~CAstar()
{

}

template<class T>
void CAstar<T>::SetPath(POINT ptStart, POINT ptEnd, T *mapInfo, POINT ptRowCol)
{
	m_ptStart = ptStart;
	m_ptEnd   = ptEnd;
	m_mapInfo = mapInfo;
	m_ptMap	  = ptRowCol;
}

template<class T>
PNODE CAstar<T>::GetPath()
{
	Release();
	if(m_ptStart.x == m_ptEnd.x && m_ptStart.y == m_ptEnd.y) return NULL;
	InitList(m_ptStart);
	if(!Search())
	{
		Release();
	}
	return NULL;
}

template<class T>
PNODE CAstar<T>::GetPath(POINT ptStart, POINT ptEnd, T *mapInfo, POINT ptRowCol)
{
	Release();
	m_ptStart = ptStart;
	m_ptEnd   = ptEnd;
	m_mapInfo = mapInfo;
	m_ptMap	  = ptRowCol;
	if(m_ptStart.x == m_ptEnd.x && m_ptStart.y == m_ptEnd.y) return NULL;
	InitList(m_ptStart);
	if(!Search())
	{
		Release();
	}
	return NULL;
}

template<class T>
void CAstar<T>::InitList(POINT ptStart)
{
	CloseList.push_back(new NODE(ptStart, 0, 0, 0, NULL));
}

template<class T>
bool CAstar<T>::Search()
{
	//第一个关闭节点为起点
	NODE *MinF = *CloseList.begin();
	
	while(MinF)
	{
		if(MinF->pt.x == m_ptEnd.x && MinF->pt.y == m_ptEnd.y)
		{
			return true;
		}
		//检查周围节点
		CheckAroundPt(MinF);
		MinF = FindMinFNode();
	}
	return false;
}

template<class T>
NODE* CAstar<T>::FindMinFNode()
{
	if(OpenList.size() == 0)
	{
		return NULL;
	}
	
	nodeList::iterator iterMinf = OpenList.begin();
	for(nodeList::iterator iter = iterMinf; iter != OpenList.end(); ++iter)
	{
		if((*iterMinf)->f > (*iter)->f)
		{
			iterMinf = iter;
		}
	}
	//清楚最小F值的节点，并加入关闭列表
	CloseList.push_back(*iterMinf);
	OpenList.erase(iterMinf);

	return CloseList.back();
}

template<class T>
void CAstar<T>::CheckAroundPt(NODE* preNode)
{
	int &x = preNode->pt.x;
	int &y = preNode->pt.y;

	CheckPt(POINT(x-1, y), G_NEAR, preNode);//上
	CheckPt(POINT(x+1, y), G_NEAR, preNode);//下
	CheckPt(POINT(x, y-1), G_NEAR, preNode);//左
	CheckPt(POINT(x, y+1), G_NEAR, preNode);//右
/*
	CheckPt(POINT(x-1, y-1), G_FAR, preNode);//左上
	CheckPt(POINT(x-1, y+1), G_FAR, preNode);//右上
	CheckPt(POINT(x+1, y-1), G_FAR, preNode);//左下
	CheckPt(POINT(x+1, y+1), G_FAR, preNode);//右下*/
}

template<class T>
bool CAstar<T>::CheckPt(POINT pt, int G, NODE* preNode)
{
	if(pt.x < 0 || pt.x >= m_ptMap.x || pt.y < 0 || pt.y >= m_ptMap.y)
	{
		return false;
	}
	if(IsBlock(pt) || IsInClose(pt))
	{
		return false;
	}

	NODE *nodeOpen = IsInOpen(pt);
	if(nodeOpen)
	{
		//如果此节点的原G值比新G值高，则换掉此节点的G值
		if(nodeOpen->g > preNode->g+G)
		{
			nodeOpen->preNode = preNode;
			nodeOpen->g = preNode->g+G;
			nodeOpen->f = nodeOpen->g+nodeOpen->h;
		}
	}
	else
	{
		//构建新节点，加入开放列表
		nodeOpen = new NODE();
		nodeOpen->pt = pt;
		nodeOpen->g = preNode->g+G;
		nodeOpen->h = abs(pt.x - m_ptEnd.x)*10+abs(pt.y - m_ptEnd.y)*10;
		nodeOpen->f = nodeOpen->g + nodeOpen->h;
		nodeOpen->preNode = preNode;
		OpenList.push_back(nodeOpen);
	}
	return true;
}

template<class T>
bool CAstar<T>::IsBlock(POINT pt)
{
	T &IsPass = *m_mapInfo;
	//地图能通过返回true，不能通过返回false
	return IsPass[pt.x][pt.y];
}

template<class T>
bool CAstar<T>::IsInClose(POINT pt)
{
	//如果pt存在关闭列表则返回true，不存在关闭列表返回false
	for(nodeList::iterator iter = CloseList.begin(); iter != CloseList.end(); iter++)
	{
		if((*iter)->pt.x == pt.x && (*iter)->pt.y == pt.y)
		{
			return true;
		}
	}
	return false;
}

template<class T>
NODE* CAstar<T>::IsInOpen(POINT pt)
{
	//如果存在开放列表，就返回节点，否则返回空
	for(nodeList::iterator iter = OpenList.begin(); iter != OpenList.end(); iter++)
	{
		if((*iter)->pt.x == pt.x && (*iter)->pt.y == pt.y)
		{
			return *iter;
		}
	}
	return NULL;
}

template<class T>
void CAstar<T>::Release()
{
	while(!OpenList.empty())
	{
		delete OpenList.back();
		OpenList.pop_back();
	}
	while(!CloseList.empty())
	{
		delete CloseList.back();
		CloseList.pop_back();
	}
}
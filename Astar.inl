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
	//��һ���رսڵ�Ϊ���
	NODE *MinF = *CloseList.begin();
	
	while(MinF)
	{
		if(MinF->pt.x == m_ptEnd.x && MinF->pt.y == m_ptEnd.y)
		{
			return true;
		}
		//�����Χ�ڵ�
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
	//�����СFֵ�Ľڵ㣬������ر��б�
	CloseList.push_back(*iterMinf);
	OpenList.erase(iterMinf);

	return CloseList.back();
}

template<class T>
void CAstar<T>::CheckAroundPt(NODE* preNode)
{
	int &x = preNode->pt.x;
	int &y = preNode->pt.y;

	CheckPt(POINT(x-1, y), G_NEAR, preNode);//��
	CheckPt(POINT(x+1, y), G_NEAR, preNode);//��
	CheckPt(POINT(x, y-1), G_NEAR, preNode);//��
	CheckPt(POINT(x, y+1), G_NEAR, preNode);//��
/*
	CheckPt(POINT(x-1, y-1), G_FAR, preNode);//����
	CheckPt(POINT(x-1, y+1), G_FAR, preNode);//����
	CheckPt(POINT(x+1, y-1), G_FAR, preNode);//����
	CheckPt(POINT(x+1, y+1), G_FAR, preNode);//����*/
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
		//����˽ڵ��ԭGֵ����Gֵ�ߣ��򻻵��˽ڵ��Gֵ
		if(nodeOpen->g > preNode->g+G)
		{
			nodeOpen->preNode = preNode;
			nodeOpen->g = preNode->g+G;
			nodeOpen->f = nodeOpen->g+nodeOpen->h;
		}
	}
	else
	{
		//�����½ڵ㣬���뿪���б�
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
	//��ͼ��ͨ������true������ͨ������false
	return IsPass[pt.x][pt.y];
}

template<class T>
bool CAstar<T>::IsInClose(POINT pt)
{
	//���pt���ڹر��б��򷵻�true�������ڹر��б���false
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
	//������ڿ����б��ͷ��ؽڵ㣬���򷵻ؿ�
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
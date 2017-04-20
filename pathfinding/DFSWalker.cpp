#include "DFSWalker.h"


std::vector<GraphNode*> CDFSWalker::Search(GraphNode * pathBegin, GraphNode * pathEnd, int maxIterations)
{
	//Seleccionar primer nodo
	std::vector<GraphNode*> backProp;
	auto pActualNode = pathBegin;
	m_closedList.push_back(pActualNode);
	pActualNode->pathNode = std::make_unique<PathNode>();
	pActualNode->pathNode->enlisted = true;
	//Meter en la lista los hijos del nodo actual
	EnlistNodes(pActualNode);
	for (size_t i = 0; i < maxIterations; i++)
	{
		//Revisar si es el final
		if (pActualNode == pathEnd)
		{
			backProp = GetPath(pActualNode);
			break;
		}
		//Seleccionar siguiente nodo
		pActualNode = SelectNextNode(pActualNode);
		//Meter en la lista los hijos del nodo actual
		EnlistNodes(pActualNode);
	}
	//Reset();
	return backProp;
}

std::vector<GraphNode*> CDFSWalker::Search(GraphNode * pathBegin, GraphNode * pathEnd)
{
	//Seleccionar primer nodo
	std::vector<GraphNode*> backProp;
	auto pActualNode = pathBegin;
	m_closedList.push_back(pActualNode);
	pActualNode->pathNode = std::make_unique<PathNode>();
	pActualNode->pathNode->enlisted = true;
	//Meter en la lista los hijos del nodo actual
	EnlistNodes(pActualNode);
	do
	{
		//Revisar si es el final
		if (pActualNode == pathEnd)
		{
			backProp = GetPath(pActualNode);
			break;
		}
		//Seleccionar siguiente nodo
		pActualNode = SelectNextNode(pActualNode);
		//Meter en la lista los hijos del nodo actual
		EnlistNodes(pActualNode);
	} while (m_openList.size() > 0);
	//Reset();
	return backProp;
}

std::list<GraphNode*> CDFSWalker::GetClosedList()
{
	return m_closedList;
}

GraphNode* CDFSWalker::SelectNextNode(GraphNode* pActual)
{
	GraphNode* pActualNode = m_openList.back();
	m_openList.pop_back();
	//m_closedList.push_back(pActual);
	return pActualNode;
}

void CDFSWalker::EnlistNodes(GraphNode * pActual)
{
	for (auto &option : pActual->children)
	{
		if (option->active) {
			if (option->pathNode == nullptr)
				option->pathNode = std::make_unique<PathNode>();
			if (!option->pathNode->enlisted) {
				m_openList.push_back(option);
				m_closedList.push_back(option);
				option->pathNode->enlisted = true;
				option->pathNode->father = pActual;
			}
		}
	}
}

void CDFSWalker::Reset()
{
	for (auto &it : m_closedList)
	{
		it->pathNode.reset();
	}
	m_closedList.clear();
	m_openList.clear();

}

CDFSWalker::CDFSWalker()
{
}


CDFSWalker::~CDFSWalker()
{
}

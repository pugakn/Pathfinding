#include "DijikstraWalker.h"



GraphNode * CDijikstraWalker::SelectNextNode(GraphNode * pActual)
{
	GraphNode* pActualNode = m_openList.front();
	m_openList.pop_front();
	return pActualNode;
}

void CDijikstraWalker::EnlistNodes(GraphNode * pActual)
{
	for (auto &option : pActual->children)
	{
		if (option->active) {
			if (option->pathNode == nullptr) {
				option->pathNode = std::make_unique<PathNode>();
				option->pathNode->father = pActual;
				option->pathNode->weight = pActual->pathNode->weight + option->weight;
				m_openList.push_back(option);
				m_closedList.push_back(option);
				option->pathNode->enlisted = true;
			}
			else
				if (option->pathNode->weight > pActual->pathNode->weight + option->weight)
				{
					option->pathNode->father = pActual;
					option->pathNode->weight = pActual->pathNode->weight + option->weight;
					m_openList.push_back(option);
					m_closedList.push_back(option);
					option->pathNode->enlisted = true;
				}
		}
	}
}

std::vector<GraphNode*> CDijikstraWalker::Search(GraphNode * pathBegin, GraphNode * pathEnd, int maxIterations)
{
	//Seleccionar primer nodo
	std::vector<GraphNode*> backProp;
	auto pActualNode = pathBegin;
	m_closedList.push_back(pActualNode);
	pActualNode->pathNode = std::make_unique<PathNode>();
	pActualNode->pathNode->enlisted = true;
	for (size_t i = 0; i < maxIterations; i++)
	{
		//Meter en la lista los hijos del nodo actual
		EnlistNodes(pActualNode);
		//Seleccionar siguiente nodo
		pActualNode = SelectNextNode(pActualNode);
	}
	backProp = GetPath(pathEnd);
	//Reset();
	return backProp;
}

std::vector<GraphNode*> CDijikstraWalker::Search(GraphNode * pathBegin, GraphNode * pathEnd)
{
	//Seleccionar primer nodo
	std::vector<GraphNode*> backProp;
	auto pActualNode = pathBegin;
	m_closedList.push_back(pActualNode);
	pActualNode->pathNode = std::make_unique<PathNode>();
	pActualNode->pathNode->enlisted = true;
	pActualNode->pathNode->weight = 0;
	//Meter en la lista los hijos del nodo actual
	EnlistNodes(pActualNode);
	do
	{
		//Seleccionar siguiente nodo
		pActualNode = SelectNextNode(pActualNode);
		//Meter en la lista los hijos del nodo actual
		EnlistNodes(pActualNode);
	} while (m_openList.size() > 0);
	backProp = GetPath(pathEnd);
	//Reset();
	return backProp;
}

std::list<GraphNode*> CDijikstraWalker::GetClosedList()
{
	return m_closedList;
}

void CDijikstraWalker::Reset()
{
	for (auto &it : m_closedList)
	{
		it->pathNode.reset();
	}
	m_closedList.clear();
	m_openList.clear();
}

CDijikstraWalker::CDijikstraWalker()
{
}


CDijikstraWalker::~CDijikstraWalker()
{
}

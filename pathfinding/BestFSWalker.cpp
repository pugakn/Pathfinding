#include "BestFSWalker.h"

std::vector<GraphNode*> CBestFSWalker::Search(GraphNode * pathBegin, GraphNode * pathEnd, int maxIterations)
{
	//Seleccionar primer nodo
	std::vector<GraphNode*> backProp;
	auto pActualNode = pathBegin;
	m_closedList.push_back(pActualNode);
	pActualNode->pathNode = std::make_unique<PathNode>();
	pActualNode->pathNode->enlisted = true;
	pActualNode->pathNode->weight = pActualNode->weight;
	//Meter en la lista los hijos del nodo actual
	EnlistNodes(pActualNode, pathEnd);
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
		EnlistNodes(pActualNode, pathEnd);
	}
	//Reset();
	return backProp;
}

std::vector<GraphNode*> CBestFSWalker::Search(GraphNode * pathBegin, GraphNode * pathEnd)
{
	//Seleccionar primer nodo
	std::vector<GraphNode*> backProp;
	auto pActualNode = pathBegin;
	m_closedList.push_back(pActualNode);
	pActualNode->pathNode = std::make_unique<PathNode>();
	pActualNode->pathNode->enlisted = true;
	pActualNode->pathNode->weight = pActualNode->weight;
	//Meter en la lista los hijos del nodo actual
	EnlistNodes(pActualNode, pathEnd);
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
		EnlistNodes(pActualNode,pathEnd);
	} while (m_openList.size() > 0);
	//Reset();
	return backProp;
}

std::list<GraphNode*> CBestFSWalker::GetClosedList()
{
	return m_closedList;
}

GraphNode * CBestFSWalker::SelectNextNode(GraphNode * pActual)
{
	m_openList.sort([](const GraphNode * a, const GraphNode * b) { return a->pathNode->weight > b->pathNode->weight; });
	GraphNode* pActualNode = m_openList.back();
	m_openList.pop_back();
	return pActualNode;
}

void CBestFSWalker::EnlistNodes(GraphNode * pActual, GraphNode* pFinalNode)
{
	for (auto &option : pActual->children)
	{
		if (option->active) {
			if (option->pathNode == nullptr)
				option->pathNode = std::make_unique<PathNode>();
			if (!option->pathNode->enlisted) {
				m_openList.push_back(option);
				m_closedList.push_back(option);
				option->pathNode->weight = pHeuristicFoo(pFinalNode, option);
				option->pathNode->enlisted = true;
				option->pathNode->father = pActual;
			}
		}
	}
}

void CBestFSWalker::Reset()
{
	for (auto &it : m_closedList)
	{
		it->pathNode.reset();
	}
	m_closedList.clear();
	m_openList.clear();
}
CBestFSWalker::CBestFSWalker()
{
}


CBestFSWalker::~CBestFSWalker()
{
}

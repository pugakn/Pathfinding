#pragma once
#include "WalkerBase.h"
class CBFSWalker :
	public CWalkerBase
{
private:
	std::list<GraphNode*> m_openList;
	std::list<GraphNode*> m_closedList;
	GraphNode* SelectNextNode(GraphNode* pActual);
	void EnlistNodes(GraphNode* pActual);
public:
	std::vector<GraphNode*> Search(GraphNode* pathBegin, GraphNode* pathEnd, int maxIterations) override;
	std::vector<GraphNode*> Search(GraphNode* pathBegin, GraphNode* pathEnd) override;
	std::list<GraphNode*> GetClosedList() override;

	void Reset() override;

	CBFSWalker();
	~CBFSWalker();
};


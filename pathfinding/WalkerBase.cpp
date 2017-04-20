#include "WalkerBase.h"



CWalkerBase::CWalkerBase()
{
}

std::vector<GraphNode*> CWalkerBase::GetPath(GraphNode* pActualNode)
{
	std::vector<GraphNode*> tempBackProp;
	tempBackProp.push_back(pActualNode);
	while (pActualNode->pathNode->father != nullptr)
	{
		if (pActualNode->pathNode->father == nullptr)
		{
			tempBackProp.push_back(pActualNode);
			break;
		}
		pActualNode = pActualNode->pathNode->father;
		tempBackProp.push_back(pActualNode);
	}
	return tempBackProp;
}


	


void CWalkerBase::SetHeuristic(Heuristic::E heuristic)
{
	switch (heuristic)
	{
	case Heuristic::kEuclidean:
		pHeuristicFoo = [](GraphNode* finalNode, GraphNode*actualNode) 
		{
			return Magnitude(finalNode->worldPosition - actualNode->worldPosition); 
		};
		break;
	case Heuristic::kCuadratic:
		pHeuristicFoo = [](GraphNode* finalNode, GraphNode*actualNode)
		{
			Vector3D dif = finalNode->worldPosition - actualNode->worldPosition;
			return dif.x*dif.x + dif.y*dif.y + dif.z+dif.z;
		};
		break;
	case Heuristic::kManhatan:
		pHeuristicFoo = [](GraphNode* finalNode, GraphNode*actualNode)
		{
			Vector3D dif = finalNode->worldPosition - actualNode->worldPosition;
			return abs(dif.x) + abs(dif.y);
		};
		break;

	}
}

CWalkerBase::~CWalkerBase()
{
}

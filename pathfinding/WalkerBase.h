#pragma once
#include <list>
#include <vector>
#include <functional>
#include <memory>
#include "Vector3D.h"
namespace Heuristic
{
	enum E
	{
		kEuclidean,
		kCuadratic,
		kManhatan
	};
}

struct GraphNode;
struct PathNode //PathNode
{
	bool enlisted;
	GraphNode* father;
	float weight;
	float gCost;
	PathNode() {
		enlisted = false;
		father = nullptr;
		gCost = 0;
		weight = 0;
	}
};

struct GraphNode
{
	GraphNode()
	{
		weight = 1;
		active = true;
	}
	unsigned int id;
	std::list<GraphNode*> children;
	float weight;
	Vector3D worldPosition;
	bool active;
	std::unique_ptr<PathNode> pathNode;
};

class CWalkerBase
{
protected:
	std::function<float(GraphNode* finalNode, GraphNode*actualNode)> pHeuristicFoo; //Retorna el peso evaludao con la heuristica
public:
	CWalkerBase();
	virtual std::vector<GraphNode*> Search(GraphNode* pathBegin, GraphNode* pathEnd, int maxIterations) = 0;
	virtual std::vector<GraphNode*> Search(GraphNode* pathBegin, GraphNode* pathEnd) = 0;
	virtual std::list<GraphNode*> GetClosedList() = 0;
	//Reset
	virtual void Reset() = 0;
	//BackProp
	std::vector<GraphNode*> GetPath(GraphNode* pActualNode);
	void SetHeuristic(Heuristic::E heuristic);

	virtual ~CWalkerBase();
};


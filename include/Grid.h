#pragma once
#include <memory>
#include <functional>
#include <queue>

class GridPosition {
public:
  GridPosition(int x, int y);

  typedef std::shared_ptr<GridPosition> Ptr;

  double overallCosts = 0;
  double costs = 0;
  int x = 0;
  int y = 0;

  void printPath(bool last = true);

  Ptr previousNode;

  bool hasHigherCostsThan(const GridPosition& other) const;
};

class Grid {
public:
  bool _grid[10][10] = {};
  bool _closedList[10][10] = {};

  typedef GridPosition::Ptr Node;

  struct NodeComparator {
    bool operator()(const Node &lhs, const Node&rhs) const {
      return lhs->hasHigherCostsThan(*rhs);
    };
  };

  typedef std::priority_queue<Node, std::vector<Node>, NodeComparator> OpenList;

  bool expand(const Node& currentNode, const Node& endNode, OpenList& openList);

  bool pop(OpenList& openList, Node& node) const;

};

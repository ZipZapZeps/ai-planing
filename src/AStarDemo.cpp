// AI.cpp : Definiert den Einstiegspunkt für die Konsolenanwendung.
//

#include <vector>
#include <map>
#include <set>
#include <memory>
#include <functional>
#include <queue>
#include "AStar.h"

class GridPosition {
public:
  GridPosition(int x_, int y_)
    : x(x_)
    , y(y_) {}

  typedef std::shared_ptr<GridPosition> Ptr;

  int x = 0;
  int y = 0;
  double costs = 0;
  double heuristic = 0;

  Ptr previousNode;

  bool operator <(const GridPosition& other) const {
    return (costs + heuristic) > (other.costs + other.heuristic);
  }

};

class Grid {
public:
  bool _grid[10][10] = {};
  bool _closedList[10][10] = {};

  typedef GridPosition::Ptr Node;

  struct NodeComparator {
    bool operator()(const Node &lhs, const Node&rhs) const {
      return *lhs < *rhs;
    };
  };

  typedef std::priority_queue<Node, std::vector<Node>, NodeComparator> OpenList;

  bool expand(const Node& currentNode, const Node& endNode, OpenList& openList) {
    if (currentNode->x == endNode->x && currentNode->y == endNode->y) {
      // we are at the end
      return true;
    }

    if (_closedList[currentNode->x][currentNode->y]) {
      // we were expanded previously
      return false;
    }

    _closedList[currentNode->x][currentNode->y] = true;

    for (int i = -1; i <= 1; ++i) {
      for (int j = -1; j <= 1; ++j) {
        if (i == 0 && j == 0) {
          continue;
        }
        int x = i + currentNode->x;
        int y = j + currentNode->y;

        if (x < 0 || y < 0 || x >= 10 || y >= 10) {
          continue;
        }

        if (_closedList[x][y] || _grid[x][y]) {
          continue;
        }

        auto* nextNode = new GridPosition(x, y);
        nextNode->costs = currentNode->costs + sqrt(double(abs(i) + abs(j)));
        nextNode->heuristic = abs(nextNode->x - endNode->x) + abs(nextNode->y - endNode->y);
        nextNode->previousNode = currentNode;
        openList.push(GridPosition::Ptr(nextNode));
      }
    }
    return false;
  }

  Node pop(OpenList& openList) const {
    Node n = openList.top();
    openList.pop();
    return n;
  }

};

int main()
{
  Grid g;
  g._grid[0][3] = true;
  g._grid[1][3] = true;
  g._grid[2][3] = true;
  g._grid[3][3] = true;
  g._grid[3][2] = true;
  g._grid[3][1] = true;

  Grid::Node initialNode(new GridPosition(0, 0));
  Grid::Node endNode(new GridPosition(9, 9));
  Grid::Node currentNode;

  AI::Planing::AStar<Grid> astar;
  astar.run(g, initialNode, endNode, currentNode);

  return 0;
}


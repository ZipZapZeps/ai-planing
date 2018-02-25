#include "Grid.h"
#include <iostream>

GridPosition::GridPosition(int x_, int y_)
  : x(x_)
  , y(y_) {}

bool GridPosition::hasHigherCostsThan(const GridPosition& other) const {
  return overallCosts > other.overallCosts;
}

void GridPosition::printPath(bool last) {
  if (previousNode.get()) {
    previousNode->printPath(false);
  }

  std::cout << "(" << x << "," << y << ")";
  if (last) {
    std::cout << std::endl;
  }
  else {
    std::cout << " ";
  }

}

bool Grid::expand(const Node& currentNode, const Node& endNode, OpenList& openList) {
  if (currentNode->x == endNode->x && currentNode->y == endNode->y) {
    // we found the final node
    return true;
  }

  if (_closedList[currentNode->x][currentNode->y]) {
    // this node was expanded previously
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
      nextNode->overallCosts = nextNode->costs + abs(nextNode->x - endNode->x) + abs(nextNode->y - endNode->y);
      nextNode->previousNode = currentNode;
      openList.push(GridPosition::Ptr(nextNode));
    }
  }
  return false;
}

bool Grid::pop(OpenList& openList, Node& node) const {
  if (openList.empty()) {
    return false;
  }
  node = openList.top();
  openList.pop();
  return true;
}

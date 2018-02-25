
#include "AStar.h"
#include "Grid.h"

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
  Grid::Node finalPath;

  AI::Planing::AStar<Grid> astar;
  astar.run(g, initialNode, endNode, finalPath);

  finalPath->printPath();

  return 0;
}


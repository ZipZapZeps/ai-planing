#pragma once

namespace AI {

  namespace Planing {

    template<class StateContext>
    class AStar {
    public:
      typedef typename StateContext::OpenList OpenList;
      typedef typename StateContext::Node Node;

      bool run(StateContext& stateContext, const Node& startNode, const Node& endNode, Node& currentNode) {
        currentNode = startNode;
        while (true) {
          if (stateContext.expand(currentNode, endNode, _openList)) {
            return true;
          }

          if (_openList.empty()) {
            return false;
          }

          currentNode = stateContext.pop(_openList);
        }

        return false;
      }

    private:
      OpenList _openList;

    };

  } // namespace Planing

} // namespace AI


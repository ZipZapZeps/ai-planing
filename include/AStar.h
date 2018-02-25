#pragma once

namespace AI {

  namespace Planing {

    enum class AStarResult {
      PathFound,
      NoPathFound
    };

    template<class StateContext>
    class AStar {
    public:
      typedef typename StateContext::OpenList OpenList;
      typedef typename StateContext::Node Node;

      /// <param name="path">The resulting path</param>
      AStarResult run(StateContext& stateContext, const Node& startNode, const Node& endNode, Node& path) {
        path = startNode;

        do {

          if (stateContext.expand(path, endNode, _openList)) {
            // we found the final node
            return AStarResult::PathFound;
          }

        } while (stateContext.pop(_openList, path));

        // there are no node to explore anymore
        return AStarResult::NoPathFound;
      }

      /// <remarks>Access to the OpenList is usefull for debugging</remarks>
      const OpenList& getOpenList() const { return _openList; }

    private:
      OpenList _openList;

    };

  } // namespace Planing

} // namespace AI


#pragma once
#include <vector>
#include <numeric>

namespace AI {
  namespace GameTheory {

    template<class GameState>
    class MonteCarloTreeSearchNode {
    public:
      typedef MonteCarloTreeSearchNode<GameState> Node;
      typedef std::vector<GameState> GameStates;
      typedef std::vector <Node> Nodes;

      void expand(const GameState& gameState) {
        gameState.expand(_gameStates);
        _nodes.resize(_gameStates.size());
      }

      unsigned int _numGamesPlayed = 0;
      unsigned int _numGamesWon = 0;

      Nodes _nodes;
      GameStates _gameStates;

      double computeUTC(double explorationBias, unsigned int numTotalGames) const {
        if (_numGamesPlayed) {
          return ((double)_numGamesWon / (double)_numGamesPlayed) + explorationBias * log((double)_numGamesPlayed / (double)numTotalGames);
        }
        return std::numeric_limits<double>::max();
      }

      Node* computeBestNode(double explorationBias) {
#if 1
        struct {
          Node* node;
          double bestUTC;
          unsigned int _numGamesPlayed;
          double explorationBias;

          auto operator +(Node& n) const {
            double utc = n.computeUTC(explorationBias, _numGamesPlayed);
            if (utc > bestUTC) {
              auto bn(*this);
              bn.bestUTC = utc;
              bn.node = &n;
              return bn;
            }
            return *this;
          }
        } selectBestNode = { nullptr, 0., 0, explorationBias };

        return std::accumulate(_nodes.begin(), _nodes.end(), selectBestNode).node;

#else
        std::size_t bestNode = 0;
        double bestUTC = 0.;
        for (std::size_t i = 0; i < _nodes.size(); ++i) {
          double utc = _nodes[i].computeUTC(explorationBias, _numGamesPlayed);
          if (utc > bestUTC) {
            bestUTC = utc;
            bestNode = i;
          }
        }
        return &*(_nodes.begin() + bestNode);
#endif
      }
    };

    template<class GameState>
    class MonteCarloTreeSearch {
    public:
      typedef typename MonteCarloTreeSearchNode<GameState> Node;

      Node _rootNode;
      GameState _rootGameState;

      double _explorationBias = sqrt(2.);

      void run() {
        _rootNode.expand(_rootGameState);
        auto* bestNode = _rootNode.computeBestNode(_explorationBias);
        // select
        // explore
        // simulate
        // backtrack
      }
    };
  }
}

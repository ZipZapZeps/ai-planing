#pragma once
#include <vector>

class TicTacToe {
public:
  typedef std::vector<TicTacToe> Games;

  int expand(Games& games) const {
    games.clear();
    games.reserve(9);

    auto winningPlayer = getWinningPlayer();
    if (winningPlayer != NotSet) {
      return winningPlayer;
    }

    auto nextPlayer = getNextPlayer();

    for (int i = 0; i < 3; ++i) {
      for (int j = 0; j < 3; ++j) {
        if (_fields[i][j] == NotSet) {
          games.push_back(*this);
          games.back()._fields[i][j] = _nextPlayer;
          games.back()._nextPlayer = nextPlayer;
        }
      }
    }

    return NotSet;
  }

  enum Player {
    Player1,
    Player2,
    NotSet
  };


  Player getWinningPlayer() const {
    for (int i = 0; i < 3; ++i) {
      auto winningPlayer = getWinningPlayerForRow(i);
      if (winningPlayer != NotSet) {
        return winningPlayer;
      }
    }

    for (int i = 0; i < 3; ++i) {
      auto winningPlayer = getWinningPlayerForCol(i);
      if (winningPlayer != NotSet) {
        return winningPlayer;
      }
    }

    Player winningPlayer = getWinningPlayerForDiagonal1();
    if (winningPlayer != NotSet) {
      return winningPlayer;
    }

    return getWinningPlayerForDiagonal2();
  }

  inline Player getWinningPlayerForDiagonal1() const {
    if (_fields[0][0] == _fields[1][1] && _fields[0][0] == _fields[2][2]) {
      return _fields[0][0];
    }
    return NotSet;
  }

  inline Player getWinningPlayerForDiagonal2() const {
    if (_fields[2][0] == _fields[1][1] && _fields[2][0] == _fields[0][2]) {
      return _fields[2][0];
    }
    return NotSet;
  }

  inline Player getWinningPlayerForRow(int row) const {
    if (_fields[row][0] == _fields[row][1] && _fields[row][0] == _fields[row][2]) {
      return _fields[row][0];
    }
    return NotSet;
  }

  inline Player getWinningPlayerForCol(int col) const {
    if (_fields[0][col] == _fields[1][col] && _fields[0][col] == _fields[2][col]) {
      return _fields[0][col];
    }
    return NotSet;
  }

  Player getNextPlayer() const {
    if (_nextPlayer == Player1) {
      return Player2;
    }
    return Player1;
  }

  Player _nextPlayer = Player1;
  Player _fields[3][3] = {};

};

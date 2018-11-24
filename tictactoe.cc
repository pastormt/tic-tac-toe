#include <iostream>
#include <vector>
#include <utility>

using namespace std;

class TicTacToe {
  vector<vector<char>> board;
  char player;

  bool isBoardFull() {
    for (auto row : board) {
      for (char c : row) {
        if (c == '-') {
          // found an empty space, so...
          return false;
        }
      }
    }
    return true;
  }

  bool isWonBy(char player) {
    bool won = false;

    // won horizontally?
    for (auto row : board) {
      won = true;
      for (char c : row) {
        if (c != player) {
          won = false;
          break;
        }
      }
      if (won == true) return true;
    }

    // won vertically?
    for (int i = 0; i < board[0].size(); i++) {
      won = true;
      for (int j = 0; j < board.size(); j++) {
        if (board[j][i] != player) {
          won = false;
          break;
        }
      }
      if (won == true) return true;
    }

    // won diagonally?
    won = true;
    for (int i = 0, j = 0; i < board.size(); i++, j++) {
      if (board[i][j] != player) {
        won = false;
        break;
      }
    }
    if (won == true) return true;

    won = true;
    for (int i = board.size() - 1, j = 0; i >= 0; i--, j++) {
      if (board[i][j] != player) {
        won = false;
        break;
      }
    }
    if (won == true) return true;

    return false;
  }

  void printBoard() {
    cout << "Board is currently: " << endl;
    for (auto row : board) {
      for (char c : row) {
        cout << c << ' ';
      }
      cout << endl;
    }
  }

  pair<int,int> convertToXY(int guess) {
    guess--;
    int x = guess % board[0].size();
    int y = guess / board.size();
    return make_pair(x,y);
  }

  bool placeGuessIfValid(int guess, char player) {
    pair<int,int> x_y = convertToXY(guess);
    int x = x_y.first;
    int y = x_y.second;

    bool valid = false;
    if (board[y][x] == '-') {
      board[y][x] = player;
      valid = true;
    }
    return valid;
  }

  void getGuess(char player) {
    int guess;
    do {
      cout << "Make a guess, " << player << endl;
      cin >> guess;
    } while (!placeGuessIfValid(guess, player));
  }

  void printInstructions() {
    cout << "Board positions are: " << endl;
    for (int i = 0; i < board[0].size(); i++) {
      for (int j = 0; j < board.size(); j++) {
        int pos = i*3 + j + 1;
        cout << pos << ' ';
      }
      cout << endl;
    }
  }

  public:
    TicTacToe() {
      board = {
        {'-','-','-'},
        {'-','-','-'},
        {'-','-','-'},
      };
      player = 'O';
    }

    void playGame() {

      printInstructions();
      printBoard();

      while (true) {
        getGuess(player);
        printBoard();

        if (isWonBy(player)) {
          cout << "Game won by player " << player << endl;
          return;
        }

        if (isBoardFull()) {
          cout << "Game tied" << endl;
          return;
        }

        player = player == 'O' ? 'X' : 'O';
      } 
    }
};

int main() {
  TicTacToe().playGame();
  return 0;
}

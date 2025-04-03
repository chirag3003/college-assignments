// N Queen


#include <iostream>
#include <vector>

using namespace std;

bool isSafe(vector<vector<int>> board, int n, int x, int y) {
  for (int i = 0; i < n; i++) {
    if (board[i][y] == 1) {
      return false;
    }
  }
  for (int i = 0; i < n; i++) {
    if (board[x][i] == 1) {
      return false;
    }
  }

  // check if the queen can be placed in the diagonal
  int x1 = x;
  int y1 = y;
  while (x1 >= 0 && y1 >= 0) {
    if (board[x1][y1] == 1) {
      return false;
    }
    x1--;
    y1--;
  }
  x1 = x;
  y1 = y;
  while (x1 < n && y1 < n) {
    if (board[x1][y1] == 1) {
      return false;
    }
    x1++;
    y1++;
  }
  x1 = x;
  y1 = y;
  while (x1 >= 0 && y1 < n) {
    if (board[x1][y1] == 1) {
      return false;
    }
    x1--;
    y1++;
  }
  x1 = x;
  y1 = y;
  while (x1 < n && y1 >= 0) {
    if (board[x1][y1] == 1) {
      return false;
    }
    x1++;
    y1--;
  }
  return true;
}

bool solveNQueen(vector<vector<int>> &board, int n, int x) {
  if (n == 0) {
    return true;
  }
  if (x == n) {
    return true;
  }

  for (int j = 0; j < n; j++) {
    if (board[x][j] == 0) {
      if (isSafe(board, n, x, j)) {
        board[x][j] = 1;
        if (solveNQueen(board, n, x + 1)) {
          return true;
        }
      }
      board[x][j] = 0;
    }
  }

  return false;
}

int main() {
  int n;
  cout << "Enter the number of rows: ";
  cin >> n;

  vector<vector<int>> board;
  for (int i = 0; i < n; i++) {
    vector<int> row;
    for (int j = 0; j < n; j++) {
      row.push_back(0);
    }
    board.push_back(row);
  }

  solveNQueen(board, n, 0);

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      cout << board[i][j] << " ";
    }
    cout << endl;
  }
}

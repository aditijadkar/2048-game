/****How to Play 2048
Game Objective:
Combine tiles with the same number to create a tile with the number 2048.
Game Board:
The game board is a 4x4 grid where tiles with numbers appear.
You can move the tiles up, down, left, or right.
Controls:
W: Move tiles Up.
A: Move tiles Left.
S: Move tiles Down.
D: Move tiles Right.
Game Mechanics:
When you press a movement key, all tiles on the board will move in the specified direction.
If two tiles with the same number collide, they will merge into a single tile with a number equal to the sum of the two tiles.
After each move, a new tile with a value of 2 or 4 will randomly appear on an empty spot on the board.
Winning the Game:
The game is won when a tile with the number 2048 appears on the board.
Game Over:
The game is over if there are no empty spots on the board and no valid moves remaining (no adjacent tiles can be merged).****/


#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <iomanip>

using namespace std;

const int SIZE = 4;

class Game2048 {
private:
    vector<vector<int>> board;
    bool isMoved;

    void initializeBoard() {
        board.resize(SIZE, vector<int>(SIZE, 0));
        addRandomTile();
        addRandomTile();
    }

    void addRandomTile() {
        srand(time(0));
        int x, y;
        do {
            x = rand() % SIZE;
            y = rand() % SIZE;
        } while (board[x][y] != 0);
        board[x][y] = (rand() % 2 + 1) * 2;
    }

    void drawBoard() {
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                cout << setw(4) << board[i][j];
            }
            cout << endl;
        }
    }

    void moveLeft() {
        isMoved = false;
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE - 1; ++j) {
                if (board[i][j] == 0 && board[i][j + 1] != 0) {
                    board[i][j] = board[i][j + 1];
                    board[i][j + 1] = 0;
                    isMoved = true;
                }
            }
        }
    }

    void mergeLeft() {
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE - 1; ++j) {
                if (board[i][j] != 0 && board[i][j] == board[i][j + 1]) {
                    board[i][j] *= 2;
                    board[i][j + 1] = 0;
                    isMoved = true;
                }
            }
        }
    }

    void moveUp() {
        isMoved = false;
        for (int j = 0; j < SIZE; ++j) {
            for (int i = 0; i < SIZE - 1; ++i) {
                if (board[i][j] == 0 && board[i + 1][j] != 0) {
                    board[i][j] = board[i + 1][j];
                    board[i + 1][j] = 0;
                    isMoved = true;
                }
            }
        }
    }

    void mergeUp() {
        for (int j = 0; j < SIZE; ++j) {
            for (int i = 0; i < SIZE - 1; ++i) {
                if (board[i][j] != 0 && board[i][j] == board[i + 1][j]) {
                    board[i][j] *= 2;
                    board[i + 1][j] = 0;
                    isMoved = true;
                }
            }
        }
    }

    void rotateBoardClockwise() {
        vector<vector<int>> temp(SIZE, vector<int>(SIZE, 0));
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                temp[j][SIZE - i - 1] = board[i][j];
            }
        }
        board = temp;
    }

public:
    Game2048() {
        initializeBoard();
    }

    void move(char direction) {
        switch (direction) {
            case 'w': // up
                moveUp();
                mergeUp();
                moveUp();
                break;
            case 's': // down
                rotateBoardClockwise();
                rotateBoardClockwise();
                moveUp();
                mergeUp();
                moveUp();
                rotateBoardClockwise();
                rotateBoardClockwise();
                break;
            case 'a': // left
                moveLeft();
                mergeLeft();
                moveLeft();
                break;
            case 'd': // right
                rotateBoardClockwise();
                rotateBoardClockwise();
                rotateBoardClockwise();
                moveLeft();
                mergeLeft();
                moveLeft();
                rotateBoardClockwise();
                break;
            default:
                cout << "Invalid move! Use 'w', 'a', 's', 'd' to move." << endl;
                return;
        }
        if (isMoved) {
            addRandomTile();
        }
    }

    void play() {
        while (true) {
            drawBoard();
            char direction;
            cout << "Enter move (w: up, a: left, s: down, d: right): ";
            cin >> direction;
            move(direction);
            cout << endl;
        }
    }
};

int main() {
    Game2048 game;
    game.play();
    return 0;
}

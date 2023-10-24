#include <iostream>
#include <vector>

using namespace std;

class Board {
private:
    vector<vector<char> > grid;

public:
    Board(int size) {
        grid.resize(size, vector<char>(size, '-'));
    }

    void display() {
        for (const auto& row : grid) {
            for (char cell : row) {
                cout << cell << " ";
            }
            cout << endl;
        }
        // cout << endl;
    }

    bool placeMark(int row, int col, char mark) {
        if (row < 0 || row >= grid.size() || col < 0 || col >= grid.size() || grid[row][col] != '-') {
            cout << "Invalid Move" << endl;
            return false;
        }

        grid[row][col] = mark;
        return true;
    }

    bool checkWin(char mark) {
        for (const auto& row : grid) {
            bool win = true;
            for (char cell : row) {
                if (cell != mark) {
                    win = false;
                    break;
                }
            }
            if (win) return true;
        }

        // Check columns
        for (int col = 0; col < grid.size(); col++) {
            bool win = true;
            for (int row = 0; row < grid.size(); row++) {
                if (grid[row][col] != mark) {
                    win = false;
                    break;
                }
            }
            if (win) return true;
        }

        // Check diagonals
        bool win = true;
        for (int i = 0; i < grid.size(); i++) {
            if (grid[i][i] != mark) {
                win = false;
                break;
            }
        }
        if (win) return true;

        // Check reverse diagonals
        win = true;
        for (int i = 0; i < grid.size(); i++) {
            if (grid[i][grid.size() - 1 - i] != mark) {
                win = false;
                break;
            }
        }
        return win;        

    }

    bool isFull() {
        for (const auto& row : grid) {
            for (char cell : row) {
                if (cell == '-')
                    return false;
            }
        }
        return true;
    }
};

class Player {
private:
    char mark;
    string name;

public:
    Player(char m, string full_name) : mark(m), name(full_name) {}

    char getMark() {
        return mark;
    }

    string getName(){
        return name;
    }
    

    bool makeMove(Board& board, int row, int col) {
        return board.placeMark(row, col, mark);
    }
};

class Game {
private:
    Board board;
    Player player1;
    Player player2;
    Player* currentPlayer;

public:
    Game(int size, char mark1, string first_player, char mark2, string second_player) : board(size), player1(mark1, first_player), player2(mark2, second_player) {
        currentPlayer = &player1;
        board.display();
    }

    void switchPlayer() {
        if (currentPlayer == &player1) {
            currentPlayer = &player2;
        } else {
            currentPlayer = &player1;
        }
    }

    bool play(int row, int col) {
        if (currentPlayer->makeMove(board, row, col)) {
            board.display();
            if (board.checkWin(currentPlayer->getMark())) {
                cout << "Player " << currentPlayer->getName() << " wins!" << endl;
                return true;
            } else if (board.isFull()) {
                cout << "It's a draw!" << endl;
                return true;
            } else {
                switchPlayer();
            }
        }
        // cout << "Invalid Move" << endl;
        return false;
    }
};

int main() {

    char first, second;
    string first_player,second_player;
    
    cout << "Enter X/O and the First Player name" << endl;
    cin >> first >> first_player;
    cout << "Enter X/O and the Second Player name" << endl;
    cin >> second >> second_player;
    
    
    Game ticTacToe(3, first, first_player, second, second_player);
    int tests; 
    cout <<"Please enter number of moves" << endl;
    cin >> tests;
    cout << "Enter moves" << endl;
    for(int t = 0;t<tests; t++)
    {
        int i,j ;
        cin >> i >> j;
        bool game_complete = ticTacToe.play(i-1, j-1);
        if(game_complete)
            return 0;
    }
    return 0;
}

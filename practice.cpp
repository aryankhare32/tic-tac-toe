// #include <cstdlib>
// #include <csignal>
// #include <csetjmp>
// #include <cstdarg>
// #include <typeinfo>
// #include <typeindex>
// #include <type_traits>
// #include <bitset>
// #include <functional>
// #include <utility>
// #include <ctime>
// #include <chrono>
// #include <cstddef>
// #include <initializer_list>
// #include <tuple>
// #include <new>
// #include <memory>
// #include <scoped_allocator>
// #include <climits>
// #include <cfloat>
// #include <cstdint>
// #include <cinttypes>
// #include <limits>
// #include <exception>
// #include <stdexcept>
// #include <cassert>
// #include <system_error>
// #include <cerrno>
// #include <cctype>
// #include <cwctype>
// #include <cstring>
// #include <cwchar>
// #include <cuchar>
// #include <string>
// #include <array>
// #include <vector>
// #include <deque>
// #include <list>
// #include <forward_list>
// #include <set>
// #include <map>
// #include <unordered_set>
// #include <unordered_map>
// #include <stack>
// #include <queue>
// #include <algorithm>
// #include <iterator>
// #include <cmath>
// #include <complex>
// #include <valarray>
// #include <random>
// #include <numeric>
// #include <ratio>
// #include <cfenv>
// #include <iosfwd>
// #include <ios>
// #include <istream>
// #include <ostream>
// #include <iostream>
// #include <fstream>
// #include <sstream>
// #include <strstream>
// #include <iomanip>
// #include <streambuf>
// #include <cstdio>
// #include <locale>
// #include <clocale>
// #include <codecvt>
// #include <regex>
// #include <atomic>
// #include <thread>
// #include <mutex>
// #include <future>
// #include <condition_variable>
// #include <ciso646>
// #include <ccomplex>
// #include <ctgmath>
// #include <cstdbool>

#include<iostream>
#include<vector>

using namespace std;
class Board {
    private:
        vector<vector<char> > grid;
    
    public:
         Board (int size){
            grid.resize(size, vector<char> (size,'-'));
         }

        void displayBoard(){
            for(auto it: grid)
            {
                for(char ch: it)
                {
                    cout << ch << " ";
                }

                cout << endl;
            }
        }

        bool markBoard(int row, int col, char mark){
            int row_size = grid.size();
            int col_size = grid[0].size();
            if(row<0 || row>row_size || col<0 || col>col_size || grid[row][col] != '-'){
                cout << "Invalid Move, please try again!" << endl;
                return false;
            }else{
                grid[row][col] = mark;
                return true;
            }
        }

        bool checkWin(int row, int col, char mark){
            // IMPLEMENT LOGIC
            // We can also make other functions to check rows column diagonal and reverse diagonal logic
            // check row
            bool win = true;
            for (char cell : grid[row]) {
                if (cell != mark) {
                    win = false;
                    break;
                }
            }
            if (win) return true;

            // Check columns
                win = true;
                for (int row = 0; row < grid.size(); row++) {
                    if (grid[row][col] != mark) {
                        win = false;
                        break;
                    }
                }
                if (win) return true;
            // }

            // Check diagonals
            win = true;
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

        bool isFull(){
            for(auto it: grid)
            {
                for(char ch: it)
                {
                    if(ch == '-')
                        return false;
                }
            }
            return true;
        }
    
};

class Player {
    private:
        string name;
        char mark;
    
    public: 
        Player(string full_name, char m): name(full_name), mark(m) {}

        bool makeMove(Board &board, int row, int col){
                return board.markBoard(row, col, mark);
            }

        char getMark(){
            return mark;
        }    
        
        string getName(){
            return name;
        }
    };

class Game {
    private:
        Board board;
        Player player1;
        Player player2;
        Player * current_player;
    
    public:
        Game(int size, char mark1, string name1, char mark2, string name2): board(size), player1(name1, mark1), player2(name2, mark2) {
            current_player = &player1;
            board.displayBoard();
        }

        void switchPlayer(){
            if(current_player == &player1){
                current_player = &player2;
            }else{
                current_player = &player1;
            }
        }
        bool play(int row, int col){
            if(current_player->makeMove(board, row, col)){
                board.displayBoard();
                if(board.checkWin(row, col, current_player->getMark())){
                    cout << "Player " << current_player->getName() << " Wins!" << endl;
                    return true;
                } 
                else if(board.isFull()){
                    cout << "Match drawn" << endl;
                    return true;
                }
                else {
                    switchPlayer();
                    return false;
                }
            }else{
                return false;
            }
        }   
    };


int main(){

    int size  = 3;
    char mark1, mark2;
    string first_player, second_player;
    cout << "Enter first player's mark and name :" << endl;
    cin >> mark1 >> first_player;
    cout << "Enter second player's mark and name :" << endl;
    cin >> mark2 >> second_player;
    int possible_moves = size*size;

    Game tic_tac_toe(size, mark1, first_player, mark2, second_player);
    
    for(int i=0; i<possible_moves;i++)
    {
        int row, col;
        // string exit_string;
        // cout << "Please Enter 'exit' if you want to exit" << endl;
        // cin >> exit_string;
        // if(exit_string == "exit")
        //     return 0;
        cout << "Enter the next moves row number and column number:" << endl;
        cin >> row >> col;
        bool is_game_complete = tic_tac_toe.play(row-1,col-1);
        if(is_game_complete == true){
            return 0;
        }
    }

    return 0;

}
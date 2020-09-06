#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Board {

        int board[9][9]; // create a 2d matrix for the sudoku board

    public:

        Board(){
            for(int row=0;row<9;row++){
                for(int col=0;col<9;col++){
                    board[col][row] = 0;
                }
            }
        }

        void insertValue(int col, int row, int val){
            board[col][row] = val;
        }

        void printBoard(){
            string border = "-------------";
            for(int row=0;row<9;row++){
                if(row%3==0){
                    cout << border << endl;
                }
                for(int col=0;col<9;col++){
                    if(col%3==0){
                        cout << '|';
                    }
                    cout << board[col][row];
                }
                cout << '|' << endl;
            }
            cout << border << endl;
        }

        bool check_row(int x, int y, int val){
            for(int i=0;i<9;i++){
                if(i!=x){
                    if(board[i][y] == val){
                        return false;
                    }
                }
            }
            return true;
        }

        bool check_col(int x, int y, int val){
            for(int i=0;i<9;i++){
                if(i!=y){
                    if(board[x][i] == val){
                        return false;
                    }
                }
            }
            return true;
        }

        bool check_box(int x, int y, int val){
            int x_offset = x%3;
            int y_offset = y%3;
            for(int col = x-x_offset;col<x-x_offset+3;col++){
                for(int row = y-y_offset;row<y-y_offset+3;row++){
                    if(col!=x || row!=y){
                        if(board[col][row]==val){
                            return false;
                        }
                    }
                }
            }
            return true;
        }

        bool check_val(int x, int y, int val){
            return check_row(x,y,val) && check_col(x,y,val) && check_box(x,y,val);
        }

        bool solve(int x, int y){
            if(y>8) return true;
            if(board[x][y]!=0){
                if(x<8){
                    if(solve(x+1,y)){
                        return true;
                    }
                }
                else {
                    if(solve(0,y+1)){
                        return true;
                    }
                }
                return false;
            }
            for(int guess=1;guess<10;guess++){
                if(check_val(x,y,guess)){
                    board[x][y] = guess;
                    if(x<8){
                        if(solve(x+1,y)){
                            return true;
                        }
                    }
                    else {
                        if(solve(0,y+1)){
                            return true;
                        }
                    }
                }
            }
            board[x][y] = 0;
            return false;
        }
};

int main(int argc, char **argv){
    Board grid = Board();
    int x;
    int y;
    int val;
    while(cin>>x>>y>>val){
        grid.insertValue(x-1,y-1,val);
    }
    cout << "\nGiven Board:\n\n";
    grid.printBoard();
    grid.solve(0,0);
    cout << "\nSolved Board:\n\n";
    grid.printBoard();
}
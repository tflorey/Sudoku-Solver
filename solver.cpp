/* Sudoku Solver
Author: Trent Florey

This code receives x, y, and value triples of an unsolved sudoku board in stdin
and prints the given board to stdout. Then, it solves the sudoku board through a recursive solve
function where the base case is reaching the 10th row (outside of the bounds of the board).
Finally, the solved board is printed to stdout.
*/

#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Board { //class for the Sudoku grid with solver and check value methods

        int board[9][9]; // create a 2d matrix for the sudoku board

    public:

        Board(){ // when a board object is created, sets all values in the 2d matrix to 0
            for(int row=0;row<9;row++){
                for(int col=0;col<9;col++){
                    board[col][row] = 0; 
                }
            }
        }

        void insertValue(int col, int row, int val){ // method to set values in board at a row and column
            board[col][row] = val;
        }

        void printBoard(){ // method to print the board so it looks like a sudoku grid to the user
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

        bool check_row(int x, int y, int val){ // checks if val is found in the row of the cell provided by x and y
            for(int i=0;i<9;i++){
                if(i!=x){
                    if(board[i][y] == val){
                        return false;
                    }
                }
            }
            return true;
        }

        bool check_col(int x, int y, int val){ // checks if val is found in the col of the cell provided by x and y
            for(int i=0;i<9;i++){
                if(i!=y){
                    if(board[x][i] == val){
                        return false;
                    }
                }
            }
            return true;
        }

        bool check_box(int x, int y, int val){ // checks if val is found in the box of the cell provided by x and y
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

        bool check_val(int x, int y, int val){ // checks if the value meets all 3 conditions for the given cell
            return check_row(x,y,val) && check_col(x,y,val) && check_box(x,y,val);
        }

        bool solve(int x, int y){ // recursive solve function that iterates through each cell and backtracks when it reaches a "dead end"
            if(y>8) return true; // here is the base case
            if(board[x][y]!=0){ // ignore all cells that have been given values
                if(x<8){
                    if(solve(x+1,y)){ //recursive call moving across the row
                        return true;
                    }
                }
                else {
                    if(solve(0,y+1)){ //recursive call moving down to the next row if the end of the row has been reached
                        return true;
                    }
                }
                return false;
            }
            for(int guess=1;guess<10;guess++){ // loop through from 1 to 9 inclusive and check if the value is acceptable
                if(check_val(x,y,guess)){
                    board[x][y] = guess;
                    if(x<8){
                        if(solve(x+1,y)){ // recursive call moving across the row
                            return true;
                        }
                    }
                    else {
                        if(solve(0,y+1)){ // recursive call moving down to the next row
                            return true;
                        }
                    }
                }
            }
            board[x][y] = 0; // if no value is found reset the cell, return false, and backtrack to a new value in a previous call
            return false;
        }
};

int main(int argc, char **argv){
    Board grid = Board(); // create a new board object
    int x;
    int y;
    int val;
    while(cin>>x>>y>>val){ // take x, y, and value data from stdin
        grid.insertValue(x-1,y-1,val); //insert these values into the board object
    }
    cout << "\nGiven Board:\n\n"; 
    grid.printBoard(); //print the given board so the user can see whether input matched intended input
    grid.solve(0,0); // call solve on the given board
    cout << "\nSolved Board:\n\n";
    grid.printBoard(); // print the solved board for the final product
}
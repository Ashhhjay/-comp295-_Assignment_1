#include <iostream>


using namespace std;

const int ROW = 4;
const int COL = 4;
int board[ROW][COL] = {0};
int score = 0;
int high_score = 0;

void printBoard() {
	cout<<"\n\t\tPress \"w\" to go UP, \"s\" to go DOWN, \"a\" to go LEFT, \"d\" to go RIGHT\n";    
	cout<<"\t\tPress Esc anytime to quit the game\n\n\n";
	cout<<"\n\t\t\t\t\t\t\t\t\t"<<"Score = " << score << "   High Score: " << high_score << endl;;
	cout<<"\t\t\t\t\t";
    cout << "+------+------+------+------+" << endl;
    for (int i = 0; i < ROW; i++) {
    	cout<<"\t\t\t\t\t";
        for (int j = 0; j < COL; j++) {
            cout << "|";
            if (board[i][j] == 0) {
                cout << "      ";
            } else {
                cout << setw(6) << board[i][j];
            }
        }
        cout << "|" << endl;
        cout<<"\t\t\t\t\t";
        cout << "+------+------+------+------+" << endl;
    }
}

void initializeBoard() {
    srand(time(NULL));
    // add two random tiles to the board with different values
    int row1, col1, row2, col2;
    do {
        row1 = rand() % ROW;
        col1 = rand() % COL;
        row2 = rand() % ROW;
        col2 = rand() % COL;
    } while (board[row1][col1] != 0 || board[row2][col2] != 0 || (row1 == row2 && col1 == col2));
    
    board[row1][col1] = (rand() % 2 + 1) * 2;  // randomly set the value to 2 or 4
    board[row2][col2] = (rand() % 2 + 1) * 2;  // randomly set the value to 2 or 4, but different from the first tile
}


int main(){
	initializeBoard();
	printboard();
}

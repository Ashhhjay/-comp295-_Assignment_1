#include <iostream>
#include <cstdlib>
#include <ctime>
#include <conio.h>
#include <iomanip>

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


void clearBoard() {
    for (int i = 0; i < ROW; i++) {
        for (int j = 0; j < COL; j++) {
            board[i][j] = 0;
        }
    }
}


void addPiece() {
    // generate a random position
    int r, c;
    do {
        r = rand() % 4;
        c = rand() % 4;
    } while (board[r][c] != 0);
    // generate a random value (2 or 4)
    int value = (rand() % 2 + 1) * 2;
    // set the tile value
    board[r][c] = value;
}

void upmove() {
    bool moved = false;
    for (int j = 0; j < COL; j++) {
        int firstRow = 0;
        for (int i = 1; i < ROW; i++) {
            if (board[i][j] != 0) {
                if (board[firstRow][j] == 0 ) {
                    board[firstRow][j] += board[i][j];
                    board[i][j] = 0;
                    moved = true;
                }
                else if (board[firstRow][j] == board[i][j]) {
                    board[firstRow][j] += board[i][j];
                    board[i][j] = 0;
                    moved = true;
                    score += board[firstRow][j];
                } else {
                    firstRow++;
                    board[firstRow][j] = board[i][j];
                    if (i != firstRow) {
                        board[i][j] = 0;
                        moved = true;
                    }
                }
            }
        }
    }
    if (moved) {
        addPiece();
    }
}

void downmove() {
    bool moved = false;
    for (int j = 0; j < COL; j++) {
        int lastRow = ROW - 1;
        for (int i = ROW - 2; i >= 0; i--) {
            if (board[i][j] != 0) {
                if (board[lastRow][j] == 0) {
                    board[lastRow][j] += board[i][j];
                    board[i][j] = 0;
                    moved = true;
                }
                else if (board[lastRow][j] == board[i][j]) {
                    board[lastRow][j] += board[i][j];
                    board[i][j] = 0;
                    moved = true;
                    score += board[lastRow][j];
                } else {
                    lastRow--;
                    board[lastRow][j] = board[i][j];
                    if (i != lastRow) {
                        board[i][j] = 0;
                        moved = true;
                    }
                }
            }
        }
    }
    if (moved) {
        addPiece();
    }
}

void leftmove() {
    bool moved = false;
    for (int i = 0; i < ROW; i++) {
        int lastCol = 0;
        for (int j = 1; j < COL; j++) {
            if (board[i][j] != 0) {
                if (board[i][lastCol] == 0) {
                    board[i][lastCol] += board[i][j];
                    board[i][j] = 0;
                    moved = true;
                }
                else if (board[i][lastCol] == board[i][j]) {
                    board[i][lastCol] += board[i][j];
                    board[i][j] = 0;
                    moved = true;
                    score += board[i][lastCol];
                } else {
                    lastCol++;
                    board[i][lastCol] = board[i][j];
                    if (j != lastCol) {
                        board[i][j] = 0;
                        moved = true;
                    }
                }
            }
        }
    }
    if (moved) {
        addPiece();
    }
}

void rightmove() {
    bool moved = false;
    for (int i = 0; i < ROW; i++) {
        int lastCol = COL-1;
        for (int j = COL-2; j >= 0; j--) {
            if (board[i][j] != 0) {
                if (board[i][lastCol] == 0) {
                    board[i][lastCol] += board[i][j];
                    board[i][j] = 0;
                    moved = true;
                }
                else if (board[i][lastCol] == board[i][j]) {
                    board[i][lastCol] += board[i][j];
                    board[i][j] = 0;
                    moved = true;
                    score += board[i][lastCol];
                } else {
                    lastCol--;
                    board[i][lastCol] = board[i][j];
                    if (j != lastCol) {
                        board[i][j] = 0;
                        moved = true;
                    }
                }
            }
        }
    }
    if (moved) {
        addPiece();
    }
}


bool check_game_over() {
    for (int i = 0; i < ROW-1; i++) {
        for (int j = 0; j < COL-1; j++) {
            if (board[i][j] == 0 || board[i][j+1] == 0) {
                return false;
            }
            if (board[i][j] == board[i+1][j])
                return false;
            if (board[i][j] == board[i][j+1])
                return false;
            if (board[i][j] == 2048 || board[i+1][j] == 2048 || board[i][j+1] == 2048 || board[i+1][j+1] == 2048) {
                cout << "Congratulations! You won!" << endl;
                return true;
            }
        }
    }
    return true;
}
void playGame(){
	system("cls");
    initializeBoard();
    printBoard();
    char move;
    while (1) {
        move = getch();
        if (move == 'w' || move == 'W') {
            upmove();
        } else if (move == 's' || move == 'S') {
            downmove();
        } else if (move == 'a' || move == 'A') {
            leftmove();
        } else if (move == 'd' || move == 'D') {
            rightmove();
        } else if (move == 27) {
            cout << "Game over!" << endl;
            break;
        } else {
            cout << "Invalid move!" << endl;
            continue;
        }
        system("cls");
        printBoard();
        
        if (high_score < score) {
            high_score = score;
                    
        }
        // check for game over
        if (check_game_over()) {
            cout << "Game over! Final score: " << score << endl;
                if (score > high_score) {
                    high_score = score;
                    cout << "New high score: " << high_score << endl;
                }
            break;
        }
    }
}




int main() {
    cout << "*************************************************Welcome to the game****************************************************\n";
    char choice;
    while (true) {
    	cout << "(a) Play Game\n";
    	cout << "(b) Quit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        if (choice == 'a' || choice == 'A') {
            playGame();
            break;
        } else if (choice == 'b' || choice == 'B') {
            cout << "Goodbye!\n";
            exit(0);
        } else {
	        cout << "Invalid input, please enter 'a' or 'b'.\n";
	   	}
	}
    
    char askagain;
    while (true) {
    	cout << "Play again? (y/n): ";
        cin >> askagain;
        if (askagain == 'y' || askagain == 'Y') {
            // Reset game variables and game board
            clearBoard();
            score = 0;
            playGame();
            
        } else if (askagain == 'n' || askagain == 'N') {
        	cout << "High score: " << high_score << endl;
            cout<< "Thank you for playing the game(RANG BAAZ).";
            break;
        } else {
            cout << "Invalid input. Please enter 'y' or 'n'.\n";
            continue;
        }
    }

    return 0;
}


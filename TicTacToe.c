#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

const char PLAYER = 'X';
const char COMPUTER = 'O';
char board[3][3];

void resetBoard();
void printBoard();
int checkSpaces();
void PlayerMove();
void ComputerMove();
char checkWinner();
void printWinner(char winner);

int main(){
    srand(time(0));  // Seed random number generator once
    char winner = ' ';
    resetBoard();

    while(winner == ' ' && checkSpaces() > 0){  
        printBoard();
        PlayerMove();
        winner = checkWinner();
        if(winner != ' ' || checkSpaces() == 0){  
            break;
        }
        ComputerMove();
        winner = checkWinner();
        if(winner != ' ' || checkSpaces() == 0){  
            break;
        }
    }
    printBoard();
    printWinner(winner);
    return 0;
}

void resetBoard(){
    for(int i=0; i<3; i++){
        for(int j=0; j<3; j++){
            board[i][j] = ' ';
        }
    }
}

void printBoard(){
    for(int i=0; i<3; i++){
        printf(" %c | %c | %c \n", board[i][0], board[i][1], board[i][2]);
        if(i < 2) printf("---|---|---\n");
    }
}

int checkSpaces(){
    int freeSpaces = 0;
    for(int i=0; i<3; i++){
        for(int j=0; j<3; j++){
            if(board[i][j] == ' '){
                freeSpaces++;
            }
        }
    }
    return freeSpaces;
}

void PlayerMove(){
    int x, y;
    do{       
        printf("Enter Row and Column (1-3 1-3): ");
        scanf("%d %d", &x, &y);
        x--; y--;
        if(x < 0 || x >= 3 || y < 0 || y >= 3){
            printf("INVALID MOVE! Out of bounds. Try again.\n");
        }
        else if(board[x][y] != ' '){
            printf("INVALID MOVE! Cell occupied. Try again.\n");
        }
        else{
            board[x][y] = PLAYER;
            break;
        }
    }while (1);    
}

void ComputerMove(){
    int x, y;
    if(checkSpaces() > 0){
        do{
            x = rand() % 3;
            y = rand() % 3;
        }while (board[x][y] != ' '); 
        board[x][y] = COMPUTER;
    }
}

char checkWinner(){
    for(int i=0; i<3; i++){
        if(board[0][i] != ' ' && board[0][i] == board[1][i] && board[0][i] == board[2][i]){
            return board[0][i];                    
        }
        if(board[i][0] != ' ' && board[i][0] == board[i][1] && board[i][0] == board[i][2]){
            return board[i][0];                    
        }
    }

    // Check main diagonal
    if(board[0][0] != ' ' && board[0][0] == board[1][1] && board[0][0] == board[2][2]){
        return board[0][0];
    }

    // Check anti-diagonal
    if(board[0][2] != ' ' && board[0][2] == board[1][1] && board[0][2] == board[2][0]){
        return board[0][2];
    }

    return ' ';
}

void printWinner(char winner){
    if(winner == PLAYER){
        printf("!!!You Win!!!\n");
    }
    else if(winner == COMPUTER){
        printf("...Computer Wins...\n");
    }
    else{
        printf("---TIE---\n");
    }
}



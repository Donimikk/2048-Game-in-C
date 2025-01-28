#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <unistd.h>

void print_grid(int **grid, int size) {
    system("clear || cls");
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size*4+1; j++) {
            printf("-");
        }
        printf("\n");
        for(int j = 0; j < size; j++) {
            printf("|");
            if(grid[i][j]==0){
                printf("   ");
            }else{
                printf(" %d ",grid[i][j]);
            }
        }
        printf("|\n");
    }
    for (int j = 0; j < size*4+1; j++) {
        printf("-");
    }
    printf("\n");
}

void free_grid(int **grid, int size) {
    for (int i = 0; i < size; i++) {
        free(grid[i]);
    }
    free(grid);
}

void add_number(int **grid, int size, int score) {
    int i,j;
    int value = rand() % 10;
    do{
        i = rand() % size;
        j = rand() % size;
    }while (grid[i][j] != 0);
    grid[i][j] = (value == 1) ? 4 : 2;
    if(score==-1){
        add_number(grid,size,score+1);
    }
}
int move_left(int **grid, int size){
    int score=0;
    for (int i = 0; i < size; i++) {
        for (int j = 1; j < size; j++) {
            if (grid[i][j] != 0) {
                //jj=j
                for (int jj = j; jj > 0; jj--) {
                    if (grid[i][jj - 1] == grid[i][j]) {
                        score += grid[i][j] * 2;
                        grid[i][jj - 1] *= 2;
                        grid[i][j] = 0;
                        break;
                    }
                }
            }
        }
    }
    //MOVEMENT
    for (int i = 0; i < size; i++) {
        for (int j = 1; j < size; j++) {
            if (grid[i][j] != 0) {
                for (int jj = 0; jj < j; jj++) {
                    if (grid[i][jj] == 0) {
                        grid[i][jj] = grid[i][j];
                        grid[i][j] = 0;
                        break;
                    }
                }
            }
        }
    }
    return score;
}
int move_right(int **grid, int size){
    int score=0;
    //NUMBERS COLLIDE
    for (int i = 0; i < size; i++) {
        for (int j = size - 2; j >= 0; j--) {
            if (grid[i][j] != 0) {
                //jj=j;
                for (int jj = j; jj < size; jj++) {
                    if (grid[i][jj + 1] == grid[i][j]) {
                        score += grid[i][j] * 2;
                        grid[i][jj + 1] *= 2;
                        grid[i][j] = 0;
                        break;
                    }
                }
            }
        }
    }
    //MOVEMENT
    for (int i = 0; i < size; i++) {
        for (int j = 1; j < size; j++) {
            if (grid[i][j] != 0) {
                for (int jj = size - 1; jj > 0; jj--) {
                    if (grid[i][jj] == 0) {
                        grid[i][jj] = grid[i][j];
                        grid[i][j] = 0;
                        break;
                    }
                }
            }
        }
    }
    return score;
}
int move_up(int **grid, int size){
    int score=0;
    //NUMBERS COLLIDE
    for (int j = 0; j < size; ++j) {
        for (int i = 1; i < size; i++) {
            if (grid[i][j] != 0) {
                for (int ii = i; ii >= 0; ii--) {
                    if (grid[ii][j] == grid[i][j]) {
                        score += grid[i][j] * 2;
                        grid[ii][j] *= 2;
                        grid[i][j] = 0;
                        break;
                    }
                }
            }
        }
    }
    //MOVEMENT
    for (int j = 0; j < size; ++j) {
        for (int i = 1; i < size; i++) {
            if (grid[i][j] != 0) {
                for (int ii = i; ii >= 0; ii--) {
                    if (grid[ii][j] == 0) {
                        grid[ii][j] = grid[i][j];
                        grid[i][j] = 0;
                        break;
                    }
                }
            }
        }
    }
    return score;
}
int move_down(int **grid, int size){
    int score = 0;
    //NUMBERS COLLIDE
    for (int j = 0; j < size; ++j) {
        for (int i = size - 2; i >= 0; i--) {
            if (grid[i][j] != 0) {
                for (int ii = i; ii < size; ii++) {
                    if (grid[ii][j] == grid[i][j]) {
                        score += grid[i][j] * 2;
                        grid[ii][j] *= 2;
                        grid[i][j] = 0;
                        break;
                    }
                }
            }
        }
    }
    //MOVEMENT
    for (int j = 0; j < size; ++j) {
        for (int i = size - 2; i >= 0; i--) {
            if (grid[i][j] != 0) {
                for (int ii = i; ii < size; ii++) {
                    if (grid[ii][j] == 0) {
                        grid[ii][j] = grid[i][j];
                        grid[i][j] = 0;
                        break;
                    }
                }
            }
        }
    }
    return score;
}
int movement(int **grid, int size, int dir) {
    //MOVE LEFT
    if (dir == 0) {
        return move_left(grid,size);
    }
    //MOVE RIGHT
    if (dir == 2) {
        return move_right(grid,size);
    }
    //MOVE UP
    if (dir == 1) {
        return move_up(grid,size);
    }
    //MOVE DOWN
    if (dir == 3) {
        return move_down(grid,size);
    }
    return 1;
}
int win(int **grid,int size){
    for(int i =0;i<size;i++){
        for(int j = 0; j<size;j++){
            if(grid[i][j]==2048){
                return 0;
            }
        }
    }
    return 1;
}
int lose(int **grid,int size){
    for(int i =0;i<size;i++){
        for(int j = 0; j<size;j++){
            if(grid[i][j]==0){
                return 0;
            }
        }
    }
    return 1;
}
void game(int **grid,int size){
    int score=-1;
    char x;
    add_number(grid,size,score);
    score=0;
    while(win(grid,size)){
        print_grid(grid,size);
        scanf("%c",&x);
        switch (tolower(x)) {
            case 'u':{
                score+=movement(grid,size,1);
                break;
            }
            case 'd':{
                score+=movement(grid,size,3);
                break;
            }
            case 'l':{
                score+=movement(grid,size,0);
                break;
            }
            case 'r':{
                score+=movement(grid,size,2);
                break;
            }
            default:{
                printf("Wrong input! Try again:");
                sleep(2);
                break;
            }
        }
        if(!lose(grid,size)){
            add_number(grid,size,score);
        }else{
            print_grid(grid,size);
            printf("YOU LOST!");
            break;
        }
    }
}
int main(){
    srand(time(NULL));
    printf("Hello, choose size of the game(4-9): ");
    int size,score=-1;
    do{
        scanf("%d",&size);
    }while(size<4||size>9);
    int **board = malloc(size*sizeof(int*));
    if(board==NULL){
        printf("Error allocating memory for board\n");
        return 1;
    }
    for(int i=0;i<size;i++){
        board[i]=malloc(size*sizeof(int));
        if(board[i]==NULL){
            printf("Error allocating memory for board\n");
            for(int j=0;j<i;j++){
                free(board[j]);
            }
            free(board);
            return 1;
        }
    }
    for(int i=0;i<size;i++){
        for(int j=0;j<size;j++){
            board[i][j]=0;
        }
    }
    add_number(board, size, score);
    print_grid(board,size);
    score=0;
    movement(board,size,0);

    print_grid(board,size);


    free_grid( board, size);
    return 0;


}
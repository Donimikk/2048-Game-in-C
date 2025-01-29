#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <fcntl.h>
#include <stdbool.h>

void print_grid(int **grid, int size,int score, int best);
void free_grid(int **grid, int size);

void add_number(int **grid, int size, int score);
int move_left(int **grid, int size);
int move_right(int **grid, int size);
int move_up(int **grid, int size);
int move_down(int **grid, int size);
int movement(int **grid, int size, int dir);
int win(int **grid,int size);
int lose(int **grid,int size);
void clean_grid(int **grid,int size);
int game(int **grid,int size,int best);
int main(){
    srand(time(NULL));
    printf("Hello, choose size of the game(4-9): ");
    int size;
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
    clean_grid(board, size);

    int scoreboard = open("score.txt", O_RDWR | O_CREAT, 0666 );
    if(scoreboard==-1){
        printf("Error opening scoreboard\n");
        //close(scoreboard);
        free_grid(board,size);
        return 1;
    }
    int bestscore = 0;
    if (read(scoreboard, &bestscore, sizeof(int)) != sizeof(int)) {
        bestscore = 0;  // Initialize if read fails
    }

    int score = game(board, size, bestscore);
    if (score > bestscore) {
        lseek(scoreboard, 0, SEEK_SET);
        write(scoreboard, &score, sizeof(int));  // Write the new high score
    }
    free_grid( board, size);
    close(scoreboard);
    return 0;
}
void print_grid(int **grid, int size,int score, int best) {
    system("clear || cls");
    char offset;
    printf("\n\n\t\t2048 GAME");
    printf("\n=========================================\n"
           "YOUR SCORE: %d\n"
           "BEST SCORE: %d\n",score,best);

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
    printf("QUIT-> q\n"
           "RESTART-> r\n"
           "MOVEMENT-> wasd\n");
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
    //MOVEMENT
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
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
    //TILE MERGE
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size-1; j++) {
            if (grid[i][j] != 0) {
                if(grid[i][j]==grid[i][j+1]){
                    score+=grid[i][j]*2;
                    grid[i][j]*=2;
                    grid[i][j+1]=0;
                    for(int x=j+1;x<size-1;x++){
                        grid[i][x]=grid[i][x+1];
                    }
                }
            }
        }
    }
    return score;
}
int move_right(int **grid, int size){
    int score=0;
    //MOVEMENT
    for (int i = 0; i < size; i++) {
        for (int j = size - 1; j >= 0; j--) {
            if (grid[i][j] != 0) {
                for (int jj = size - 1; jj > j; jj--) {
                    if (grid[i][jj] == 0) {
                        grid[i][jj] = grid[i][j];
                        grid[i][j] = 0;
                        break;
                    }
                }
            }
        }
    }
    //NUMBERS COLLIDE
    for (int i = 0; i < size; i++) {
        for (int j = size - 1; j >= 0; j--) {
            if (grid[i][j] != 0) {
                if(grid[i][j]==grid[i][j-1]){
                    score+=grid[i][j]*2;
                    grid[i][j]*=2;
                    grid[i][j-1]=0;
                    for(int x=j-1;x>0;x--){
                        grid[i][x]=grid[i][x-1];
                    }
                }
            }
        }
    }
    return score;
}
int move_up(int **grid, int size){
    int score=0;
    //MOVEMENT
    for (int j = 0; j < size; ++j) {
        for (int i = 0; i < size; i++) {
            if (grid[i][j] != 0) {
                for (int ii = 0; ii < i; ii++) {
                    if (grid[ii][j] == 0) {
                        grid[ii][j] = grid[i][j];
                        grid[i][j] = 0;
                        break;
                    }
                }
            }
        }
    }
    //NUMBERS COLLIDE
    for (int j = 0; j < size; ++j) {
        for (int i = 0; i < size-1; i++) {
            if (grid[i][j] != 0) {
                if(grid[i][j]==grid[i+1][j]){
                    score+=grid[i][j]*2;
                    grid[i][j]*=2;
                    grid[i+1][j]=0;
                    for(int x=i+1;x<size-1;x++){
                        grid[x][j]=grid[x+1][j];
                    }
                }
            }
        }
    }
    return score;
}
int move_down(int **grid, int size){
    int score = 0;
    //MOVEMENT
    for (int j = 0; j < size; ++j) {
        for (int i = size - 1; i >= 0; i--) {
            if (grid[i][j] != 0) {
                for (int ii = size-1; ii > i; ii--) {
                    if (grid[ii][j] == 0) {
                        grid[ii][j] = grid[i][j];
                        grid[i][j] = 0;
                        break;
                    }
                }
            }
        }
    }
    //NUMBERS COLLIDE
    for (int j = 0; j < size; ++j) {
        for (int i = size - 1; i > 0; i--) {
            if (grid[i][j] != 0) {
                if(grid[i][j]==grid[i-1][j]){
                    score+=grid[i][j]*2;
                    grid[i][j]*=2;
                    grid[i-1][j]=0;
                    for(int x=i-1;x>0;x--){
                        grid[x][j]=grid[x-1][j];
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
                return 1;
            }
        }
    }
    return 0;
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
void clean_grid(int **grid,int size){
    for(int i=0;i<size;i++){
        for(int j=0;j<size;j++){
            grid[i][j]=0;
        }
    }
}
int game(int **grid,int size,int best){
    int score=-1;
    char x;
    add_number(grid,size,score);
    score=0;
    while(!win(grid,size)) {
        print_grid(grid, size,score,best);
        printf("CHOOSE DIRECTION: ");
        scanf(" %c", &x);

        bool def;
        do {
            def=0;
            switch (tolower(x)) {
                case 'w': {
                    score += movement(grid, size, 1);
                    break;
                }
                case 's': {
                    score += movement(grid, size, 3);
                    break;
                }
                case 'a': {
                    score += movement(grid, size, 0);
                    break;
                }
                case 'd': {
                    score += movement(grid, size, 2);
                    break;
                }
                case 'q': {
                    print_grid(grid, size, score,best);
                    printf("THANKS FOR PLAYING!\nYOUR FINAL SCORE: %d", score);
                    return score;
                }
                case 'r': {
                    clean_grid(grid, size);
                    score=-1;
                    break;
                }
                default: {
                    print_grid(grid, size, score,best);
                    printf("WRONG INPUT, TRY AGAIN: ");
                    scanf(" %c", &x);
                    def=1;
                    break;
                }
            }
        }while(def);
        if (!lose(grid, size)) {
            add_number(grid, size, score);
            if(score == -1){
                score=0;
            }
        } else {
            print_grid(grid, size,score,best);
            printf("YOU LOST!\nYOUR FINAL SCORE: %d", score);
            return score;
        }
    }
    print_grid(grid,size,score,best);
    printf("YOU WON!\nYOUR FINAL SCORE: %d",score);
    return score;
}
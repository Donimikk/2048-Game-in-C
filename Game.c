#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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

int movement(int **grid, int size, int dir) {
    //MOVE LEFT
    int jj, ii, score = 0;
    if (dir == 0) {
        //NUMBERS COLLIDE
        for (int i = 0; i < size; i++) {

            for (int j = 1; j < size; j++) {

                if (grid[i][j] != 0) {
                    //jj=j;
                    for (jj = j; jj > 0; jj--) {

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
                    for (jj = 0; jj < j; jj++) {
                        if (grid[i][jj] == 0) {
                            grid[i][jj] = grid[i][j];
                            grid[i][j] = 0;
                            break;
                        }
                    }
                }
            }
        }
    }

    //MOVE RIGHT
    if (dir == 2) {
        //NUMBERS COLLIDE
        for (int i = 0; i < size; i++) {

            for (int j = size-2; j >= 0; j--) {

                if (grid[i][j] != 0) {
                    //jj=j;
                    for (jj = j; jj < size; jj++) {

                        if (grid[i][jj +1] == grid[i][j]) {
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
                    for (jj = size-1; jj > 0; jj--) {
                        if (grid[i][jj] == 0) {
                            grid[i][jj] = grid[i][j];
                            grid[i][j] = 0;
                            break;
                        }
                    }
                }
            }
        }
    }

    //MOVE UP
    if(dir == 1){
        //NUMBERS COLLIDE
        for (int j = 0; j < size; ++j) {
            for(int i = 1; i<size;i++){
                if(grid[i][j]!=0){
                    for(ii=i;ii>=0;ii--){
                        if(grid[ii][j]==grid[i][j]){
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
            for(int i = 1; i<size;i++){
                if(grid[i][j]!=0){
                    for(ii=i;ii>=0;ii--){
                        if(grid[ii][j]==0){
                            grid[ii][j] = grid[i][j];
                            grid[i][j]=0;
                            break;
                        }
                    }
                }
            }
        }
    }
    if(dir == 3){
        //NUMBERS COLLIDE
        for (int j = 0; j < size; ++j) {
            for(int i = size-2; i>=0;i--){
                if(grid[i][j]!=0){
                    for(ii=i;ii<size;ii++){
                        if(grid[ii][j]==grid[i][j]){
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
            for(int i = size-2; i>=0;i--){
                if(grid[i][j]!=0){
                    for(ii=i;ii<size;ii++){
                        if(grid[ii][j]==0){
                            grid[ii][j] = grid[i][j];
                            grid[i][j]=0;
                            break;
                        }
                    }
                }
            }
        }
    }
    return score;
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
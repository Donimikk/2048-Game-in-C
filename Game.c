#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void print_grid(int **grid, int size) {
    //system("clear || cls");
    system("cls >nul 2>&1 || clear >nul 2>&1");
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
                        }

                    }

                }

            }

        }
        //MOVEMENT
        for (int i = 0; i < size; i++) {
            for (int j = 1; j < size; j++) {
                if (grid[i][j] != 0) {

                }
            }
        }
    }

    return score;
}

int main(){
    srand(time(NULL));
    printf("Hello, choose size of the game(4-9): ");
    int size,score=0;
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
    system("cls");
    print_grid(board,size);
    add_number(board, size, score);


    free_grid( board, size);
    return 0;


}
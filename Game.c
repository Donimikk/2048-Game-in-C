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


int main(){
    printf("Hello, choose size of the game(4-9): ");
    int size=10;
    while(size<4||size>9){
        scanf("%d",&size);
    }
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
    free_grid( board, size);

    return 0;


}
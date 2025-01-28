#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void print_grid(int **grid, int size) {

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            printf("____");
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
    for (int j = 0; j < size; j++) {
        printf("____");
    }
    printf("\n");
}

int main(){
    printf("Hello, choose size of the game(4-9)\n");
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
    print_grid(board,size);


}
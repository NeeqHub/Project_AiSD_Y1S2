#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define N 8

// This function checks that the next move is correct
bool isGood(int x, int y, int tab[N][N])
{
     if(x >= 0 && x < N && y >= 0 && y < N && tab[x][y] == -99)
        return true;
     else
        return false;
}

/* After finding a solution function show on screen a chessboard with
   numbers of movements */
void printSolution(int tab[N][N])
{
    for(int i=0; i<N; i++)
    {
        for(int j=0; j<N; j++)
            printf(" [%d] ",tab[i][j]);

        printf("\n");
    }
}

bool tryFind(int mov_i, int *x, int *y, int tab[N][N])
{
    // Variable contains next move on X axis
    int nx = 0;

    // Variable contains next move on Y axis
    int ny = 0;

    if(mov_i == N*N)
        return true;

    int i;
    // Checks all possible movements
    for(i=0; i<N; i++)
    {
        switch(i)
        {
            case 0: nx = *x+2;
                ny = *y+1;
                break;
            case 1: nx = *x+1;
                ny = *y+2;
                break;
            case 2: nx = *x-1;
                ny = *y+2;
                break;
            case 3: nx = *x-2;
                ny = *y+1;
                break;
            case 4: nx = *x-2;
                ny = *y-1;
                break;
            case 5: nx = *x-1;
                ny = *y-2;
                break;
            case 6: nx = *x+1;
                ny = *y-2;
                break;
            case 7: nx = *x+2;
                ny = *y-1;
                break;
    }

        if(isGood(nx,ny,tab))
        {
            tab[nx][ny] = mov_i;

            if(tryFind(mov_i+1,&nx,&ny,tab)==true)
                return true;
            else
                tab[nx][ny] = -99;
        }

    }
    return false;
}

// Function using tryFind() function determinate that the problem can be solved
bool findSolution(int *x_pos, int *y_pos, int szachownica[N][N])
{
    szachownica[*x_pos][*y_pos] = 0;

    if(tryFind(1,x_pos, y_pos, szachownica)==false)
    {
        printf("Brak rozwiązania.");
        return false;
    }
    else
        printSolution(szachownica);

    return true;
}

int main()
{
    int szachownica[N][N];

    int i,j;
    // Draws the chessboard
    for(i=0; i<N; i++)
    {
        for(j=0; j<N; j++)
        {
            szachownica[i][j]= -99;
            printf("[  ]");
        }


        printf("\n");
    }

    int x = 0;
    int y = 0;

    printf("Podaj miejsce startu konika x: ");
    scanf("%d",&x);
    printf("Podaj miejsce startu konika y: ");
    scanf("%d",&y);

    findSolution(&x,&y,szachownica);

    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <windows.h>
#include <time.h>
#define N 8

int sizeChessboard = 0;
int amountOfMoves = 0;
int amountOfWholeMoves = 0;

bool isGood(int x, int y, int tab[sizeChessboard][sizeChessboard])
{
     if(x >= 0 && x < sizeChessboard && y >= 0 && y < sizeChessboard && tab[x][y] == -1)
        return true;
     else
        return false;
}

void printSolution(int tab[sizeChessboard][sizeChessboard], int mov_i)
{
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);


    printf("------------------------------------------------------------------------------------------------------------------------------------ \n");
    for(int i=0; i<sizeChessboard; i++)
    {
        for(int j=0; j<sizeChessboard; j++)
        {
            if(tab[i][j] == mov_i)
            {
                SetConsoleTextAttribute(hStdOut,10);
                printf("[%*d]",3,tab[i][j]);
            }
            else if(tab[i][j] < mov_i && tab[i][j] > -1)
            {
                SetConsoleTextAttribute(hStdOut,9);
                printf("[%*d]",3,tab[i][j]);
            }
            else
            {
                SetConsoleTextAttribute(hStdOut,7);
                printf("[%*d]",3,tab[i][j]);
            }
        }


        printf("\n");
    }
    SetConsoleTextAttribute(hStdOut,7);
    printf("------------------------------------------------------------------------------------------------------------------------------------ \n");
}

void printSolutionAuto(int tab[sizeChessboard][sizeChessboard])
{
    printf("------------------------------------------------------------------------------------------------------------------------------------ \n");
    for(int i=0; i<sizeChessboard; i++)
    {
        for(int j=0; j<sizeChessboard; j++)
            printf("[%*d]",3,tab[i][j]);

        printf("\n");
    }
    printf("------------------------------------------------------------------------------------------------------------------------------------ \n");
}

int tryFind(int mov_i, int x, int y, int tab[sizeChessboard][sizeChessboard],int choice)
{
    // Variable contains next move on X axis
    int nx = 0;

    // Variable contains next move on Y axis
    int ny = 0;

    if(mov_i == sizeChessboard * sizeChessboard)
        return true;

    if(choice == 2)
    {
        printSolution(tab,mov_i-1);
    }

    if(choice == 3)
    {
        int m = 0;
        printSolution(tab,mov_i-1);
        printf("[!0] Kontynuacja \n");
        printf(" [0] Wyjscie \n");
        scanf("%d",&m);

        if(m == 0)
            exit(0);
    }


    int i;
    // Checks all possible movements
    for(i=0; i<8; i++)
    {
        switch(i)
        {
            case 0: nx = x+2;
                ny = y+1;
                break;
            case 1: nx = x+1;
                ny = y+2;
                break;
            case 2: nx = x-1;
                ny = y+2;
                break;
            case 3: nx = x-2;
                ny = y+1;
                break;
            case 4: nx = x-2;
                ny = y-1;
                break;
            case 5: nx = x-1;
                ny = y-2;
                break;
            case 6: nx = x+1;
                ny = y-2;
                break;
            case 7: nx = x+2;
                ny = y-1;
                break;
    }

    amountOfWholeMoves++;

    if(isGood(nx,ny,tab))
    {
        amountOfMoves ++;

        tab[nx][ny] = mov_i;

        if(tryFind(mov_i+1,nx,ny,tab, choice)==true)
            return true;
        else
            tab[nx][ny] = -1;
    }
    }
    return 0;
}

bool findSolution(int x_pos, int y_pos, int chessBoard[sizeChessboard][sizeChessboard],int choice)
{
    chessBoard[x_pos][y_pos] = 0;

    if(tryFind(1,x_pos, y_pos, chessBoard,choice)==false)
    {
        printf("Brak rozwiazania. \n");
        return false;
    }
    else
    {
        printSolutionAuto(chessBoard);
    }

    return true;
}

static int cx[N]={1,1,2,2,-1,-1,-2,-2};
static int cy[N]={2,-2,1,-1,2,-2,1,-1};

int limits(int *a, int x, int y)
{
    if((x>=0 && y>=0) && (x<sizeChessboard && y<sizeChessboard))
        return 1;
    return 0;
}

int isempty(int *a, int x, int y)
{
    if((limits(a,x,y)) && (a[y*sizeChessboard+x]<0))
        return 1;
    return 0;
}

int getcount(int *a, int x, int y)
{
    int i,count=0;
    for(i=0;i<N;++i)
    {
        if(isempty(a,(x+cx[i]),(y+cy[i])))
            count++;
    }
    return count;
}

int progress(int *a, int *x, int *y)
{
    int start,count,i,flag=-1,c,min=(N+1),nx,ny;
    start = rand()%N;
    for(count=0;count<N;++count)
    {
        i=(start+count)%N;
        nx=*x+cx[i];
        ny=*y+cy[i];
        if((isempty(a,nx,ny))&&(c=getcount(a,nx,ny))<min)
        {
            flag=i;
            min=c;
        }
    }
    if(min==N+1)
        return 0;

    nx=*x+cx[flag];
    ny=*y+cy[flag];
    a[ny*sizeChessboard+nx]=a[(*y)*sizeChessboard+(*x)]+1;
    amountOfMoves++;

    *x=nx;*y=ny;

    print(a);
    return 1;
}

void print(int *a)
{
    int i,j;
    printf("------------------------------------------------------------------------------------------------------------------------------------ \n");
    for(i=0;i<sizeChessboard;++i)
    {
        for(j=0;j<sizeChessboard;++j)
            printf("[%*d] ",3,a[j*sizeChessboard+i]);
        printf("\n");
    }
    printf("------------------------------------------------------------------------------------------------------------------------------------ \n");
}

int generate(int xx, int yy)
{
    int a[sizeChessboard*sizeChessboard];
    int i,x,y,sx,sy;
    for(i=0;i<sizeChessboard*sizeChessboard;++i)
        a[i]=-1;

    sx=x=xx;
    sy=y=yy;

    a[y*sizeChessboard+x]=1;

    for(i=0;i<sizeChessboard*sizeChessboard-1;++i)
    {
        if(progress(a,&x,&y)==0)
        {
            return 0;
        }
    }

    return 1;
}

int main()
{
    int choice = 0;
    int menu = 99;

    while(menu != 0)
    {

        printf("Podaj rozmiar szachownicy: ");
        scanf("%d",&sizeChessboard);

        int chessBoard[sizeChessboard][sizeChessboard];

        int i,j;
        for(i=0; i<sizeChessboard; i++)
        {
            for(j=0; j<sizeChessboard; j++)
            {
                chessBoard[i][j]= -1;
                printf("[  ]");
            }

            printf("\n");
        }

        int x = 99;
        int y = 99;

        while(x >= sizeChessboard || y >= sizeChessboard)
        {
            printf("Podaj miejsce startu konika x: ");
            scanf("%d",&x);
            printf("Podaj miejsce startu konika y: ");
            scanf("%d",&y);

            if(x >= sizeChessboard || y >= sizeChessboard || x < 0 || y < 0)
                printf("Nie poprawne dane, pozycja powinna byc w zakresie [0...'rozmiar tablicy' - 1] \n");
        }

        printf("1. Brute force \n");
        printf("2. Warnsdorff rule \n");
        scanf("%d",&choice);

        switch(choice)
        {
            case 1:
            printf("[1] Automat \n");
            printf("[2] Automat z lista wykonanych ruchow \n");
            printf("[3] Krok po kroku recznie \n");
            scanf("%d",&choice);

            findSolution(x,y,chessBoard,choice);
            printf("Ilosc prawidlowo wykonanych ruchow: %d \n",amountOfMoves);
            printf("Ilosc wszystkich prob ruchu: %d \n",amountOfWholeMoves);
            amountOfMoves = 0;
            amountOfWholeMoves = 0;
            break;

            case 2:
            srand(time(NULL));
            if((generate(x,y)) == 1)
            {
                printf("Ilosc wykonanych ruchow: %d \n",amountOfMoves);
            }
            else
                printf("Nie udalo sie znalezc rozwiazania... \n");

            amountOfMoves = 0;
            break;
        }

        printf("[!0] Kontynuacja \n");
        printf(" [0] Wyjscie \n");
        scanf("%d",&menu);
    }

    return 0;
}

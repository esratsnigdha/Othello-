#include<bits/stdc++.h>
#include<conio.h>
#include<chrono>
using namespace std;
int board[8][8], wcount=2, bcount=2;
const int dirx[] = {-1, -1, -1, 0, 1, 1, 1, 0};
const int diry[] = {-1, 0, 1, 1, 1, 0, -1, -1};
vector<pair<int,int> >bmoves;
void delay();
void init();
void display_board();
void start_game();
void black_turn();
void white_turn();
bool out_of_bound(int x, int y);
bool endgame();
void game_over();

int main()
{
    init();
    start_game();
}
void delay(int n)
{
    using namespace std::this_thread; // sleep_for, sleep_until
    using namespace std::chrono; // nanoseconds, system_clock, seconds

    sleep_for(nanoseconds(10));
    sleep_until(system_clock::now() + seconds(n));
}
void init()
{
    ///0 white 1 black -1 empty
    for(int i=0; i<8; i++)
    {
        for(int j=0; j<8; j++)
            board[i][j] = -1;
    }
    board[3][3] = board[4][4] = 0; ///white
    board[4][3] = board[3][4] = 1; ///black

    display_board();

}
void display_board()
{
    char val;
    cout<<"  ";
    for(int i=0; i<8; i++)
        printf("  %d ",i+1);
    cout<<endl;

    for(int i=0; i<8; i++)
    {
        cout<<"  ";
        for(int j=0; j<8; j++)
        {
            printf(" ---");
        }
        cout<<endl;
        printf("%c ",'A'+i);
        for(int j=0; j<8; j++)
        {
            if(board[i][j]==-1)
                val = ' ';
            else if(board[i][j]==0)
                val = 'W';
            else
                val = 'B';
            printf("| %c ", val);
        }

        printf("|\n");
    }
    printf("  ");
    for(int j=0; j<8; j++)
    {
        printf(" ---");
    }
    cout<<endl;
}
void start_game()
{
    for(int i=1; ; i++)
    {
        if(endgame())
            break;
        if(i%2)
            black_turn();
        else
            white_turn();
    }
    game_over();
}
bool endgame()
{
    if(wcount==0 or bcount==0)
        return true;
    return false;
}
void black_turn()
{
    bmoves.clear();
    vector<int>validir;
    validir.clear();
    for(int i=0; i<8; i++)
    {
        for(int j=0; j<8; j++)
        {
            if(board[i][j] == -1)
            {
                ///check for adjacency
                for(int k=0; k<8; k++)
                {
                    if(board[i + dirx[k]][j + diry[k]] == 0 and !out_of_bound(i+dirx[k], j+diry[k]))
                    {
                        ///check if valid
                        int a = i+dirx[k],b = j+diry[k];

                        while(!out_of_bound(a,b) && board[a][b]!=-1)
                        {
                            //printf("Checking %d,%d\n",a,b);
                            if(board[a][b]==1)
                            {
                                bmoves.push_back(make_pair(i,j));
                                validir.push_back(k);
                                //printf("This is a valid move\n");
                                break;
                            }
                            a+=dirx[k];
                            b+=diry[k];
                        }
                    }
                }
            }
        }
    }


    pair<int,int>temp;
    printf("Available moves are: \n");
    for(int i=0; i<bmoves.size(); i++)
    {
        temp = bmoves[i];
        printf("%d. %c%d\n",i+1, 'A'+temp.first,temp.second+1);
    }

    printf("Enter your choice: ");
    int n;
    while(true)
    {

        cin>>n;
        if(n>bmoves.size())
        {
            printf("Wrong Input. Try Again!!!\n");
            continue;
        }
        break;
    }
    n=n-1;

    ///update board
    int a,b,idx;
    a=bmoves[n].first;
    b=bmoves[n].second;

    idx=validir[n];
    while(board[a][b]!=1)
    {
        system("CLS");
        if(board[a][b]==0)
            wcount--;

        display_board();
        board[a][b]=1;
        bcount++;
        a+=dirx[idx];
        b+=diry[idx];

        delay(1);
    }
    system("CLS");
    display_board();

}
bool out_of_bound(int x, int y)
{
    return x>7 || y>7 || x<0 || y<0;
}
void white_turn()
{
    bmoves.clear();
    delay(2);
    vector<int>validir;
    vector<int>dist;
    dist.clear();
    validir.clear();
    for(int i=0; i<8; i++)
    {
        for(int j=0; j<8; j++)
        {
            if(board[i][j] == -1)
            {
                for(int k=0; k<8; k++)
                {
                    if(board[i + dirx[k]][j + diry[k]] == 1 and !out_of_bound(i+dirx[k], j+diry[k]))
                    {
                        int a = i+dirx[k],b = j+diry[k],cnt=0;
                        while(!out_of_bound(a,b) && board[a][b]!=-1)
                        {
                            cnt++;
                            if(board[a][b]==0)
                            {
                                bmoves.push_back(make_pair(i,j));
                                validir.push_back(k);
                                dist.push_back(cnt);
                                break;
                            }
                            a+=dirx[k];
                            b+=diry[k];
                        }
                    }
                }
            }
        }
    }

    pair<int,int>temp;
    printf("Available moves are: \n");
    for(int i=0; i<bmoves.size(); i++)
    {
        temp = bmoves[i];
        printf("%d. %c%d\n",i+1, 'A'+temp.first,temp.second+1);
    }
    delay(2);

    int maxidx = -1, maxval = INT_MIN;
    for(int i=0; i<dist.size(); i++)
    {
        if(dist[i]>maxval)
        {
            maxval = dist[i];
            maxidx = i;
        }
    }
    printf("Maximum move = %c,%d\n",'A'+bmoves[maxidx].first, bmoves[maxidx].second+1);

    ///update board
    int a,b,idx;
    a=bmoves[maxidx].first;
    b=bmoves[maxidx].second;
    ///a,b is the cell to place new move
    idx=validir[maxidx];
    while(board[a][b]!=0)
    {
        system("CLS");
        if(board[a][b]==1)
            bcount--;

        display_board();
        board[a][b]=0;
        wcount++;
        a+=dirx[idx];
        b+=diry[idx];

        delay(2);
    }
    system("CLS");
    display_board();
    delay(2);

    return;
}
void game_over() {
    system("CLS");
    printf("\n");
    printf("G A M E O V E R\n");



    if(bcount>wcount)
        printf("Black won the game. Total pieces earned %d\n",bcount);
    if(bcount==wcount)
        printf("It's a tie.\n");
    else
        printf("White won the game. Total pieces earned %d\n",wcount);

    cout<<endl<<endl;
    display_board();
}


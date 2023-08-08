#include<bits/stdc++.h>
#include <iostream>
#include <conio.h> // For _kbhit() and _getch()
#include <windows.h> // For Sleep
#include <cstdlib>
#include <ctime>
using namespace std;
int n;
class Snake{
public:
    vector<pair<int,int>>coord;
    int dirc;

    Snake(){
        //cout<<"came_here"<<endl;
        coord.push_back({1,1});
        dirc=0;
    }
};
class food{
public:
    int x,y;
    food(){
        x=rand()%(n-1);
        if(!x) x++;
        y=rand()%(n-1);
        if(!y) y++;
    }
};

class Board{
public:
    vector<vector<char>>grid;
    Snake sk;
    food fd;

    Board(){
        grid.resize(n,vector<char>(n,'#'));
        for(int i=1;i<n-1;i++){
            for(int j=1;j<n-1;j++) grid[i][j]=' ';
        }
        grid[fd.x][fd.y]='%';
    }
};
void Update_board(int flag, Board*bd){
    int i=(bd->sk.coord)[(bd->sk.coord).size()-1].first;
    int j=(bd->sk.coord)[(bd->sk.coord).size()-1].second;
    
    int cnt=1;
    if(!flag){
        while(bd->grid[i][(j+cnt)%n]=='#') cnt++;
        (bd->sk.coord).push_back({i,(j+cnt)%n});
    }
    else if(flag==3){
        while(bd->grid[(i+cnt)%n][j]=='#') cnt++;
        (bd->sk.coord).push_back({(i+cnt)%n,j});
    }
    else if(flag==2){
        while(bd->grid[i][(j-cnt+n)%n]=='#') cnt++;
        (bd->sk.coord).push_back({i,(j-cnt+n)%n});
    }
    else{
        while(bd->grid[(i-cnt+n)%n][j]=='#') cnt++;
        (bd->sk.coord).push_back({(i-cnt+n)%n,j});
    }

    i=(bd->sk.coord)[(bd->sk.coord).size()-1].first;
    j=(bd->sk.coord)[(bd->sk.coord).size()-1].second;

    if((bd->grid)[i][j]!='%'){
        (bd->sk.coord).erase((bd->sk.coord).begin());
    }
    else{
        (bd->grid)[i][j]=' ';
        food newfood;
        (bd->grid)[newfood.x][newfood.y]='%';
    }


}

void print(Board *bd){
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            //cout<<i<<" "<<j<<"  ";
            bool flk=0;
            for(int k=0;k<(bd->sk.coord).size();k++){
                if((bd->sk.coord)[k].first == i && (bd->sk.coord)[k].second == j){
                    flk=1;
                    break;
                }
            }
            if(flk) cout<<"0";
            else cout<<(bd->grid)[i][j];
        }
        cout<<endl;
    }
}

bool Check_for_GameEnd(Board *bd){
    int i=(bd->sk.coord)[(bd->sk.coord).size()-1].first;
    int j=(bd->sk.coord)[(bd->sk.coord).size()-1].second;

    for(int k=0;k<(bd->sk.coord).size()-1;k++){
        if((bd->sk.coord)[k].first==i && (bd->sk.coord)[k].second==j)
        return true;
    }
    return false;
}

void Start_game(Board *bd){
        int flag=bd->sk.dirc;
        int level=0;
        while(level<1 || level>10)
        {
        cout<<"choose a level between 1 to 10"<<endl;
        cin>>level;
        }
        while(1){
        if(_kbhit()){
            char key=_getch();
            if(key=='d') flag=0;
            else if(key=='w') flag=1;
            else if(key=='a') flag=2;
            else if(key=='s') flag=3;
        }
        Update_board(flag,bd);
        print(bd);
        Sleep((11-level)*25);
        system("cls");
        if(Check_for_GameEnd(bd)){
            cout<<"Ohhh No"<<endl;
            cout<<"Play safe! You are Dead Now"<<endl;
            cout<<endl;
            cout<<"Your score: "<<(bd->sk.coord).size()<<endl;
            break;
        }
        }
}

   //    1
    // 2<-->0
    //    3

class sys{
public:
    Board *bd;
    sys(){
        cout<<"Your Game is starting"<<endl;
        
        Sleep(500);
        bd=new Board();
        Start_game(bd);
    }
    

};


int main(){

    n=10;
    sys *st=new sys();
}
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define MAX 1000000000000000000
#define MIN -MAX
map<string,pair<long long,int>> mem;
int n;
int row[100];
int col[100];
int filled = 0;
string cur ;
int calls = 0;
#define pii pair<int,int>

pair<int,int> evaluate(char a){

    int diag = 0,revdiag=0;
    int id=-1,irv=-1;
    for(int i =0;i<n;i++){

        if(cur[n*i+i] == a)  diag ++;
        else if(cur[n*i+i] == (char)0) id = n*i+i;

            if(cur[(i+1)*(n-1)] == a) revdiag++;
        else if(cur[(i+1)*(n-1)] == (char)0) irv = (i+1)*(n-1);

    }

    if(diag == n || revdiag == n) return {1,0};

    if(diag == n-1 && id != -1) return {-1,id};

    if(revdiag == n-1 && irv!=-1) return {-1,irv};

    for(int i =0;i<n;i++) {
        if (((row[i] == n || col[i] == n) && a == 'X') || ((row[i] == -n || col[i] == -n) && a == 'O'))
            return {1, 0};

        if(row[i] == n-1 && a == 'X')
            for(int j = 0;j<n;j++)
                if(cur[n*i+j] == (char)0 )
                    return {-1,n*i+j};

        if(col[i] == n-1 && a == 'X')
            for(int j =0;j<n;j++)
                if(cur[n*j+i] == (char)0)
                    return {-1,n*j+i};

        if(row[i] == 1-n && a == 'O')
            for(int j =0;j<n;j++)
                if(cur[n*i+j] == (char)0)
                    return {-1,n*i+j};


        if(col[i] == 1-n && a == 'O')
            for(int j = 0;j<n;j++)
                if(cur[n*j+i] == (char)0)
                    return {-1,n*j+i};
    }
    return {0,0};
}

bool isWin(){return evaluate('X').first == 1;}
bool isLost(){return evaluate('O').first == 1;}
bool isDraw(){return filled >= n*n;}
bool isCloseWin(){return evaluate('X').first == -1 && 0 ;}
bool isCloseLose(){return evaluate('O').first == -1 && 0 ;}

void print(){for(int i =0;i<n;i++) {for(int j = 0;j<n;j++) if(cur[n*i+j] == 0) cout << '_' << ' '; else cout << cur[n*i+j] <<' ' ;cout << endl;}cout << endl;}

ll minimum();
ll maximum(){
    calls ++;
//    if(mem.count(cur) == 1) return mem[cur].first;
        if(isWin()) return 1000000000000000000;
    if(isLost()) return -1000000000000000000;
    if(isDraw()) return 0;

    if(isCloseWin()){
        pair<int,int> stateX = evaluate('X');
//        cur[stateX.second] = 'X';
        mem[cur] = {1000000000000000000,stateX.second};
//        cur[stateX.second] = (char)0;
        return 1000000000000000000;
    }

    if(isCloseLose()){
        pii stateO = evaluate('O');
        int i = stateO.second;
        cur[i] = 'X';
        filled++;
        row[stateO.second/n]++;
        col[stateO.second%n]++;

        ll ans =  minimum();
        filled--;
        row[stateO.second/n]--;
        col[stateO.second%n]--;
        cur[i] = (char)0;
        mem[cur] = {ans,i};

        return ans;
    }

    ll mx = MIN;
    int ind ;
    for(int i =0;i<n;i++)
        for (int j = 0; j < n; j++)
            if (cur[n*i+j] == 0) {
                row[i]++,col[j]++,filled++,cur[n*i+j] = 'X';
                ll ans = minimum();
                if (mx < ans) mx = ans , ind = n*i+j;
                row[i]--,col[j]--,filled--,cur[n*i+j] = (char)0;

//                if(ans > 0)
//                    break;
            }

//    mem[cur] = {mx,ind};
    return mx;}

ll minimum(){
    calls ++;
//    if(mem.count(cur) == 1) return mem[cur].first;
        if(isWin()) return 1000000000000000000;
    if(isLost()) return -1000000000000000000;
    if(isDraw()) return 0;

    if(isCloseLose()){
//        cur[stateO.second] = 'O';
        pii stateO = evaluate('O');
        mem[cur] = {-1000000000000000000,stateO.second};
//        cur[stateO.second] = (char)0;
        return -1000000000000000000;
    }


    if(isCloseWin()){
        pii stateX = evaluate('X');
        cur[stateX.second] = 'O';
        filled++;
        row[stateX.second/n]--;
        col[stateX.second%n]--;

        ll ans =  maximum();
        filled--;
        row[stateX.second/n]++;
        col[stateX.second%n]++;
        cur[stateX.second] = (char)0;

        mem[cur] = {ans,stateX.second};

        return ans;
    }
    ll mn = MAX;
    int ind ;
    for(int i =0;i<n;i++)
        for(int j = 0;j<n;j++)
            if(cur[n*i+j] == 0) {
                filled++,row[i]--,col[j]--,cur[n*i+j] = 'O';
                ll ans = maximum();
                if(ans < mn)  mn = ans , ind = n*i+j;
                filled--,row[i]++,col[j]++,cur[n*i+j] = (char)0;

//                if(ans < 0)
//                    break;
            }
//    mem[cur] = {mn,ind};
    return mn;}

void assign(int i,int j ,char a){
    cur[n*i+j] = a, filled++;
    if(a == 'X') row[i]++,col[j]++;
    else row[i]--,col[j]--;}



bool isFinished(){

    return isDraw() || isWin() || isLost();}


void moveX(){

    if(n > 3 && !filled) assign(n-1,n-1,'X');

    else {
//        maximum();
//        int index = mem[cur].second;
//        assign(index / n, index % n, 'X');

        ll mx = MIN;
        int ind ;
        for(int i =0;i<n;i++)
            for (int j = 0; j < n; j++)
                if (cur[n*i+j] == 0) {
                    row[i]++,col[j]++,filled++,cur[n*i+j] = 'X';
                    ll ans = minimum();
                    if (mx < ans) mx = ans , ind = n*i+j;
                    row[i]--,col[j]--,filled--,cur[n*i+j] = (char)0;
                }
        assign(ind/n,ind%n,'X');
    }
    print();

}

void moveO(){
    if(n >= 3 && !filled) assign(n-1,n-1,'O');

    else {
        minimum();
        int index = mem[cur].second;
        assign(index / n, index % n, 'O');
    }
    print();

}


int main(void){

    n = 3;

    for(int i = 1;i<=n*n;i++)
        cur += (char)0;

    moveX();
        while(!isFinished()) {
        int row,col;
        cout << "YOUR TURN !!!" << endl;
        cin >> row >> col;
        assign(row-1,col-1,'O');
        moveX();
    }


    if(isWin())
        cout << "KHALED HAS WON YOU !!!" << endl;
    else
        cout << "GOOD JOB ! YOU HAVE DRAWN WITH KHALED !" << endl;

    cout << endl <<  "Number of Recursive Calls: " << calls << endl;

    return 0;
}
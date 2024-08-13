/*
Usei como referência a implementação desse repositório:
- https://github.com/KHvic/uva-online-judge/blob/master/10010-Where's%20Waldorf%3F.cpp

Comando usado para compilar:
$ g++ wheres_waldorf.cpp -o wheres_waldorf.out -Wall

Entrada:
1

8 11
abcDEFGhigg
hEbkWalDork
FtyAwaldORm
FtsimrLqsrc
byoArBeDeyv
Klcbqwikomk
strEBGadhrb
yUiqlxcnBjf
4
Waldorf
Bambi
Betty
Dagbert
*/

#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> dirs = {{0,1},{1,0},{-1,0},{0,-1},{-1,-1},{-1,1},{1,-1},{1,1}};

int main()
{
    int t,n,m,q;
    string in;
    scanf("%d",&t);
    while(t--) {
        scanf("%d %d",&n,&m);
        vector<string> grid;
        for(int i=0;i<n;i++){
            cin >> in;
            transform(in.begin(),in.end(),in.begin(),::tolower);
            grid.push_back(in);
        }
        scanf("%d",&q);
        for(int i=0;i<q;i++){
            cin >> in;
            transform(in.begin(),in.end(),in.begin(),::tolower);
            bool found = false;
            for(int i=0;i<n&&!found;i++){
                for(int j=0;j<m&&!found;j++){
                    for(auto& dir : dirs){
                        int x=i,y=j,cur=0;
                        while(cur<(int)in.length()){
                            if(x<0||y<0||x>=n||y>=m || grid[x][y] != in[cur]) break;
                            if(++cur == (int)in.length())
                                found = true;
                            x+=dir[0], y+=dir[1];
                        }
                        if(found){
                            printf("%d %d\n",i+1,j+1);
                            break;
                        }
                    }
                }
            }
        }
        if(t) printf("\n");
    }
}

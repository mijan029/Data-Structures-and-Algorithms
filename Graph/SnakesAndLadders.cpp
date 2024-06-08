#include<iostream>
#include<queue>
#include<vector>
#include <fstream>
using namespace std;
#define N 10001
vector<int> path, nodes[N];
int ladder_start[N], ladder_end[N], snake_head[N], snake_tail[N], visited[N], pr[N];

//Initialize all array
void initialize(int n)
{
    path.clear();
    for(int i=1; i<=n; i++){
        ladder_start[i]=0;
        ladder_end[i]=0;
        snake_head[i]=0;
        snake_tail[i]=0;
        visited[i]=0;
        pr[i]=0;
        nodes[i].clear();
    }
}

//finding the minimal path
int find_path(int node, int n)
{
    int len=0;
    while(pr[node]){
        path.push_back(node);
        if(ladder_end[node] && node-pr[node]>n){
            path.push_back(ladder_end[node]);
            len++;
        }
        if(snake_tail[node] && pr[node]>node) {
            path.push_back(snake_tail[node]);
            len++;
        }
        node=pr[node];
    }
    path.push_back(node);
    return len;
}

//BFS for finding minimum path and visiting node
int SnakesAndLadders(int x, int n)
{
    queue<int> q;
    int len=-1;
    q.push(1);
    visited[1]=1;
    while(!q.empty()){
         int u = q.front();
         q.pop();
         for(int i=0; i<nodes[u].size(); i++){
            int v = nodes[u][i];
            if(!visited[v]){
                visited[v]=1;
                if(ladder_start[v]) v=ladder_start[v];
                if(snake_head[v])v=snake_head[v];
                visited[v]=1;
                pr[v]=u;
                q.push(v);
                if(nodes[u][i]==x)
                    len = find_path(x, n);
            }
         }
    }
    return len;
}


int main()
{
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    int t, n, x, l, s;
    cin>>t;
    while(t--){

        //input and initialize
        cin>>n>>x;

        //input ladders
        cin>>l;
        for(int i=0; i<l; i++){
            int start, en;
            cin>>start>>en;
            ladder_start[start]=en;
            ladder_end[en]=start;
        }

        //input snakes
        cin>>s;
        for(int i=0; i<s; i++){
            int head, tail;
            cin>>head>>tail;
            snake_head[head]=tail;
            snake_tail[tail]=head;
        }

        //creating graph using list
        for(int i=1; i<x; i++){
            if(!snake_head[i] && !ladder_start[i]){
                for(int j=1; j<=n; j++){
                    if(i+j<=x){
                        nodes[i].push_back(i+j);
                    }
                }
            }
        }

        //Output
        int len = SnakesAndLadders(x,n);
        if(len==-1)
            cout<<-1<<endl<<"No solution"<<endl;
        else {
            cout<<path.size()-len-1<<endl;
            for(int i = path.size()-1; i>0; i--)
                cout<<path[i]<<" -> ";
            cout<<path[0]<<endl;
        }
        bool flag=true;
        for(int i=1; i<=x; i++)
            if(!visited[i]) flag=false;
        if(flag) cout<<"All reachable"<<endl;
        else{
            for(int i=1; i<=x; i++)
                if(!visited[i]) cout<<i<<' ';
            cout<<endl;
        }

        initialize(x);
    }
}

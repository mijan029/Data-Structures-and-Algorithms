#include<bits/stdc++.h>
using namespace std;


//Bellman-Ford's Algorithm for finding minimum cost
int parent[1005];
map< pair<int,int>, double> W;
double cost[1005];
int Bellman_Ford(int n, int s, vector<int> G[])
{

    for(int i=1; i<=n; i++)
        cost[i] = 1e9;
    cost[s]=0;


    int m=n;
    while(m--){
        for(int i=1; i<=n; i++){
            for(int j=0; j<G[i].size(); j++){
                int v = G[i][j];
                int u = i;
                if(cost[v] > cost[u]+W[{u,v}]){
                    cost[v] = cost[u] + W[{u,v}];
                    parent[v] = u;
                }
            }
        }
    }

    for(int i=1; i<=n; i++){
        for(int j=0; j<G[i].size(); j++){
            int v = G[i][j];
            int u = i;
            if(cost[v] > cost[u]+W[{u,v}]){
                return 0;
            }
        }
    }

    return 1;
}

void print_path(int n)
{
    if(parent[n]==0) {
        cout<<n-1;
        return;
    }
    print_path(parent[n]);
    cout<<" -> "<<n-1;
}

int main()
{
    int n, m, s, k;
    vector<int> G[1005];
    cin>>n>>m;
    for(int i=1; i<=m; i++){
        int u, v;
        double w;
        cin>>u>>v>>w;
        u++; v++;
        G[u].push_back(v);
        W[{u,v}] = w;
    }

    cin>>s>>k; s++; k++;
    int st = Bellman_Ford(n, s, G);

    if(st){
        cout<<"The graph does not contain a negative cycle"<<endl;
        cout<<"Shortest path cost: "<<cost[k]<<endl;
        print_path(k);
        cout<<endl;
    }

    else cout<<"The graph contains a negative cycle"<<endl;
    return 0;

}

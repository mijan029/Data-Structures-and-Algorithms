#include<bits/stdc++.h>
using namespace std;


//Dijkstra's Algorithm for finding minimum cost
int parent[1005], vist[1005];
map< pair<int,int>, double> W;
double cost[1005];
void dijkstra(int n, int s, vector<int> G[])
{

    for(int i=1; i<=n; i++)
        cost[i] = 1e9;
    cost[s]=0;

    priority_queue<pair<double, int>, vector<pair<double, int> >, greater<pair<double, int> > > pq;
    pq.push({0,s});

    while(!pq.empty()){
        pair<double, int> p = pq.top();
        pq.pop();
        int u=p.second;
        if(vist[u]==0){
            vist[u] = 1;
            for(int i=0; i<G[u].size(); i++){
                if(vist[G[u][i]]==0){
                    int v = G[u][i];
                    if(cost[v] > cost[u]+W[{u,v}]){
                        cost[v] = cost[u] + W[{u,v}];
                        parent[v] = u;
                        pq.push({cost[v],v});
                    }
                }
            }
        }
    }
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
    dijkstra(n, s, G);
    cout<<"Shortest path cost: "<<cost[k]<<endl;


    print_path(k);
    cout<<endl;

    return 0;

}

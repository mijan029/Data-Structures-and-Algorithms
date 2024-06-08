#include<bits/stdc++.h>
using namespace std;


//Prim's Algorithm for finding MST
int parent[1005];
map< pair<int,int>, int> W;
double prim_cost=0;
void Find_prim(int n, vector<int> G[])
{
    double key [n+1];
    int visit[n+1];
    for(int i=0; i<n; i++){
        key[i]=1e9;
        visit[i]=0;
    }
    key[0]=0;
    priority_queue<pair<double, int>, vector<pair<double, int> >, greater<pair<double, int> > > pq;
    pq.push({0,0});

    while(!pq.empty()){
        pair<double, int> p = pq.top();
        pq.pop();
        if(visit[p.second] == 0){
            prim_cost+=p.first;
            visit[p.second] = 1;
            for(int i=0; i<G[p.second].size(); i++){
                if(visit[G[p.second][i]]==0){
                    int v = G[p.second][i];
                    if(key[v] > W[{v,p.second}]){
                        key[v] = W[{v,p.second}];
                        parent[v] = p.second;
                        pq.push({key[v],v});
                    }
                }
            }
        }
    }
}



// Kruskal's algorithm for finding MST
int final_predecessor(int n, int *pr)
{
    if(n != pr[n])
        pr[n] = final_predecessor(pr[n], pr);
    return pr[n];
}

vector<pair<double, pair<int,int> > > Find_kruskal( vector<pair<double, pair<int,int> > > G, int n )
{
    vector<pair<double, pair<int,int> > > A;
    int pr[n+1];
    for(int i=0; i<n; i++)
        pr[i]=i;
    sort(G.begin(), G.end());
    for(int i=0; i<G.size(); i++){
        int u = G[i].second.first;
        int v = G[i].second.second;
        double w = G[i].first;
        if(final_predecessor(u, pr) != final_predecessor(v, pr)){
            A.push_back(G[i]);
            pr[pr[u]] = pr[v];
        }
    }

    return A;
}

int main()
{
    freopen("mst.in.txt","r",stdin);
    int n, m;
    vector<pair<double, pair<int,int> > > G, A;
    vector<int> G1[1005];
    cin>>n>>m;
    for(int i=1; i<=m; i++){
        int u, v;
        double w;
        cin>>u>>v>>w;
        G.push_back({w,{u,v}});
        G1[u].push_back(v);
        G1[v].push_back(u);
        W[{u,v}] = W[{v,u}] = w;
    }

    Find_prim(n, G1);
    cout<<"Cost of the minimum spanning tree : "<<prim_cost<<endl;
    cout<<"List of edges selected by prim's: {";
    for(int i=1; i<n; i++){
        cout<<'('<<i<<","<<parent[i]<<")";
        if(i+1 == n) cout<<'}'<<endl;
        else cout<<", ";
    }


    A = Find_kruskal(G, n);

   /* double cost=0;
    for(int i=0; i<A.size(); i++){
        double w = A[i].first;
        cost+=w;
    }

    cout<<"Cost of the minimum spanning tree : "<<cost<<endl;*/
    cout<<"List of edges selected by kruskal's: {";
    for(int i=0; i<A.size(); i++){
        int u = A[i].second.first;
        int v = A[i].second.second;
        cout<<'('<<u<<","<<v<<")";
        if(i+1 == A.size()) cout<<'}'<<endl;
        else cout<<", ";
    }
    fclose(stdin);

    return 0;

}

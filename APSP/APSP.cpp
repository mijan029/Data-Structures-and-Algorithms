#include<bits/stdc++.h>
using namespace std;

#define inf 1e9
//Matrix multiplication for finding APSP

int mat[105][105], W[105][105];
void matrix_multiplication(int n)
{
    for(int i=1; i<=n; i++){
        for(int j=1; j<=n; j++){
            for(int k=1; k<=n; k++)
                if(mat[i][j]> mat[i][k] + W[k][j]){
                    mat[i][j] = mat[i][k] + W[k][j];
                }
        }
    }
}


// Floyd-Warshall algorithm for finding APSP

void floyd_warshall(int n)
{
    for(int k=1; k<=n; k++){
        for(int j=1; j<=n; j++){
            for(int i=1; i<=n; i++)
                if(mat[i][j]> mat[i][k] + mat[k][j]){
                    mat[i][j] = mat[i][k] + mat[k][j];
                }
        }
    }
}



int main()
{
    int n, m;
    cin>>n>>m;

    for(int i=1; i<=n; i++){
        for(int j=1; j<=n; j++){
            mat[i][j]=W[i][j]=inf;
        }
    }
    for(int i=1; i<=n; i++)
        mat[i][i]=W[i][i]=0;

    for(int i=1; i<=m; i++){
        int u, v, w;
        cin>>u>>v>>w;
        mat[u][v] = w;
        W[u][v] = w;
    }

    //for(int i=1; i<=n-2; i++)
       // matrix_multiplication(n);

    floyd_warshall(n);

    cout<<"Shortest distance matrix"<<endl;
    for(int i=1; i<=n; i++){
        for(int j=1; j<=n; j++)
            mat[i][j] == inf ? cout<<"INF " : cout<<mat[i][j]<<' ';
        cout<<endl;
    }


    return 0;

}

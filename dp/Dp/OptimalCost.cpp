#include<iostream>
#include<algorithm>
using namespace std;

int a[15][15];

int cost(int n, int j)
{
    int i=1, sum=0;
    while(n){
        if(n%2) sum+=a[j][i];
        n/=2;
        i++;
    }
    return sum;
}
int main()
{
    int n;
    cin>>n;
    for(int i=1; i<=n; i++){
        for(int j=1; j<=n; j++)
            cin>>a[i][j];
    }
    int m = 1<<10;
    int minimumCost[m];
    minimumCost[0]=0;
    for(int i=1; i<m; i++){
        minimumCost[i]=1e9;
        for(int j=0; j<10; j++){
            if((1<<j)&i){
                minimumCost[i]=min(minimumCost[i],minimumCost[i-(1<<j)]+cost(i,j+1));
            }
        }
    }
    cout<<minimumCost[m-1]<<endl;
}


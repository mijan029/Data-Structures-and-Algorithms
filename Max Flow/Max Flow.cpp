#include<bits/stdc++.h>
using namespace std;
#define N 100
#define inf 10000000

int W[N], L[N], R[N], a[N][N];
string s[N];
vector<int>vc[N];
map<int,int> mp[N];


void bfs(int src, int *vs, int *pr)
{
    queue<int>q;
    q.push(src);
    while(!q.empty()){
        int u = q.front();
        q.pop();
        vs[u]=1;
        for(int i=0; i<vc[u].size(); i++){
            int v = vc[u][i];
            if(vs[v]==0 && mp[u][v]!=0){
                pr[v]=u;
                q.push(v);
            }
        }
    }
}

int get_mn(int *pr, int src, int n)
{
    if(pr[n] == src) return mp[src][n];
    else return min(mp[pr[n]][n],get_mn(pr, src, pr[n]));
}
void update_augmented_path(int *pr, int src, int n){
    int mn = get_mn(pr, src, n);
    while(n!=src){
        int u = pr[n];
        mp[u][n]-=mn;
        mp[n][u]+=mn;
        n=u;
    }
}

void eliminate(int n)
{
    int src=0, sink = n*n+1;



    for(int i=1; i<=n; i++){

        for(int ii=0; ii<=sink; ii++){
            mp[ii].clear(); vc[ii].clear();
        }

        for(int j=1; j<=n; j++){
            for(int k=j+1; k<=n; k++){
                if(j!=i && k!=i){
                    mp[j][sink]=W[i]+R[i]-W[j];
                    mp[k][sink]=W[i]+R[i]-W[k];
                    vc[j].push_back(sink);
                    vc[k].push_back(sink);
                    int gnode = j*n+k;
                    vc[gnode].push_back(j);
                    vc[gnode].push_back(k);
                    mp[gnode][j]=inf;
                    mp[gnode][k]=inf;
                    vc[src].push_back(gnode);
                    mp[src][gnode]=a[j][k];
                }
            }
        }

        while(1){
            int NN = n*n+2;
            int pr[NN], vs[NN];
            for(int j=0; j<=NN; j++){
                pr[j] = vs[j]=0;
            }
            bfs(src,vs,pr);
            if(vs[sink]==0) break;
            update_augmented_path(pr, src, sink);
        }

        bool key = false;
        for(int j=0; j<vc[src].size(); j++){
            int u = vc[src][j];
            if(mp[src][u] != 0)
                key = true;
        }

        if(key){
            cout<<s[i]<<" is eliminated."<<endl;

            int m = (1<<n)-1;
            for(int j = m; j>0; j--){
                int sum=0, total = 0, ind=0, sum1=0;
                int k=j;
                int select[n+2];
                for(int p=0; p<=n; p++)
                    select[p]=0;
                while(k){
                    ind++;
                    if(k%2 && ind!=i){
                        sum+=W[ind];
                        total++;
                        select[ind]=1;
                    }
                    k/=2;
                }
                for(int p=1; p<=n; p++){
                    for(k=p+1; k<=n; k++){
                        if(select[p]&&select[k]) sum1+=a[p][k];
                    }
                }
                double avg = 1.0*(sum+sum1)/total;
                if(avg>W[i]+R[i]){
                    int tot = total;
                    string str="";
                    for(int p=1; p<=n; p++){
                        if(select[p]){
                            if(tot==1 && total == 1)str+=s[p];
                            else if (tot==total) str = s[p];
                            else if(tot == 1){
                                str=str+" and "+s[p];
                            }
                            else str = str+", "+s[p];
                            tot--;
                        }
                    }
                    cout<<"They can win at most "<<W[i]<<" + "<<R[i]<<" = "<<W[i]+R[i]<<" games."<<endl;
                    cout<<str<<" have won a total of "<<sum<<" games."<<endl;
                    cout<<"They play each other "<<sum1<<" times."<<endl;
                    cout<<"So on average, each of the teams wins "<<sum+sum1<<"/"<<total<<" = "<<avg<<" games."<<endl;

                    break;
                }
            }
        }
    }
}

int main()
{

    int n;
    cin>>n;
    for(int i=1; i<=n; i++){
        cin>>s[i]>>W[i]>>L[i]>>R[i];
        for(int j=1; j<=n; j++){
            cin>>a[i][j];
        }
    }

    eliminate(n);


}

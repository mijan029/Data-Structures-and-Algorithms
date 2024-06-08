#include<bits/stdc++.h>
using namespace std;

class matrix
{
public:
    int order, fixedrow, fixedcol, level, serial, bound;
    vector<vector<int>>a;
    matrix(int n, int fixedrow, int fixedcol, int level, int serial){
        vector<int>v;
        for(int i=0; i<=n; i++){
            for(int j=0; j<=n; j++)
                v.push_back(0);
            a.push_back(v);
        }
        order = n;
        this->fixedrow = fixedrow;
        this->fixedcol = fixedcol;
        this->level = level;
        this->serial = serial;
    }

    void swapcol(int i, int j)
    {
        for(int l=1; l<=order; l++){
            swap(a[l][i],a[l][j]);
        }
    }

    void swaprow(int i, int j)
    {
        for(int l=1; l<=order; l++){
            swap(a[i][l],a[j][l]);
        }
    }


};

void print(matrix m)
{
    int n = m.order;
    for(int i=1; i<=n; i++){
        for(int j=1; j<=n; j++){
            cout<<m.a[i][j];
        }
        cout<<endl;
    }
}


bool operator<( const matrix& m1, const matrix& m2)
{
    if(m1.bound!=m2.bound) return !(m1.bound<m2.bound);
    else if(m1.level!=m2.level) return m1.level<m2.level;
    else return m1.serial <= m2.serial;
}

priority_queue<matrix> q;

int calunfixed(matrix m, int i, int j)
{
    int n = m.order, mx=0;
    for(int l=i; l<=n; l++){
        int cnt=0;
        for(int k=j; k<=n; k++){
            if(m.a[l][k]!=0) cnt++;
        }
        mx = max(mx,cnt);
    }

    for(int l=j; l<=n; l++){
        int cnt=0;
        for(int k=i; k<=n; k++){
            if(m.a[k][l]!=0) cnt++;
        }
        mx = max(mx,cnt);
    }
    return (mx+1)/2;
}

int calfixed(matrix m, int l, int p)
{
    int mx=0;
    int n = m.order;
    for(int i=1; i<=p; i++){
        int cnt=1, cnt1=1, coun=0;
        for(int k=i-1; k>0; k--){
            if(m.a[k][i]!=0)
                cnt = i-k+1;
        }
        for(int k=i+1; k<=m.fixedrow; k++){
            if(m.a[k][i]!=0)
                cnt1 = k-i+1;
        }
        for(int k = m.fixedrow+1; k<=n; k++){
            if(m.a[k][i]!=0)
                coun++;
        }
        coun?cnt1 = m.fixedrow-i+1+coun:cnt1=cnt1;
        mx = max(mx,max(cnt,cnt1));
    }

    for(int i=1; i<=l; i++){
        int cnt=1, cnt1=1, coun=0;
        for(int k=i-1; k>0; k--){
            if(m.a[i][k]!=0)
                cnt = i-k+1;
        }
        for(int k=i+1; k<=m.fixedcol; k++){
            if(m.a[i][k]!=0)
                cnt1 = k-i+1;
        }
        for(int k = m.fixedcol+1; k<=n; k++){
            if(m.a[i][k]!=0)
                coun++;
        }
        coun?cnt1 = m.fixedcol-i+1+coun:cnt1=cnt1;
        mx = max(mx,max(cnt,cnt1));
    }
    return mx;

}


int calbound(matrix m)
{
    return max(calfixed(m, m.fixedrow, m.fixedcol),calunfixed(m,m.fixedrow+1,m.fixedcol+1));

}

void branching(matrix m)
{
    matrix m1 = m;
    int n = m.order;
    if(m1.fixedcol == m1.fixedrow){
        for(int i = m1.fixedcol+1; i<=n; i++){
            m1 = m;
            for(int j=i; j>m1.fixedcol+1; j--)
                m1.swapcol(j-1,j);

            m1.fixedcol++;
            m1.level++;
            m1.serial = i-m1.fixedcol+1;
            m1.bound = calbound(m1);

            q.push(m1);

        }

    }

    else{
        for(int i = m1.fixedrow+1; i<=n; i++){
            m1 = m;
            for(int j=i; j>m1.fixedrow+1; j--)
                m1.swaprow(j-1,j);

            m1.fixedrow++;
            m1.level++;
            m1.serial = i-m1.fixedrow+1;
            m1.bound = calbound(m1);
            q.push(m1);

        }
    }
}



int main()
{
    int n;
    cin>>n;
    matrix m = *(new matrix(n,0,0,1,1));
    for(int i=1; i<=n; i++){
        for(int j=1; j<=n; j++){
            cin>>m.a[i][j];
        }
    }
    m.bound = calbound(m);
    q.push(m);
    int cnt=0;
    while(!q.empty()){
        cnt++;
        matrix m1 = q.top();
        q.pop();
        if(m1.fixedrow == m1.fixedcol && m1.fixedrow == n-1){
            print(m1);
            break;
        }
        branching(m1);
    }
}

/*
4
1 0 0 1
0 0 1 0
1 0 0 1
0 1 1 1
*/


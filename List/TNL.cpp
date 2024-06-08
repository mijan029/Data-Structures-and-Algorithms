#include<iostream>
#include "List.cpp"
#include "Arr.cpp"
#include "LL.cpp"
using namespace std;

void print(aList<int> &lst, int n)
{
    for(int i=0; i<n; i++){
        if(i==lst.getValue()) {
            cout<<i;
            lst.next();
        }
        if(i!=n-1) cout<<',';
    }
    cout<<endl;
}

int main()
{
    int K, L, M, T;
    aList<int> rList;
    aList<int> bList;
    aList<int> tList;
    cin>>K;
    for(int i=0; i<K; i++)
        rList.append(i);
    cin>>L;
    for(int i=0; i<L; i++){
        int b;
        cin>>b;
        bList.append(b);
    }
    cin>>M;
    for(int i=0; i<M; i++){
        int t;
        cin>>t;
        tList.append(t);
    }
    cin>>T;
    print(rList,K);
    print(bList,K);
    print(tList,K);
    while(T--){

    }
}


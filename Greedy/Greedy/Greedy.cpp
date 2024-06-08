#include<iostream>
#include<algorithm>
using namespace std;

int main()
{
    long long n, k, cost=0;
    cin>>n>>k;
    long long arr[n];
    for(int i=0; i<n; i++)
        cin>>arr[i];
    sort(arr,arr+n,greater<int>());
    for(int i=0; i<n; i++)
        cost+=arr[i]*(i/k+1);
    cout<<cost<<endl;
}

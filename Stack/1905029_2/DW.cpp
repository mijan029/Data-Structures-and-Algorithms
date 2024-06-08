#include<iostream>
#include"Stack_ADT.cpp"
#include"LL_based_stack.cpp"
#include"Arr_Based_stack.cpp"

using namespace std;

template <class A> int check(arrStack<A> &fm, int n)
{
    int key=0;
    for(int i=n; i>0; i--){
        arrStack<A> fmcopy;
        while(fm.length()){
            A temp = fm.pop();
            if(temp == i) key++;
            fmcopy.push(temp);
        }
        while(fmcopy.length()) fm.push(fmcopy.pop());
    }
    return key == n ? 1 : 0;
}
template <class A> int check(LLStack<A> &fm, int n)
{
    int key=0;
    for(int i=n; i>0; i--){
        arrStack<A> fmcopy;
        while(fm.length()){
            A temp = fm.pop();
            if(temp == i) key++;
            fmcopy.push(temp);
        }
        while(fmcopy.length()) fm.push(fmcopy.pop());
    }
    return key == n ? 1 : 0;
}
int main()
{
    int n, x;
    cin>>n>>x;
    int TimeNeeded[x+1];
    for(int i=1; i<=x; i++)
        cin>>TimeNeeded[i];

    int t0=0, totalTime=0;
    LLStack<int> dw, tm, fm[n+1], fmId, tmCopy, ti;
    int k, t, s;
    while(1){
        cin>>k>>t>>s;
        if(!k) break;

        fm[k].push(s);
        if(s == n && check(fm[k],n))
            fmId.push(k);

        if(t<=t0){
                dw.push(s);
                ti.push(t);
        }
        else{
            while(t0<t && dw.length()){
                int s1=dw.pop();
                int t1 = ti.pop();
                if(t1>t0) t0=t1;
                t0+=TimeNeeded[s1];
                tm.push(t0-1);
            }
            dw.push(s);
            ti.push(t);
        }
    }
    while(dw.length()){
        int s1=dw.pop();
        int t1 = ti.pop();
        if(t1>t0) t0=t1;
        t0+=TimeNeeded[s1];
        tm.push(t0-1);
    }

    cout<<t0-1<<endl;
    while(tm.length()) tmCopy.push(tm.pop());
    while(tmCopy.length()){
        cout<<tmCopy.pop();
        if(tmCopy.length()) cout<<',';
    }
    fmId.length() == n ? cout<<"\nY\n" : cout<<"\nN\n";
    while(fmId.length()){
        cout<<fmId.pop();
        if(fmId.length()) cout<<',';
    }
    cout<<endl;
}





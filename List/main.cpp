#include<iostream>
#include "List.cpp"
#include "Arr.cpp"
#include "LL.cpp"
using namespace std;

template <class A> void print(aList<A> &customlist)
{
    int pos=customlist.currPos();
    cout<<'<';
    for(int i=customlist.moveToStart(); i<customlist.length(); i++){
        if(i==pos) cout<<'|';
        if(i==customlist.length()-1) cout<<customlist.getValue();
        else cout<<customlist.getValue()<<' ';
        customlist.next();
    }
    cout<<'>'<<endl;
    customlist.moveToPos(pos);
}
int main()
{
    int k, x;
    cin>>k>>x;
    aList<int> customlist(x);
    //LList<int> customlist;
    for(int i=0; i<k; i++){
        int element;
        cin>>element;
        customlist.append(element);
    }
    print(customlist);
    while(1){
        int q, p;
        cin>>q>>p;
        if(!q) return 0;
        int returnValue=-1;
        if(q==1) customlist.clear();
        if(q==2) customlist.insert(p);
        if(q==3) customlist.append(p);
        if(q==4) returnValue = customlist.remove();
        if(q==5) customlist.moveToStart();
        if(q==6) customlist.moveToEnd();
        if(q==7) customlist.prev();
        if(q==8) customlist.next();
        if(q==9) returnValue = customlist.length();
        if(q==10) returnValue = customlist.currPos();
        if(q==11) customlist.moveToPos(p);
        if(q==12) returnValue = customlist.getValue();
        if(q==13) returnValue = customlist.Search(p);
        print(customlist);
        cout<<returnValue<<endl;
    }
}


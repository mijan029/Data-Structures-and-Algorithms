#include<iostream>
#include"Stack_ADT.cpp"
#include"LL_based_stack.cpp"
#include"Arr_Based_stack.cpp"

using namespace std;

template <class A> void print(arrStack<A> &customStack)
{
    arrStack<A> newStack;
    cout<<'<';
    while(customStack.length()) newStack.push(customStack.pop());
    while(newStack.length()) {
        A val = newStack.pop();
        customStack.push(val);
        if(!newStack.length()) cout<<val;
        else cout<<val<<' ';
    }
    cout<<'>'<<endl;
}

template <class A> void print(LLStack<A> &customStack)
{
    LLStack<A> newStack;
    cout<<'<';
    while(customStack.length()) newStack.push(customStack.pop());
    while(newStack.length()) {
        A val = newStack.pop();
        customStack.push(val);
        if(!newStack.length()) cout<<val;
        else cout<<val<<' ';
    }
    cout<<'>'<<endl;
}

int main()
{
    int k;
    cin>>k;
    //int a[4] = {1,22,3,4};
    arrStack<int> customStack;
    //LLStack<int> customStack;
    for(int i=0; i<k; i++){
        int element;
        cin>>element;
        customStack.push(element);
    }
    print(customStack);
    while(1){
        int q, p;
        cin>>q>>p;
        int returnValue=-1;
        if(!q) return 0;
        if(q==1) customStack.clear();
        if(q==2) customStack.push(p);
        if(q==3) returnValue = customStack.pop();
        if(q==4) returnValue = customStack.length();
        if(q==5) returnValue = customStack.topValue();
        if(q==6) customStack.setDirection(p);
        print(customStack);
        cout<<returnValue<<endl;
    }
}




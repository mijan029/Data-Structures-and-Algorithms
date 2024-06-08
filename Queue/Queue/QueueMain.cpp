#include<iostream>
#include"QueueADT.cpp"
#include"Queue-Arr-Implementation.cpp"
#include"Queue-LinkedList-Implementation.cpp"

using namespace std;

template <class A> void print(LLQueue<A> &customQueue)
{
    LLQueue<A> newQueue;
    cout<<'<';
    while(customQueue.length()) {
        A val = customQueue.dequeue();
        newQueue.enqueue(val);
        if(!customQueue.length()) cout<<val;
        else cout<<val<<' ';
    }
    cout<<'>'<<endl;

    while(newQueue.length()) {
        customQueue.enqueue(newQueue.dequeue());
    }
}

template <class A> void print(ArrBasedQueue<A> &customQueue)
{
    ArrBasedQueue<A> newQueue;
    cout<<'<';
    while(customQueue.length()) {
        A val = customQueue.dequeue();
        newQueue.enqueue(val);
        if(!customQueue.length()) cout<<val;
        else cout<<val<<' ';
    }
    cout<<'>'<<endl;

    while(newQueue.length()) {
        customQueue.enqueue(newQueue.dequeue());
    }
}

int main()
{
    int k;
    cin>>k;
    //int *a; a = new int[5];
    ArrBasedQueue<int> customqueue;
    //LLQueue<int> customqueue;
    for(int i=0; i<k; i++){
        int element;
        cin>>element;
        customqueue.enqueue(element);
    }
    print(customqueue);
    while(1){
        int q, p;
        cin>>q>>p;
        int returnValue=-1;
        if(!q) return 0;
        if(q==1) customqueue.clear();
        if(q==2) customqueue.enqueue(p);
        if(q==3) returnValue = customqueue.dequeue();
        if(q==4) returnValue = customqueue.length();
        if(q==5) returnValue = customqueue.frontValue();
        if(q==6) returnValue = customqueue.rearValue();
        if(q==7) returnValue = customqueue.leaveQueue();
        print(customqueue);
        cout<<returnValue<<endl;
    }
}





#include<iostream>
#include"QueueADT.cpp"
#include"Queue-Arr-Implementation.cpp"
#include"Queue-LinkedList-Implementation.cpp"

using namespace std;


int main()
{
    int n;
    cin>>n;
    int time1=-1,booth1=-1,booth2=-1, time2=-1, T=-1;
    ArrBasedQueue<int>queue1, queue2;
    //LLQueue<int>queue1, queue2;
    while(n--){
        int t, val;
        cin>>t>>val;
        while(T<t){
            if(queue1.length()&&queue1.frontValue()+time1<T){
                queue1.dequeue();
                time1=booth1=T-1;
            }
            if(queue2.length()&&queue2.frontValue()+time2<T){
                queue2.dequeue();
                time2=booth2=T-1;
            }
            if(queue1.length()-1>queue2.length()){
                queue2.enqueue(queue1.leaveQueue());
            }
            if(queue2.length()-1>queue1.length()){
                queue1.enqueue(queue2.leaveQueue());
            }
            if(!queue1.length()) time1=T;
            if(!queue2.length()) time2=T;

            T++;
            if(queue1.length()+queue2.length()==0){
                time1 = t-1;
                time2 = t-1;
                T = t;
                break;
            }
        }
        if(queue1.length()>queue2.length())
                queue2.enqueue(val);
        else queue1.enqueue(val);
    }
    while(queue1.length()||queue2.length()){
            if(queue1.length()&&queue1.frontValue()+time1<T){
                queue1.dequeue();
                time1=booth1=T-1;
            }
            if(queue2.length()&&queue2.frontValue()+time2<T){
                queue2.dequeue();
                time2=booth2=T-1;
            }
            if(queue1.length()-1>queue2.length()){
                queue2.enqueue(queue1.leaveQueue());
            }
            if(queue2.length()-1>queue1.length()){
                queue1.enqueue(queue2.leaveQueue());
            }

            T++;
    }
    cout<<"Booth 1 finishes at time t = "<<booth1+1<<endl;
    cout<<"Booth 2 finishes at time t = "<<booth2+1<<endl;
    return 0;
}






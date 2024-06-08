template <class A> class ArrBasedQueue:public Queue<A>
{
private:
    int head, tail, sz;
    A *arr;
    void addMemory(){
        sz=sz*2-1;
        A *newArr = new A[sz];
        int i=0;
        while(head!=tail){
            i++;
            newArr[i]=arr[head];
            head=(head+1)%((sz+1)/2);
        }
        head=1;
        tail=i+1;
        delete[] arr;
        arr=newArr;
    }
public:
     ArrBasedQueue(int sz=5)
     {
         this->sz=sz+1;
         arr = new A[this->sz];
         head=1;
         tail=0;
     }
     ArrBasedQueue(A *providedArr, int sz=2)
     {
         this->sz=sz;
         arr =  providedArr;
         head=1;
         tail=0;
     }
     ~ArrBasedQueue(){
        delete[] arr;
     }
     void clear(){
        head=1;
        tail=0;
     }

     void enqueue(A item){
        tail=(tail+1)%sz;
        if((tail+1)%sz == head) addMemory();
        arr[tail]=item;
     }
     A dequeue(){
        if(!length()) return NULL;
        A item = arr[head];
        head = (head+1)%sz;
        return item;
     }
     int length(){
        return (sz+1+tail-head)%sz;
     }
     A frontValue(){
        if(!length()) return NULL;
        return arr[head];
     }
     A rearValue(){
        if(!length()) return NULL;
        return arr[tail];
     }
     A leaveQueue(){
        if(!length()) return NULL;
        A item = arr[tail];
        tail = (tail-1+sz)%sz;
        return item;
     }
};

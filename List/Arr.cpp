template <class A> class aList:public List<A>
{
private:
    int curr, len, chunk, maxsize;
    A *arr;
    void addMemory(){
        maxsize+=chunk;
        A *newArr = new A[maxsize];
        for(int i=0; i<len; i++)
            newArr[i]=arr[i];
        delete[] arr;
        arr=newArr;
    }
public:
     aList(int x=20)
     {
         maxsize = x;
         chunk=x;
         arr = new A[x];
         curr=0;
         len=0;
     }
     aList(A *providedArr, int sz, int x=0)
     {
         maxsize = x;
         chunk=x;
         arr = new A[x];
         curr=0;
         len=0;
         for(int i=0; i<sz; i++)
            arr[len++]=providedArr[i];
     }
     ~aList(){
        delete[] arr;
     }
     void clear(){
        len=0;
        curr=0;
     }

     void insert(A item){
        for(int i=len; i>curr; i--){
            if(len==maxsize) addMemory();
            arr[i]=arr[i-1];
        }
        arr[curr]=item;
        len++;
     }
     void append(A item){
        if(len==maxsize) addMemory();
        arr[len++]=item;
     }
     A remove(){
        A ele=arr[curr];
        len--;
        for(int i=curr; i<len; i++)
            arr[i]=arr[i+1];

        if(curr==len) curr--;
        return ele;
     }
     int moveToStart(){
        curr=0;
        return curr;
     }
     int moveToEnd(){
        curr = len-1;
        return curr;
     }
     void prev(){
        if(curr) curr--;
     }
     void next(){
        if(curr<len-1) curr++;
     }
     int length(){
        return len;
     }
     int currPos(){
        return curr;
     }
     void moveToPos(int pos){
        curr=pos;
     }
     A getValue(){
        return arr[curr];
     }
     int Search(A item){
        int found=-1;
        for(int i=0; i<len; i++)
            if(arr[i]==item) found=i;
        return found;
     }

};

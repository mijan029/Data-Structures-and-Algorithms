template <class A> class arrStack:public Stack<A>
{
private:
    int len1, chunk=6, dir, len2;
    A *arr;
    void addMemory(){
        chunk+=chunk;
        A *newArr = new A[chunk];
        for(int i=0; i<len1; i++)
            newArr[i]=arr[i];
        for(int i=chunk/2-1, j=1; i>=len1; i--,j++)
            newArr[chunk-j]=arr[i];
        delete[] arr;
        arr=newArr;
    }
public:
     arrStack()
     {
         arr = new A[chunk];
         len1=0;
         len2=0;
         dir=1;
     }
     arrStack(A *providedArr, int di)
     {
         int sz=sizeof(providedArr);
         arr = new A[chunk];
         len1=0;
         len2=0;
         dir=di;
         for(int i=0; i<sz; i++)
            push(providedArr[i]);
     }
     ~arrStack(){
        delete[] arr;
     }
     void clear(){
        len1=0;
        len2=0;
     }

     void push(A item){
        if(len1+len2==chunk) addMemory();
        dir==1 ? arr[len1++]=item : arr[chunk-1-len2++]=item;
     }
     A pop(){
        dir==1?len1--:len2--;
        return dir==1?arr[len1]:arr[chunk-len2-1];
     }
     int length(){
        return dir==1?len1:len2;
     }
     A topValue(){
        if(!len1 && dir==1) return NULL;
        if(!len2 && dir==-1) return NULL;
        return dir==1?arr[len1-1]:arr[chunk-len2];
     }
     void setDirection(int dir){
        this->dir=dir;
     }
};

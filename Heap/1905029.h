using namespace std;

class Heap
{
private:
    int sz;
    int mxsize;
    int *HeapArr;
    void Heapify(int i)
    {
        int large = i;
        if(2*i+1<=sz && HeapArr[2*i+1]>HeapArr[large])
            large = 2*i+1;
        if(2*i<=sz && HeapArr[2*i]>HeapArr[large])
            large = 2*i;
        if(i!=large) {
            swap(HeapArr[i],HeapArr[large]);
            Heapify(large);
        }
    }

public:
    Heap(int mxsize){
        this->mxsize = mxsize+1;
        HeapArr = new int[mxsize+1];
        sz=0;
    }
    Heap(vector<int>&v){
        sz=0;
        mxsize = v.size();
        HeapArr = new int[mxsize+1];
        //BuildHeap
        for(int i=0; i<v.size(); i++) HeapArr[++sz]=v[i];
        for(int i=sz/2; i>0; i--)
            Heapify(i);
    }
    ~Heap(){
        delete[] HeapArr;
    }

    void insert(int n){
        int index = ++sz;
        HeapArr[sz]=n;
        while(index/2) {
            if(HeapArr[index/2]<HeapArr[index])
                swap(HeapArr[index/2],HeapArr[index]);
            index/=2;
        }
    }

    int getMax(){
        return HeapArr[1];
    }

    void deleteKey(){
        HeapArr[1]=HeapArr[sz--];
        Heapify(1);
    }

    int size(){
        return sz;
    }
};

void heapsort(vector<int> &v){
    Heap h(v);
    v.clear();
    while(h.size()){
        v.push_back(h.getMax());
        h.deleteKey();
    }
}

template <class A> class Queue
{
    virtual void clear()=0;
    virtual void  enqueue(A item)=0;
    virtual A dequeue()=0;
    virtual int length()=0;
    virtual A frontValue()=0;
    virtual A rearValue()=0;
    virtual A leaveQueue()=0;
};


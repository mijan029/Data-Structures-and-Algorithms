template <class A> class Stack
{
    virtual void clear()=0;
    virtual void  push(A item)=0;
    virtual A pop()=0;
    virtual int length()=0;
    virtual A topValue()=0;
    virtual void setDirection(int dir)=0;
};

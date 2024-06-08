template <class A> class List
{
    virtual void clear()=0;
    virtual void insert(A item)=0;
    virtual void append(A item)=0;
    virtual A remove()=0;
    virtual int moveToStart()=0;
    virtual int moveToEnd()=0;
    virtual void prev()=0;
    virtual void next()=0;
    virtual int length()=0;
    virtual int currPos()=0;
    virtual void moveToPos(int pos)=0;
    virtual A getValue()=0;
    virtual int Search(A item)=0;
};

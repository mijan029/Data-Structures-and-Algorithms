template <class A> class LLStack:public Stack<A>
{
private:
    int len;
    class node{
        public:
            node *next;
            A val;
            node(A value, node *nxt=NULL){
                val = value;
                next = nxt;
            }
    };
    node *top;
public:
     LLStack()
     {
         len=0;
         top=NULL;
     }
     ~LLStack(){
        clear();
     }
     void clear(){
        while(top!=NULL) this->pop();
     }
     void push(A item){
        top = new node(item, top);
        len++;
     }
     A pop(){
        if(!len) return NULL;
        A val = top->val;
        node *tmp = top->next;
        delete top;
        top = tmp;
        len--;
        return val;
     }
     int length(){
        return len;
     }
     A topValue(){
        if(!len) return NULL;
        return top->val;
     }
     void setDirection(int dir){

     }
};


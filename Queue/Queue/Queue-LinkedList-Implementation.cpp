template <class A> class LLQueue:public Queue<A>
{
private:
    int len;
    class node{
        public:
            node *next;
            node *prev;
            A val;
            node(A value, node *nxt=NULL, node *prv=NULL){
                val = value;
                next = nxt;
                prev = prv;
            }
    };
    node *head, *tail;
public:
     LLQueue()
     {
         len=0;
         head = NULL;
         tail = NULL;
     }
     ~LLQueue(){
        clear();
     }
     void clear(){
        tail=NULL;
        while(head!=NULL) this->dequeue();
     }
     void enqueue(A item){
        tail = new node(item, NULL, tail);
        if(!len) head = tail;
        else tail->prev->next=tail;
        len++;
     }
     A dequeue(){
        if(!len) return NULL;
        A value = head->val;
        node *temp = head->next;
        delete head;
        head=temp;
        len--;
        return value;
     }
     int length(){
        return len;
     }
     A frontValue(){
        if(!len) return NULL;
        return head->val;
     }
     A rearValue(){
        if(!len) return NULL;
        return tail->val;
     }
     A leaveQueue(){
        if(!len) return NULL;
        A value = tail->val;
        node *temp = tail->prev;
        delete tail;
        tail=temp;
        len--;
        return value;
     }
};



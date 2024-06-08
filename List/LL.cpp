template <class A> class LList:public List<A>
{
private:
    class Node
    {
    public:
        A value;
        Node *next;
        Node *prev;
        Node(A val){
            value = val;
            next = NULL;
            prev = NULL;
        }
    };
    int currpos, len;
    Node *head, *tail, *currptr;
public:

     LList()
     {
         currpos=0;
         len=0;
     }
     ~LList(){
     }
     void clear(){
        len=0;
        currpos=0;
        while(tail!=head){
            Node *temp=tail->next;
            delete tail;
            tail=temp;
        }
        delete tail;
     }

     void insert(A item){
        Node *temp=new Node(item);
        if(currptr!=tail) currptr->prev->next=temp;
        temp->next=currptr;
        if(currptr!=tail) temp->prev=currptr->prev;
        currptr->prev=temp;
        if(currptr==tail) tail=temp;
        currptr=temp;
        len++;
     }
     void append(A item){
        if(!len){
            tail = head = new Node(item);
        }
        else{
            Node *temp=head;
            head->next=new Node(item);
            head=head->next;
            head->prev=temp;
        }
        len++;
     }
     A remove(){
        if(currptr==head){
            currpos--;
            head = currptr->prev;
        }
        else if(currptr==tail)
            tail=currptr->next;
        else{
            currptr->prev->next=currptr->next;
            currptr->next->prev=currptr->prev;
        }
        A val = currptr->value;
        delete currptr;
        len--;
        return val;
     }
     int moveToStart(){
        currpos=0;
        currptr=tail;
        return currpos;
     }
     int moveToEnd(){
        currpos = len-1;
        currptr=head;
        return currpos;
     }
     void prev(){
        currptr=currptr->prev;
        if(currpos) currpos--;
     }
     void next(){
        currptr = currptr->next;
        if(currpos<len-1) currpos++;
     }
     int length(){
        return len;
     }
     int currPos(){
        return currpos;
     }
     void moveToPos(int pos){
        currpos=pos;
        currptr=tail;
        for(int i=1; i<=pos; i++)
            currptr=currptr->next;
     }
     A getValue(){
        return currptr->value;
     }
     int Search(A item){
        int found=-1;
        Node *temp=tail;
        for(int i=0; i<len; i++){
            if(temp->value==item) found=i;
            temp=temp->next;
        }
        return found;
     }
};

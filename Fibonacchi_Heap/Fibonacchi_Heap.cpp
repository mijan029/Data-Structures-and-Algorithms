#include<iostream>
#include<math.h>
using namespace std;

class node
{
public:
    int degree, key;
    bool mark;
    node *parent, *child, *right, *left;
    node(int key){
        this->key = key;
        degree=0;
        mark = false;
        parent = child = right = left = NULL;
    }
    ~node()
    {
        key = 0;
        degree=0;
        mark = false;
        parent = child = right = left = NULL;
    }
};

class fibHeap
{
    int n, curNodeNumber;
    node** nodePointerArray;
    node* min;
public:
    fibHeap(int n)
    {
        this->n = n;
        curNodeNumber = 0;
        nodePointerArray = new node*[n+1];
        min = NULL;
    }

    node* nodePointerOf(int key)
    {
        return nodePointerArray[key];
    }

    void add_root(node* mn, node* nd)
    {
        if(mn == NULL){
            nd->right = nd;
            nd->left = nd;
            return;
        }
        node* temp = mn->right;
        mn->right = nd;
        nd->left = mn;
        nd->right = temp;
        temp->left = nd;
    }

    void remove_root(node* mn)
    {
        mn->left->right = mn->right;
        mn->right->left = mn->left;
    }

    void insert(node* nd)
    {
        if(min == NULL){
            nd->right = nd;
            nd->left = nd;
            min = nd;
        }
        else{
            add_root(min, nd);
            if(nd->key < min->key)
                min = nd;
        }
        nodePointerArray[nd->key] = nd;
        curNodeNumber++;
    }

    void consolidate()
    {
        if(min==NULL) return;
        int m = log2(curNodeNumber)+1;
        node** A = new node*[m];
        for(int i=0; i<=m ; i++)
            A[i]=NULL;
        node* finish = min->left;
        node* now = min;
        bool flag = true;
        while(1)
        {
            if(now == finish) flag = false;
            node*  next = now->right;
            int deg = now->degree;
            while(A[deg]!=NULL){
                if(A[deg]->key<now->key){
                    remove_root(now);
                    now->parent = A[deg];
                    add_root(A[deg]->child,now);
                    now->mark = false;
                    A[deg]->degree++;
                    now = A[deg];
                }
                else if(A[deg]->key>now->key){
                    remove_root(A[deg]);
                    A[deg]->parent = now;
                    add_root(now->child,A[deg]);
                    A[deg]->mark=false;
                    now->degree++;
                    if(min->key > now->key) min = now;
                }
                A[deg] = NULL;
                deg++;
            }
            A[deg] = now;
            if(min->key > now->key) min = now;

            if(!flag) break;
            now = next;
        }
    }

    node extractMin()
    {
        node* start = min->child;
        node* choloman = start;
        if(start!=NULL){
            add_root(min,start);
            start->parent = NULL;
            start->mark = false;
            while(choloman->right!=start){
                add_root(min,choloman->right);
                choloman = choloman->right;
                choloman->parent = NULL;
                choloman->mark = false;
            }
        }
        min->degree=0;
        choloman = min;
        start = min->right;

        remove_root(min);
        min = start;


        consolidate();

        return *choloman;
    }

};

int main()
{
    int n;
    cin>>n;
    fibHeap H(n);
    for(int i=1; i<=n; i++)
        H.insert(new node(i));

    while(1){
        int m;
        cin>>m;
        node* check = H.nodePointerOf(m);
        cout<<check->key<<endl;



    }
}

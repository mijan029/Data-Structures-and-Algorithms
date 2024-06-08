#include<iostream>
#include<fstream>
using namespace std;

class node
{
public:
    int child_count, key, color;
    node *p, *right, *left;
    node(int key, int color){
        this->key = key;
        this->color = color;
        child_count = 0;
        p = right = left = NULL;
    }
    ~node()
    {

    }


};

class RBTree
{
public:
    node *nil, *root;
    RBTree()
    {
        root = nil = new node(0, 1);
    }

};


void add(RBTree *T, node *x, int val)
{
     while(x!=T->nil){
        x->child_count+=val;
        x = x->p;
     }
}
void Left_rotate(RBTree* T, node* x)
{

    node *y = x->right;
    x->right = y->left;
    if(y->left != T->nil){
        y->left->p = x;
    }
    y->p = x->p;
    if(x->p == T->nil){
        T->root = y;
    }
    else if(x == x->p->left){
        x->p->left = y;
    }
    else x->p->right = y;
    y->left = x;
    x->p = y;

    x->child_count+= x->right->child_count - y->child_count;
    y->child_count = x->child_count + y->right->child_count+1;
}

void Right_rotate(RBTree* T, node* x)
{
    node *y = x->left;
    x->left = y->right;
    if(y->right != T->nil){
        y->right->p = x;
    }
    y->p = x->p;
    if(x->p == T->nil){
        T->root = y;
    }
    else if(x == x->p->right){
        x->p->right = y;
    }
    else x->p->left = y;
    y->right = x;
    x->p = y;

    x->child_count+= x->left->child_count - y->child_count;
    y->child_count = x->child_count + y->left->child_count+1;
}


void Insert_Fix(RBTree *T, node* z)
{
    while(z->p->color == 0){
        if(z->p == z->p->p->left){
            node *y = z->p->p->right;
            /// 1st case
            if(y->color == 0){
                z->p->color = 1;
                y->color = 1;
                z->p->p->color = 0;
                z = z->p->p;
            }
            else
            {
                if(z == z->p->right){
                    /// 2nd case
                    z = z->p;
                    Left_rotate(T,z);
                }
                /// 3rd case
                z->p->color = 1;
                z->p->p->color = 0;
                Right_rotate(T,z->p->p);
            }
        }
        else{
            node *y = z->p->p->left;
            if(y->color == 0){
                z->p->color = 1;
                y->color = 1;
                z->p->p->color = 0;
                z = z->p->p;
            }
            else
            {
                if(z == z->p->left){
                    z = z->p;
                    Right_rotate(T,z);
                }
                z->p->color = 1;
                z->p->p->color = 0;
                Left_rotate(T,z->p->p);
            }
        }
    }
    T->root->color = 1;
}


void Insert(RBTree *T, node *z)
{
    node *y = T->nil;
    node *x = T->root;

    while(x != T->nil){
        y = x;
        if(z->key < x->key)
            x = x->left;
        else
            x = x->right;
    }
    z->p = y;
    if(y == T->nil)
        T->root = z;
    else if(z->key < y->key)
        y->left = z;
    else y->right = z;
    z->left = T->nil;
    z->right = T->nil;
    z->color = 0;
    add(T, z, 1);
    Insert_Fix(T,z);
}

node* minimum(RBTree *T, node *n)
{
    while(n->left!=T->nil) n = n->left;
    return n;
}

void transplant(RBTree *T, node *u, node *v){
    if(u->p == T->nil)
        T->root = v;
    else if(u == u->p->left)
        u->p->left = v;
    else
        u->p->right = v;
    v->p = u->p;
}

void delete_Fix(RBTree *T, node *x)
{
      while(x != T->root && x->color == 1){
        if(x == x->p->left){
            node *w = x->p->right;
            if(w->color == 0){
                ///case 1
                w->color = 1;
                x->p->color = 0;
                Left_rotate(T,x->p);
                w = x->p->right;
            }
            if(w->left->color == 1 && w->right->color == 1){
                /// 2nd case
                w->color = 0;
                x = x->p;
            }
            else{
                ///3rd case
                if(w->right->color == 1){
                    w->left->color = 1;
                    w->color = 0;
                    Right_rotate(T,w);
                    w = x->p->right;
                }
                /// 4th case
                w->color = x->p->color;
                x->p->color = 1;
                w->right->color = 1;
                Left_rotate(T,x->p);
                x = T->root;
            }
        }
        else{
            node *w = x->p->left;
            if(w->color == 0){
                ///case 1
                w->color = 1;
                x->p->color = 0;
                Right_rotate(T,x->p);
                w = x->p->left;
            }
            if(w->right->color == 1 && w->left->color == 1){
                /// 2nd case
                w->color = 0;
                x = x->p;
            }
            else{
                ///3rd case
                if(w->left->color == 1){
                    w->right->color = 1;
                    w->color = 0;
                    Left_rotate(T,w);
                    w = x->p->left;
                }
                /// 4th case
                w->color = x->p->color;
                x->p->color = 1;
                w->left->color = 1;
                Right_rotate(T,x->p);
                x = T->root;
            }
        }
      }
      x->color = 1;
}

void Delete(RBTree *T, node* z)
{
    node *y = z, *x;
    int color = y->color;
    if(z->left == T->nil){
        x = z->right;
        add(T, z, -1);
        transplant(T,z,x);
    }
    else if(z->right == T->nil){
        x = z->left;
        add(T, z, -1);
        transplant(T,z,x);
    }
    else{
        y = minimum(T, z->right);
        z->key = y->key;
        color = y->color;
        x = y->right;
        add(T, y, -1);
        transplant(T,y,x);
    }

    delete y;
    if(color == 1)
        delete_Fix(T,x);
}




node* Search(RBTree *T, int x)
{
    node *r = T->root;
    while(r != T->nil){
        if(r->key == x) return r;
        if(r->key > x) r = r->left;
        else r = r->right;
    }
    return NULL;
}

int lessOf(RBTree *T , int x)
{
    int ans = 0;
    node *r = T->root;
    while(r != T->nil){
        if(r->key >= x){
            ans += r->right->child_count+1;
            r = r->left;
        }
        else
            r = r->right;
    }
    return ans;

}

int main()
{
    int n, numOfNode=0;
    ifstream cin("./in.txt");
    //ofstream cout("./myout.txt");
    cin>>n;
    RBTree *T = new RBTree();
    cout<<n<<endl;
    while(n--){
        int e, x;
        cin>>e>>x;
        node *nd = Search(T, x);
        if(e==0){
            if(nd == NULL) cout<<0<<' '<<x<<' '<<0<<endl;
            else {
                Delete(T, nd);
                numOfNode--;
                cout<<0<<' '<<x<<' '<<1<<endl;
            }
        }
        else if(e==1){
            if(nd != NULL) cout<<1<<' '<<x<<' '<<0<<endl;
            else {
                Insert(T, new node(x,0));
                numOfNode++;
                cout<<1<<' '<<x<<' '<<1<<endl;
            }
        }
        else if(e==2){
            if(nd == NULL) cout<<2<<' '<<x<<' '<<0<<endl;
            else {
                cout<<2<<' '<<x<<' '<<1<<endl;
            }
        }
        else{
            cout<<3<<' '<<x<<' '<<numOfNode-lessOf(T, x)<<endl;
        }
    }

    return 0;
}

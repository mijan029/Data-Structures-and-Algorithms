#include<iostream>
#include<sstream>
#include<fstream>
using namespace std;

template <class A> class node
{
private:
    A key;
    node* left;
    node* right;
public:
    node(A key){
        this->key=key;
        left=NULL;
        right=NULL;
    }
    node(){}
    ~node(){

    }
    A getKey(){ return key; }
    void setKey(A k) { key = k; }
    node* getLeft(){ return left; }
    void setLeft(node<A>* nd){ left=nd; }
    node* getRight(){ return right; }
    void setRight(node<A>* nd){ right=nd; }
    bool isLeaf() { return (left==NULL && right==NULL); }
};

template <class A> class BST : public node<A>
{
private:
    node<A>* root;
    node<A>* helper;
    A getMin(node<A>* n){
        if(n->getLeft() == NULL) return n->getKey();
        return getMin(n->getLeft());
    }
    node<A>* helpDelete(A key, node<A>* rt){
        if(rt==NULL) return NULL;
        if(rt->getKey()>key) rt->setLeft(helpDelete(key, rt->getLeft()));
        else if(rt->getKey()<key) { rt->setRight(helpDelete(key, rt->getRight()));}
        else{
            node<A>*temp = rt;
            if(rt->isLeaf()){ delete rt; return NULL; }
            else if(rt->getLeft()==NULL) rt = rt->getRight();
            else if(rt->getRight()==NULL) rt = rt->getLeft();
            else{
                A mnKey = getMin(rt->getRight());
                helpDelete(mnKey,root);
                rt->setKey(mnKey);
                temp = NULL;
            }
            delete temp;
        }
        return rt;
    }

    void help_InOrder(node<A>*rt)
    {
        if(rt==NULL) return;
        help_InOrder(rt->getLeft());
        cout<<rt->getKey()<<' ';
        help_InOrder(rt->getRight());
    }
    void help_PreOrder(node<A>*rt)
    {
        if(rt==NULL) return;
        cout<<rt->getKey()<<' ';
        help_PreOrder(rt->getLeft());
        help_PreOrder(rt->getRight());
    }
    void help_PostOrder(node<A>*rt)
    {
        if(rt==NULL) return;
        help_PostOrder(rt->getLeft());
        help_PostOrder(rt->getRight());
        cout<<rt->getKey()<<' ';
    }

    void print(node<A>*rt)
    {
        if(rt==NULL) return;
        if(rt->isLeaf()){
            cout<<rt->getKey();
            return;
        }
        cout<<rt->getKey()<<'(';
        print(rt->getLeft());
        cout<<")(";
        print(rt->getRight());
        cout<<')';
    }
    void helpclear(node<A>* rt){
        if(rt==NULL) return;
        helpclear(rt->getLeft());
        helpclear(rt->getRight());
        delete rt;

    }
public:
    BST(){

        root = NULL;
        helper = NULL;
    }
    ~BST(){
        helpclear(root);
    }
    bool Find(A key){
        while(helper!=NULL){
            if(helper->getKey() == key) { helper = root; return true; }
            helper->getKey()>key ? helper = helper->getLeft():helper=helper->getRight();
        }
        helper = root;
        return false;
    }
    void Insert(A key){
        node<A>* help_helper = helper;
        while(helper!=NULL){
            help_helper = helper;
            helper->getKey()>key ? helper = helper->getLeft():helper=helper->getRight();
        }
        if(root == NULL) root = new node<A>(key);
        else {
            if(help_helper->getKey() > key)
                help_helper->setLeft(new node<A>(key));
            else help_helper->setRight(new node<A>(key));
        }
        helper = root;
        print(root);
    }
    void Delete(A key){
        if(!Find(key)) cout<<"Invalid Operation";
        else {
            helper = root = helpDelete(key,root);
            print(root);
        }
    }
    void In_Order(){
        help_InOrder(root);
    }
    void Pre_Order(){
        help_PreOrder(root);
    }
    void Post_Order(){
        help_PostOrder(root);
    }
};

int main()
{
    BST<int> bst;
    string line;
    fstream myfile("BST.txt");
    while(getline(myfile,line)){
        string st;
        for(int i=2; i<line.size(); i++)
            st+=line[i];
        if(line[0]!='T') {
            int x;
            stringstream val(st);
            val>>x;
            if(line[0]=='F') {
                if(bst.Find(x)) cout<<"True";
                else cout<<"False";
            }
            if(line[0]=='I') bst.Insert(x);
            if(line[0]=='D') bst.Delete(x);
        }
        else{
            if(st=="In") bst.In_Order();
            else if(st=="Pre") bst.Pre_Order();
            else bst.Post_Order();
        }
        cout<<endl;
    }
}

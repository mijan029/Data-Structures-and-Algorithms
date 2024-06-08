#include<bits/stdc++.h>
#include <time.h>
using namespace std;

vector< string > v_str;
#define ll long long
ll p = 111111, mod = 1000000007;
double report[5][15][5];

template <class A> class LList
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


string randomWordGenerator()
{
    string s="";
    for(int i=0; i<7; i++){
        s+='a'+(rand()%26);
    }
    return s;
}

ll Hash1(string s)
{
    int n = s.size();
    ll arr[n+1];
    arr[0]=1;
    for(int i=1; i<n; i++)
        arr[i] = arr[i-1]*p % mod;
    ll hashVal=0;
    for(int i=0; i<n; i++)
        hashVal=(hashVal+arr[i]*(s[i]-'a'))%mod;
    return hashVal;
}

ll Hash2(string s, ll n)
{
    ll hashVal=Hash1(s);
    if(!hashVal%n) return 1;
    return n-(hashVal%n);
}

void uniqueStrings(int n)
{
    v_str.clear();
    set<string> s;
    int j=0;
    while(s.size()<n){
        string str = randomWordGenerator();
        if(s.find(str)==s.end())
            v_str.push_back(str);
        s.insert(str);
    }
}

void uniqueHashValue(int n, ll p, ll mod)
{
    set<ll> s_int;
    for(auto x:v_str ){
        ll hashVal = Hash1(x);
        s_int.insert(hashVal);
    }
    int m = s_int.size();
    cout<<m<<' '<<n<<endl;
    cout<<"There are "<<100.0*m/n<<"% unique hash values of the Keys"<<endl;
}

class SC{
    LList<pair<string,int> > *arr;
    int n ;
public:
    SC(int n)
    {
        this->n = n;
        arr = new LList<pair<string,int> >[n];
    }
    ~SC(){
    }
    void Insert(pair<string,int> s)
    {
        int ind = Hash1(s.first)%n;
        arr[ind].append(s);
    }
    int Search(string s){
        int ind = Hash1(s)%n;
        arr[ind].moveToStart();
        for(int i=0; i<arr[ind].length(); i++){
            pair<string,int> pr = arr[ind].getValue();
            if(pr.first == s) return i;
            arr[ind].next();
        }
        return -1;
    }

    void Delete(string s){
        int pos = Search(s);
        if(pos==-1) cout<<"There is no such key"<<endl;
        else{
            int ind = Hash1(s)%n;
            arr[ind].moveToPos(pos);
            arr[ind].remove();
        }
    }

    int keyVal(string s)
    {
        int ind = Hash1(s)%n;
        arr[ind].moveToStart();
        for(int i=0; i<arr[ind].length(); i++){
            pair<string,int> pr = arr[ind].getValue();
            if(pr.first == s) return pr.second;
            arr[ind].next();
        }
        return 0;
    }
    void check()
    {
        for(int i=0; i<n; i++){
            arr[i].moveToStart();
            for(int j=0; j<arr[i].length(); j++){
                pair<string,int> ps = arr[i].getValue();
                string s = arr[i].getValue().first;
                arr[i].next();
                cout<<i<<' '<<s<<' '<<ps.second<<endl;
            }
            cout<<endl;
        }
    }
};


class LP{
    pair<string,int> *arr;
    int n ;
public:
    double probCounting;
    LP(int n)
    {
        probCounting=0;
        this->n = n;
        arr = new pair<string,int>[n];
        for(int i=0; i<n; i++)
            arr[i] = {"",0};
    }
    ~LP(){
    }
    void Insert(pair<string,int> s)
    {

        for(int i=0; i<n; i++){
            int ind = (Hash1(s.first)+i)%n;
            if(arr[ind].first=="" || arr[ind].first=="0"){
                arr[ind]=s;
                break;
            }
        }
    }
    int Search(string s){
        for(int i=0; i<n; i++){
            if(i) probCounting++;
            int ind = (Hash1(s)+i)%n;
            if(arr[ind].first==s) return i;
            if(arr[ind].first==""){
                break;
            }
        }
        //cout<<"key not found"<<endl;
        return -1;
    }

    int keyVal(string s)
    {
        for(int i=0; i<n; i++){
            int ind = (Hash1(s)+i)%n;
            if(arr[ind].first==s) return arr[ind].second;
            if(arr[ind].first==""){
                break;
            }
        }
        return 0;
    }

    void Delete(string s){
        int pos = Search(s);
        if(pos==-1) cout<<"There is no such key"<<endl;
        else{
            int ind = (Hash1(s)+pos)%n;
            arr[ind] = {"0",0};
        }
    }
    void check()
    {
        for(int i=0; i<n; i++){
            cout<<arr[i].first<<' '<<arr[i].second<<endl;
        }
    }
};


class QP{
    pair<string,int> *arr;
    int n ;
public:
    double probCounting;
    QP(int n)
    {
        probCounting=0;
        this->n = n;
        arr = new pair<string,int>[n];
        for(int i=0; i<n; i++)
            arr[i] = {"",0};
    }
    ~QP(){
    }
    void Insert(pair<string,int> s)
    {

        for(int i=0; i<n; i++){
            int ind = (Hash1(s.first)+11*i+17*i*i)%n;
            if(arr[ind].first=="" || arr[ind].first=="0"){
                arr[ind]=s;
                break;
            }
        }
    }




    int Search(string s){
        for(int i=0; i<n; i++){
            if(i) probCounting++;
            int ind = (Hash1(s)+11*i+17*i*i)%n;
            if(arr[ind].first==s) return 11*i+17*i*i;
            if(arr[ind].first==""){
                break;
            }
        }
        //cout<<"key not found"<<endl;
        return -1;
    }

    int keyVal(string s)
    {
        for(int i=0; i<n; i++){
            int ind = (Hash1(s)+11*i+17*i*i)%n;
            if(arr[ind].first==s) return arr[ind].second;
            if(arr[ind].first==""){
                break;
            }
        }
        return 0;
    }

    void Delete(string s){
        int pos = Search(s);
        if(pos==-1) cout<<"There is no such key"<<endl;
        else{
            int ind = (Hash1(s)+pos)%n;
            arr[ind] = {"0",0};
        }
    }
    void check()
    {
        for(int i=0; i<n; i++){
            cout<<arr[i].first<<' '<<arr[i].second<<endl;
        }
    }
};


class DP{
    pair<string,int> *arr;
    int n ;

public:
    double probCounting;
    DP(int n)
    {
        probCounting = 0;
        this->n = n;
        arr = new pair<string,int>[n];
        for(int i=0; i<n; i++)
            arr[i] = {"",0};
    }
    ~DP(){
    }
    void Insert(pair<string,int> s)
    {

        for(int i=0; i<n; i++){
            int ind = (Hash1(s.first)+Hash2(s.first, n)*i)%n;
            if(arr[ind].first=="" || arr[ind].first=="0"){
                arr[ind]=s;
                break;
            }
        }
    }
    int Search(string s){
        for(int i=0; i<n; i++){
            if(i) probCounting++;
            int ind = (Hash1(s)+Hash2(s, n)*i)%n;
            if(arr[ind].first==s) return Hash2(s, n)*i;
            if(arr[ind].first==""){
                break;
            }
        }
        //cout<<"key not found"<<endl;
        return -1;
    }

    int keyVal(string s)
    {
        for(int i=0; i<n; i++){
            int ind = (Hash1(s)+Hash2(s, n)*i)%n;
            if(arr[ind].first==s) return arr[ind].second;
            if(arr[ind].first==""){
                break;
            }
        }
        return 0;
    }

    void Delete(string s){
        int pos = Search(s);
        if(pos==-1) cout<<"There is no such key"<<endl;
        else{
            int ind = (Hash1(s)+pos)%n;
            arr[ind] = {"0",0};
        }
    }
    void check()
    {
        for(int i=0; i<n; i++){
            cout<<arr[i].first<<' '<<arr[i].second<<endl;
        }
    }
};


int main()
{

    srand(time(0));

    int n;
    cin>>n;

    /*DP *sep = new DP(n);
    int j=0;
    while(1)
    {
        int k; string s;
        cin>>k>>s;
        if(k==1) sep->Insert({s,j}), j++;
        else if(k==2) sep->Delete(s);
        else{
            cout<<sep->keyVal(s)<<endl;
        }
    }*/

    std::chrono::steady_clock::time_point startTime, endTime;
    double timeTaken;

    for(double i = 4; i<=9; i+=1){
        //cout<<"------------------------------start with i = ."<<i<<"----------------------------"<<endl;
        int m = (i*n)/10;
        int k = m*0.1;
        double k1=k;
        int l=i;
        uniqueStrings(m);


        ///seperate chaining
        //cout<<"Starting seperate chaining"<<endl;
        SC *sep = new SC(n);
        for(int j = 0; j<m; j++)
            sep->Insert({v_str[j],j+1});

        startTime = std::chrono::steady_clock::now();
        for(int j = 0; j<k; j++)
            sep->Search(v_str[j]);
        endTime = std::chrono::steady_clock::now();
        timeTaken = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime).count();
        report[0][l][0]=timeTaken/k1;
        report[0][l][1]=0;
        //cout<<"Time Taken before "<<timeTaken<<endl;

        for(int j = 0; j<k; j++)
            sep->Delete(v_str[j]);

        startTime = std::chrono::steady_clock::now();
        for(int j = k; j<k+k/2; j++)
            sep->Search(v_str[j]);
        for(int j = 0; j<k-k/2; j++)
            sep->Search(v_str[j]);
        endTime = std::chrono::steady_clock::now();
        timeTaken = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime).count();
        report[0][l][2]=timeTaken/k1;
        report[0][l][3]=0;
        //cout<<"Time Taken after "<<timeTaken<<endl;



        ///Linear Probing
        //cout<<"Linear probing starting"<<endl;
        LP *lin = new LP(n);
        for(int j = 0; j<m; j++)
            lin->Insert({v_str[j],j+1});

        startTime = std::chrono::steady_clock::now();
        lin->probCounting=0;
        for(int j = 0; j<k; j++)
            lin->Search(v_str[j]);
        endTime = std::chrono::steady_clock::now();
        timeTaken = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime).count();
        report[1][l][0]=timeTaken/k1;
        report[1][l][1]=lin->probCounting/k1;
        //cout<<"Time Taken before "<<timeTaken<<' '<<"prob "<<lin->probCounting<<endl;

        for(int j = 0; j<k; j++)
            lin->Delete(v_str[j]);

        startTime = std::chrono::steady_clock::now();
        lin->probCounting=0;
        for(int j = k; j<k+k/2; j++)
            lin->Search(v_str[j]);
        for(int j = 0; j<k-k/2; j++)
            lin->Search(v_str[j]);
        endTime = std::chrono::steady_clock::now();
        timeTaken = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime).count();
        report[1][l][2]=timeTaken/k1;
        report[1][l][3]=lin->probCounting/k1;
        //cout<<"Time Taken after "<<timeTaken<<' '<<"prob "<<lin->probCounting<<endl;


        ///Quadratic Probing
        //cout<<"Quadratic probing starting"<<endl;
        QP *qud = new QP(n);
        for(int j = 0; j<m; j++)
            qud->Insert({v_str[j],j+1});

        startTime = std::chrono::steady_clock::now();
        qud->probCounting=0;
        for(int j = 0; j<k; j++)
            qud->Search(v_str[j]);
        endTime = std::chrono::steady_clock::now();
        timeTaken = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime).count();
        report[2][l][0]=timeTaken/k1;
        report[2][l][1]=lin->probCounting/k1;
        //cout<<"Time Taken before "<<timeTaken<<' '<<"prob "<<qud->probCounting<<endl;

        for(int j = 0; j<k; j++)
            qud->Delete(v_str[j]);

        startTime = std::chrono::steady_clock::now();
        qud->probCounting=0;
        for(int j = k; j<k+k/2; j++)
            qud->Search(v_str[j]);
        for(int j = 0; j<k-k/2; j++)
            qud->Search(v_str[j]);
        endTime = std::chrono::steady_clock::now();
        timeTaken = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime).count();
        report[2][l][2]=timeTaken/k1;
        report[2][l][3]=lin->probCounting/k1;
        //cout<<"Time Taken after "<<timeTaken<<' '<<"prob "<<qud->probCounting<<endl;


        ///Double Probing
        //cout<<"Double probing starting"<<endl;
        DP *dou = new DP(n);
        for(int j = 0; j<m; j++)
            dou->Insert({v_str[j],j+1});

        startTime = std::chrono::steady_clock::now();
        dou->probCounting=0;
        for(int j = 0; j<k; j++)
            dou->Search(v_str[j]);
        endTime = std::chrono::steady_clock::now();
        timeTaken = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime).count();
        report[3][l][0]=timeTaken/k1;
        report[3][l][1]=lin->probCounting/k1;
        //cout<<"Time Taken before "<<timeTaken<<' '<<"prob "<<dou->probCounting<<endl;


        for(int j = 0; j<k; j++)
            dou->Delete(v_str[j]);

        startTime = std::chrono::steady_clock::now();
        dou->probCounting=0;
        for(int j = k; j<k+k/2; j++)
            dou->Search(v_str[j]);
        for(int j = 0; j<k-k/2; j++)
            dou->Search(v_str[j]);
        endTime = std::chrono::steady_clock::now();
        timeTaken = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime).count();
        report[3][l][2]=timeTaken/k1;
        report[3][l][3]=lin->probCounting/k1;
        //cout<<"Time Taken after "<<timeTaken<<' '<<"prob "<<dou->probCounting<<endl;
    }


    for(int i=0; i<4; i++){
        cout<<"                                          Table : "<<i+1<<endl;
        cout<<"--------------------------------------------------------------------------------------------------------------------"<<endl;
        cout<<"---------------Before Deletion-------------------------After Deletion-----------------"<<endl;
        cout<<"Load Factor    "<<"Avg S_time      "<<"Avg_probe                 "<<"Avg S_time      "<<"Avg_probe     "<<endl;
        for(int j=4; j<10; j++){
            cout<<'.'<<j<<"               "<<report[i][j][0]<<"                   "<<report[i][j][1]<<"                 "<<report[i][j][2]<<"        "<<report[i][j][3]<<endl<<endl;
        }
        cout<<endl<<endl;
    }

    cout<<endl<<endl;
    for(int i=4; i<10; i++){
        cout<<"                                          Table : "<<i-3<<endl;
        cout<<"--------------------------------------------------------------------------------------------------------------------"<<endl;
        cout<<"----------------------Before Deletion-------------------------After Deletion-----------------"<<endl;
        cout<<"Method                  "<<"Avg S_time            "<<"Avg_probe            "<<"Avg S_time          "<<"Avg_probe     "<<endl;
        for(int j=0; j<4; j++){
            if(j==0) cout<<"Sep chaining";
            else if(j==1) cout<<"Linear Probe";
            else if(j==2) cout<<"Quadra probe";
            else cout<<"DoublHashing";
            cout<<"             "<<report[j][i][0]<<"                   "<<report[j][i][1]<<"                 "<<report[j][i][2]<<"        "<<report[j][i][3]<<endl<<endl;
        }
        cout<<endl<<endl;
    }



    return 0;
}


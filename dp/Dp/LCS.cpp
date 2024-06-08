#include<iostream>
#include<algorithm>
using namespace std;

string save_str[55][55];
bool vs[55][55];

string LCS(string s1, string s2, int i, int j)
{
    if(i<0 || j<0) return "";
    if(vs[i][j]) return save_str[i][j];
    string s="";
    if(s1[i]==s2[j]) {
        s+=LCS(s1,s2,i-1,j-1);
        s+=s1[i];
    }
    else {
        string str1 = LCS(s1,s2,i-1,j);
        string str2 = LCS(s1,s2,i,j-1);
        str1.size()>=str2.size() ? s=str1 : s=str2;
    }
    vs[i][j]=1;
    save_str[i][j]=s;
    return s;
}

int main()
{
    string s1, s2, common;
    cin>>s1>>s2;
    common = LCS(s1, s2, s1.size()-1, s2.size()-1);
    cout<<common.size()<<endl<<common<<endl;
}

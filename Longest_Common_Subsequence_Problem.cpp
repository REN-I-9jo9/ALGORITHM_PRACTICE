#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
using namespace std;
struct element
{
    int n=0;
    int prex=0,prey=0;
    int thisx=0,thisy=0;
};
element lcs(char s1,char s2,element m,element l,element t,element lt);
int main()
{
/** --------------------Read----------------------------- **/
    cout<<"¿é¤J¨â­Ó¦r¦ê"<<endl;
    string s1,s2;
    cin>>s1>>s2;
    element lcsr[s1.size()+1][s2.size()+1];
/** --------------------Read----------------------------- **/
/** --------------------LCS------------------------------ **/
    for(int i1=0;i1<=s1.size();i1++)
    {
        for(int i2=0;i2<=s2.size();i2++)
        {
            lcsr[i1][i2].thisx=i1;
            lcsr[i1][i2].thisy=i2;
            lcsr[i1][i2]=lcs(s1[i1-1],s2[i2-1],lcsr[i1][i2],lcsr[i1-1][i2],lcsr[i1][i2-1],lcsr[i1-1][i2-1]);
        }
    }
/** --------------------LCS------------------------------ **/
/** --------------------Result--------------------------- **/
    int wid=5;
    cout<<setw(wid*2)<<"000";
    for(int i2=0;i2<s2.size();i2++)
        cout<<setw(wid)<<s2[i2];
    cout<<endl;
    for(int i1=0;i1<=s1.size();i1++)
    {
        if(i1>=1)
            cout<<setw(wid)<<s1[i1-1];
        else
            cout<<setw(wid)<<"000";
        for(int i2=0;i2<=s2.size();i2++)
            cout<<setw(wid)<<lcsr[i1][i2].n;
        cout<<endl;
    }
    cout<<endl;
    cout<<"Ans:";
    element c=lcsr[s1.size()][s2.size()];
    string b;
    while(1)
    {
        if((c.thisx==c.prex+1&&c.thisy==c.prey+1))
            b+=s1[c.thisx-1];
        //cout<<"("<<c.thisx<<","<<c.thisy<<")<--";
        if(c.thisx==0||c.thisy==0)
            break;
        c=lcsr[c.prex][c.prey];
    }
    //cout<<"(0,0)";
    cout<<" ";
    for(int i=b.length()-1;i>=0;i--)
        cout<<b[i];
    cout<<endl;

/** --------------------Result--------------------------- **/

    return 0;
}
element lcs(char s1,char s2,element m,element l,element t,element lt)
{
    if(m.thisx==0||m.thisy==0)
    {
        return m;
    }
    if(s1==s2)
    {
        m.n=lt.n+1;
        m.prex=lt.thisx;
        m.prey=lt.thisy;
        return m;
    }
    else
    {
        if(l.n>=t.n)
        {
            m.n=l.n;
            m.prex=l.thisx;
            m.prey=l.thisy;
            return m;
        }
        else if(t.n>l.n)
        {
            m.n=t.n;
            m.prex=t.thisx;
            m.prey=t.thisy;
            return m;
        }
    }
}















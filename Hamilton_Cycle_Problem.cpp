#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <queue>
#include <string>
using namespace std;
bool check(int arr[],int end,int a);
bool check2(vector<int> arr,int end,int a);
int main()
{
/** --------------------Read The File-------------------- **/
    cout<<"Åª¨úinput4.txt"<<endl;
    ifstream in("input4.txt");
    int v1,v2,vcount;
    in>>vcount;
    bool graph[vcount+1][vcount+1]={0};
    for(int i=0;i<=vcount;i++)
        for(int j=0;j<=vcount;j++)
            graph[i][j]=0;
    while(in>>v1>>v2)
    {
        graph[v1][v2]=1;
        graph[v2][v1]=1;
    }
    in.close();
    cout<<"The Number Of Vertex Is "<<vcount<<endl<<"Edges:"<<endl;
    for(int i=1;i<=vcount;i++)
        for(int j=i;j<=vcount;j++)
            if(graph[i][j]==1)
                cout<<i<<" - "<<j<<endl;
    cout<<endl;


/** --------------------Read The File-------------------- **/
/** --------------------Hamilton Cycle(DFS)-------------- **/
    int resultDFS[vcount+1]={0};
    resultDFS[0]=1;
    cout<<"DFS:"<<endl<<endl;
    for(int level=0;level<=vcount;level++)
    {
        cout<<"NO."<<level<<" : "<<resultDFS[level]<<endl;
        int start=resultDFS[level+1];
        resultDFS[level+1]=0;
        for(int i=start+1;i<=vcount;i++)
        {
            if(graph[resultDFS[level]][i])
            {
                cout<<"check "<<resultDFS[level]<<" - "<<i<<" ";
                if(!check(resultDFS,vcount+1,i))
                {
                    cout<<"ok"<<endl;
                    resultDFS[level+1]=i;
                    break;
                }
                else{cout<<"cycle"<<endl;}
            }
        }
        for(int i=0;resultDFS[i]!=0;i++)
            cout<<resultDFS[i]<<" ";
        cout<<endl<<endl;
        if(!resultDFS[level+1])
        {
            if((level==vcount-1)&&graph[vcount][1])
            {
                cout<<"complete"<<endl<<endl;
                break;
            }
            else
            {
                level-=2;
                cout<<"back"<<endl;
            }
        }
    }
    resultDFS[vcount]=1;
/** --------------------Hamilton Cycle(DFS)-------------- **/
/** --------------------Result(DFS)---------------------- **/
    cout<<"Ans:"<<endl;
    for(int i=0;i<=vcount;i++)
    {
        cout<<resultDFS[i];
        if(i!=vcount)
            cout<<"-";
    }
    cout<<endl;
/** --------------------Result(DFS)---------------------- **/
/** --------------------Hamilton Cycle(BFS)-------------- **/
    cout<<endl<<endl<<"BFS:"<<endl<<endl;
    vector<int> a;
    a.push_back(1);
    queue<vector<int> > BFStree;
    BFStree.push(a);
    cout<<"push "<<a.back()<<endl;
    while(!BFStree.empty())
    {
        vector<int> current=BFStree.front();
        if(current.size()==vcount&&graph[current.back()][1]==1)
        {
            cout<<"complete"<<endl;
            BFStree.front().push_back(1);
            break;
        }
        cout<<"pop  "<<current.back()<<endl;
        BFStree.pop();
        for(int i=0;i<=vcount;i++)
        {

            if(graph[current.back()][i])
            {
                if(!check2(current,current.size(),i))
                {
                    cout<<"push "<<i<<endl;
                    vector<int> add=current;
                    add.push_back(i);
                    BFStree.push(add);
                }
            }
        }
    }


/** --------------------Hamilton Cycle(BFS)-------------- **/
/** --------------------Result(BFS)---------------------- **/
    vector<int> res=BFStree.front();
    cout<<endl<<"Ans:"<<endl;
    for(int i=0;i<=vcount;i++)
    {
        cout<<res[i];
        if(i!=vcount)
            cout<<"-";
    }
    cout<<endl;
/** --------------------Result(BFS)---------------------- **/
    return 0;
}
bool check(int arr[],int end,int a)
{
    for(int i=0;i<end;i++)
        if(arr[i]==a)
            return 1;
    return 0;
}
bool check2(vector<int> arr,int end,int a)
{
    for(int i=0;i<end;i++)
        if(arr[i]==a)
            return 1;
    return 0;
}

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;
struct coord
{
    float x,y;
    int rank=0;
};
void quick_sort(coord arr[],int start,int end);
void rank_find(coord arr[],int start,int end);
void rank_find2(coord arr[],int start,int end);
int main()
{
/** --------------------Read The File-------------------- **/
    ifstream in("input1.txt");
    coord dot[2000];
    int count=0;
    while(in>>dot[count].x>>dot[count].y)
        count++;
    cout<<"The Number Of Dots Is "<<count<<endl;
    in.close();
/** --------------------Read The File-------------------- **/

/** --------------------Quick Sort----------------------- **/
    quick_sort(dot,0,count-1);
/** --------------------Quick Sort----------------------- **/

/** --------------------Rank Finding--------------------- **/
    rank_find(dot,0,count-1);
/** --------------------Rank Finding--------------------- **/

/** --------------------Result--------------------------- **/
    int maxrank=0,minrank=0;
    float average=0;
    for(int i=0;i<count;i++)
    {
        if(i==0||dot[i].rank>=maxrank)
            maxrank=dot[i].rank;
        if(i==0||dot[i].rank<=minrank)
            minrank=dot[i].rank;
        average+=dot[i].rank;
    }
    average/=count;

    cout<<"Max Rank="<<maxrank<<endl<<"Min Rank="<<minrank<<endl<<"Avrage="<< setprecision(2)<<average<<endl<<endl;
    cout<<setw(14)<<"X "<<setw(11)<<"Y "<<setw(5)<<"Rank"<<endl;
    for(int i=0;i<count;i++)
        cout<<setw(3)<<i+1<<setw(10)<<dot[i].x<<" "<<setw(10)<<dot[i].y<<" "<<setw(5)<<dot[i].rank<<endl;
/** --------------------Result--------------------------- **/
    return 0;
}
void rank_find(coord arr[],int begin,int end)
{
    if (begin>=end)
        return;
    int center=(end+begin)/2;
    rank_find(arr,begin,center);
    rank_find(arr,center+1,end);

    for(int i=center+1;i<=end;i++)
    {
        for(int j=begin;j<=center;j++)
        {
            if(arr[j].y<arr[i].y)
                arr[i].rank++;
        }
    }
    return;
}
void quick_sort(coord arr[],int begin,int end)
{
	if (begin>=end)
        return;
	coord center=arr[end];
	int left=begin,right=end-1;
	while (left<right)
    {
		while (arr[left].x<center.x&&left<right)
            left++;
        while (arr[right].x>=center.x&&left<right)
            right--;
        std::swap(arr[left],arr[right]);
	}
	if (arr[left].x>=arr[end].x)
		std::swap(arr[left],arr[end]);
	else
		left++;
	quick_sort(arr,begin,left-1);
	quick_sort(arr,left+1,end);
}
//void rank_find2(coord arr[],int start,int end)
//{
//    for(int i=start;i<=end;i++)
//    {
//        for(int j=start;j<i;j++)
//        {
//            if(arr[i].y>arr[j].y)
//                arr[i].rank++;
//        }
//    }
//}

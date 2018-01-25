#include<iostream>
#include<cstdlib>
#include<fstream>
#include<cmath>
using namespace std;
struct coord{float x,y;};
coord dot[2000];
int maxcount=0;
int r[2000];
int check=1;

void quick_sort(coord a[],int l,int r);
void convex_hull(int n,int m);
int mer(int num,int count);
int main()
{
/** --------------------Read The File-------------------- **/
    cout<<"Ū��input3.txt"<<endl;
    ifstream in("input3.txt");
    if(!in)
    {
        cout<<"Fail";
        system("PAUSE");
        return 0;
    }
    while(in>>dot[maxcount].x>>dot[maxcount].y)
        maxcount++;
    cout<<"The Number Of Dots Is "<<maxcount<<endl;
    in.close();
/** --------------------Read The File-------------------- **/
/** --------------------Sort----------------------------- **/
    quick_sort(dot,0,maxcount-1);
    for(int i=0;i<maxcount;i++)
        cout<<i<<"("<<dot[i].x<<","<<dot[i].y<<")"<<endl;
    cout<<endl;
/** --------------------Sort----------------------------- **/
/** --------------------Convex Hull---------------------- **/
    convex_hull(maxcount,0);
/** --------------------Convex Hull---------------------- **/
    system("PAUSE");
    return 0;
}
/** /////////////////////////////////////////////�ֳt�Ƨ� **/
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
        swap(arr[left],arr[right]);
	}
	if (arr[left].x>=arr[end].x)
		swap(arr[left],arr[end]);
	else
		left++;
	quick_sort(arr,begin,left-1);
	quick_sort(arr,left+1,end);
}
/** ////////////////////////////////////////////�ֳt�Ƨ� **/
/** //////////////////////////////////////////���j�ε��G **/
void convex_hull(int count,int start)//n�`�� m�Ĥ@���I���s��
{
    if(count>3)
    {
        convex_hull(count/2,start);
        convex_hull(count-count/2,start+count/2);
        int mergenum=mer(start,count);
        if(count==maxcount||count==maxcount/2||count==(maxcount-maxcount/2))
        {
            if(count==maxcount)
                cout<<"FINAL: ";
            else if(check)
            {
                cout<<"LEFT: ";
                check=0;
            }
            else if(count==(maxcount-maxcount/2))
                cout<<"RIGHT: ";
            cout<<mergenum<<" dots : ";
            for(int i=start;i<start+count;i++)
            {
                if(r[i]==mergenum)
                {
                    cout<<i<<"("<<dot[i].x<<","<<dot[i].y<<")"<<" => ";
                    break;
                }
            }
            for(int i=1;i<=mergenum;i++)
            {
                for(int j=start;j<start+count;j++)
                {
                    if(r[j]==i)
                    {
                        cout<<j<<"("<<dot[i].x<<","<<dot[i].y<<")";
                        if(i!=mergenum)
                            cout<<" => ";
                    }
                }
            }
            cout<<endl;
        }
    }
}
/** //////////////////////////////////////////���j�ε��G **/
/** ////////////////////////////////////////////////�X�� **/
int mer(int num,int count)//bb�s�� kk�`��
{
    float min=dot[num].y,vecx=1,vecy=0;
    int lowest/**�̧C�I�s��**/,now/**�ثe���I**/,nextnum/**�U�@���I���s��**/;
    for(int i=num;i<num+count;i++)
    {
        r[i]=0;
        if(dot[i].y<min)
        {
            min=dot[i].y;
            lowest=i;
        }
    }
    now=lowest;
    int ver=1;//�������I�s��
    while(1)
    {
        r[now]=ver;
        double maxangle=-1;//������COS�̤j��
        for(int j=num;j<num+count;j++)
        {
            if(j!=now)
            {
                float x,y;
                x=dot[j].x-dot[now].x;
                y=dot[j].y-dot[now].y;//�V�q
                double result=(x*vecx+y*vecy)/(sqrt(x*x+y*y)*sqrt(vecx*vecx+vecy*vecy));
                if(result>maxangle)
                {
                    maxangle=result;
                    nextnum=j;
                }
            }
        }
        vecx=dot[nextnum].x-dot[now].x;
        vecy=dot[nextnum].y-dot[now].y;
        now=nextnum;
        ver++;
        if(now==lowest)
            break;
    }
    return ver-1;
}
/** ////////////////////////////////////////////////�X�� **/

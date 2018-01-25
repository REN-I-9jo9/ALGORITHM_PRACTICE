#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <vector>
#include <climits>
#include <sstream>
using namespace std;
class psdata
{
private:
	vector<int> data;
	vector<int> flag;
public:
	psdata(vector<int> init):flag(5,0)
	{
		data=init;
		if (init.size()<5)
		{
			for(int i=0;i<data.size()%5;i++)
				data.push_back(INT_MAX);
		}
	}
    vector<int> getdata(){return data;}
	vector<int> getflag(){return flag;}
	void sort(){std::sort(data.begin(),data.end());}
	int mid(){return data[2];}
	void set_flag(int ccenter)
	{
		for (int i=0;i<5;i++)
		{
			int num=data[i];
			if (num<ccenter)
				flag[i]=1;
			else if (num==ccenter)
				flag[i]=2;
			else if (num>ccenter)
				flag[i]=3;
		}
	}
};
int getmid(vector<int> v);
vector<psdata> makedata(const vector<int>& list);
int pruneandsearch(int k, int set, vector<psdata> dset);
int main()
{
/** --------------------Read The File-------------------- **/
    cout<<"讀取input5.txt"<<endl;
	ifstream in("input5.txt");
    int a;
    vector<int> predata;
    while(in>>a)
        predata.push_back(a);
    in.close();
    cout<<"Count= "<<predata.size()<<endl;
    for(int i=0;i<predata.size();i++)
        cout<<predata[i]<<" ";
    cout<<endl;
	vector<psdata> data = makedata(predata);
/** --------------------Read The File-------------------- **/
/** --------------------Result--------------------------- **/
	while (true)
	{
		cout<<endl<<"輸入k: ";
		int k;
		cin>>k;
		if (k<=0||k>predata.size())
        {
            cout << "無效的數字k" << endl;
			break;
        }
		int result = pruneandsearch(k, 0, data);
		cout<<"第 "<<k<<" 個資料為:"<<result<<endl;
	}
/** --------------------Result--------------------------- **/
	return 0;
}
/** --------------------Selection Problem---------------- **/
int getmid(vector<int> center)
{
	nth_element(center.begin(),center.begin()+center.size()/2,center.end());
	return center[center.size()/2];
}
vector<psdata> makedata(const vector<int>& list)
{
	vector<psdata> data;
	for(int i=0;i<list.size()/5;i++)
	{
		vector<int> v(5,0);
		for(int j=0;j<5;j++)
			v[j]=list[i*5+j];
		data.push_back(psdata{v});
	}
	int over=list.size()%5;
	if (over!=0)
	{
		vector<int> v;
		for(int i=0;i<over;i++)
			v.push_back(list[(list.size()/5)*5+i]);
		data.push_back(psdata{v});
	}
	return data;
}
int pruneandsearch(int k, int set, vector<psdata> dset)
{
	if (dset.size()<=2)
	{
		vector<int> v=dset[0].getdata();
		if (dset.size()==2)
		{
			vector<int> u=dset[1].getdata();
			v.insert(v.end(),u.begin(),u.end());
		}
		sort(v.begin(), v.end());
		int result = v[k - 1];
		return result;
	}
	for(vector<psdata>::iterator iter=dset.begin();iter!=dset.end();iter++)
		iter->sort();
	vector<int> center;
	for(vector<psdata>::iterator iter=dset.begin();iter!=dset.end();iter++)
		center.push_back(iter->mid());
	int ccenter=getmid(center);
	for(vector<psdata>::iterator iter=dset.begin();iter!=dset.end();iter++)
		iter->set_flag(ccenter);
	vector<int> s1, s2, s3;
	for(vector<psdata>::iterator iter=dset.begin();iter!=dset.end();iter++)
	{
		vector<int> elements=iter->getdata();
		vector<int> elements_flag=iter->getflag();
		for(int i=0;i<5;i++)
		{
			int flag=elements_flag[i];
			if(flag==1)
				s1.push_back(elements[i]);
			else if(flag==2)
				s2.push_back(elements[i]);
			else if(flag==3)
				s3.push_back(elements[i]);
		}
	}
	vector<psdata> next;
	if(s1.size()>=k)
	{
		set=1;
		next=makedata(s1);
	}
	else if(s1.size()+s2.size()>=k)
		return s2[0];
	else
	{
		set=3;
		k-=s1.size()+s2.size();
		next=makedata(s3);
	}
	return  pruneandsearch(k,set,next);
}
/** --------------------Selection Problem---------------- **/

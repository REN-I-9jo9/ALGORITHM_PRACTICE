#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;
/** a structure to represent an edge in graph**/
struct Edge
{
	int src, dest;
/** ------------- **/
/**/float weight;/**//**changed**/
/** ------------- **/
};

/** a structure to represent a graph**/
struct Graph
{
	/** V-> Number of vertices, E-> Number of edges**/
	int V, E;

	/** graph is represented as an array of edges**/
	struct Edge* edge;
};

struct subset
{
	int parent;
	int rank;
};

/** Creates a graph with V vertices and E edges**/
struct Graph* createGraph(int V, int E)
{
	struct Graph* graph = (struct Graph*) malloc( sizeof(struct Graph) );
	graph->V = V;
	graph->E = E;

	graph->edge = (struct Edge*) malloc( graph->E * sizeof( struct Edge ) );

	return graph;
}

/** A utility function to find set of an element i**/
/** (uses path compression technique)**/
int find(struct subset subsets[], int i)
{
	/** find root and make root as parent of i (path compression)**/
	if (subsets[i].parent != i)
		subsets[i].parent = find(subsets, subsets[i].parent);

	return subsets[i].parent;
}

/** A function that does union of two sets of x and y**/
/** (uses union by rank)**/
void Union(struct subset subsets[], int x, int y)
{
	int xroot = find(subsets, x);
	int yroot = find(subsets, y);

	/** Attach smaller rank tree under root of high rank tree**/
	/** (Union by Rank)**/
	if (subsets[xroot].rank < subsets[yroot].rank)
		subsets[xroot].parent = yroot;
	else if (subsets[xroot].rank > subsets[yroot].rank)
		subsets[yroot].parent = xroot;

	/** If ranks are same, then make one as root and increment**/
	/** its rank by one**/
	else
	{
		subsets[yroot].parent = xroot;
		subsets[xroot].rank++;
	}
}

/** The main function to check whether a given graph contains cycle or not**/
int isCycle( struct Graph* graph )
{
	int V = graph->V;
	int E = graph->E;

	/** Allocate memory for creating V sets**/
	struct subset *subsets =
		(struct subset*) malloc( V * sizeof(struct subset) );

	for (int v = 0; v < V; ++v)
	{
		subsets[v].parent = v;
		subsets[v].rank = 0;
	}

	/** Iterate through all edges of graph, find sets of both**/
	/** vertices of every edge, if sets are same, then there is**/
	/** cycle in graph.**/
	for(int e = 0; e < E; ++e)
	{
		int x = find(subsets, graph->edge[e].src);
		int y = find(subsets, graph->edge[e].dest);

		if (x == y)
			return 1;

		Union(subsets, x, y);
	}
	return 0;
}
void quick_sort(Edge arr[],int begin,int end)
{
	if (begin>=end)
        return;
	Edge center=arr[end];
	int left=begin,right=end-1;
	while (left<right)
    {
		while (arr[left].weight<center.weight&&left<right)
            left++;
        while (arr[right].weight>=center.weight&&left<right)
            right--;
        std::swap(arr[left],arr[right]);
	}
	if (arr[left].weight>=arr[end].weight)
		std::swap(arr[left],arr[end]);
	else
		left++;
	quick_sort(arr,begin,left-1);
	quick_sort(arr,left+1,end);
}
int main()
{
/** --------------------Read The File---------------------------------------- **/
    ifstream in("input2.txt");
    Edge g[2000];
    int V=0,E=0;
    in>>V;
    cout<<"The Number Of Vertex Is "<<V<<".  ";
    while(in>>g[E].src>>g[E].dest>>g[E].weight)
    {
        if(g[E].src>V||g[E].dest>V)
        {
            cout<<"error at line:"<<E+2<<endl;
            return 0;
        }
        E++;
    }
    cout<<"The Number Of Edge Is "<<E<<"."<<endl;
    in.close();
/** --------------------Read The File---------------------------------------- **/
/** --------------------Create Graph----------------------------------------- **/
    quick_sort(g,0,E-1);
	struct Graph* graph = createGraph(V, E);
	cout<<"The Graph Is:"<<endl;
	cout<<" dest     edge     weight"<<endl;
    for(int i=0;i<E;i++)
    {
        graph->edge[i].src = g[i].src-1;
        graph->edge[i].dest = g[i].dest-1;
        graph->edge[i].weight = g[i].weight;
        cout<<setw(5)<<graph->edge[i].dest+1<<" "<<setw(8)<<graph->edge[i].src+1<<" "<<setw(10)<<graph->edge[i].weight<<endl;
    }
    cout<<endl;
/** --------------------Create Graph----------------------------------------- **/
/** --------------------Find Minimum Spanning Tree--------------------------- **/
    struct Graph* tree = createGraph(V, V-1);
    int checked=0;
    for(int j=0;j<V-1;j++)
    {
        cout<<"Round "<<j+1<<":"<<endl;
        for(int i=checked;i<E;i++)
        {
            checked++;
            tree->edge[j]=graph->edge[i];
            struct Graph* check = createGraph(V, j+1);
            for(int k=0;k<=j;k++)
                check->edge[k]=tree->edge[k];
            if(!isCycle(check))
                break;
            cout<<"Edge "<<tree->edge[j].dest+1<<"<->"<<tree->edge[j].src+1<<" Makes A Cycle. Cannot Add In To Forest."<<endl;
        }
        cout<<"Add Edge "<<tree->edge[j].dest+1<<"<->"<<tree->edge[j].src+1<<" In To Forest."<<endl<<endl;
    }
    for(int i=checked;i<E;i++)
        cout<<"Edge "<<tree->edge[i].dest+1<<"<->"<<tree->edge[i].src+1<<"'s Weight Is Too Big. Cannot Add In To Forest."<<endl;
/** --------------------Find Minimum Spanning Tree--------------------------- **/
/** --------------------Result----------------------------------------------- **/
    cout<<endl<<"The Tree Is:"<<endl;
    cout<<" dest     edge     weight"<<endl;
    for(int i=0;i<tree->E;i++)
        cout<<setw(5)<<tree->edge[i].dest+1<<" "<<setw(8)<<tree->edge[i].src+1<<" "<<setw(10)<<tree->edge[i].weight<<endl;
/** --------------------Result----------------------------------------------- **/

    return 0;
}




















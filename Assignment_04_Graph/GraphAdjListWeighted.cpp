#include<stdio.h>
#include<stdlib.h>
#include <iostream>
#define NULL_VALUE -999999
#define INFINITY 999999
#define WHITE 1
#define GREY 2
#define BLACK 3
#define prl(x) std::cout << x << std::endl;

class Queue
{
    int queueInitSize ;
    int queueMaxSize;
    int * data;
    int length;
    int front;
    int rear;
public:
    Queue();
    ~Queue();
    void enqueue(int item); //insert item in the queue
    int dequeue(); //returns the item according to FIFO
    bool empty(); //return true if Queue is empty
};

Queue::Queue()
{
    queueInitSize = 2 ;
    queueMaxSize = queueInitSize;
    data = new int[queueMaxSize] ; //allocate initial memory
    length = 0 ;
    front = 0;
    rear = 0;
}


void Queue::enqueue(int item)
{
	if (length == queueMaxSize)
	{
		int * tempData ;
		//allocate new memory space for tempList
		queueMaxSize = 2 * queueMaxSize ;
		tempData = new int[queueMaxSize] ;
		int i, j;
		j = 0;
		for( i = rear; i < length ; i++ )
		{
			tempData[j++] = data[i] ; //copy items from rear
		}
		for( i = 0; i < rear ; i++ )
		{
			tempData[j++] = data[i] ; //copy items before rear
		}
		rear = 0 ;
		front = length ;
		delete[] data ; //free the memory allocated before
		data = tempData ; //make list to point to new memory
	}

	data[front] = item ; //store new item
	front = (front + 1) % queueMaxSize ;
	length++ ;
}


bool Queue::empty()
{
	if(length == 0) return true ;
	else return false ;
}


int Queue::dequeue()
{
	if(length == 0) return NULL_VALUE ;
	int item = data[rear] ;
	rear = (rear + 1) % queueMaxSize ;
	length-- ;
	return item ;
}


Queue::~Queue()
{
    if(data) delete[] data; //deallocate memory
    data = 0; //set to NULL
}

//****************Queue class ends here************************

//****************Dynamic ArrayList class based************************
class ArrayList
{
	int * list;
	int length ;
	int listMaxSize ;
	int listInitSize ;
public:
	ArrayList() ;
	~ArrayList() ;
	int searchItem(int item) ;
    void insertItem(int item) ;
	void removeItem(int item) ;
	void removeItemAt(int item);
	int getItem(int position) ;
	int getLength();
	bool empty();
	void printList();
} ;


ArrayList::ArrayList()
{
	listInitSize = 2 ;
	listMaxSize = listInitSize ;
	list = new int[listMaxSize] ;
	length = 0 ;
}

void ArrayList::insertItem(int newitem)
{
	int * tempList ;
	if (length == listMaxSize)
	{
		//allocate new memory space for tempList
		listMaxSize = 2 * listMaxSize ;
		tempList = new int[listMaxSize] ;
		int i;
        for( i = 0; i < length ; i++ )
        {
            tempList[i] = list[i] ; //copy all items from list to tempList
        }
        delete[] list ; //free the memory allocated before
        list = tempList ; //make list to point to new memory
	};

	list[length] = newitem ; //store new item
	length++ ;
}

int ArrayList::searchItem(int item)
{
	int i = 0;
	for (i = 0; i < length; i++)
	{
		if( list[i] == item ) return i;
	}
	return NULL_VALUE;
}

void ArrayList::removeItemAt(int position) //do not preserve order of items
{
	if ( position < 0 || position >= length ) return ; //nothing to remove
	list[position] = list[length-1] ;
	length-- ;
}


void ArrayList::removeItem(int item)
{
	int position;
	position = searchItem(item) ;
	if ( position == NULL_VALUE ) return ; //nothing to remove
	removeItemAt(position) ;
}


int ArrayList::getItem(int position)
{
	if(position < 0 || position >= length) return NULL_VALUE ;
	return list[position] ;
}

int ArrayList::getLength()
{
	return length ;
}

bool ArrayList::empty()
{
    if(length==0)return true;
    else return false;
}

void ArrayList::printList()
{
    int i;
    for(i=0;i<length;i++)
        printf("%d ", list[i]);
    printf("Current size: %d, current length: %d\n", listMaxSize, length);
}

ArrayList::~ArrayList()
{
    if(list) delete [] list;
    list = 0 ;
}

//******************ArrayList class ends here*************************

//******************Graph class starts here**************************
class Graph
{
	int nVertices, nEdges ;
	bool directed ;
	ArrayList  * adjList ;
	ArrayList  * weightList ;
	//define other variables required for bfs such as color, parent, and dist
	//you must use pointers and dynamic allocation
	int *color, *parent, *dist;

public:
	Graph(bool dir = false);
	~Graph();
	void setnVertices(int n);
	void addEdge(int u, int v, int w);
	void removeEdge(int u, int v);
	bool isEdge(int u, int v);
    int getDegree(int u);
    void printAdjVertices(int u);
    bool hasCommonAdjacent(int u, int v);
    int getDist(int u, int v);
    void printGraph();
	void bfs(int source); //will run bfs in the graph
	void dfs(int source); //will run dfs in the graph
};


Graph::Graph(bool dir)
{
	nVertices = 0 ;
	nEdges = 0 ;
	adjList = 0 ;
	weightList = 0;
	directed = dir ; //set direction of the graph
	//define other variables to be initialized
}

void Graph::setnVertices(int n)
{
	this->nVertices = n ;
	if(adjList!=0) delete[] adjList ; //delete previous list
	adjList = new ArrayList[nVertices] ;
	weightList = new ArrayList[nVertices];
	color = new int[n];
    parent = new int[n];
    dist = new int[n];
}

void Graph::addEdge(int u, int v, int w)
{
    if(u < 0 || v < 0 || u >= nVertices || v >= nVertices) return; //vertex out of range
    if(adjList[u].searchItem(v) != NULL_VALUE) return;
    this->nEdges++ ;
	adjList[u].insertItem(v) ;
	weightList[u].insertItem(w);
	if(!directed)
    {
        adjList[v].insertItem(u) ;
        weightList[v].insertItem(w);
    }
}

void Graph::removeEdge(int u, int v)
{
    //write this function
    int position = adjList[u].searchItem(v);
    if(position == NULL_VALUE) return;
    adjList[u].removeItemAt(position);
    weightList[u].removeItemAt(position);
    nEdges--;
    if(!directed)
    {
        position = adjList[v].searchItem(u);
        adjList[v].removeItemAt(position);
        weightList[v].removeItemAt(position);
    }
}

bool Graph::isEdge(int u, int v)
{
    //returns true if (u,v) is an edge, otherwise should return false
    if(adjList[u].searchItem(v) == NULL_VALUE) return false;
    else return true;
}

int Graph::getDegree(int u)
{
    //returns the degree of vertex u
    return adjList[u].getLength();
}

void Graph::printAdjVertices(int u)
{
    //prints all adjacent vertices of a vertex u
    for(int i = 0; i < adjList[u].getLength(); i++)
    {
        printf("%d ", adjList[u].getItem(i));
    }
    printf("\n");
}

bool Graph::hasCommonAdjacent(int u, int v)
{
    //returns true if vertices u and v have common adjacent vertices
    for(int i = 0; i < adjList[u].getLength(); i++)
    {
        int node = adjList[u].getItem(i);
        if(adjList[v].searchItem(node) != NULL_VALUE) return true;
    }
    return false;
}

void Graph::bfs(int source)
{
    //complete this function
    //initialize BFS variables
    for(int i=0; i<nVertices; i++)
    {
        color[i] = WHITE ;
        parent[i] = -1 ;
        dist[i] = INFINITY ;
    }
    Queue q ;
    color[source] = GREY;
    dist[source] = 0 ;
    q.enqueue(source) ;
    while( !q.empty() )
    {
        int u = q.dequeue();
        for(int i = 0; i < adjList[u].getLength(); i++)
        {
            int v = adjList[u].getItem(i);
            int w = weightList[u].getItem(i);
            if(color[v] == WHITE)
            {
                color[v] = GREY;
                dist[v] = dist[u] + w;
                parent[v] = u;
                q.enqueue(v);
            }
        }
        color[u] = BLACK;
    }
}

int Graph::getDist(int u, int v)
{
    //returns the shortest path distance from u to v
    //must call bfs using u as the source vertex, then use distance array to find the distance
    bfs(u);

    return dist[v] ;
}

void Graph::printGraph()
{
    printf("\nNumber of vertices: %d, Number of edges: %d\n", nVertices, nEdges);
    for(int i=0;i<nVertices;i++)
    {
        printf("%d:", i);
        for(int j=0; j<adjList[i].getLength();j++)
        {
            printf(" %d(%d)", adjList[i].getItem(j), weightList[i].getItem(j));
        }
        printf("\n");
    }
}

Graph::~Graph()
{
    //write your destructor here
    if(adjList != 0)
    {
        delete [] adjList;
        adjList = 0;
    }
    if(weightList != 0)
    {
        delete [] weightList;
        weightList = 0;
    }
    if(color != 0)
    {
        delete [] color;
        color = 0;
    }
    if(parent != 0)
    {
        delete [] parent;
        parent = 0;
    }
    if(dist != 0)
    {
        delete [] dist;
        dist = 0;
    }
}


//**********************Graph class ends here******************************

void printMenu()
{
    printf("1. Add edge.\t 2. Remove Edge.\t 3. Is Edge.\n");
    printf("4. Get degree.\t 5. Print adjacents.\t 6. Has common adjacent.\n");
    printf("7. BFS.\t\t 8. Get distance.\t 9. Print Graph.\n");
    printf("10. Exit.\n");
}


//******main function to test your code*************************
int main(void)
{
    //freopen("inMat.txt", "r", stdin);

    int n;
    Graph g;
    printf("Enter number of vertices: ");
    scanf("%d", &n);
    g.setnVertices(n);

    while(1)
    {
        printMenu();
        int ch;
        scanf("%d",&ch);
        if(ch == 1)
        {
            int u, v, w;
            scanf("%d %d %d", &u, &v, &w);
            // prl("adding " << u << " " << v << " " << w);
            g.addEdge(u, v, w);
        }
        else if(ch == 2)
        {
            int u, v;
            scanf("%d%d", &u, &v);
            // prl("removing " << u << " " << v);
            g.removeEdge(u, v);
        }
        else if(ch == 3)
        {
            int u, v;
            scanf("%d%d", &u, &v);
            // prl("Is there edge " << u << " " << v);
            printf("%d\n", g.isEdge(u, v));
        }
        else if(ch == 4)
        {
            int u;
            scanf("%d", &u);
            // prl("Degree of " << u);
            printf("%d\n", g.getDegree(u));
        }
        else if(ch == 5)
        {
            int u;
            scanf("%d", &u);
            // prl("adjacent vertices of " << u);
            g.printAdjVertices(u);
        }
        else if(ch == 6)
        {
            int u, v;
            scanf("%d %d", &u, &v);
            // prl("Is there common adjacent between " << u << " " << v);
            printf("%d\n", g.hasCommonAdjacent(u, v));
        }
        else if(ch == 7)
        {
            // prl("Running BFS...");
            g.bfs(0);
        }
        else if(ch == 8)
        {
            int u, v;
            scanf("%d %d", &u, &v);
            // prl("Distance between " << u << " " << v);
            printf("%d\n", g.getDist(u, v));
        }
        else if(ch == 9)
        {
            g.printGraph();
        }
        else if(ch == 10)
        {
            break;
        }
        //g.printGraph();
    }

}

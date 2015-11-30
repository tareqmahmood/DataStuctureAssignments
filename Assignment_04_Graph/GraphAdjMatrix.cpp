#include <stdio.h>
#include <stdlib.h>
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


//******************Graph class starts here**************************
class Graph
{
	int nVertices, nEdges ;
	bool directed ;
	int ** matrix ; //adjacency matrix to store the graph
	//define other variables required for bfs such as color, parent, and dist
	//you must use pointers and dynamic allocation
	int *color, *parent, *dist;

public:
	Graph(bool dir = false);
	~Graph();
	void setnVertices(int n);
	void addEdge(int u, int v);
	void removeEdge(int u, int v);
	bool isEdge(int u, int v);
    int getDegree(int u);
    void printAdjVertices(int u);
    bool hasCommonAdjacent(int u, int v);
    int getDist(int u, int v);
    void printGraph();
	void bfs(int source); //will run bfs in the graph
};


Graph::Graph(bool dir)
{
	nVertices = 0 ;
	nEdges = 0 ;
	matrix = 0 ;
	directed = dir ; //set direction of the graph
	//define other variables to be initialized
}

void Graph::setnVertices(int n)
{
	this->nVertices = n ;

	//allocate space for the matrix
    matrix = new int*[nVertices];
    for(int i=0;i<nVertices;i++)
    {
        matrix[i] = new int[nVertices];
        for(int j=0;j<nVertices;j++)
            matrix[i][j] = 0; //initialize the matrix cells to 0
    }
    color = new int[n];
    parent = new int[n];
    dist = new int[n];
}

void Graph::addEdge(int u, int v)
{
    //write your code here
    if(u < 0 || u >= nVertices || v < 0 || v >= nVertices) return;
    if(matrix[u][v] == 1) return;   // already connected
    matrix[u][v] = 1;
    nEdges++;
    if(!directed)
    {
        matrix[v][u] = 1;
        //nEdges++;
    }
}

void Graph::removeEdge(int u, int v)
{
    //write this function
    if(u < 0 || u >= nVertices || v < 0 || v >= nVertices) return;
    if(matrix[u][v] == 0) return;   // already disconnected
    matrix[u][v] = 0;
    nEdges--;
    if(!directed)
    {
        matrix[v][u] = 0;
        //nEdges--;
    }
}

bool Graph::isEdge(int u, int v)
{
    //returns true if (u,v) is an edge, otherwise should return false
    return matrix[u][v];
}

int Graph::getDegree(int u)
{
    //returns the degree of vertex u
    /*
    int inDegree = 0, outDegree = 0;
    for(int i = 0; i < nVertices; i++)
    {
        if(matrix[u][i]) outDegree++;
        if(matrix[i][u]) inDegree++;
    }
    if(directed)
    {
        printf("Indegree : %d\n", inDegree);
        printf("Outdegree : %d\n", outDegree);
        return inDegree + outDegree;
    }
    else
    {
        return outDegree;
    }
    */
    int degree = 0;
    for(int i = 0; i < nVertices; i++)
    {
        if(matrix[u][i]) degree++;
    }
    return degree;
}

void Graph::printAdjVertices(int u)
{
    //prints all adjacent vertices of a vertex u
    for(int i = 0; i < nVertices; i++)
    {
        if(matrix[u][i]) printf("%d ", i);
    }
    printf("\n");
}

bool Graph::hasCommonAdjacent(int u, int v)
{
    //returns true if vertices u and v have common adjacent vertices
    for(int i = 0; i < nVertices; i++)
    {
        if(matrix[u][i] && matrix[v][i]) return true;
    }
    return false;
}

void Graph::bfs(int source)
{
    //write this function

    for(int i = 0; i < nVertices; i++)
    {
        color[i] = WHITE;
        parent[i] = -1;
        dist[i] = INFINITY;
    }
    Queue q;
    color[source] = GREY;
    dist[source] = 0;
    q.enqueue(source);

    while(!q.empty())
    {
        int u = q.dequeue();
        for(int v = 0; v < nVertices; v++)
        {
            if(matrix[u][v] && color[v] == WHITE)
            {
                color[v] = GREY;
                dist[v] = dist[u] + 1;
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
    //return INFINITY ;
    bfs(u);
    return dist[v];
}


void Graph::printGraph()
{
    printf("\nNumber of vertices: %d, Number of edges: %d\n", nVertices, nEdges);
    for(int i=0;i<nVertices;i++)
    {
        printf("%d:", i);
        for(int j=0; j<nVertices;j++)
        {
            if(matrix[i][j]==1)
                printf(" %d", j);
        }
        printf("\n");
    }
}

Graph::~Graph()
{
    //write your destructor here
    for(int i = 0; i < nVertices; i++)
    {
        delete [] matrix[i];
    }
    if(matrix != 0)
    {
        delete [] matrix;
        matrix = 0;
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
    //freopen("outMat.txt", "w", stdout);
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
            int u, v;
            scanf("%d%d", &u, &v);
            // prl("adding " << u << " " << v);
            g.addEdge(u, v);
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

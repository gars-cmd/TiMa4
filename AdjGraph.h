struct AdjNode
{
    int dest;
    int weight;
    struct AdjNode* next;
};


struct AdjList
{
    struct AdjNode *head;
};


struct AdjGraph
{
    int sized;
    int nbr_V;
    struct AdjList *nodesArr;
};

struct AdjGraph* createGraph( int size);
int indexOf(struct AdjGraph* graph ,   int wanted);
struct AdjNode* AddNode(struct AdjGraph* graph , int dest , int weight );
void AddEdge(struct AdjGraph* graph , int src , int dest , int weight);
void removeNode(struct AdjGraph* graph ,int node);
int* dijkstra (struct AdjGraph* graph , int src);
int factorial(int a);
void swap(char *x , char *y);
void permutations(struct AdjGraph* graph,struct stack* stacked , char* string , int indexStart , int indexEnd);
int TSP(struct AdjGraph* graph , char* string);
void removeGraph(struct AdjGraph* graph );
#include <stdio.h>
#include <stdlib.h>
#include "MinHeap.h"
#include <limits.h>
#include <string.h>
#include "stack.h"


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


struct AdjGraph* createGraph( int size)
{
//create a new object of type graph
struct AdjGraph* graph = (struct AdjGraph*) malloc(sizeof(struct AdjGraph));
// define the size as the number of given nodes
graph->sized = size;
graph->nbr_V = 0;

// accord size of memory for each Adjlist 
graph->nodesArr = (struct AdjList*) malloc(size*sizeof(struct AdjList));

//initialize all the AdjList of nodes to be empty
for (int i = 0; i < size; i++)
{
    graph->nodesArr[i].head = NULL;
}
return graph;

}
// we check if a node exist in a given Adjgraph
int indexOf(struct AdjGraph* graph ,   int wanted)
{
for (int i = 0; i < graph->nbr_V; i++)
{
    if (graph->nodesArr[i].head->dest == wanted)
    {
        return i;
    }
    
}
return -1;
}

struct AdjNode* AddNode(struct AdjGraph* graph , int dest , int weight )
{
    // if this node doesn't exist
    if (indexOf(graph , dest ) == -1)
    {
        //create a new node 
        struct AdjNode* newOne = (struct AdjNode*)malloc(sizeof(struct AdjNode));
        newOne->dest = dest;
        newOne->next = NULL;
        newOne ->weight = weight;

        // if the graph is already full 
        if (graph->nbr_V == graph->sized)
        {
            graph->nodesArr = realloc( graph->nodesArr , ((graph->nbr_V+1)*sizeof(struct AdjList)) );
            graph->nbr_V++;
            graph->sized++;
            graph->nodesArr[graph->sized-1].head = newOne;
            return newOne;
        }
        else
        {
            graph->nodesArr[graph->nbr_V].head = newOne;
            graph->nbr_V++;
        }
    }
    // if the node already exist
    else
    {
        int index = indexOf(graph , dest);
        // printf("1\n");
        struct AdjNode* curr = (struct AdjNode*)malloc(sizeof(struct AdjNode));
        // printf("2\n");
        curr = graph->nodesArr[index].head->next;
        // printf("3\n");
        struct AdjNode* prev = (struct AdjNode*)malloc(sizeof(struct AdjNode));
        // printf("4\n");
        prev = graph->nodesArr[index].head;
        prev->next= NULL;
        // printf("5\n");
        // if the node don't have any edges do nothing
        if (curr == NULL)
        {
            return NULL;
        }
        // run over all the edges and make all them equal to null    
        while (curr->next!=NULL)
        {
            prev = curr;
            curr = curr->next;
            // prev->next=NULL;
            free(prev);
            // printf("next\n");
        }
        free(curr);
        // free(prev);
    }
return NULL;
}

void AddEdge(struct AdjGraph* graph , int src , int dest , int weight)
{
    int check = 1;
    if (indexOf(graph , src) == -1)
    {
        AddNode(graph,src,0);
    }
    if (indexOf(graph,dest)==-1)
    {
        AddNode(graph,dest,0);
    }
    
   
        struct AdjNode* newCon = malloc(sizeof(struct AdjNode));
        newCon->dest = dest;
        newCon->weight = weight;
        newCon->next = NULL;
        // printf("3\n");

        int indexSrc = indexOf(graph ,src);
        if (graph->nodesArr[indexSrc].head->next==NULL)
        {
            // printf("4\n");
            graph->nodesArr[indexSrc].head->next = newCon;
            // printf("4.5\n");
        }
        else
        {
            // printf("5\n");
           struct AdjNode* curr = malloc(sizeof(struct AdjNode));
           curr =  graph->nodesArr[indexSrc].head;
           while (curr->next!=NULL)
           {
               
               if (curr->next->dest==dest)
               {
                   check=0;
                   curr->next->weight=weight;
                //    printf("check\n");
                   break;
                  
               }
            //    printf("6\n");
               curr = curr->next;
           }
            // printf("8\n");
           if (check == 1)
           {
               curr->next = newCon;
           }
           
        //    printf("\nfrom %d to %d cost= %d\n",src,newCon->dest,newCon->weight);
        //    free(curr);
        }
   
}

void removeNode(struct AdjGraph* graph ,int node)
{
    // if the node doesn't exist in the graph so do nothing
    if (indexOf(graph , node)== -1)
    {
        //printf("1");
        return;
    }
    else
    {
    
        //we getting the index of the node we looking for in the list of nodes
        int i = indexOf(graph,node);
        int k = 0;
        // create a new list to hold the graph
        struct AdjList* newList = (struct AdjList*) malloc(graph->sized*sizeof(struct AdjList));
        for (int j = 0; j < graph->nbr_V; j++)
        {
            //printf("2");
            // if the node is the one we want to remove
            if (j==i)
            {
                //printf("3");
                struct AdjNode* point = (struct AdjNode*)malloc(sizeof(struct AdjNode));
                point = graph->nodesArr[i].head;
                struct AdjNode* prev = (struct AdjNode*)malloc(sizeof(struct AdjNode));
                prev = graph->nodesArr[i].head;
                prev->next= NULL;
                //we free all the memory of the nodes that represent an edge from the node
                
                while (point->next!=NULL)
                {
                    //printf("4");
                    prev = point;
                    point = point->next;
                    free(prev);
                }
            free(point);
                
            }
            else
            {
                
            struct AdjNode* curr = (struct AdjNode*)malloc(sizeof(struct AdjNode));
            struct AdjNode* tempPoint = (struct AdjNode*)malloc(sizeof(struct AdjNode));
            curr = graph->nodesArr[j].head;
            newList[k].head = curr;
            tempPoint = newList[k].head->next;

            // we copy all the list to another list without the node we want to remove
            while (curr->next!=NULL)
            {
               
                //printf("6");
                //if we find a node that have an edge to the node we want to remove 
                if (curr->next->dest == node)
                {
                    struct AdjNode* deleter = (struct AdjNode*)malloc(sizeof(struct AdjNode));
                    deleter = graph->nodesArr[j].head;
                    while (deleter->next!=NULL)
                    {
                        
                        if (deleter->next->dest == node)
                        {
                            if (deleter->next->next == NULL)
                            {
                                free(deleter->next);
                                // #########remove the double (0,0)########
                                
                            }
                            else
                            {
                               deleter->next = deleter->next->next;
                            }

                        }
                    deleter = deleter->next;
                    }
                    
                }
                else
                {
                    //printf("8");
                    tempPoint = curr->next;
                    tempPoint = tempPoint->next;
                }
                curr = curr->next;
            }
            k++;
            // free(curr);
            }  
        }
       free(graph->nodesArr);
       graph->nodesArr = newList;
       graph->nbr_V--;
    }


}

int* dijkstra (struct AdjGraph* graph , int src)
{
    if (indexOf(graph,src)==-1)
    {
        return NULL;
    }
    
    int size = graph->nbr_V;
    int *min_dist= malloc(size*sizeof(int));

    // create the MinHeap for dijkstra use
    struct MinHeap* Heap = creatMinHeap(size);

    //initialize the values in the minHeap
    for (int i = 0; i < size; i++)
    {
        //printf("1");
        min_dist[i] = INT_MAX;
       // printf("\nmindist[%d] = %d\n",i,min_dist[i]);
        Heap->array[i] = AddHeapNode(i,min_dist[i]);
        Heap->state[i] = i;

    }
    //initialize the value for the src node to be 0
    int index = indexOf(graph,src);
    Heap->array[index] = AddHeapNode(index , min_dist[index]);
    Heap->state[index] = index;
    min_dist[index] = 0;
    decreaseKey(Heap , index , min_dist[index]);
    Heap->size = size;
    //printf("2");

    while (Heap->size != 0)
    {
        //printf("3");
        struct HeapNode* minNode = pop(Heap);
        int min_id = minNode->id;

        struct AdjNode* pointer = graph->nodesArr[min_id].head;
        while (pointer != NULL)
        {
            
            int temp_id = indexOf(graph,pointer->dest);
            if (Heap->state[temp_id] < Heap->size)
            {
                // printf("\ncondition : tableau min_id = %d , pointerW = %d , tableau temp_id = %d \n" , min_dist[min_id] , pointer->weight , min_dist[temp_id]);
                if (min_dist[min_id] != INT_MAX && pointer->weight + min_dist[min_id] < min_dist[temp_id])
                {
                   
                    min_dist[temp_id] = min_dist[min_id] + pointer->weight;
                    decreaseKey(Heap , temp_id , min_dist[temp_id]);
                }
                
                //printf("7");
            }
            pointer = pointer->next;
        }
        
    }
    return min_dist;
} 

int factorial(int a){
    int ans = 1;
    while (a>0)
    {
        ans *= a;
        a--;
    }
    return ans;
}

void swap(char *x , char *y)
{
    char temp;
    temp = *x;
    *x = *y;
    *y = temp;
}

void permutations(struct AdjGraph* graph,struct stack* stacked , char* string , int indexStart , int indexEnd)
{
    // get the size of the string
    int i;
    
    if (indexStart == indexEnd)
    {
        
        //printf("%s\n",string);
        int temp_result = 0;
        for (int j = 0; j < indexEnd; j++)
        {
            
            int* container = malloc ((indexEnd+1)*sizeof(int));
            int x = string[j] -'0';
            int y = string[j+1] -'0';
            int index1 = indexOf(graph,x);
            int index2 = indexOf(graph,y);
            container = dijkstra(graph,x);
            // printf("\n%d to %d = %d\n ",x,y,container[index2]);
            if (container[index2]==INT_MAX)
            {
                temp_result = INT_MAX;
            }
            else
            {
                temp_result+=container[index2];
            }
            free(container);
        }
        // printf("\n temp = %s , cost = %d",string,temp_result);
        push(stacked,temp_result);
    }
    else
    {
       // printf("4");
        for (i = indexStart; i <= indexEnd; i++)
        {
            //printf("5");
            swap((string+indexStart) , (string+i));
            permutations(graph ,stacked, string , indexStart+1 , indexEnd);
            swap( (string+indexStart) , (string+i));
        }
        
    }

}

int TSP(struct AdjGraph* graph , char* string)
{
    int len = strlen(string);
    struct stack* stacked = newStack(factorial(len));
    permutations(graph,stacked,string,0,len-1);

    int min = INT_MAX;
    while (!isEmpty(stacked))
    {
        int temp_min = popStack(stacked);
        if (temp_min > 0 && temp_min<min)
        {
            min = temp_min;
        }
    }
    if (min == INT_MAX)
    {
        return -1;
    }
    else
    {
        return min;
    }
    free(stacked);
}

void removeGraph(struct AdjGraph* graph )
{
    for (int i = 0; i < graph->sized ; i++)
    {
        // printf("check");
        free(graph->nodesArr[i].head);
    }
    free(graph);
    // printf("nice");
}














#include<stdio.h>
#include <stdlib.h>


//node into minHeap
struct HeapNode
{
    int id;
    int dist;
};



//MinHeap object
struct MinHeap
{
    int size;
    int charge;
    int *state;
    struct HeapNode **array;
};

//add a new node
struct HeapNode* AddHeapNode(int id , int dist)
{
    struct HeapNode* new_node = (struct HeapNode*)malloc(sizeof(struct HeapNode));
    new_node->dist = dist;
    new_node->id = id;
    return new_node;
}


//create a MinHeap
struct MinHeap* creatMinHeap(int charge)
{
    struct MinHeap* newHeap = (struct MinHeap*)malloc(sizeof(struct MinHeap));
    newHeap->array = (struct HeapNode**)malloc(charge * sizeof(struct HeapNode*));
    newHeap->charge = charge;
    newHeap->size=0;
    newHeap->state = (int*)malloc(charge * sizeof(int) );
    return newHeap;
}

void minHeapify(struct MinHeap* Heap , int id)
{
    //create vars
    int min;
    int left;
    int right;

    //initialize our window
    min = id;
    left = 2*id +1;
    right = 2*id+2;


    if (left < Heap->size && Heap->array[left]->dist < Heap->array[min]->dist )
    {
        min = left ;
    }

    if (right < Heap->size && Heap->array[right]->dist < Heap->array[min]->dist )
    {
        min = right ;
    }
    
    if (min != id)
    {
        struct HeapNode *minNode = Heap->array[min];
        struct HeapNode *idNode = Heap->array[id]; 

        Heap->state[minNode->id] = id;
        Heap->state[idNode->id] = min;

        //swap the nodes
        struct HeapNode* swapNode = Heap->array[min];
        Heap->array[min] = Heap->array[id];
        Heap->array[id] = swapNode;

        minHeapify(Heap , min);

    }
    

}
// function to pop the min
struct HeapNode* pop(struct MinHeap* Heap)
{
    if (Heap->size == 0)
    {
        return NULL;
    }
    struct HeapNode* root = Heap->array[0];
    struct HeapNode* end = Heap->array[Heap->size-1];
    Heap->array[0] = end;
    Heap->state[root->id] = Heap->size-1;
    Heap->state[end->id] = 0;
    Heap->size--;
    minHeapify(Heap,0);
    return root;
}

void decreaseKey (struct MinHeap* Heap , int id , int dist)
{
    int i = Heap->state[id];
    Heap->array[i]->dist = dist;
    while (i && Heap->array[i]->dist < Heap->array[(i-1)/2]->dist)
    {
        Heap->state[Heap->array[i]->id] = (i-1)/2;
        Heap->state[Heap->array[(i-1)/2]->id]=i;

        //swap the nodes
        struct HeapNode* swapNode = Heap->array[i];
        Heap->array[i] = Heap->array[(i-1)/2];
        Heap->array[(i-1)/2] = swapNode;
        i = (i-1)/2;
        
    } 
}


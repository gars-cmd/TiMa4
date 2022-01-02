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

struct HeapNode* AddHeapNode(int id , int dist);
struct MinHeap* creatMinHeap(int charge);
void minHeapify(struct MinHeap* Heap , int id);
struct HeapNode* pop(struct MinHeap* Heap);
void decreaseKey (struct MinHeap* Heap , int id , int dist);


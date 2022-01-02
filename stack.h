struct stack
{
    int maxsize;    // define max capacity of the stack
    int top;
    int *items;
};

struct stack* newStack(int capacity);
void push(struct stack *pt, int x);
int popStack(struct stack *pt);
int isEmpty(struct stack *pt);
int isFull(struct stack *pt);

#include <stdio.h>
#include <stdlib.h>
 

struct stack
{
    int maxsize;    
    int top;
    int *items;
};
 
struct stack* newStack(int capacity)
{
    struct stack *pt = (struct stack*)malloc(sizeof(struct stack));
 
    pt->maxsize = capacity;
    pt->top = -1;
    pt->items = (int*)malloc(sizeof(int) * capacity);
 
    return pt;
}
 
int size(struct stack *pt) {
    return pt->top + 1;
}

int isEmpty(struct stack *pt) {
    return pt->top == -1;                   // or return size(pt) == 0;
}
 
int isFull(struct stack *pt) {
    return pt->top == pt->maxsize - 1;      // or return size(pt) == pt->maxsize;
}
 
void push(struct stack *pt, int x)
{
    // check if the stack is already full. Then inserting an element would
    // lead to stack overflow
    if (isFull(pt))
    {
        //printf("Overflow\nProgram Terminated\n");
        exit(EXIT_FAILURE);
    }
 
    //printf("Inserting %d\n", x);
 
    // add an element and increment the top's index
    pt->items[++pt->top] = x;
}
 
int peek(struct stack *pt)
{
    // check for an empty stack
    if (!isEmpty(pt)) {
        return pt->items[pt->top];
    }
    else {
        exit(EXIT_FAILURE);
    }
}
 

int popStack(struct stack *pt)
{
    // check for stack underflow
    if (isEmpty(pt))
    {
        //printf("Underflow\nProgram Terminated\n");
        exit(EXIT_FAILURE);
    }
 
    //printf("Removing %d\n", peek(pt));
 
    // decrement stack size by 1 and (optionally) return the popped element
    return pt->items[pt->top--];
}

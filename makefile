FLAG = -g -Wall

all: AdjGraph.o MinHeap.o stack.o main.o prog

AdjGraph.o: AdjGraph.c 
	gcc $(FLAG) -c AdjGraph.c
	
MinHeap.o: MinHeap.c
	gcc $(FLAG) -c MinHeap.c

stack.o: stack.c
	gcc $(FLAG) -c stack.c 

main.o: main.c
	gcc $(FLAG) -c main.c

prog: main.o AdjGraph.o MinHeap.o stack.o 
	gcc $(FLAG) -o prog main.o AdjGraph.o MinHeap.o stack.o 

.PHONY: clean all

clean:
	rm -f *.o prog tmp_out.txt


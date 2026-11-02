#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct StackNode {
	char url[50];
	struct StackNode* next;
} StackNode;

typedef struct Stack {
	StackNode* top;
} Stack;

typedef struct QueueNode {
	char url[50];
	struct QueueNode* next;
} QueueNode;

typedef struct Queue {
	struct QueueNode* front;
	struct QueueNode* rear;
} Queue;

void push(Stack* stack, char* newUrl);
char* pop(Stack* stack);
char* peekStack(Stack* stack);
bool isStackEmpty(Stack* stack);
void freeStack(Stack* stack);

void enqueue(Queue* queue, char* newUrl);
char* dequeue(Queue* queue);
char* peekQueue(Queue* queue);
bool isQueueEmpty(Queue* queue);
void freeQueue(Queue* queue);

int main()
{


	return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_SIZE 50

typedef struct StackNode {
	char url[MAX_SIZE];
	struct StackNode* next;
} StackNode;

typedef struct Stack {
	StackNode* top;
} Stack;

typedef struct QueueNode {
	char url[MAX_SIZE];
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
Stack* initializeStack(void);
StackNode* createStackNode(char* newUrl);

void enqueue(Queue* queue, char* newUrl);
char* dequeue(Queue* queue);
char* peekQueue(Queue* queue);
bool isQueueEmpty(Queue* queue);
void freeQueue(Queue* queue);
Queue* initializeQueue(void);
QueueNode* createQueueNode(char* newUrl);

void manageHistory(Queue* queue, char* url);
void printQueueHistory(Queue* queue);


void push(Stack* stack, char* newUrl) {
	if (isStackEmpty(stack)) {
		printf("Stack Underflow");
		exit(EXIT_FAILURE);
	}
	StackNode* newNode = createStackNode(newUrl);
	newNode->next = stack->top;
	stack->top = newNode;
}

char* pop(Stack* stack) {
	if (isStackEmpty(stack)) {
		printf("Stack Underflow");
		exit(EXIT_FAILURE);
	}

	StackNode* temp = stack->top;
	char* urlCopy = (char*)malloc(MAX_SIZE);
	if (urlCopy == NULL) {
		printf("No Memory");
		exit(EXIT_FAILURE);
	}

	strcpy(urlCopy, temp->url);
	stack->top = temp->next;
	free(temp);
	return urlCopy;
}

char* peekStack(Stack* stack) {
	if (isStackEmpty(stack)) {
		printf("Stack Underflow Exception");
		exit(EXIT_FAILURE);
	}
	return stack->top->url;
}

bool isStackEmpty(Stack* stack) {
	return stack->top == NULL;
}

void freeStack(Stack* stack) {
	while (!isStackEmpty(stack)) {
		char* url = pop(stack);
		free(url);
	}
	free(stack);
}

Stack* initializeStack(void) {
	Stack* stack = (Stack*)malloc(sizeof(Stack));
	if (stack == NULL) {
		printf("No Memory");
		exit(EXIT_FAILURE);
	}
	stack->top = NULL;
	return stack;
}

StackNode* createStackNode(char* newUrl) {
	StackNode* newNode = (StackNode*)malloc(sizeof(StackNode));
	if (newNode == NULL) {
		printf("No Memory");
		exit(EXIT_FAILURE);
	}

	strcpy(newNode->url, newUrl);
	newNode->next = NULL;
	return newNode;
}

void enqueue(Queue* queue, char* newUrl) {
	QueueNode* newNode = createQueueNode(newUrl);
	if (isQueueEmpty(queue)) {
		queue->front = newNode;
		queue->rear = newNode;
	} else {
		queue->rear->next = newNode;
		queue->rear = newNode;
	}
}

char* dequeue(Queue* queue) {
	if (isQueueEmpty(queue)) {
		printf("Queue is Empty\n");
		return NULL;
	}

	QueueNode* temp = queue->front;
	char* urlCopy = (char*)malloc(MAX_SIZE);
	if (urlCopy == NULL) {
		printf("No Memory");
		exit(EXIT_FAILURE);
	}

	strcpy(urlCopy, temp->url);
	queue->front = temp->next;
	if (queue->front == NULL) {
		queue->front = NULL;
	}

	free(temp);
	return urlCopy;
}

char* peekQueue(Queue* queue) {
	if (isQueueEmpty(queue)) {
		printf("Queue is Empty\n");
		return NULL;
	}

	return queue->front->url;
}

bool isQueueEmpty(Queue* queue) {
	return queue->front == NULL;
}

void freeQueue(Queue* queue) {
	while (!isQueueEmpty(queue)) {
		char* url = dequeue(queue);
		free(url);
	}

	free(queue);
}

Queue* initializeQueue(void) {
	Queue* queue = (Queue*)malloc(sizeof(Queue));
	if (queue == NULL) {
		printf("No Memory");
		exit(EXIT_FAILURE);
	}

	queue->front = NULL;
	queue->rear = NULL;
	return queue;
}

QueueNode* createQueueNode(char* newUrl) {
	QueueNode* newNode = (QueueNode*)malloc(sizeof(QueueNode));
	if (newNode == NULL) {
		printf("No Memory");
		exit(EXIT_FAILURE);
	}

	strcpy(newNode->url, newUrl);
	newNode->next = NULL;
	return newNode;
}

void manageHistory(Queue* queue, char* url) {
	QueueNode* current = queue->front;
	QueueNode* prev = NULL;
	bool exist = false;

	while (current != NULL) {
		if (strcmp(current->url, url) == 0) {
			exist = true;
			break;
		}
		prev = current;
		current = current->next;
	}

	// If the url exist in the history
	if (exist) {
		// Only one history
		if (current == queue->front && current == queue->rear) {
			return;
		}
		// If the url is first history
		else if (current == queue->front) {
			queue->front = current->next;
			queue->rear->next = current;
			queue->rear = current;
			current->next = NULL;
		}
		// If the url is last history
		else if (current == queue->rear) {
			return;
		}
		else {
			prev->next = current->next;
			queue->rear->next = current;
			queue->rear = current;
			current->next = NULL;
		}
	}
	else {
		enqueue(queue, url);
	}
}

void printQueueHistory(Queue* queue);

int main()
{
	Stack* backStack = initializeStack();
	Stack* forwardStack = initializeStack();
	Queue* historyQueue = initializeQueue();

	int choice = 0;
	char inputUrl[MAX_SIZE];

	while (1) {
		printf("----------------------------------\n");
		printf("     Browser History Manager\n");
		printf("----------------------------------\n");
		printf("Menu:\n");
		printf("  1. Visit New Web Page\n");
		printf("  2. Navigate Backward\n");
		printf("  3. Navigate Forward\n");
		printf("  4. Display Current Page\n");
		printf("  5. Browsing History Log (Queue)\n");
		printf("  6. Exit\n");
		printf("----------------------------------\n");
		printf("Please enter a number (1-6): ");

		if (scanf("%d", &choice) != 1) {
			printf("\nInvalid input. Please enter a number.\n");
			while (getchar() != '\n');
			continue;
		}
		while (getchar() != '\n');

		if (choice == 6) {
			printf("Exiting.. \n");
			freeStack(backStack);
			freeStack(forwardStack);
			freeQueue(historyQueue);
			break;
		}

		switch (choice) {
		case 1: {

		}
		case 2: {

		}
		case 3: {

		}
		case 4: {

		}
		case 5: {

		}
		default :
			printf("Error: Invalid choice. Please select between 1 and 6.\n");
		}


	}

	return 0;
}
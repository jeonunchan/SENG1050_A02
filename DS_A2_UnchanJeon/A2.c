/*
FILE            :   A2.c
PROJECT         :   SENG1050_A2
PROGRAMMER      :   Unchan Jeon
FIRST VERSION   :   2026-11-01
DESCRIPTION     :
	The functions in this file are used to implement simplified web browser history manager using "stacks" and "queues".
*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// Define constant for URL size
#define MAX_SIZE 50

// Define stack and queue structures
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

// Declaration of stack function prototypes
void push(Stack* stack, char* newUrl);
char* pop(Stack* stack);
char* peekStack(Stack* stack);
bool isStackEmpty(Stack* stack);
void freeStack(Stack* stack);
Stack* initializeStack(void);
StackNode* createStackNode(char* newUrl);

// Declaration of queue function prototypes
void enqueue(Queue* queue, char* newUrl);
char* dequeue(Queue* queue);
char* peekQueue(Queue* queue);
bool isQueueEmpty(Queue* queue);
void freeQueue(Queue* queue);
Queue* initializeQueue(void);
QueueNode* createQueueNode(char* newUrl);

void manageHistory(Queue* queue, char* url);
void printQueueHistory(Queue* queue);

//  FUNCTION        :   push
//  DESCRIPTION     :
//      This function adds a new URL to the top of the stack
//  PARAMETERS      :
//      Stack* stack	: Pointer to the stack to add the URL to
//		char* newUrl	: Pointer to the URL data to add
//  RETURNS         :
//      void
void push(Stack* stack, char* newUrl) {
	StackNode* newNode = createStackNode(newUrl);
	newNode->next = stack->top;
	stack->top = newNode;
}

//  FUNCTION        :   pop
//  DESCRIPTION     :
//      This function removes and returns the URL from the top of the stack
//  PARAMETERS      :
//      Stack* stack	: Pointer to the stack to remove the URL from
//  RETURNS         :
//      char*	urlCopy	: Pointer to the copied URL removed from the stack
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

//  FUNCTION        :   peekStack
//  DESCRIPTION     :
//      This function returns the URL from the top of the stack without removing it
//  PARAMETERS      :
//      Stack* stack	: Pointer to the stack to check
//  RETURNS         :
//      char*	stack->top->url : Pointer to the URL at the top of the stack
char* peekStack(Stack* stack) {
	if (isStackEmpty(stack)) {
		printf("Stack Underflow Exception");
		exit(EXIT_FAILURE);
	}
	return stack->top->url;
}

//  FUNCTION        :   isStackEmpty
//  DESCRIPTION     :
//      This function checks whether the stack is empty
//  PARAMETERS      :
//      Stack* stack	: Pointer to the stack to verify
//  RETURNS         :
//      true if the stack is empty
//		false otherwise
bool isStackEmpty(Stack* stack) {
	return stack->top == NULL;
}

//  FUNCTION        :   freeStack
//  DESCRIPTION     :
//      This function frees all allocated memory for the stack and its nodes
//  PARAMETERS      :
//      Stack*	stack	: Pointer to the target stack to free
//  RETURNS         :
//      void
void freeStack(Stack* stack) {
	while (!isStackEmpty(stack)) {
		char* url = pop(stack);
		free(url);
	}
	free(stack);
}

//  FUNCTION        :   initializeStack
//  DESCRIPTION     :
//      This function initializes and returns a new stack
//  PARAMETERS      :
//      void
//  RETURNS         :
//      Stack* stack	: Pointer to the initialized stack
Stack* initializeStack(void) {
	Stack* stack = (Stack*)malloc(sizeof(Stack));
	if (stack == NULL) {
		printf("No Memory");
		exit(EXIT_FAILURE);
	}
	stack->top = NULL;
	return stack;
}

//  FUNCTION        :   createStackNode
//  DESCRIPTION     :
//      This function creates a new stack node with the provided URL data
//  PARAMETERS      :
//      char* newUrl	: Pointer to the URL data for the new stack node
//  RETURNS         :
//      StackNode* newNode	: Pointer to the created stack node
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

//  FUNCTION        :   enqueue
//  DESCRIPTION     :
//      This function adds a new URL to the rear of the queue
//  PARAMETERS      :
//      Queue* queue	: Pointer to the queue to add the URL to
//		char* newUrl	: Pointer to the URL to add
//  RETURNS         :
//      void
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

//  FUNCTION        :   dequeue
//  DESCRIPTION     :
//      This function removes and the URL from the front of the queue
//  PARAMETERS      :
//      Queue* queue	: Pointer to the queue to remove the URL from
//  RETURNS         :
//      char* urlCopy	: Pointer to the copied URL removed from the queue
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
		queue->rear = NULL;
	}

	free(temp);
	return urlCopy;
}

//  FUNCTION        :   peekQueue
//  DESCRIPTION     :
//      This function returns the URL from the front of the queue without removing it
//  PARAMETERS      :
//      Queue* queue	: Pointer to the queue to check
//  RETURNS         :
//      NULL if queue is empty
//		char* queue->front->url	: Pointer to the URL at the front of the queue
char* peekQueue(Queue* queue) {
	if (isQueueEmpty(queue)) {
		printf("Queue is Empty\n");
		return NULL;
	}

	return queue->front->url;
}

//  FUNCTION        :   isQueueEmpty
//  DESCRIPTION     :
//      This function checks whether the queue is empty
//  PARAMETERS      :
//      Queue* queue	: Pointer to the queue to verify
//  RETURNS         :
//      true if the queue is empty
//		false otherwise     
bool isQueueEmpty(Queue* queue) {
	return queue->front == NULL;
}

//  FUNCTION        :   freeQueue
//  DESCRIPTION     :
//      This function frees all allocated memory for the queue and its nodes
//  PARAMETERS      :
//      Queue* queue	: Pointer to the target queue to free
//  RETURNS         :
//      void
void freeQueue(Queue* queue) {
	while (!isQueueEmpty(queue)) {
		char* url = dequeue(queue);
		free(url);
	}

	free(queue);
}

//  FUNCTION        :   initializeQueue
//  DESCRIPTION     :
//      This function initializes and returns a new queue
//  PARAMETERS      :
//      void
//  RETURNS         :
//      Queue*	queue : Pointer to the initialized queue
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

//  FUNCTION        :   createQueueNode
//  DESCRIPTION     :
//      This function creates new queue node with the provided URL data
//  PARAMETERS      :
//      char* newUrl	: Pointer to the URL data for the new queue node
//  RETURNS         :
//      QueueNode* newNode	: Pointer to the created queue node
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

//  FUNCTION        :   manageHistory
//  DESCRIPTION     :
//      This function manages simplified browser history using a queue.
//		If the URL already exists, it moves it to the rear
//		Otherwise, it enqueues it
//  PARAMETERS      :
//      Queue*	queue	: Pointer to the history queue to manage
//		char*	url		: Pointer to the URL to manage
//  RETURNS         :
//      void
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

	// If the URL exists in the history
	if (exist) {
		// Only one history exists
		if (current == queue->front && current == queue->rear) {
			return;
		}
		// If the URL is at the front of the queue
		else if (current == queue->front) {
			queue->front = current->next;
			queue->rear->next = current;
			queue->rear = current;
			current->next = NULL;
		}
		// If the URL is already at the rear of the queue
		else if (current == queue->rear) {
			return;
		}
		// If the URL is in the middle
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

//  FUNCTION        :   printQueueHistory
//  DESCRIPTION     :
//      This function displays browser history log from the queue
//  PARAMETERS      :
//      Queue*	queue	: Pointer to the queue to display
//  RETURNS         :
//      void
void printQueueHistory(Queue* queue) {
	if (isQueueEmpty(queue)) {
		printf("Browsing History Log is empty.\n");
		return;
	}
	printf("\n-- Browsing History Log (Queue) --\n");
	QueueNode* current = queue->front;
	while (current != NULL) {
		printf("%s\n", current->url);
		current = current->next;
	}
	printf("----------------------------------\n");
}

//  FUNCTION        :   main
//  DESCRIPTION     :
//      This function runs main loop for simplified browser history manager program. 
//  PARAMETERS      :
//      int			argc
//		const char* argv[]
//  RETURNS         :
//      0 if there is no error
//		non-zero integer if an error occurred
int main(int argc, const char* argv[])
{
	// Initialize stacks and queue
	Stack* backStack = initializeStack();
	Stack* forwardStack = initializeStack();
	Queue* historyQueue = initializeQueue();

	int choice = 0;
	char inputUrl[MAX_SIZE];

	// Main loop starts here
	while (1) {
		printf("\n----------------------------------\n");
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

		// If user entered invalid input, return to the menu
		if (scanf("%d", &choice) != 1) {
			printf("\nInvalid input. Please enter a number.\n");
			while (getchar() != '\n');
			continue;
		}
		while (getchar() != '\n');

		// If user entered 6, exit after freeing stacks and queue
		if (choice == 6) {
			printf("Exiting.. \n");
			freeStack(backStack);
			freeStack(forwardStack);
			freeQueue(historyQueue);
			break;
		}

		switch (choice) {

		case 1: {
			//
			// Visit new web page
			//
			printf("Please enter URL to visit: ");
			scanf("%49s", inputUrl);
			while (getchar() != '\n');

			// Add new URL to the backStack
			push(backStack, inputUrl);

			// Empty forwardStack
			while (!isStackEmpty(forwardStack)) {
				char* poppedUrl = pop(forwardStack);
				free(poppedUrl);
			}

			// Add history to the queue
			manageHistory(historyQueue, inputUrl);
			printf("Successfully visited %s.\n", inputUrl);
			break;
		}
		case 2: {
			//
			// Navigate backward
			//

			// Check if there is a previous page
			if (isStackEmpty(backStack) || backStack->top->next == NULL) {
				printf("Error: There is no previous page.\n");
				break;
			}

			// Remove previous URL from backStack and add it to the forwardStack
			char* currentPage = pop(backStack);
			push(forwardStack, currentPage);
			free(currentPage);

			// Set new previous page
			char* prevPage = peekStack(backStack);
			printf("Navigated back to %s\n", prevPage);
			// Change history URL order (move previous page to rear)
			manageHistory(historyQueue, prevPage);
			break;
		}
		case 3: {
			//
			// Navigate Forward
			//
			
			// Check if there is a forward page
			if (isStackEmpty(forwardStack)) {
				printf("Error: There is no forward page.\n");
				break;
			}

			// Remove URL from forwardStack and add it to the backStack
			char* nextPage = pop(forwardStack);
			push(backStack, nextPage);

			printf("Navigated forward to %s\n", nextPage);
			// Change history URL order (move next page to rear)
			manageHistory(historyQueue, nextPage);
			free(nextPage);
			break;
		}
		case 4: {
			//
			// Display current page
			//

			// Check if there is current page
			if (isStackEmpty(backStack)) {
				printf("Current Page: NONE (History is empty)\n");
			}
			else {
				printf("Current Page: %s\n", peekStack(backStack));
			}
			break;
		}
		case 5: {
			//
			// Display browsing history log
			//
			printQueueHistory(historyQueue);
			break;
		}
		default :
			printf("Error: Invalid choice. Please select between 1 and 6.\n");
		}


	}

	return 0;
}
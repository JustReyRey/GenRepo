#include <stdio.h>
#include <stdlib.h>
#include "stackADT.h"

Stack* createStack (void (*printFunction)(void *toBePrinted),void (*deleteFunction)(void *toBeDeleted),int (*compareFunction)(const void *first,const void *second)){
  Stack* stack = malloc(sizeof(Stack));
  stack->count = 0;
  stack->list = initializeList(printFunction,deleteFunction,compareFunction);
  return stack;
}

List *initializeList(void (*printFunction)(void *toBePrinted),void (*deleteFunction)(void *toBeDeleted),int (*compareFunction)(const void *first,const void *second)){
  List *list = malloc(sizeof(List));
  list->head = NULL;
  list->tail = NULL;
  list->printNode = printFunction;
  list->deleteNode = deleteFunction;
  list->compare = compareFunction;
  return list;  
}

Node *initializeNode(void *data){
  Node *newNode = malloc(sizeof(Node));
  newNode->data = data;
  newNode->prev = NULL;
  newNode->next = NULL;
  return newNode;
}

void insertBack(List *list,void *toBeAdded){
  Node* newNode = initializeNode(toBeAdded);

  if(list->tail == NULL){
    list->head = newNode;
    list->tail = newNode;
    return;
  }
  newNode->prev = list->tail;
  list->tail->next = newNode;
  list->tail = newNode;

}

void* getFromBack(List *list){
  void *temp = list->tail->data;  
  return temp;
}

int deleteNodeFromList (List *list, void *toBeDeleted){

	Node* temp = list->head;
	if (list->head == NULL){
	  return EXIT_FAILURE;
	}
	if(temp != NULL && temp->data == toBeDeleted){
	  list->head = temp->next;
	  list->deleteNode(temp);
	  return EXIT_SUCCESS;
       
	}
	
	Node *prev;
	while (temp != NULL && temp->data != toBeDeleted){
          prev = temp;
	  temp->data = prev->data;
  	  temp = temp->next;
	}

	if (temp == NULL){
	  return -1;
	}

	prev->next = temp->next;
	list->deleteNode(temp);
       
		
	return EXIT_SUCCESS;
}

void* top (Stack *stack){
  void *temp;
  temp = getFromBack(stack->list);
  return temp;
}
 

void push (Stack *stack,void *data){
  insertBack(stack->list,data);
  stack->count += 1;
}


void pop (Stack *stack){
  if(count(stack) > 0){
    void* data = top(stack);
    int result = deleteNodeFromList(stack->list,data);
    if(result == EXIT_SUCCESS){
      stack->count -= 1;
    }
  }
}

int count (Stack* s){
  return s->count;
}

void deleteList(List *list){
	
	Node *current = list->head;
	Node *next = current;
	while (current != NULL){ 
	  next = current->next;
	  free(current);
	  current = next;
	}
	free(next);
	free(current);
	free(list);

}





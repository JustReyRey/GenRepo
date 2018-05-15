#include <stdio.h>
#include <stdlib.h>
#include "LinkedListAPI.h"
//LinkedListAPI.h = API Found with only function prototypes. allowing to see what functions are needed to complete a linked lists, while requiring each function to be completed in entirety.


List *initializeList(void (*printFunction)(void *toBePrinted),void (*deleteFunction)(void *toBeDeleted),int (*compareFunction)(const void *first,const void *second)){
List *list = malloc(sizeof(List));
list->head = NULL;
list->tail = NULL;
 list->printNode = printFunction;
 list->deleteNode = deleteFunction;
 list->compare = compareFunction;
return list;
}

Node *initializeNode (void *data){
	Node *newNode = malloc(sizeof(Node));
	newNode->data = data;
	newNode->next = NULL;
	newNode->prev = NULL;
	return newNode;
}

//Links a node initialized within function to the linked list and becomes the new head of the list
void insertFront (List *list,void *toBeAdded){
	Node* newNode = initializeNode(toBeAdded);
 	
	if(list->head == NULL){
	  list->head = newNode;
	  list->tail = newNode;
	  return;
	}
	newNode->next = list->head;
	list->head->prev = newNode;
	list->head = newNode;
}

//Links a node initialized within function to the linked list and becomes the new tail of the list
void insertBack (List *list,void *toBeAdded){
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



void *getFromFront (List *list){
  Node *temp = list->head->data;
 return temp;
}

void *getFromBack (List *list){
  Node *temp = list->tail->data;
 return temp;
}

/* 
iterates through the linked list stating from the head and uses the custom print function to print values within the data variable
*/
void printForward(List *list){
  Node* current = list->head;
  void (*funcPrint)(void* toPrint);
  funcPrint = list->printNode;
  
  while (current != NULL){
    funcPrint(current->data);
    current = current->next;
  }

}

/* 
iterates through the linked list stating from the tail and uses the custom print function to print values within the data variable
*/
void printBackwards(List *list){
  Node* current = list->tail;
  void (*funcPrint)(void* toPrint);
  funcPrint = list->printNode;
  while (current != NULL){
    funcPrint(current->data);
    current = current->prev;
  }
}



/*
used to delete specific information that is contained within the linked list
@returns -1 if the value being searched for is never found
*/
int deleteNodeFromList (List *list, void *toBeDeleted){

	Node* temp = list->head;
	if(temp != NULL && temp->data == toBeDeleted){
	  list->head = temp->next;
	  free(temp->data);
	  free(temp);
	  return 0;
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
	free(temp->data);
	free(temp);
		
	return 0;
}


//used to delete the created linked list by iterating through and freeing memory
void deleteList(List *list){
	
	Node *current = list->head;
	Node *next = current;
	while (current != NULL){ 
	  next = current->next;
	  free(current->data);
	  free(current);
	  current = next;
	}
	free(next);
	free(current);
	free(list);

}

#include "linkListADT.h"
#include "queuePriorityADT.h"
//uses the linkedListADT.h prioritQueue is used as a wrapper to complete the priority queue functionality

/*
@Node Structure used for prioirty queue
typedef struct listNode{
    void *data;
    struct listNode *prev;
    struct listNode *next;
  int priority;
} Node;
*/

Queues *create(void (*printFunction)(void *toBePrinted),void (*deleteFunction)(void *toBeDeleted),int (*compareFunction)(const void *first,const void *second)){

  Queues *que = malloc(sizeof(Queues));
  que->count = 0;
  que->list = initializeList(printFunction,deleteFunction,compareFunction);
  return que;

}

Node *initializePriorityNode(void *data, int priority){

  Node *newNode = initializeNode(data);
  newNode->priority = priority;
  return newNode;

}

void Destroy(Queues *q){
  deleteList(q->list);
  free(q);
}

void pop(Queues *q){
  deleteNodeFromList(q->list,peek(q));
}

void insert(Queues *q,void *data, int priority){
  insertPrioritySorted(q->list,data,priority);

}

void *peek(Queues *q){
  void *temp = getFromFront(q->list);
  return temp;
}

void removeFromQue (Queues *q, void *toBeDeleted){

  deleteNodeFromList (q->list,toBeDeleted);
  
}

//inserts a node within the que based upon the priorty value stored within the node
void insertPrioritySorted(List *list, void *toBeAdded, int priority){
  Node *newNode = initializePriorityNode(toBeAdded,priority);
  Node *currentNode;
 
  if (list->head == NULL){
        list->head = newNode;
	list->tail = newNode;
  }
    else if (list->head->priority > newNode->priority) {
        newNode->next = list->head;
        newNode->next->prev = newNode;
        list->head = newNode;
    }
 
    else {
        currentNode = list->head;
        while ( currentNode->next != NULL && (currentNode->next->priority <= newNode->priority) ){
            currentNode = currentNode->next;
	}
        newNode->next = currentNode->next;

        if (currentNode->next != NULL){
            newNode->next->prev = newNode;
	}
	if (currentNode->next == NULL){
	  list->tail = newNode;
	}
        currentNode->next = newNode;
        newNode->prev = currentNode;
    }
}


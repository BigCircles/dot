#include <stdio.h>
#include <stdlib.h>
#include "linkedworm.h"

//int main(){
//  linkedlist* start = createnode(5,5); 
//  add(start, 4, 4);
//  add(start, 3, 3);
//  add(start, 2, 2);
//  displayworm(start);
//  updatewormhead(start, 1, 0);
//  displayworm(start);
//  updatewormhead(start, -1, 0);
//  displayworm(start);
//
//  linkedlist* walk = start;
//  linkedlist* next = NULL;
//
//  // Free testing
//  while(walk != NULL)
//  {
//    next = walk->next;
//    free(walk);
//    walk = next;
//  }
//  return 0;
//}
//
void add(linkedlist* head, int x, int y){
  linkedlist* new = createnode(x, y); 
  // head is empty
  if(!head){
    printf("%s\n", "head undefined error");
  }
  else if(head){
    //traverse to the end of the list
    while( head->next != NULL){
      head = head->next;
    } 
    head->next = new;
  }
}

linkedlist* createnode(int x, int y){
  linkedlist* tmp = malloc(sizeof(linkedlist));
  tmp->current.x = x;
  tmp->current.y = y;
  tmp->prev.x = x;
  tmp->prev.y = y;
  tmp->next = NULL;
  return tmp;
}


void incrementworm(linkedlist* head, coord prev){
    head->prev = head->current;
    head->current = prev; 
    if(head->next != NULL)
      incrementworm(head->next, head->prev);
    else 
      return;
}

void updateworm(linkedlist* head, int x, int y){
  head->current.x =  x;
  head->current.y =  y;
  if(head->next != NULL)
    incrementworm(head->next, head->prev);
}

void freemem(linkedlist* head){
  linkedlist* next = NULL;
  while(head != NULL){
    next = head->next;
    free(head);
    head = next; 
  }
}

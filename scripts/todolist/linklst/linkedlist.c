#include <stdio.h>
#include <stdlib.h>
#include "linkedlist.h"

linkedlist* create(char* newitem){
  linkedlist* i = malloc(sizeof(linkedlist)) ;
  i->nodevalue=1;
  i->item=newitem;
  i->next=NULL;
  return i;  
}

void add(linkedlist* list, char* newitem){
  linkedlist* new = malloc(sizeof(linkedlist)); 
  new->nodevalue = list->nodevalue+1;
  new->item = newitem;
  new->next = NULL;
  for(;list->next; list = list->next){

  }
  list->next = new;
}

void print(linkedlist* list){
  linkedlist* i = list;
 for(;i != NULL; i = i->next){
    printf("%i-%s\n", i->nodevalue, i->item);
  }
}

void release(linkedlist* head){
 linkedlist* start = head;
 linkedlist* next = NULL;
 for(;start != NULL; start = next)
 {
    next = start->next;
    free(start);
 }
}


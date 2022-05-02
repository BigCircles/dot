typedef struct linkedlist {
  int nodevalue;
  char *item;
  struct linkedlist *next;
} linkedlist;

linkedlist* create(char* newitem);
void add(linkedlist* list, char* newitem);
void print(linkedlist* list);
void release(linkedlist* head);

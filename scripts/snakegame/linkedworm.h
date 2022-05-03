typedef struct coord {
  int x,y;
} coord; 

typedef struct node {
  coord current;
  coord prev;
  struct node* next;
} linkedlist;

void add(linkedlist* head, int x, int y );
linkedlist* createnode(int x, int y);
void incrementworm(linkedlist* head, coord prev);
void updateworm(linkedlist* head, int x, int y);
void freemem(linkedlist* head);



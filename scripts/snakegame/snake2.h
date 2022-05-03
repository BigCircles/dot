#define LENGTH 20 
#define HEIGHT 10

#include "linkedworm.h"


typedef struct coords {
  int x,y;
} coords;

typedef struct fruit {
  coords coord;
  char symbol;
} fruit;

void draw(char array[HEIGHT][LENGTH], linkedlist* p1, fruit curr); char getinput();
char update(char input, linkedlist* p1, char array[HEIGHT][LENGTH] ,char prev_in, fruit *curr);
int gamelost(int gamestate);
fruit spawnfruit();
void initboard(char array[HEIGHT][LENGTH], linkedlist* player, fruit currentfruit);

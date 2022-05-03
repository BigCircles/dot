#define LENGTH 20 
#define HEIGHT 10

typedef struct coords {
  int x,y;
} coords;

typedef struct node {
  coords current;
  coords previous;
  node* nextlink;

} worm;

typedef struct fruit {
  coords coord;
  char fruitsym;
} fruit;

void draw(char array[HEIGHT][LENGTH], coords p1, fruit curr); char getinput();
char update(char input, coords* p1, char array[HEIGHT][LENGTH] ,char prev_in, fruit *curr);
int gamelost(int gamestate);
fruit spawnfruit();


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ncurses.h>
#include <time.h>
#include "snake2.h"
#include <sys/ioctl.h>

/*
Daniel Stremler
4/25/2022
Snake Game
Parts of the Game
- Spawn a board - X
- Snake movement, one link - X
- Fruit spawning - X
- Map Area (Array seems good as size never changes) - X
 * */
int main(){
  int input=0;
  int fruitcounter = 0;

  char gameboard[HEIGHT][LENGTH];
  char prev_input; 
  fruit currentfruit = spawnfruit();
  linkedlist* player = createnode((HEIGHT/2), (LENGTH/2));

  // ncurses init
  initscr(); // Start curses mode
  curs_set(0);
  nocbreak;
  noecho();
  initboard(gameboard, player, currentfruit);
  
  // game loop
  while(!gamelost(prev_input)){
    nanosleep((const struct timespec[]){{0,500000000}},NULL);
    input = getinput();
    prev_input = update(input, player, gameboard, prev_input, &currentfruit, &fruitcounter);
    draw(gameboard, player, currentfruit);
  }
  freemem(player);
  endwin();
  return 0;
}

/*
 Game bounds - #
 Left / Right Array position Length 0, max-1 
 Top / Bottom Array position Height 0, max-1
 * */
void draw(char array[HEIGHT][LENGTH], linkedlist* p1, fruit curr){
  clear();
  struct winsize w;
  ioctl(0, TIOCGWINSZ, &w);
  int rows=w.ws_row;
  int cols=w.ws_col;

  int rowcenter = (rows - HEIGHT)/2;
  int colcenter = (cols - LENGTH)/2;

  //Probably an easier way to do this with ncurses
  //Center Columns
  for(int x=0; x <rowcenter;x++){ 
    printw("\n");
  }

  for(int x=0; x < HEIGHT;x++){ 
    //Center Rows
    for(int x=0;x<colcenter;x++){
      printw(" ");
    }
    for(int y=0; y < LENGTH; y++){
        printw("%c", array[x][y]);
    }
    printw("\n");
  }
  refresh();
}

char getinput(){
  timeout(0);
  char keyboard = getch();
  flushinp();
  return keyboard;
}

char update(char input, linkedlist* p1, char array[HEIGHT][LENGTH], char prev_in, fruit* curr, int* fruitcount){
  char currinput = input; 

  struct winsize w;
  ioctl(0, TIOCGWINSZ, &w);
  int rows=w.ws_row;
  int cols=w.ws_col;

  int rowcenter = (rows - HEIGHT)/2;
  int colcenter = (cols - LENGTH)/2;

  // Player keeps moving in whichever direction they last played
  if ((int)currinput == -1){
    currinput = prev_in;
  }
  p1->prev = p1->current;
  array[p1->prev.x][p1->prev.y] = ' ';
  //Update player direction
  switch(currinput){
    case 'w':
      p1->current.x = p1->current.x - 1; 
      break;
    case 'a':
      p1->current.y = p1->current.y - 1; 
      break;
    case 's':
      p1->current.x = p1->current.x + 1; 
      break;
    case 'd':
      p1->current.y = p1->current.y + 1; 
      break;
  }
  updateworm(p1, p1->current.x, p1->current.y); 
  array[p1->current.x][p1->current.y] = 'o';

  //make tmp list to iterate though - so i dont lose head
  //update board with current worm position
  linkedlist* playertmp = p1;
  while(playertmp->next != NULL){
    playertmp = playertmp->next;
    array[playertmp->prev.x][playertmp->prev.y] = ' ';
    array[playertmp->current.x][playertmp->current.y] = 'o';
  }

  //Fruit Spawning
  if (p1->current.x == curr->coord.x && p1->current.y == curr->coord.y){
    add(p1,p1->prev.x, p1->prev.y);
    //deferenced so i'm not incrementing address value by 1
    //pointer++ would give the value of the next place in memory
    *fruitcount = *fruitcount+1;
    fruit new = spawnfruit();
    while(new.coord.x == curr->coord.x && new.coord.y == curr->coord.y){
        new = spawnfruit();
    }
    curr->coord = new.coord;
   array[curr->coord.x][curr->coord.y] = curr->symbol;
  }

  //
  // Check if player hit the border of the game
  if(p1->current.x == 0 || p1->current.x == (HEIGHT-1)
    || p1->current.y == 0 || p1->current.y == (LENGTH-1)){
    //Dereferenced fruitcount because i sent in its address into the function
    mvprintw(rowcenter+HEIGHT, colcenter,"%s%i\n", "Player Scored: ", *fruitcount);
    mvprintw(rowcenter+HEIGHT+1, colcenter,"%s\n", "Game Over");
    refresh();
    sleep(3);
    return 1;
  }
//  if(p1->current.y == 0 || p1->current.y == (LENGTH-1)){
//    printw("%s%i\n", "Player Scored: ", fruitcounter);
//    printw("Game Lost");
//    refresh();
//    sleep(3);
//    return 1;
//  }

  return currinput;
}

int gamelost(int gamestate){
  if(gamestate == 1)
    return 1;
  return 0;
}

fruit spawnfruit(){
  fruit new;
  srand(time(0));
  new.coord.x = rand()%(HEIGHT-2)+ 1;
  new.coord.y = rand()%(LENGTH-2)+ 1;
  new.symbol = 'F';
  return new;
}

void initboard(char array[HEIGHT][LENGTH], linkedlist* player, fruit fruit){
//Establish Bounds
  for(int x=0; x < HEIGHT;x++){ 
    for(int y=0; y < LENGTH; y++){
      if (x == 0 || x == (HEIGHT-1) || y == 0 || y == (LENGTH-1)){
        array[x][y] = '#';
      }else{
        array[x][y] = ' ';
      }
    }
  }
  // init player position
  array[player->current.x][player->current.y] = 'o';
  //init fruit position
  array[fruit.coord.x][fruit.coord.y] = fruit.symbol;
}


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ncurses.h>
#include <time.h>
#include "snake2.h"

/*
Daniel Stremler
4/25/2022
Snake Game
Parts of the Game
- Spawn a board - X
- Snake movement, one link - X
- Fruit spawning 
- Map Area (Array seems good as size never changes) - X
 * */
int main(){
  int input;
  char gameboard[HEIGHT][LENGTH];
  char prev_input; 
  fruit currentfruit = spawnfruit();
  coords player = {(HEIGHT/2),(LENGTH/2)};

  // ncurses init
  initscr(); // Start curses mode
  curs_set(0);
  nocbreak;
  noecho();
  
  // game loop
  while(!gamelost(prev_input)){
    nanosleep((const struct timespec[]){{0,500000000}},NULL);
    draw(gameboard, player, currentfruit);
    input = getinput();
    prev_input = update(input,&player, gameboard, prev_input, &currentfruit);
  }
  endwin();
  return 0;
}

/*
 Game bounds - #
 Left / Right Array position Length 0, max-1 
 Top / Bottom Array position Height 0, max-1
 * */
void draw(char array[HEIGHT][LENGTH], coords p1, fruit curr){
  clear();
  for(int x=0; x < HEIGHT;x++){ 
    for(int y=0; y < LENGTH; y++){
      if(x == p1.x & p1.y == y){
        array[p1.x][p1.y] = 'o';
        printw("%c", array[x][y]);
        continue;
      }
      if(x == curr.coord.x && y == curr.coord.y){
        array[x][y] = curr.fruitsym;
        printw("%c", array[x][y]);
        continue;
      }

      if (x == 0 || x == (HEIGHT-1) || y == 0 || y == (LENGTH-1)){
        array[x][y] = '#';
        printw("%c", array[x][y]);
      }else{
        array[x][y] = ' ';
        printw("%c", array[x][y]);
      }
    }
    printw("\n");
  }
}

char getinput(){
  timeout(0);
  char keyboard = getch();
  flushinp();
  return keyboard;
}

char update(char input, coords* p1, char array[HEIGHT][LENGTH], char prev_in, fruit* curr){
  char currinput = input; 
  //printw("%c\n", prev_in);
 // printw("%i\n", currinput);
 
  // Player keeps moving in whichever direction they last played
  if ((int)currinput == -1){
    currinput = prev_in;
  }

  if (p1->x == curr->coord.x && p1->y == curr->coord.y){
    fruit new = spawnfruit();
    while(new.coord.x == curr->coord.x && new.coord.y == curr->coord.y){
        new = spawnfruit();
    }
    curr->coord.x = new.coord.x;
    curr->coord.y = new.coord.y;
    refresh();
  }

  // Check if player hit the border of the game
  if(p1->x == 0 || p1->x == (HEIGHT-1)){
    //printw("%s%i\n", "Player Scored: ", p1->counter);
    printw("Game Lost");
    refresh();
    sleep(3);
    return 1;
  }
  if(p1->y == 0 || p1->y == (LENGTH-1)){
    //printw("%s%i\n", "Player Scored: ", p1->counter);
    printw("Game Lost");
    refresh();
    sleep(3);
    return 1;
  }

  //Update player direction
  switch(currinput){
    case 'w':
      p1->x = p1->x - 1; 
      break;
    case 'a':
      p1->y = p1->y - 1; 
      break;
    case 's':
      p1->x = p1->x + 1; 
      break;
    case 'd':
      p1->y = p1->y + 1; 
      break;
  }

  refresh();
  return currinput;
}

int gamelost(int gamestate){
  if(gamestate == 1)
    return 1;
  return 0;
}

fruit spawnfruit(){
  fruit new;
  new.coord.x = (rand()%(HEIGHT-2)+ 1);
  new.coord.y = (rand()%(LENGTH-2)+ 1);
  new.fruitsym = 'F';
  return new;
}

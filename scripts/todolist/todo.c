#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "todo.h"


//Location the todo script is being ran from
char installpath[80] = "/home/stremler/.config/dot/scripts/todolist";
char todotxt[80];

int main(int argc, char* argv[]){
  setuppath();
 char *input = ""; 
  char option;
  char *aoption = ""; 
  // Take note that this needs parens around the option=getopt
  // Not sure why? Maybe it forces it to eval that first
  
  if (argc == 1){
    printf("%s\n", "Usage:");
    printf("%s\n", "todo -a [item] to add to list");
    printf("%s\n", "todo -d to display the list");
    printf("%s\n", "todo -r [item number] to remove item");
  }
  while((option=getopt(argc, argv, "a:dr:")) != -1){
    switch(option){
      case 'a':
        input = optarg;
        savetofile(input);
        break;
      case 'd':
        displaylist();
        break;
      case 'r':
        input = optarg;
        removeline(atoi(input));
        break;
      case '?':
        printf("%s\n", "'?': Option NOT found");
        break;
      default:
        fprintf(stderr, "%s\n", "Default hit");
        break;
    }   
    argc -= optind;
    argv += optind;
  }
  return 1;
}

void setuppath(){
  strcpy(todotxt, installpath);
  strcat(todotxt, "/todolist.txt");
}

void removeline(int linenum){
  char replicatxt[80];
  char lineread[81];
  int linesread=0;

  strcpy(todotxt, installpath);
  strcat(todotxt, "/todolist.txt");
  FILE *old = fopen(todotxt, "r");

  strcpy(replicatxt, installpath);
  strcat(replicatxt, "/replica.txt");
  FILE *new = fopen(replicatxt, "w");

  if (old == NULL || new == NULL)
    return;

  while(fgets(lineread,80,old)!= NULL){
    linesread++;
    if (linesread == linenum){
      continue;
    }
    else{
      fprintf(new,"%s", lineread);
    }
  }

  remove(todotxt);
  rename(replicatxt, todotxt);
  fclose(old);
  fclose(new);
  displaylist();
}

//todo: Save a argument to file
void savetofile(char* input){
  FILE *listfile = fopen(todotxt, "a");
    if (fprintf(listfile,"%s\n", input) <= -1)
      printf("%s\n", "Writing to file encountered an error");
  fclose(listfile);
  displaylist();
}

void displaylist(){
  FILE *listfile = fopen(todotxt, "r");
  char lineread[81];
  int linecounter=1;

  printf("%s\n", "Todolist");
  printf("%s\n", "-------------------------------------");
  while(fgets(lineread,80,listfile) != NULL){
      printf("%i- %s", linecounter++, lineread);    
  }
  printf("%s\n", "-------------------------------------");
  fclose(listfile);
}

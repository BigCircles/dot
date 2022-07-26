#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void reverse_print(char *input){
  size_t string_length = strlen(input);
  char *curr_index = (input + (string_length - 1));
  if (*curr_index == '\r' || *curr_index == '\n')
    *curr_index = '\0';
  while (curr_index >= input){
    printf("%c", *curr_index);
    curr_index = curr_index - 1;
  }
  printf("\n");
}

void get_string(char *input, int arrsize){
  printf("%s\n", "Please print a string to reverse");
  fgets(input, arrsize, stdin);
}

int main(int argc, char *argv[]){
  int arrsize = 100;
  char string[arrsize];

  if (argc == 1){ // If called with no args ask for args to reverse
    while (fgets(string, arrsize, stdin)){
      reverse_print(string);
    }
      return 0;
  }
  if (argc == 2) {
    if (strstr(argv[1], "help")){
      printf("%s\n", "Usage: reverseinput [<string>]");
      return 0;
    }
    reverse_print(argv[1]);
    return 0;
  }
  printf("%s", "Script was passed more then 1 argument to reverse.");
  return 1;
}

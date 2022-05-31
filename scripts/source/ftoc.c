#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
  
float ftoc(int faren);

int main(int argc, char *argv[]){
  int conv_value =0;
  char temp[6] = {0};
  int err = 0;
 
  if(argc == 1){
    err = scanf("%5s", temp);
    conv_value = atoi(temp);
  }else if(argc == 2){
    if(strcmp(argv[1], "help") == 0){
      printf("%s\n", "Usage: /ftoc [farenheit]");
      return 1;
    }
    conv_value = atoi(argv[1]);
  }
  else{
    printf("%s\n", "Invalid arguments - ftoc help - for usage");
    return 1;
  }

  if(conv_value == 0){
     printf("%s\n", "Error when converting integer");
     return 1;
  }

  printf("%.2fc\n", ftoc(conv_value));
  return 0;
}

// C = (F-32) / 1.8
float ftoc(int faren){
  return (faren-32)*0.5556;
}

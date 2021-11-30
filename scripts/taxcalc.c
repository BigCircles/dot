#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

float calctax(float price, float taxrate){
  return price * (taxrate/100+1.0);
}

int main(int argc, char *argv[]){
  char ch = 0;
  float price = 0.0;
  float tax = 0.0;
  float total = 0.0;

  if(argc==1)
    printf("%s\n", "Usage: taxcalc [price] [taxrate]");
  if(argc == 3){
    price = atof(argv[1]);
    tax = atof(argv[2]);
    printf("%s%.2f\n", "Price + Tax is: ", calctax(price, tax));
  }
  return 0;
}

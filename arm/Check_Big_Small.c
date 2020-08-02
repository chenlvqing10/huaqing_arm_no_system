#include <stdio.h>

int check()
{
  //define a union
  union{
    char c;
    int  i;
  }ui;

  //if big(00 00 00 01) c=00 then little(01 00 00 00) c=01
  ui.i=1;
  
  return ui.c;
}

int main()
{
 if(check()==1)
    printf("the Big-end Storage Pattern\n");
 else
    printf("the Little-end Storage Pattern\n");
}

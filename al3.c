#include <stdio.h>

int main()
{
 int var;
 int d1;
 int d2;
 int d3;

 var = 129;
 d1 = var / 100;
 d2 = (var % 100)/10;
 d3 = (var % 10);
  
printf("%d %d %d\n",d1,d2,d3);

 putchar(d1+'0');
 putchar(d2+'0');
 putchar(d3+'0');
}

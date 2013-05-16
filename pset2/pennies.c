/*
 * show how many pennies you will get
 */
#include <cs50.h>
#include <stdio.h>
#include <math.h>

long long ex(int e);
int
main(void)
{int d;
 int p;
// int total;
long long total=0;
long long total2=0;
do
 {printf("Days in month: ");
  d = GetInt();
  }
 while(!(d==28||d==29||d==30||d==31));
 do
  {printf("Pennies on first day: ");
   p = GetInt();
  }
 while(p <= 0);

 for(int i=0;i<d;i++)
{
//if(i==30)
//printf("%f\n",ex(i));
 total += ex(i);
 total2 += pow(2,i);
 }
// int final = total/100;
 //int real = (int)total/100;

 printf("$%lld\n",p*total);
 printf("$%lld\n",p*total2);

}
long long ex(int e)
{
//int ans = 1;
long long ans = 1;
 for(int i=0;i<e;i++)
 ans *= 2;
 return ans;
}


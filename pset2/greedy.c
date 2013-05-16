/*
 * given a mount of money,show how many coins you need to represent
 * that money.
 * Written by linuxfish
 * Date: 05/08/2013
 */

#include <stdio.h>
#include <cs50.h>
#include <math.h>

int
main(void)
{
    int count = 0;
    printf("how much change is owed? ");
    int change = round(GetFloat() * 100);
    while (change <= 0)
        {
            printf("Er,how much change is owed? ");
            change = round(GetFloat() * 100);
        }
    count = count + change / 25;
    change = change % 25;
    count = count + change /10;
    change = change % 10;
    count = count + change / 5;
    change = change % 5;
    int total = count + change;
    printf("The total coins needed is: %d\n",total);
}

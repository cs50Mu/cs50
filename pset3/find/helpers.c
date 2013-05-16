/**************************************************************************** 
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 ***************************************************************************/
       
#include <cs50.h>

#include "helpers.h"


/*
 * Returns true if value is in array of n values, else false.
 */

bool 
search(int value, int array[], int n)
{
    // TODO: re-implement as binary search
/*    for (int i = 0; i < n; i++)
        if (array[i] == value)
            return true;
    return false; */
    int low = 0;
    int high = n - 1;
    while (low <= high)
    {
        int middle = low + (high-low)/2;
        if (value > array[middle])
        {
            low = middle + 1;
        }
        else if (value < array[middle])
        {
            high = middle - 1;
        }
        else
            return true;
     }
return false;    
}
            



/*
 * Sorts array of n values.
 */

void 
sort(int values[], int n)
{
    // TODO: implement an O(n^2) sort
    for (int i=0;i<n;i++)
    {
        for (int j=i+1;j<n;j++)
        {
            if (values[i] > values[j])
            {
                int temp;
                temp = values[i];
                values[i] = values[j];
                values[j] = temp;
            }
         }
     }
}

/*
 * Caesar encrypt
 */

#include <stdio.h>
#include <cs50.h>
#include <stdlib.h>
#include <string.h>

int
main(int argc,string argv[])
{
    int k = atoi(argv[1]);   // convert string to int
    printf("Tell me the text you want to encrypt:\n");
    string text = GetString();
    for (int i=0,n=strlen(text);i<n;i++)
    {
        if (text[i] >= 65 && text[i] <= 90)
        {
            text[i] = (((text[i] - 65) + k)%26) + 65;   // Notice the algorithm here
        }
        else if (text[i] >= 97 && text[i] <= 122)
        {
            text[i] = (((text[i] - 97) + k)%26) + 97;
        }
    }
    for (int i=0,n=strlen(text);i<n;i++)
    {
        printf("%c",text[i]);
    } 
    printf("\n");
}

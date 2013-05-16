/*
 * vigenere encrypt method
 */

#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <stdlib.h>

int
main(int argc,string argv[])
{
    string key = argv[1];
    for (int i=0;i<strlen(key);i++)
    {
        if (key[i] >=97 && key[i] <= 122)
        {
            key[i] -= 32;
        }
    }
    printf("Enter the text you wanna encrypt:\n");
    string text = GetString();
    for (int i=0,j=0;i<strlen(text);i++)
    {
        if (j == strlen(key))
        {
            j = 0;                    // cycle through the character of key by assigning j=0 at some point constently.
        }
        if (text[i] >= 65 && text[i] <= 90)
        {
            text[i] = ((text[i] - 65) + (key[j] - 65))%26 + 65;
            j++;
        }
        else if (text[i] >= 97 && text[i] <= 122)
        {
            text[i] = ((text[i] - 97) + (key[j] - 65))%26 + 97;
            j++;
        }
     }

     printf("%s\n",text);
}




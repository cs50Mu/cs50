/****************************************************************************
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 6
 *
 * valgrink warn that there are uninitilized values, could be the node struct, but don't
 * know how to initialize it, anyway, it works at last!

 
 * Implements a dictionary's functionality.
 ***************************************************************************/

#include <stdbool.h>

#include <ctype.h>    // for tolower() function.

#include "dictionary.h"

#include <string.h>

#include <stdio.h>
#include <stdlib.h>

#define HASHTABLE_SIZE 5000


int count = 0;     // gloabal counter
typedef struct node {         // data structer .aka. linked list
    char word[LENGTH+1];
    struct node *next;
    } node;
node *hashtable[HASHTABLE_SIZE] = {NULL};  // initilization, but only initilize the pointer array, not the node struct.


/*
 * Returns true if word is in dictionary else false.
 */

bool
check(const char *word)
{
    int index = 0;
    char lowerWord[LENGTH+1] = {};    // must initialize to zero! Or there will be some weird problem.
    for (int i=0,n=strlen(word);i<n;i++)
        lowerWord[i] = tolower(word[i]);   // convert all word to lowercase for comparison.
    for (int i=0,n=strlen(lowerWord);i<n;i++)
        {
            index += lowerWord[i];
        }
    index %= HASHTABLE_SIZE;
    if (hashtable[index] == NULL)   //  transverse the linked list.
        return false;
    else
    {
        node *p = hashtable[index];
        while(p != NULL)
        {
            if (strcmp(lowerWord,p->word) == 0)
                return true;
            p = p->next;
        }
    return false;
    }
}


/*
 * Loads dictionary into memory.  Returns true if successful else false.
 */

bool
load(const char *dictionary)
{
    int index;
    char word[LENGTH+1] = {};  // must initialize to zero! Or there will be some weird problem.
    FILE *fp = fopen(dictionary,"r");
    if (fp == NULL)
        return false;
    while (!feof(fp))
    {
        index = 0;
        fscanf(fp,"%s\n",word); // have to use "%s\n" instead of "%s", or the count will be wrong, don't know why.
        count++;    
        for (int i=0,n=strlen(word);i<n;i++)
            {
                index += word[i];
            }
        index %= HASHTABLE_SIZE;  // hash the word to some number
        if (hashtable[index] == NULL)
        {
            node *first = malloc(sizeof(node));  // 
            hashtable[index] = first;
            for (int i=0;i<strlen(word);i++)    // create the linked list for 
            {                                   // duplicated hash numbers.
                first->word[i] = word[i];
            }
            first->next = NULL;
        }
        else
        {
            node *first = malloc(sizeof(node));
            for (int i=0;i<strlen(word);i++)
            {
                first->word[i] = word[i];
            }
            first->next = hashtable[index];
            hashtable[index] = first;
        }
    }

fclose(fp);           
return true;
}


/*
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */

unsigned int
size(void)
{
    if (count)
        return count;
    else
        return 0;
}


/*
 * Unloads dictionary from memory.  Returns true if successful else false.
 */

bool
unload(void)
{
    for (int i=0;i<HASHTABLE_SIZE;i++)
    {
        if (hashtable[i] == NULL)
            continue;
        node *iterator = hashtable[i];
        while (iterator != NULL)
            {
                node *n = iterator;
                iterator = iterator->next;
                free(n);
            }
    }
    return true;         // can't figure out when to return false...
}

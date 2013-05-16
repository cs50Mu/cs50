/***************************************************************************
 * generate.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Generates pseudorandom numbers in [0,LIMIT), one per line.
 *
 * Usage: generate n [s]
 *
 * where n is number of pseudorandom numbers to print
 * and s is an optional seed
 ***************************************************************************/
       
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define LIMIT 65536

int
main(int argc, char *argv[])
{
    // TODO: ensure user input the correct parameters.
    if (argc != 2 && argc != 3)
    {
        printf("Usage: generate n [s]\n");
        return 1;
    }

    // TODO: convert input char into int type.
    int n = atoi(argv[1]);

    // TODO: set the seed, if seed is not given, grab it from time()
    if (argc == 3)
        srand((unsigned int) atoi(argv[2]));
    else
        srand((unsigned int) time(NULL));
    //    printf("%d",(unsigned int) time(NULL));

    // TODO: output the pseudo numbers.
    for (int i = 0; i < n; i++)
        printf("%d\n", rand() % LIMIT);

    // that's all folks
    return 0;
}

/****************************************************************************
 * recover.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Recovers JPEGs from a forensic image.
 ***************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#define BLOCKSIZE 512

int
main(void)
{
    typedef uint8_t BYTE;
    BYTE block[BLOCKSIZE];
    char filename[10];
    int count = 0;  // count for filename
    // open raw file
    FILE *fp = fopen("/home/cs50/pub/share/pset5/card.raw","r");
    if (fp == NULL)
    {
        fclose(fp);
        fprintf(stderr, "Could not open %s.\n","card.raw");
        return 2;
    }
    FILE *outfile;
    outfile = NULL;   // initinate outfile, or may cause problem.
    while (! feof(fp))
    {
        fread(block, sizeof(BYTE), BLOCKSIZE, fp);  // read in 512 bytes, then process it depending on different sitiations
        if (block[0] == 0xff && block[1] == 0xd8 && block[2] == 0xff && (block[3] == 0xe0 || block[3] == 0xe1))
        {
            if (outfile == NULL)   // first time read
            {
                sprintf(filename,"%03d.jpg",count);
                outfile = fopen(filename,"w");
                fwrite(block,sizeof(BYTE),BLOCKSIZE,outfile);
                count++;
            }
            else    // not first time
            {
                fclose(outfile);
                sprintf(filename,"%03d.jpg",count);
                outfile = fopen(filename,"w");
                fwrite(block,sizeof(BYTE),BLOCKSIZE,outfile);
                count++;
            }
         }
         else
         {
            if (count == 0)   // don't read if first block is not valid data.
                continue;
            fwrite(block,sizeof(BYTE),BLOCKSIZE,outfile); // if not the end, go on reading.
         }
       }
  } 
    



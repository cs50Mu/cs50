/****************************************************************************
 * resize.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Resizes a BMP piece by piece, just because.
 ***************************************************************************/
       
#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"


int
main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        printf("Usage: resize infile outfile n\n");
        return 1;
    }

    // remember filenames
    char *infile = argv[2];
    char *outfile = argv[3];

    // check if n is between 0 and 100 
    if(atoi(argv[3]) > 100 && atoi(argv[3]) < 0)
    {
        printf("Usage: resize n infile outfile\n");
        return 1;
    }
    // remember n for scale
    int n = atoi(argv[1]);
    
    // open input file 
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || 
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }

    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);
    
    // save old attributes
    int oldWidth = bi.biWidth;
    int oldHeight = bi.biHeight;

    // adjust BITMAPINFOHEADER to reflect change in scale
    bi.biWidth *= n;
    bi.biHeight *= n;

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // determine padding for scanlines
    int old_padding =  (4 - (oldWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    int padding =  ((4 - (bi.biWidth * sizeof(RGBTRIPLE))) % 4) % 4;
    
    
    // var to track where we are in buffer
    int tracker;
    
    // allocate storage for buffer to hold scanline
    RGBTRIPLE *buffer = malloc(sizeof(RGBTRIPLE) * (bi.biWidth));

    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(oldHeight); i < biHeight; i++)
    {
        tracker = 0;
        // iterate over pixels in scanline
        for (int j = 0; j < oldWidth; j++)
        {
            // temporary storage
            RGBTRIPLE triple;
            // read RGB triple from infile
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
            
            // write pixel to buffer n times
           for(int count = 0; count < n; count++)
           {
                *(buffer+(tracker)) = triple;
                tracker++;
           }
                
        }
            


        // skip over padding, if any
        fseek(inptr, old_padding, SEEK_CUR);

        // write RGB triple to outfile
           for(int r = 0; r < n; r++)
           {
                fwrite((buffer), sizeof(RGBTRIPLE), bi.biWidth, outptr);

                // write padding to outfile
                for (int k = 0; k < padding; k++)
                    fputc(0x00, outptr);
           }

        
    }

    // free memory from buffer
    free(buffer);
    
    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // that's all folks
    return 0;
}

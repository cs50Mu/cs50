/****************************************************************************
 * resize.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Resize a small bmp file to a larger one.
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
        printf("Usage: resize n infile outfile\n");
        return 1;
    }

    // remember filenames
    int n = atoi(argv[1]);
    char *infile = argv[2];
    char *outfile = argv[3];

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

    // prepare for the output
    LONG oldbiWidth = bi.biWidth;
    LONG oldbiHeight = bi.biHeight;
    bi.biWidth *= n;
    bi.biHeight *= n;
    bf.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + bi.biWidth * bi.biHeight;

    // allocate storage for buffer to hold new scanline.
    RGBTRIPLE *scanline = malloc(sizeof(RGBTRIPLE) * bi.biWidth);

    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // determine padding for scanlines
    int padding =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    int oldpadding =  (4 - (oldbiWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    int tracker;

    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(oldbiHeight); i < biHeight; i++)
    {
        tracker = 0;  // every new scanline reset tracker to 0.
        // iterate over pixels in scanline
        for (int j = 0; j < oldbiWidth; j++)
        {
            // temporary storage
            RGBTRIPLE triple;

            // read RGB triple from infile
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
            // fill the new scanline buffer
            for (int m =0;m<n;m++)
            {
                *(scanline+(tracker)) = triple;
                tracker++;
            }

        }
                // write RGB triple to outfile
        //        fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
        for (int p=0;p<n;p++)
        {
            fwrite(scanline, sizeof(RGBTRIPLE),bi.biWidth,outptr);  // notice here scanline is already a pointer,
             // then add it back (to demonstrate how)              // so don't need &scanline here.
            for (int k = 0; k < padding; k++)
                fputc(0x00, outptr);
        }
            // skip over padding, if any
            fseek(inptr, oldpadding, SEEK_CUR);

    }

    // free ram
    free(scanline);
    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // that's all folks
    return 0;
}

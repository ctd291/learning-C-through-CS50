/**
 * Copies a BMP piece by piece, just because.
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        fprintf(stderr, "Usage: ./resize n infile outfile\n");
        return 1;
    }

    // remember filenames
    float f = atof(argv[1]);
    if (f <= 0 || f > 100)
    {
        fprintf(stderr, "please choose a resize factor between 1 and 100\n");
        return 1;
    }
    char *infile = argv[2];
    char *outfile = argv[3];


    // open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE *outptr = fopen(outfile, "w+");
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

    // creating an updated header
        BITMAPINFOHEADER bi_u = bi;

        bi_u.biWidth = round(bi.biWidth * f);
        bi_u.biHeight = round(bi.biHeight * f);

        int padding1 = (4 - (bi_u.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

        bi_u.biSizeImage = abs(bi_u.biHeight) * (bi_u.biWidth * sizeof(RGBTRIPLE) + padding1);

        BITMAPFILEHEADER bf_u = bf;
        bf_u.bfSize = bf.bfOffBits + bi_u.biSizeImage;

    // write outfile's BITMAPFILEHEADER
    fwrite(&bf_u, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi_u, sizeof(BITMAPINFOHEADER), 1, outptr);

    // determine padding for scanlines
    int padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    char *temp_mem;
    temp_mem = malloc(bi_u.biWidth * sizeof(RGBTRIPLE) + padding1);

    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {
            // iterate over pixels in scanline
            for (int j = 0; j < bi.biWidth; j++)
            {
                // temporary storage
                printf("inptr offest: %li\n", ftell(inptr));

                RGBTRIPLE triple;

                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

                // write RGB triple to outfile f times
                for(int n = 0; n < f; n++)
                {

                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                }
            }
            // adding padding
            for (int k = 0; k < padding1; k++)
            {
                fputc(0x00, outptr);
            }
            // skip over padding, if any

            fseek(inptr, padding, SEEK_CUR);
            //printf("2 %li\n", ftell(inptr));
            //int scanline = (bi.biWidth * sizeof(RGBTRIPLE) + padding);
            //fseek(inptr, -scanline, SEEK_CUR);
            //printf("outptr offset: %li\n", ftell(outptr));

            for(int z = 1; z < f ; z++)
            {
                fseek(outptr, -(int long)(bi_u.biWidth * sizeof(RGBTRIPLE) + padding1), SEEK_CUR);

                fread(temp_mem, (bi_u.biWidth * sizeof(RGBTRIPLE) + padding1), 1, outptr);

                fwrite(temp_mem, (bi_u.biWidth * sizeof(RGBTRIPLE) + padding1), 1, outptr);

                printf("outptr offset: %li\n", ftell(outptr));

            }
        }
    free(temp_mem);
    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
 }

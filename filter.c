// Usage: ./filter [-b|-g|-r|-s] infile outfile
#include <getopt.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

void grayscale(int height, int width, RGBTRIPLE image[height][width]);
void sepia(int height, int width, RGBTRIPLE image[height][width]);
void reflect(int height, int width, RGBTRIPLE image[height][width]);
void blur(int height, int width, RGBTRIPLE image[height][width]);

int main(int argc, char *argv[])
{
    char filter = 0;
    int opt;
    while ((opt = getopt(argc, argv, "bgrs")) != -1)
    {
        if (filter != 0)
        {
            fprintf(stderr, "Only one filter allowed.\n");
            return 1;
        }
        filter = (char) opt;
    }

    if (filter == 0 || argc != optind + 2)
    {
        fprintf(stderr, "Usage: ./filter [-b|-g|-r|-s] infile outfile\n");
        return 1;
    }

    char *infile = argv[optind];
    char *outfile = argv[optind + 1];

    FILE *inptr = fopen(infile, "rb");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 1;
    }

    FILE *outptr = fopen(outfile, "wb");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 1;
    }

    BITMAPFILEHEADER bf;
    BITMAPINFOHEADER bi;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fprintf(stderr, "Unsupported file format.\n");
        fclose(inptr);
        fclose(outptr);
        return 1;
    }

    int height = abs(bi.biHeight);
    int width = bi.biWidth;

    RGBTRIPLE(*image)[width] = calloc(height, width * sizeof(RGBTRIPLE));
    if (image == NULL)
    {
        fprintf(stderr, "Not enough memory.\n");
        fclose(inptr);
        fclose(outptr);
        return 1;
    }

    int padding = (4 - (width * sizeof(RGBTRIPLE)) % 4) % 4;

    for (int i = 0; i < height; i++)
    {
        fread(image[i], sizeof(RGBTRIPLE), width, inptr);
        fseek(inptr, padding, SEEK_CUR);
    }

    switch (filter)
    {
        case 'b':
            blur(height, width, image);
            break;
        case 'g':
            grayscale(height, width, image);
            break;
        case 'r':
            reflect(height, width, image);
            break;
        case 's':
            sepia(height, width, image);
            break;
    }

    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    for (int i = 0; i < height; i++)
    {
        fwrite(image[i], sizeof(RGBTRIPLE), width, outptr);
        for (int k = 0; k < padding; k++)
        {
            fputc(0x00, outptr);
        }
    }

    free(image);
    fclose(inptr);
    fclose(outptr);
    return 0;
}

void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int avg = (int) round(
                (image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0);
            image[i][j].rgbtRed = image[i][j].rgbtGreen = image[i][j].rgbtBlue = (uint8_t) avg;
        }
    }
}

void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int r = image[i][j].rgbtRed;
            int g = image[i][j].rgbtGreen;
            int b = image[i][j].rgbtBlue;

            int sepiaRed = (int) round(0.393 * r + 0.769 * g + 0.189 * b);
            int sepiaGreen = (int) round(0.349 * r + 0.686 * g + 0.168 * b);
            int sepiaBlue = (int) round(0.272 * r + 0.534 * g + 0.131 * b);

            image[i][j].rgbtRed = sepiaRed > 255 ? 255 : (uint8_t) sepiaRed;
            image[i][j].rgbtGreen = sepiaGreen > 255 ? 255 : (uint8_t) sepiaGreen;
            image[i][j].rgbtBlue = sepiaBlue > 255 ? 255 : (uint8_t) sepiaBlue;
        }
    }
}

void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            RGBTRIPLE tmp = image[i][j];
            image[i][j] = image[i][width - 1 - j];
            image[i][width - 1 - j] = tmp;
        }
    }
}

void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE(*copy)[width] = calloc(height, width * sizeof(RGBTRIPLE));
    if (copy == NULL)
    {
        return;
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int sumR = 0, sumG = 0, sumB = 0, count = 0;
            for (int di = -1; di <= 1; di++)
            {
                for (int dj = -1; dj <= 1; dj++)
                {
                    int ni = i + di, nj = j + dj;
                    if (ni >= 0 && ni < height && nj >= 0 && nj < width)
                    {
                        sumR += copy[ni][nj].rgbtRed;
                        sumG += copy[ni][nj].rgbtGreen;
                        sumB += copy[ni][nj].rgbtBlue;
                        count++;
                    }
                }
            }
            image[i][j].rgbtRed = (uint8_t) round((double) sumR / count);
            image[i][j].rgbtGreen = (uint8_t) round((double) sumG / count);
            image[i][j].rgbtBlue = (uint8_t) round((double) sumB / count);
        }
    }

    free(copy);
}

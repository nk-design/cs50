// Generates test.bmp: a tiny 3x2, 24-bit, bottom-up BMP with known pixel
// colors (including non-4-byte-aligned rows, to exercise padding handling),
// so filter.c's output can be checked against known-correct values.
#include <stdio.h>
#include <string.h>

#include "bmp.h"

int main(void)
{
    const int width = 3;
    const int height = 2;
    const int padding = (4 - (width * (int) sizeof(RGBTRIPLE)) % 4) % 4;
    const int rowSize = width * (int) sizeof(RGBTRIPLE) + padding;

    BITMAPFILEHEADER bf = {0};
    bf.bfType = 0x4d42;
    bf.bfOffBits = 54;
    bf.bfSize = 54 + rowSize * height;

    BITMAPINFOHEADER bi = {0};
    bi.biSize = 40;
    bi.biWidth = width;
    bi.biHeight = height;
    bi.biPlanes = 1;
    bi.biBitCount = 24;
    bi.biCompression = 0;
    bi.biSizeImage = rowSize * height;

    // Top row (as seen when viewed): red, green, blue.
    RGBTRIPLE top[3] = {
        {.rgbtBlue = 0, .rgbtGreen = 0, .rgbtRed = 255},
        {.rgbtBlue = 0, .rgbtGreen = 255, .rgbtRed = 0},
        {.rgbtBlue = 255, .rgbtGreen = 0, .rgbtRed = 0},
    };
    // Bottom row: white, black, gray.
    RGBTRIPLE bottom[3] = {
        {.rgbtBlue = 255, .rgbtGreen = 255, .rgbtRed = 255},
        {.rgbtBlue = 0, .rgbtGreen = 0, .rgbtRed = 0},
        {.rgbtBlue = 128, .rgbtGreen = 128, .rgbtRed = 128},
    };

    FILE *out = fopen("test.bmp", "wb");
    if (out == NULL)
    {
        printf("Could not create test.bmp.\n");
        return 1;
    }

    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, out);
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, out);

    uint8_t pad[3] = {0, 0, 0};
    // BMP rows are stored bottom-up.
    fwrite(bottom, sizeof(RGBTRIPLE), width, out);
    fwrite(pad, 1, padding, out);
    fwrite(top, sizeof(RGBTRIPLE), width, out);
    fwrite(pad, 1, padding, out);

    fclose(out);
    printf("Wrote test.bmp (%dx%d, %d bytes/row incl. %d padding)\n",
        width, height, rowSize, padding);
    return 0;
}

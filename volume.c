// Usage: ./volume input.wav output.wav factor
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    FILE *input = fopen(argv[1], "rb");
    if (input == NULL)
    {
        printf("Could not open file %s.\n", argv[1]);
        return 1;
    }

    FILE *output = fopen(argv[2], "wb");
    if (output == NULL)
    {
        printf("Could not open file %s.\n", argv[2]);
        fclose(input);
        return 1;
    }

    float factor = atof(argv[3]);

    uint8_t header[44];
    fread(header, sizeof(uint8_t), 44, input);
    fwrite(header, sizeof(uint8_t), 44, output);

    int16_t sample;
    while (fread(&sample, sizeof(int16_t), 1, input) == 1)
    {
        sample = sample * factor;
        fwrite(&sample, sizeof(int16_t), 1, output);
    }

    fclose(input);
    fclose(output);
    return 0;
}

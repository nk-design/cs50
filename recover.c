// Usage: ./recover card.raw
#include <stdint.h>
#include <stdio.h>

#define BLOCK_SIZE 512

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: ./recover card.raw\n");
        return 1;
    }

    FILE *card = fopen(argv[1], "rb");
    if (card == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", argv[1]);
        return 1;
    }

    uint8_t buffer[BLOCK_SIZE];
    FILE *img = NULL;
    char filename[8];
    int count = 0;

    while (fread(buffer, sizeof(uint8_t), BLOCK_SIZE, card) == BLOCK_SIZE)
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff &&
            (buffer[3] & 0xf0) == 0xe0)
        {
            if (img != NULL)
            {
                fclose(img);
            }
            sprintf(filename, "%03i.jpg", count);
            img = fopen(filename, "wb");
            if (img == NULL)
            {
                fprintf(stderr, "Could not create %s.\n", filename);
                fclose(card);
                return 1;
            }
            count++;
        }

        if (img != NULL)
        {
            fwrite(buffer, sizeof(uint8_t), BLOCK_SIZE, img);
        }
    }

    if (img != NULL)
    {
        fclose(img);
    }
    fclose(card);
    return 0;
}

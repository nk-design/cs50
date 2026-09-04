// Generates card.raw: 7 fake 512-byte blocks simulating a FAT card fragment.
// Block 0 is junk before any JPEG. Blocks 1-2 are a fake JPEG (2 blocks).
// Blocks 3-6 are a second fake JPEG (4 blocks). Only the first 4 bytes of a
// header block matter to recover.c's detector; the rest is filler so output
// byte counts can be checked against known values.
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#define BLOCK_SIZE 512

static void write_block(FILE *out, int is_header, uint8_t fill)
{
    uint8_t block[BLOCK_SIZE];
    memset(block, fill, BLOCK_SIZE);
    if (is_header)
    {
        block[0] = 0xff;
        block[1] = 0xd8;
        block[2] = 0xff;
        block[3] = 0xe0;
    }
    fwrite(block, sizeof(uint8_t), BLOCK_SIZE, out);
}

int main(void)
{
    FILE *out = fopen("card.raw", "wb");
    if (out == NULL)
    {
        printf("Could not create card.raw.\n");
        return 1;
    }

    write_block(out, 0, 0x00); // block 0: junk, no image open yet
    write_block(out, 1, 0x11); // block 1: header -> starts 000.jpg
    write_block(out, 0, 0x22); // block 2: continuation of 000.jpg
    write_block(out, 1, 0x33); // block 3: header -> starts 001.jpg
    write_block(out, 0, 0x44); // block 4: continuation of 001.jpg
    write_block(out, 0, 0x55); // block 5: continuation of 001.jpg
    write_block(out, 0, 0x66); // block 6: continuation of 001.jpg

    fclose(out);
    printf("Wrote card.raw: 7 blocks; expect 000.jpg=1024 bytes, 001.jpg=2048 bytes\n");
    return 0;
}

// Generates test.wav: a tiny mono 16-bit PCM WAV with constant-value samples,
// so volume.c's scaling can be checked against a known expected output.
#include <stdint.h>
#include <stdio.h>

#pragma pack(push, 1)
typedef struct
{
    char chunkID[4];
    uint32_t chunkSize;
    char format[4];
    char subchunk1ID[4];
    uint32_t subchunk1Size;
    uint16_t audioFormat;
    uint16_t numChannels;
    uint32_t sampleRate;
    uint32_t byteRate;
    uint16_t blockAlign;
    uint16_t bitsPerSample;
    char subchunk2ID[4];
    uint32_t subchunk2Size;
} WAVHEADER;
#pragma pack(pop)

int main(void)
{
    const int numSamples = 100;
    const int16_t sampleValue = 1000;

    WAVHEADER header = {
        .chunkID = {'R', 'I', 'F', 'F'},
        .chunkSize = 36 + numSamples * sizeof(int16_t),
        .format = {'W', 'A', 'V', 'E'},
        .subchunk1ID = {'f', 'm', 't', ' '},
        .subchunk1Size = 16,
        .audioFormat = 1,
        .numChannels = 1,
        .sampleRate = 8000,
        .byteRate = 8000 * 1 * 16 / 8,
        .blockAlign = 1 * 16 / 8,
        .bitsPerSample = 16,
        .subchunk2ID = {'d', 'a', 't', 'a'},
        .subchunk2Size = numSamples * sizeof(int16_t),
    };

    FILE *out = fopen("test.wav", "wb");
    if (out == NULL)
    {
        printf("Could not create test.wav.\n");
        return 1;
    }

    fwrite(&header, sizeof(WAVHEADER), 1, out);
    for (int i = 0; i < numSamples; i++)
    {
        fwrite(&sampleValue, sizeof(int16_t), 1, out);
    }

    fclose(out);
    printf("Wrote test.wav (%zu-byte header + %d samples of %d)\n",
        sizeof(WAVHEADER), numSamples, sampleValue);
    return 0;
}

// Implements a spell-checker, mimicking (a simplified version of) CS50's
// official speller.c harness, which isn't available here.
//
// Usage: ./speller [dictionary] text

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "dictionary.h"

// Default dictionary
#define DICTIONARY_DEFAULT "dictionaries/small.txt"

// Prototype
double calculate(const struct timespec *b, const struct timespec *a);

int main(int argc, char *argv[])
{
    // Parse command-line arguments
    if (argc != 2 && argc != 3)
    {
        printf("Usage: ./speller [dictionary] text\n");
        return 1;
    }
    const char *dictionary = (argc == 3) ? argv[1] : DICTIONARY_DEFAULT;
    const char *text = (argc == 3) ? argv[2] : argv[1];

    // Benchmarks
    struct timespec before, after;
    double time_load = 0.0, time_check = 0.0, time_size = 0.0, time_unload = 0.0;

    // Load dictionary
    clock_gettime(CLOCK_MONOTONIC, &before);
    bool loaded = load(dictionary);
    clock_gettime(CLOCK_MONOTONIC, &after);
    time_load = calculate(&before, &after);

    if (!loaded)
    {
        printf("Could not load %s.\n", dictionary);
        return 1;
    }

    // Open text
    FILE *file = fopen(text, "r");
    if (file == NULL)
    {
        printf("Could not open %s.\n", text);
        unload();
        return 1;
    }

    // Prepare to report misspellings
    unsigned int index = 0, misspellings = 0, words = 0;
    char word[LENGTH + 1];

    // Check each word in text, word by word
    char c;
    while (fread(&c, sizeof(char), 1, file) == 1)
    {
        // Words consist of alphabetical characters and apostrophes,
        // the latter only permitted inside a word (e.g., "don't"),
        // never as the very first character.
        if (isalpha((unsigned char) c) || (c == '\'' && index > 0))
        {
            word[index] = c;
            index++;

            // Word too long: consume the rest of it, then ignore
            if (index > LENGTH)
            {
                while (fread(&c, sizeof(char), 1, file) == 1 && isalpha((unsigned char) c));
                index = 0;
                continue;
            }
        }

        // Ignore words with numbers, e.g., "3rd" or "2024" (skip whole token)
        else if (isdigit((unsigned char) c))
        {
            while (fread(&c, sizeof(char), 1, file) == 1 && isalnum((unsigned char) c));
            index = 0;
        }

        // Word ended (whitespace, punctuation, EOF-ish boundary)
        else if (index > 0)
        {
            word[index] = '\0';
            words++;

            clock_gettime(CLOCK_MONOTONIC, &before);
            bool misspelled = !check(word);
            clock_gettime(CLOCK_MONOTONIC, &after);
            time_check += calculate(&before, &after);

            if (misspelled)
            {
                printf("%s\n", word);
                misspellings++;
            }

            index = 0;
        }
    }

    // Check whatever's left of the buffer at end of file
    if (index > 0)
    {
        word[index] = '\0';
        words++;

        clock_gettime(CLOCK_MONOTONIC, &before);
        bool misspelled = !check(word);
        clock_gettime(CLOCK_MONOTONIC, &after);
        time_check += calculate(&before, &after);

        if (misspelled)
        {
            printf("%s\n", word);
            misspellings++;
        }
    }

    fclose(file);

    // Determine dictionary's size
    clock_gettime(CLOCK_MONOTONIC, &before);
    unsigned int n = size();
    clock_gettime(CLOCK_MONOTONIC, &after);
    time_size = calculate(&before, &after);

    // Unload dictionary
    clock_gettime(CLOCK_MONOTONIC, &before);
    bool unloaded = unload();
    clock_gettime(CLOCK_MONOTONIC, &after);
    time_unload = calculate(&before, &after);

    if (!unloaded)
    {
        printf("Could not unload %s.\n", dictionary);
        return 1;
    }

    // Report benchmarks
    printf("\nWORDS MISSPELLED:     %d\n", misspellings);
    printf("WORDS IN DICTIONARY:  %d\n", n);
    printf("WORDS IN TEXT:        %d\n", words);
    printf("TIME IN load:         %.2f\n", time_load);
    printf("TIME IN check:        %.2f\n", time_check);
    printf("TIME IN size:         %.2f\n", time_size);
    printf("TIME IN unload:       %.2f\n", time_unload);
    printf("TIME IN TOTAL:        %.2f\n\n",
           time_load + time_check + time_size + time_unload);

    return 0;
}

// Returns number of seconds between b and a
double calculate(const struct timespec *b, const struct timespec *a)
{
    return (a->tv_sec - b->tv_sec) + (a->tv_nsec - b->tv_nsec) / 1000000000.0;
}

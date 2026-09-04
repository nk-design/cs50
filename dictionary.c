// Implements a dictionary's functionality as a hash table with chaining

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table.
// A prime a bit larger than expected word counts keeps chains short
// without wasting too much memory for small dictionaries.
#define N 4093

// Hash table
static node *table[N];

// Running count of words currently loaded
static unsigned int word_count = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    unsigned int index = hash(word);
    for (node *cursor = table[index]; cursor != NULL; cursor = cursor->next)
    {
        if (strcasecmp(cursor->word, word) == 0)
        {
            return true;
        }
    }
    return false;
}

// Hashes word to a number between 0 and N - 1, case-insensitively.
// This is djb2, a simple and well-distributed string hash, folded
// through toupper so that "Word" and "word" land in the same bucket.
unsigned int hash(const char *word)
{
    unsigned long h = 5381;
    for (int i = 0; word[i] != '\0'; i++)
    {
        h = h * 33 + (unsigned char) toupper((unsigned char) word[i]);
    }
    return h % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        return false;
    }

    char word[LENGTH + 1];
    while (fscanf(file, "%45s", word) == 1)
    {
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            fclose(file);
            unload();
            return false;
        }
        strcpy(n->word, word);

        unsigned int index = hash(word);
        n->next = table[index];
        table[index] = n;

        word_count++;
    }

    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return word_count;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        node *cursor = table[i];
        while (cursor != NULL)
        {
            node *next = cursor->next;
            free(cursor);
            cursor = next;
        }
        table[i] = NULL;
    }
    word_count = 0;
    return true;
}

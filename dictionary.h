// Declares the dictionary's API

#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <stdbool.h>

// Maximum length for a word
// (e.g., "pneumonoultramicroscopicsilicovolcanoconiosis")
#define LENGTH 45

// Returns true if word is in dictionary, else false
bool check(const char *word);

// Hashes word to a number
unsigned int hash(const char *word);

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary);

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void);

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void);

#endif // DICTIONARY_H

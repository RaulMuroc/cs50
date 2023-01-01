// Implements a dictionary's functionality
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in the hash table, in our  case, the #letters in the alphabet
const unsigned int N = 26;

// Hash table
// hash table : array of linked lists
node *table[N];

// declaration of variables
unsigned int counter_of_words = 0;
unsigned int value_of_hash;

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // open the dictionary file containing the words
    FILE *file = fopen(dictionary, "r");
    if (file != NULL)
    {
        char word[LENGTH + 1];
        // while there are still words to read...
        while (fscanf(file, "%s", word) != EOF)
        {
            node *cursor = malloc(sizeof(node));

            // handle situation where it was not possible to allocate memory
            if (cursor == NULL)
            {
                return false;
            }

            // copy the current word into the current navigated node
            strcpy(cursor->word, word);
            // calcula the hash value of the current navigated word of the node
            value_of_hash = hash(word);

            if (table[value_of_hash] == NULL)
            {
                cursor->next = NULL;
            }
            else
            {
                cursor->next = table[value_of_hash];
            }
            // move to the next node
            table[value_of_hash] = cursor;
            counter_of_words++;
        }
        fclose(file);
        return true;
    }
    else
    {
        // memory error, file could not be opened....
        printf("cannot open the dictionary %s\n", dictionary);
        return false;
    }
}

// Returns true if word is in dictionary, else false
// case insensitive
// 1. hash word to obtain a hash value
// 2. access linked list at that index in the hash table
// 3. traverse linked list, looking for the word (strcasecmp)
// 3.2.1 move to next node if it is not the word I want ( cursor = cursor->next; )
// 3.2.2 if @cursor == NULL then word not found
bool check(const char *word)
{
    unsigned long hash_value =  hash(word);
    node *cursor = table[hash_value];

    while (cursor != NULL)
    {
        if (strcasecmp(cursor->word, word) == 0)
        {
            return true;
        }
        cursor = cursor->next;
    }
    return false;
}

// Hashes word to a number
// hash function : assigns a number to every input
// input: word, with alphabetical characters and (possibly) apostrophes.
// output: numerical index between 0 and N - 1, inclusive
// deterministic
// larger N means more buckets
// if function ends up with a value greater than N, you can take the value % N
// to get a value in the appropiate range
unsigned int hash(const char *word)
{
    unsigned long hash_key = 0;
    for (int i = 0; i < strlen(word); i++)
    {
        hash_key += tolower(word[i]);
    }
    return hash_key % N;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
// iterating every single linked list inside the hash table and counting the nodes inside of each list
// OR
// keep track of the #words added to the dictionary so far and return that value
unsigned int size(void)
{
    return counter_of_words;
}

// Unloads dictionary from memory, returning true if successful, else false
// call free() on every allocated memory + return true when success
// 1. iterating over your hash table
// 2. going over each of those individual linked lists
// 3. calling free on all of the nodes inside of those linked lists
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        node *cursor = table[i];
        while (cursor)
        {
            node *tmp = cursor;
            cursor =  cursor->next;
            free(tmp);
        }
    }
    return true;
}


// Implements a dictionary's functionality
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;


// TODO: Choose number of buckets in hash table
const unsigned int N = 100000;
int word_count = 0;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    // Get the hash value of the word
    int index = hash(word);

    // Iterate through the linked list at the index
    for (node* cursor = table[index]; cursor != NULL; cursor = cursor->next)
    {
        // If the word is found, return true
        if (strcmp(cursor->word, word) == 0)
        {
            return true;
        }
    }

    // If the word is not found, return false
    return false;
}


// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    unsigned int hash = 0;
    for (int i = 0, n = strlen(word); i < n; i++)
        hash = (hash << 2) ^ word[i];
    return hash % N;
}



// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    // Open the dictionary file
    FILE* file = fopen(dictionary, "r");
    if (file == NULL)
    {
        return false;
    }

    // Initialize a buffer for reading words from the file
    char word[LENGTH + 1];

    // Read words from the file one by one
    while (fscanf(file, "%s", word) != EOF)
    {
        // Increase the word count
        word_count++;

        // Get the hash value of the word
        int index = hash(word);

        // Allocate memory for a new node
        node* new_node = malloc(sizeof(node));
        if (new_node == NULL)
        {
            unload();
            fclose(file);
            return false;
        }

        // Copy the word to the new node
        strcpy(new_node->word, word);

        // Insert the new node at the beginning of the linked list
        new_node->next = table[index];
        table[index] = new_node;
    }

    // Close the dictionary file
    fclose(file);

    // Return true if the dictionary is loaded successfully
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return word_count;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    // Iterate through all the elements of the hash table
    for (int i = 0; i < N; i++)
    {
        // Iterate through the linked list at the index
        for (node* cursor = table[i]; cursor != NULL; )
        {
            node *temp = cursor;
            cursor = cursor->next;
            // Free the memory of each node
            free(temp);
        }
    }
    return true;
}
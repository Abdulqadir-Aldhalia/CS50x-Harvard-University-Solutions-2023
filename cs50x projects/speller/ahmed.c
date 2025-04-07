// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include <strings.h>
#include <stdio.h>
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
const unsigned int N = 676;
unsigned int size1=0;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    int ch=hash(word);

    node*test=table[ch];
    while(test!=NULL)
    {
       if(strcasecmp(test->word,word)==0)
       {
        return true;

       }
        test=test->next;
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    int d=toupper(word[0]) - 'A';
    int x =toupper(word[1]) - 'A';

    if(d+x>N)
    return (d+x)%N;
    return d+x;

}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    FILE *ch=fopen(dictionary,"r");
    if(ch==NULL)
    {
        return false;
    }
    char word[LENGTH + 1];
    while(fscanf(ch,"%s",word)!=EOF)
    {

        node *ins=malloc(sizeof(node));

        if(ins==NULL)
        {
            fclose(ch);
            return false;
        }


        int has=hash(word);

        strcpy(ins->word,word);

        node*test=table[has];

        if(table[has]==NULL)
        {
            table[has]=ins;

        }
        else
        {
            ins->next=table[has];

            table[has]=ins;


        }
        size1++;


    }
    fclose(ch);
    return true;
}
// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return size1;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    node*tem;
    for(int i=0;i<N;i++)
    {
        while(table[i]!=NULL)
        {
            tem=table[i];
            table[i]=table[i]->next;
            free(tem);

        }
    }
    // TODO
    return true;
}
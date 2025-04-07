// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include "dictionary.h"
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 676;
int sizeOfword=0;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    int index=hash(word);
    if(table[index]==NULL)
    {
        return false;
    }

    node *p=table[index];

    while(p!=NULL)
    {
         if(strcasecmp(p->word,word)==0)
            {
                return true;
            }
                p=p->next;
        }

         return false;
    }



// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    int a=toupper(word[0])-'A';
    int b=toupper(word[1])-'A';

    if(a+b>N)
    return(a+b)%N;
    return a+b;

}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    FILE *file=fopen(dictionary,"r");

    if(file==NULL)
    {
        printf("cant open the file");
        return false;
    }

     char word[LENGTH + 1];

     while(fscanf(file,"%s",word)!=EOF)
     {
        node *n=malloc(sizeof(node));
        if(n==NULL)
        {
            fclose(file);
            return false;
        }

        int index=hash(word);
        strcpy(n->word,word);

        if(table[index]==NULL)
        {
            table[index]=n;
        }
        else
        {
            n->next=table[index];
            table[index]=n;
        }

       sizeOfword++;

     }

    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return sizeOfword;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
   for(int i=0;i<N;i++)
    {
        node*cur=table[i];
        while(cur)
        {
            node*tem=cur;
            cur=cur->next;
            free(tem);

        }
        if(cur==NULL)
        {
            return true;
        }
    }
    // TODO
    return false;


}










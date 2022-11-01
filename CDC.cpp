#include "app.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>

uint64_t hash_func(const unsigned char *input, unsigned int pos)
{
    uint64_t hash = 0;
    for (int i = 0; i < WIN_SIZE; i++)
    {
        hash += input[pos + WIN_SIZE - 1 - i] * pow(PRIME, i + 1);
    }
    if (hash == 0)
    {
        hash++;
    }
    return hash;
}

void CDC(unsigned char * Input_add,int file_length,unsigned int * chunk_add,unsigned int * chunk_len)
{   unsigned int count=0;
    unsigned int old_add=0;
    uint64_t hash = hash_func(Input_add, 0);
    for (unsigned int i = 1; i < file_length - WIN_SIZE; i++)
    {
        hash = hash * PRIME - Input_add[i - 1] * pow(PRIME, WIN_SIZE + 1) + Input_add[i - 1 + WIN_SIZE] * PRIME;
        if (((hash % MODULUS) == TARGET) && (hash > 0))
        {
        chunk_add[count]=old_add;
        chunk_len[count]=i-old_add;
        old_add=i;
        count++;
        }
        
    }
        chunk_add[count]=old_add;
        chunk_len[count]=file_length-old_add;//force to create a chunk
        count++;
        chunk_add[count]=file_length;
        chunk_len[count]=0;//end of file indicator
        return;
}

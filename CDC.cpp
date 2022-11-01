#include "app.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>

void CDC(unsigned char * Input_add,int file_length,unsigned int * chunk_add,unsigned int * chunk_len)
{   unsigned int count=0;
    unsigned char regout,regin;
    unsigned char reg[WIN_SIZE];
    unsigned int old_add=0;
    uint64_t hash = 0;
    int buffcount=0;
    int upmul = pow(PRIME, WIN_SIZE + 1);
    for(int j=0;j<WIN_SIZE;j++){
    	 reg[j] = Input_add[j];
    	 hash += reg[j] * pow(PRIME, 12 - j);
    }
    for (int i = 1; i < file_length - WIN_SIZE; i++)
    {
        if (buffcount == WIN_SIZE){
        	buffcount=0;
        }
        regout = reg[buffcount];
        regin = Input_add[i - 1 + WIN_SIZE];
        hash = hash * PRIME;
        hash = hash - regout * upmul;
        hash += regin * PRIME;
        if (((hash % MODULUS) == TARGET) && (hash > 0))
        {
        chunk_add[count]=old_add;
        chunk_len[count]=i-old_add;
        old_add=i;
        count++;
        }
        reg[buffcount] = regin;
        buffcount++;
    }
        chunk_add[count]=old_add;
        chunk_len[count]=file_length-old_add;//force to create a chunk
        count++;
        chunk_add[count]=file_length;
        chunk_len[count]=0;//end of file indicator
        printf("CDC done with %d chunks\n",count-1);
        return;
}
int main()
{
    return 0;
}
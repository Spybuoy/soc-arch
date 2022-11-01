#include <iostream>
#include "sha256.h"
#include "app.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <string.h>
using namespace std;
using std::string;
using std::cout;
using std::endl;
void SHA(unsigned char * Input_add,unsigned int * chunk_add_old,unsigned int * chunk_len_old,unsigned int * chunk_add_new,unsigned int * chunk_len_new,char* SHAar)
{	
    int i=0;
    int count=0;
    int time=1;
    for(i=0;chunk_len_old[i]!=0;i++){
        if(chunk_len_old[i]>MAXIUM_SIZE){
          for(time=1;MAXIUM_SIZE*time<(int)chunk_len_old[i];time++){
              chunk_add_new[count]=chunk_add_old[i]+(time-1)*MAXIUM_SIZE;
              chunk_len_new[count]=MAXIUM_SIZE;
              count++;
          }
          chunk_add_new[count]=chunk_add_old[i]+(time-1)*MAXIUM_SIZE;
          chunk_len_new[count]=chunk_len_old[i]-(time-1)*MAXIUM_SIZE;
          count++;
        }
        else{
            chunk_add_new[count]=chunk_add_old[i];
            chunk_len_new[count]=chunk_len_old[i];
            count++;
        }
    }
    chunk_add_new[count]=0;
    chunk_len_new[count]=0;
    for(i=0;chunk_len_new[i]!=0;i++){
    string input(reinterpret_cast<char const*>(Input_add),chunk_add_new[i],chunk_len_new[i]);
    string output1 = sha256(input);
    strcpy(SHAar+i*64,output1.c_str());
    }
    SHAar[i*64]=0;
    //Debugging port:
        for(i=0;chunk_len_new[i]!=0;i++){
            printf("This is %d chunk with add %u and len %u SHA:",i,chunk_add_new[i],chunk_len_new[i]);
    	        for(int j=0;j<64;j++){
                    printf("%c",SHAar[i*64+j]);
                    }
            printf("\n");
        }
    return;
}

#include "app.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <string.h>
#include <string.h>

int FIND_CHUNK(unsigned char * Input_add,unsigned int * chunk_add_new,unsigned int * chunk_len_new, char* SHAar,unsigned char * Output_add)
{
    unsigned char* out_buff = (unsigned char*) (malloc(
                        sizeof(unsigned char) * MAXIUM_SIZE));
        if (out_buff == NULL) {
                perror("not enough space");
                exit(EXIT_FAILURE);
        }

    //run program
    int chunk_num=0;
    int add=0;
    int loc_indicator=0;
    int out_length=0;
    int search_num=0;
    int char_num=0;
    static char new_list[CHUNK_NUMBER*64];
    static int new_list_count=0;
    for(chunk_num=0;chunk_len_new[chunk_num]!=0;chunk_num++){
        //check SHA
    	printf("reading chunk %d\n", chunk_num);
        int a=0;
        add=new_list_count+1;
        for(search_num=0;search_num < new_list_count;search_num++){

            for(char_num=0;char_num<64;char_num++){
                if(SHAar[chunk_num*64+char_num]!=new_list[search_num*64+char_num]){
                    break;
                }
            }
            if(char_num == 64){
            	add=search_num;
                break;
            }
        }
        if(add<new_list_count){
            //write deduplicate indicator
            a=(add << 1) | (1);
            for(int c=0;c<4;c++){
            	  char charin=0;
                  charin= a >> ((c)*8);
                  Output_add[loc_indicator]=charin;
                  loc_indicator++;
              }
            printf("find duplicate in chunk %d to %d with length %d\n", chunk_num,search_num,chunk_len_new[chunk_num]);
            printf("header is %d %d %d %d", Output_add[loc_indicator-4],Output_add[loc_indicator-3],Output_add[loc_indicator-2],Output_add[loc_indicator-1]);
        }
        else{
            //write LZW output
            out_length = LZW(&Input_add[chunk_add_new[chunk_num]],&out_buff[0],chunk_len_new[chunk_num]);
            a=(out_length << 1);
                        for(int c=0;c<4;c++){
                                    	  char charin=0;
                                          charin= a >> ((c)*8);
                                          Output_add[loc_indicator]=charin;
                                          loc_indicator++;
                                      }
                        printf("header is %d %d %d %d\n", Output_add[loc_indicator-4],Output_add[loc_indicator-3],Output_add[loc_indicator-2],Output_add[loc_indicator-1]);
            memcpy(&Output_add[loc_indicator], &out_buff[0], out_length);
            loc_indicator=loc_indicator+out_length;
            printf("write chunk %d with length %d,loc is %d\n", chunk_num,out_length,loc_indicator);
            memcpy(&new_list[new_list_count*64], &SHAar[chunk_num*64], 64);
            new_list_count++;
        }
    }
            free(out_buff);
            printf("Find_chunk done\n");
            return loc_indicator;
}

#include "app.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>


int main()
{
    unsigned int chunk_add_old[CHUNK_NUMBER];
    unsigned int chunk_len_old[CHUNK_NUMBER];
	unsigned int chunk_add_new[CHUNK_NUMBER];
    unsigned int chunk_len_new[CHUNK_NUMBER];

    //allocation and transferrring input file into buffer
    int final_size;
	FILE* fp = fopen("LittlePrince.txt", "r");  //filename is changed here
	if (fp == NULL) {
		perror("invalid input file");
		exit(EXIT_FAILURE);
	}
    
    fseek(fp, 0, SEEK_END); // seek to end of file
	int file_size = ftell(fp); // get current file pointer
	fseek(fp, 0, SEEK_SET); // seek back to beginning of file

	unsigned char* buff = (unsigned char*) (malloc(  
			sizeof(unsigned char) * (file_size+1024)));
	if (buff == NULL) {
		perror("not enough space");
		fclose(fp);
		exit(EXIT_FAILURE);
	}
    unsigned char* output_add = (unsigned char*) (malloc(
			sizeof(unsigned char) * file_size));
	if (output_add == NULL) {
		perror("not enough space");
		fclose(fp);
		exit(EXIT_FAILURE);
	}
    char* SHA = (char*) (malloc(  
			sizeof(char) * CHUNK_NUMBER*64));
	if (SHA == NULL) {
		perror("not enough space");
		fclose(fp);
		exit(EXIT_FAILURE);
	}
    int bytes_read = fread(&buff[0], sizeof(unsigned char), file_size, fp);
	printf("bytes_read %d\n", bytes_read);

    //run program
    CDC(&buff[0],file_size,chunk_add_old,chunk_len_old);
    SHA(&buff[0],chunk_add_old,chunk_len_old,chunk_add_new,chunk_len_new,&SHA[0]);
    final_size=FIND_CHUNK(&buff[0],chunk_add_new,chunk_len_new,&SHA[0],&output_add[0]);
    
	//output to outfile
   	FILE *outfd = fopen("output_cpu.bin", "wb");
	int bytes_written = fwrite(&output_add[0], 1, final_size, outfd);
	printf("write file with %d\n", bytes_written);
	fclose(outfd);
    fclose(fp);
    free(buff);
    free(output_add);
    free(SHA);
    return EXIT_SUCCESS;
}
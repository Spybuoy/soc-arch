//overall part
#define CHUNK_NUMBER 1024
//CDC part
#define WIN_SIZE 12
#define PRIME 3
#define MODULUS 256
#define TARGET 0
//SHA part
#define MAXIUM_SIZE 8192
//FIND_CHUNK part
#define CODE_LENGTH (13)


void CDC(unsigned char * Input_add,int file_length,unsigned int * chunk_add,unsigned int * chunk_len);
void SHA(unsigned char * Input_add,unsigned int * chunk_add_old,unsigned int * chunk_len_old,unsigned int * chunk_add_new,unsigned int * chunk_len_new,char* SHA);
int FIND_CHUNK(unsigned char * Input_add,unsigned int * chunk_add_new,unsigned int * chunk_len_new,char* SHA,unsigned char * Output_add);
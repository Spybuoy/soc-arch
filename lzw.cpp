#include <string>
#include <map>
#include <iostream>
#include <vector>
#define CODE_LENGTH (13)

int compress(std::string uncompressed, int length,unsigned char* output) {
  int dictsize = 256;
  int bitloc = 0;
  int bytelen=0;
  unsigned char writebyte=0;
  int numin=0;
  std::map<std::string,int> dictionary;
  for (int i = 0; i < 256; i++)
    dictionary[std::string(1, i)] = i;

  std::string w,k;
  w=uncompressed[0];
  for (int i=0;i<length-1;i++) {
    k=uncompressed[i+1];
    std::string wk = w + k;
    if (dictionary.count(wk)){
      w = wk;
    }
    else {
      numin=dictionary[w];
      for(int num=0;num<CODE_LENGTH;num++){
              writebyte = writebyte | ((numin >> (12 - num)) & 1);
              bitloc++;
                 if (bitloc % 8 == 0){
                    output[bytelen]=writebyte;
                    writebyte=0;
                    bytelen++;
                  }
              writebyte = writebyte << 1;
          }
      dictionary[wk] = dictsize++;
      w = k;
    }
  }
  numin=dictionary[w];
  for(int num=0;num<CODE_LENGTH;num++){
          writebyte = writebyte | ((numin >> (12 - num)) & 1);
          bitloc++;
             if (bitloc % 8 == 0){
                output[bytelen]=writebyte;
                writebyte=0;
                bytelen++;
              }
          writebyte = writebyte << 1;
      }
  if(bitloc % 8 != 0){
         writebyte = writebyte << (7-(bitloc % 8));
                 output[bytelen]=writebyte;
                 bytelen++;
     }

    return bytelen;
  }


int LZW(unsigned char * Input_add,unsigned char * Output_add,int length) {
  std::string input(reinterpret_cast<char *>(Input_add),0,length);
  int out_length=compress(input,length,Output_add);
  return out_length;
}

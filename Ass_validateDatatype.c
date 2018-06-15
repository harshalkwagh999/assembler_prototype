#include "Assembler.h"

int validate_Datatype(char *datatype,int *err_no,char *section,int *data_size)
{//printf("validea DT %s\n",datatype);                                                                  
  if(strcmp(section,".data")==0)//check if data section
    {
      if(strcmp(datatype,"db")==0)//check for data byte
        { (*data_size)=1;//set size to 1byte
          return 0; }
      else if(strcmp(datatype,"dw")==0)//check for data word
        { (*data_size)=2;//2byte
          return 0; }
      else if(strcmp(datatype,"dd")==0)//check for data double word
        { (*data_size)=4;//4bytes
          return 0; }
      else if(strcmp(datatype,"dq")==0)//check for data quad
        { (*data_size)=8;//8bytes
          return 0; }
      else if(strcmp(datatype,"dt")==0)//check for data ten
        { (*data_size)=10;//10bytes
          return 0; }
      else
        { (*err_no)=1;//if no-> set error
          return -1; }
    }
  else if(strcmp(section,".bss")==0)//check for bss section
    {
      if(strcmp(datatype,"resb")==0)//reserve byte
        { (*data_size)=1;//set size 1byte
          return 0; }
      else if(strcmp(datatype,"resw")==0)//reserve word
        { (*data_size)=2;//2bytes
          return 0; }
      else if(strcmp(datatype,"resd")==0)//reserve double word
        { (*data_size)=4;//4bytes
          return 0; }
      else if(strcmp(datatype,"resq")==0)//reserve quad word
        { (*data_size)=8; //8bytes
          return 0; }
      else if(strcmp(datatype,"rest")==0)//reserve ten 
        { (*data_size)=10;//10byets
          return 0; }
      else
        { (*err_no)=1;//if not set error 1->invalid opcode
          return -1; }
    }
}

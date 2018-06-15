#include "Assembler.h"

int hash_On_Optab(char *key)//key=mode
{
  int index=0,i=0;
  //  printf("key: %s index: %d\n",key,index);                                                          
  for(i=0;i < strlen(key); i++)
    {//   printf("hiiii  index: %d\n",index);                                                           
      index=index+key[i];//adding ASCII values of mode eg.(Rr16)
    }

  index=index%11;//hash fun.:mod by 11
  //  printf("opcode index: %d\n",index);                                                               
  return index;//return hash key
}

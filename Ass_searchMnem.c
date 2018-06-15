#include "Assembler.h"

int search_mnem(char *val,OPTAB *op_tab)
{
  int i;
  for(i=0;i<12;i++)//checking mnemonic is available in optab and return index of it
    {
      if(strcmp(op_tab[i].mnem,val)==0)
        return i;
      //printf("  %s",opt_obj[i].mnemonic); 
    }
  return -1;
}

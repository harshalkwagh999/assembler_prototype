#include "Assembler.h"

int isImmediate(char *val,LIT_T **lit_tab,int *lit_indx,int *err_no)
{
  int i;
  for(i=0;i<strlen(val);i++)
    {
      if(!(isdigit(val[i])))
        {
          (*err_no=7);
          return -1;
	}
    }
  return 0;
}

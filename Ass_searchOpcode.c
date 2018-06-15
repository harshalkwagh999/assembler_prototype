#include "Assembler.h"
int search_opcode(OPTAB *op_tab,int mnem_indx,int op_key,char *mode,int *oplen)
{
  OPCODE *temp; int cntr;
  temp=(OPCODE*)malloc(sizeof(OPCODE));//temp veriable of OPCODE type
  temp= &(op_tab[mnem_indx].opt_arr[op_key]);//assigned address of opt_arr to temp

  if((*temp).link==NULL)//checking that mnemonic is in opt_arr itself
    {
      (*oplen)=strlen((*temp).opcode);//coping length of opcode in oplen
      return 0;
    }
  else// serching in bucket
    {   cntr=0;
      while((*temp).link!=NULL)//traversing till last bucket

        {
          if(strcmp((*temp).mode,mode)==0)//compairing for mode
	    {
	      (*oplen)=strlen((*temp).opcode);//coping length of opcode in oplen
	      break;
	    }
          else
            {
	      temp=(*temp).link;//goto next
	      ++cntr;//increment counter
	    }
        }
    }
  return cntr;//return counter:it contains the possition of bucket
}

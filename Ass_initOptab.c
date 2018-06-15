#include "Assembler.h"

int optab_Initialization(OPTAB *op_tab,char **tokenarr)
{
  OPCODE *temp=NULL;//temp variable of type OPCODE
  int hash_key=-1,ch=-1;
  hash_key=hash_On_Optab(tokenarr[1]);//tokenerr[1] contains mode of instruction 

  if(strcmp("mov",tokenarr[0])==0) {  ch=0;   }//if move ch=0 and so on for next all 11 entries
  else if(strcmp("add",tokenarr[0])==0) {  ch=1;   }
  else if(strcmp("sub",tokenarr[0])==0) {  ch=2;   }
  else if(strcmp("cmp",tokenarr[0])==0) {  ch=3;   }
  else if(strcmp("and",tokenarr[0])==0) {  ch=4;   }
  else if(strcmp("or",tokenarr[0])==0 ) {  ch=5;   }
  else if(strcmp("xor",tokenarr[0])==0) {  ch=6;   }
  else if(strcmp("not",tokenarr[0])==0) {  ch=7;   }
  else if(strcmp("inc",tokenarr[0])==0) {  ch=8;   }
  else if(strcmp("dec",tokenarr[0])==0) {  ch=9;   }
  else if(strcmp("mul",tokenarr[0])==0) {  ch=10;  }
  else if(strcmp("div",tokenarr[0])==0) {  ch=11;  }
  else {return -1;}

  if(op_tab[ch].mnem == NULL)//if optab.mnen=null(first entry)then copy at same location(every ch value have seperate entry)  
    {
      op_tab[ch].mnem=(char*)malloc(sizeof(char)*strlen(tokenarr[0]));//alocate mem. for mnemonic 
      strcpy(op_tab[ch].mnem,tokenarr[0]);//store the mnem.
    }

  if(op_tab[ch].opt_arr[hash_key].opcode==NULL)//opcode field is null mins 1st entry
    {
      op_tab[ch].opt_arr[hash_key].opcode=(char*)malloc(sizeof(char)*strlen(tokenarr[2]));//alocate mem for opcode
      strcpy(op_tab[ch].opt_arr[hash_key].opcode,tokenarr[2]);//store opcode
      op_tab[ch].opt_arr[hash_key].mode=(char*)malloc(sizeof(char)*strlen(tokenarr[1]));//alocate mem for mod
      strcpy(op_tab[ch].opt_arr[hash_key].mode,tokenarr[1]);//store mode
    }
  else
    {
      temp=(&op_tab[ch].opt_arr[hash_key]);//create temp node for traversal
      OPCODE *newnode;// create new node as bucket
      newnode=(OPCODE*)malloc(sizeof(OPCODE));// alocate size for new node dynemically
      newnode->opcode=(char*)malloc(sizeof(char)*(atoi(tokenarr[2])));//alocate mem for opcode in error table
      strcpy(newnode->opcode,tokenarr[2]);//store opcode
      newnode->mode=(char*)malloc(sizeof(char)*(atoi(tokenarr[1])));////alocate mem for mode in error table
      strcpy(newnode->mode,tokenarr[1]);//store mode

      while((*temp).link !=NULL)//traverse till last bucket/node
	{
	  temp=(*temp).link;
	}
      (*temp).link=newnode;//store newnode at the end 
    }

}

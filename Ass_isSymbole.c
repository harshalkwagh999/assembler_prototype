#include "Assembler.h"

char *isSymbol(char *val,SYMB_T *symb_tab,int symtab_index,int *entry_no,int *err_no,int dst_flag,int src_flag)
{
  int i=0,data_size=0,validate_flag=0;
  char *lable;
	
  lable=(char*)malloc(sizeof(char)*16);
  //  printf("welcome........%s\n",val);
  switch(val[0])//checking for fist charector of dword ,word or byte
    {
    case 'd'://if d
      if(val[i]=='d' && val[++i]=='w' && val[++i]=='o' && val[++i]=='r' && val[++i]=='d'  && val[++i]=='[' && val[strlen(val)-1]==']')// checking for "dword["  and "]"
	{
	  lable=(char*)malloc(sizeof(char)*(strlen(val+i+1)));//alocating mem for [dvar] dvar
	  strncpy(lable,val+i+1,(strlen(val+i+1)-1));//(lable , source , size)
	  lable[strlen(val+i+1)-1]='\0';//append '\0'
	  validate_flag=1;//set validate_flag
	  data_size=4;
	}
      else
	{
	  (*err_no)=11;
	  (*entry_no)= -1;
	  return EMPTY_STR;
	}
      break;

    case 'w':if(val[i]=='w' && val[++i]=='o' && val[++i]=='r' && val[++i]=='d'  && val[++i]=='[' && val[strlen(val)-1]==']')// checking for "word["  and "]"
	{
	  lable=(char*)malloc(sizeof(char)*(strlen(val+i+1)));
	  strncpy(lable,val+i+1,(strlen(val+i+1)-1));
	  lable[strlen(val+i+1)-1]='\0';
	  data_size=2;
	  validate_flag=1;
	}
      else
	{
	  (*err_no)=11;
	  (*entry_no)= -1;
	  return EMPTY_STR;
	}
      break;

    case 'b':if(val[i]=='b' && val[++i]=='y' && val[++i]=='t' && val[++i]=='e' && val[++i]=='[' && val[strlen(val)-1]==']')//// checking for "byte["  and "]"
	{
	  lable=(char*)malloc(sizeof(char)*strlen(val+i+1));
	  strncpy(lable,val+i+1,(strlen(val+i+1)-1));
	  lable[strlen(val+i+1)-1]='\0';
	  data_size=1;
	  validate_flag=1;
	}
      else
	{
	  (*err_no)=11;
	  (*entry_no)= -1;
	  return EMPTY_STR;
	} 
      break;      
    }

  if(validate_flag!=1)//if validate_flag is not set
    {
      (*err_no)=11;
      (*entry_no)= -1;
      return EMPTY_STR;      
    }

  for(i=0;i<symtab_index;i++)
    {
      if(strcmp(symb_tab[i].name,lable)==0)//comparing with symbol names in symbol table
	{
	  // printf("lable_type: %d\n",strcmp(symb_tab[i].section,".data"));
	  if(strcmp(symb_tab[i].section,".data")!=0 && strcmp(symb_tab[i].section,".bss")!=0)//if not .data and .bss section
	    { 
	      (*err_no)=11;
	      (*entry_no)= -1;
	      return EMPTY_STR;
	    }
	  else if(symb_tab[i].type!= data_size)//if type is not matching with data size
	    {
	      (*err_no)=10;
	      (*entry_no)= -1;
	      return EMPTY_STR;
	    }
	  if(strcmp(symb_tab[i].section,".bss")==0 && dst_flag==1)//if not .bss section and at destination possition
	    { // if this variable is at destination position then make it defined
	      symb_tab[i].flag=1;
	    }
	  else if(src_flag==1 && symb_tab[i].flag==0)
	    {
	      // printf("Label: %s, src_flag: %d, symb_tab[i].flag: %d \n",lable,src_flag,symb_tab[i].flag);
	      (*err_no)=8;
	      (*entry_no)= -1;
	      // printf("err_no: %d, entry_no: %d \n",(*err_no),(*entry_no));
	      return EMPTY_STR;
	    }

	  (*entry_no)=i;
	  // printf("%c",val[0]);
	  switch(val[0])
	    {
	    case 'b':return "m8";

	    case 'w':return "m16";

	    case 'd':return "m32";
	    }
	}      
    }
  (*err_no)=7;
  (*entry_no)=-1;
  return EMPTY_STR;
}

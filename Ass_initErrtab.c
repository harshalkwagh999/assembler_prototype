#include "Assembler.h"

int errtab_Initialisation(ERROR_T *err_tab,char **tokenarr,int tokencnt)
{
  int no,i,j,size=1;
  char *tmp_str;// temp string 
  no=atoi(tokenarr[0]);//convert tokenerr[0] to int and store in no
  for(i=1;i<tokencnt;i++)// loop starts from tokenerr[1]
    {
      size = size + (strlen(tokenarr[i])+1);//1 for space
    }
  err_tab[no].err_type=(char*)malloc(sizeof(char)*size);//aloacte size for errortype
  err_tab[no].err_code=no;// store error code 
  for(i=1;i<tokencnt;i++)
    {
      tmp_str=(char*)malloc(sizeof(char)*(strlen(tokenarr[i])+1));//alocate mem for temp string 
      strcpy(tmp_str,tokenarr[i]);// copy each token in temp string 
      strcat(tmp_str," ");//copy space after each token in temp string
      strcat(err_tab[no].err_type,tmp_str);//copy tmp_str to err_type
    }//end of for loop
} 

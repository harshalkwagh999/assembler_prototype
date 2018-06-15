#include "Assembler.h"

int tyni_tokenize(char *buffer,char ***tyni_tokenarr,int *tyni_tokencnt)
{
  int i,row=0,column=0,flag=0;
  (*tyni_tokencnt)=0;
  (*tyni_tokenarr)=(char**)malloc(sizeof(char*)*(row+1));
  (*tyni_tokenarr)[row]=(char*)malloc(sizeof(char)*(column+1));

  for(i=0;buffer[i]!='\0';i++)
    {
      /* if(buffer[i]=='\t') */
      /* 	{   if(flag==0){continue;}     } */
      /* if(buffer[i]=='"') */
      /* 	{flag=1; */
      /* 	  do */
      /* 	    { */
      /* 	      (*tyni_tokenarr)[row][column]=buffer[i]; */
      /* 	      column++; i++; */
      /* 	      (*tyni_tokenarr)[row]=(char*)realloc((*tyni_tokenarr)[row],sizeof(char)*(column+1)); */
      /* 	    }while(buffer[i]!='"'); */
      /* 	  (*tyni_tokenarr)[row][column]=buffer[i]; */
      /* 	  column++; */
      /* 	  (*tyni_tokenarr)[row]=(char*)realloc((*tyni_tokenarr)[row],sizeof(char)*(column+1)); */
      /* 	  (*tyni_tokenarr)[row][column]='\0'; */
      /* 	  i++; */

      /* 	} */

      /* if(buffer[i]==';') */
      /* 	{  break;  } */
      if(buffer[i] !='#')
	{//flag=1;
	  //  printf("hiiiiiiiii: %c\n",buffer[i]);
	  (*tyni_tokenarr)[row][column]=buffer[i];
	  column++;
	  (*tyni_tokenarr)[row]=(char*)realloc((*tyni_tokenarr)[row],sizeof(char)*(column+1));
	}
      else
	{
	  (*tyni_tokenarr)[row][column]='\0';
	  column=0;
	  row++;
	  (*tyni_tokencnt)++;
	  (*tyni_tokenarr)=(char**)realloc((*tyni_tokenarr),sizeof(char*)*(row+1));
	  (*tyni_tokenarr)[row]=(char*)malloc(sizeof(char));
	}
    }
  (*tyni_tokenarr)[row][column]='\0';
  (*tyni_tokencnt)++;
}

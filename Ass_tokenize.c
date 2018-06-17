#include "Assembler.h"

int tokenize(char *buffer,char ***tokenarr,int *tokencnt)
{
	int i,row=0,column=0,flag=0;
	(*tokencnt)=0;//initialize token count to 0
	(*tokenarr)=(char**)malloc(sizeof(char*)*(row+1));//alocate size for tokenerr single row
	(*tokenarr)[row]=(char*)malloc(sizeof(char)*(column+1));//alocating size for one colm

	for(i=0;buffer[i]!='\n';i++)//loop till end of line
	{
		if(buffer[i]=='\t')//if tab then continoue 
		{   if(flag==0){continue;}     }
		if(buffer[i]=='"')//if it is string '"':staring of string
		{flag=1;
			do
			{
				(*tokenarr)[row][column]=buffer[i];//copy form buffer to tokenerr
				column++; i++;//increment counter
				(*tokenarr)[row]=(char*)realloc((*tokenarr)[row],sizeof(char)*(column+1));
			}while(buffer[i]!='"');//till end of string
			(*tokenarr)[row][column]=buffer[i];//storing '"' from the end of string 
			column++;//increment colm count
			(*tokenarr)[row]=(char*)realloc((*tokenarr)[row],sizeof(char)*(column+1));
			(*tokenarr)[row][column]='\0';//append null charector to the end of string
			i++;

		}

		if(buffer[i]==';')//break if comment
		{  break;  }
		else if(buffer[i] !=' ' && buffer[i] !=',' && buffer[i] !='\t')//if not any :read
		{flag=1;
			//  printf("hiiiiiiiii: %c\n",buffer[i]);
			(*tokenarr)[row][column]=buffer[i];
			column++;
			(*tokenarr)[row]=(char*)realloc((*tokenarr)[row],sizeof(char)*(column+1));
		}
		else//if , or space or tab 
		{
			(*tokenarr)[row][column]='\0';//append null charector to the end of line
			column=0;//colm veriable set to initial possition 
			row++;//incremented row counter by 1
			(*tokencnt)++;// increment row count by 1
			(*tokenarr)=(char**)realloc((*tokenarr),sizeof(char*)*(row+1));//realocate size for new row of tokenerr
			(*tokenarr)[row]=(char*)malloc(sizeof(char));//
		}
	}//end of for loop 
	(*tokenarr)[row][column]='\0';//if end of line append null charector to tokenerr[]
	(*tokencnt)++;//increment tokencount 
}

#include "Assembler.h"

int validate_Data(char **data,int data_size,int *err_no,char *section,int tokencnt)
{
	int i,j,flag=0;
	int MAX=(data_size*8);
	//printf("strcmp1: %d\n",strcmp(section,".data"));
	if(strcmp(section,".data")==0)//check for data section 
	{
		if(data_size==1)//if data size is 1(char)
		{
			if((data[2][0]=='"' && data[2][strlen(data[2])-1]=='"') || (data[2][0]=='\'' && data[2][strlen(data[2])-1]=='\''))//check for " and ' for a charector
				return 0;
			else
			{
				for(i=0;i<strlen(data[2]);i++)
				{
					if(isdigit(data[2][i]))   // if digit   ==> non-zero
					{   flag =1;   }        
					else
					{  flag=0;              // if not a digit    ==> zero
						break;    }
				}
				if(flag==1)
				{  (*err_no)=11;
					return -1;	}
				else
				{  (*err_no)=7;
					return -1;   }	  
			}
		}
		else
		{ // All Number types
			flag=0;
			for(i=2;i<tokencnt;i++)
			{
				for(j=0;j < strlen(data[i]);j++)
				{
					//		  printf("isdigit%d\n",isdigit(data[i][j]));
					if(isdigit(data[i][j]))
					{   flag=1;    }
					else
					{  flag=0;
						break;    }
				}
				if(flag==0)
				{  (*err_no)=7;
					return -1;	}
				else if(atoi(data[i]) >= pow(2,MAX))
				{//printf("data_: %d,datasize: %d,power: %d\n",atoi(data[i]),data_size,(int)pow(2,MAX)); printf("MAX: %d, expl: %f\n",MAX,pow(2,MAX));
					(*err_no)=6;
					return -1;
				}
			}
			if(flag==1)
			{  return 0;    }

		}
	}
	else if(strcmp(section,".bss")==0)
	{
		for(i=0;i< strlen(data[2])-1;i++)
		{
			if(isdigit(data[2][i]))
			{  flag=1;     }
			else
			{
				(*err_no)=7;
				return -1;
			}
		}
		if(flag==1)
		{   return 0;     }
	}
}

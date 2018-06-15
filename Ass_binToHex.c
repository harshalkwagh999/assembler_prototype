#include "Assembler.h"

char* bin_hex(char* oprnd)
{
  char *str1,*str2,*string,tmp[5];
  int val1,val2,i,len,result=0;

  str1=(char*)malloc(sizeof(char)*5);//alocate mem for str1
  str2=(char*)malloc(sizeof(char)*5);//alocate mem for str2
  strncpy(str1,oprnd,4);//copy first 4 bits(char)
  strncpy(str2,oprnd+4,4);//copy next 4 bits(char)
  val1=0; val2=0;

  len=strlen(str1);
  result=atoi(str1);//convert to digit(integer)
  for(i=0;i<len;i++)//logic for bin to hex conversion
    {
      val1 +=((result%10)*pow(2,i));
      result=result/10;
    }

  len=strlen(str2);
  result=atoi(str2);//convert to digit(integer)
  for(i=0;i<len;i++)//logic for bin to hex conversion
    {
      val2 +=((result%10)*pow(2,i));
      result=result/10;
    }

  sprintf(str1,"%X",val1);//convert val1 to hex formate and store in str1
  sprintf(str2,"%X",val2);//convert val2 to hex formate and store in str2
  string=(char*)malloc(sizeof(char)*10);//alocate mem for string
  strcpy(string,(char*)str1);//copy str1
  strcat(string,(char*)str2);//copy str2
  return string;//return
}

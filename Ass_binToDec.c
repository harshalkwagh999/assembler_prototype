#include "Assembler.h"

int bin_dec(char* oprnd)
{
  int val1,i,len,result=0;
  val1=0;
  len=strlen(oprnd);
  result=atoi(oprnd);
  for(i=0;i<len;i++)
    {
      val1 +=((result%10)*pow(2,i));
      result=result/10;
    }
  return val1;
}

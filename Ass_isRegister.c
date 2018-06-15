#include "Assembler.h"

char* isRegister(char *val,int *entry_no)
{
  int i;
  char *str="aal aax aeax bcl bcx becx cdl cdx cedx dbl dbx debx esi eesi eah fdi fedi fch gsp gesp gdh hbp hebp hbh",*ptr,*val1;
val1=(char *)malloc(strlen(val)*sizeof(char));
strcpy(val1,val);
strcat(val1," ");
ptr=strstr(str,val1);//points to the first matching charector in string
if(ptr==NULL)//if no cherctor matched 
  (*entry_no)=(-1);
 else
   {
     ptr--;//pointer goes back 1 possition ie. at->a,c,d,b
     //      printf("val1= %s",val1);                                                                  
     (*entry_no)=(int)((*ptr)-'a');//ascii difference between value pointed by pointer and a ie.0,1,2,3
     if(val[0]=='e')//if at starts with e
       return "r32";
     else if(val[strlen(val)-1]=='x')//if end with x
       return "r16";
     else
       return "r8";
   }
}

#include "Assembler.h"

int validate_lable(char *lable,SYMB_T *symb_tab,int symtab_index,int *err_no)
{
  int i,j;
  if(isalpha(lable[0]) || lable[0]=='_')//check for alphabate and underscore at begining of lable
    {
      for(i=1;i< strlen(lable);i++)//check for 0-9,A-Z,a-z 
        {
          if(!(48<=lable[i]<=57 || 65<= lable[i]<= 90 || 97<= lable[i]<= 122 || lable[i]=='_'))
            {
              (*err_no)=13;//if above charectores are not matched then->13 Invalid lable name
              return -1;
            }
        }
      for(j=0;j<symtab_index;j++)//traverse through the symbol table using index
        {
          //  printf("Lable: %s\n",symb_tab[j].name);                                                   
          if(symb_tab != NULL && strcmp(lable,symb_tab[j].name)==0) //check if symbol table is null or lable is already present
            {  // symb_tab is not created and lable already exist in symb_tab
              (*err_no)=9;//9->Symbole is redefined

              return -1;
            }  
        }

      return 0;

    }
  else
    { // lable does not start with 'character' or '_' 
      (*err_no)=13;
      return -1;
    }
}

#include "Assembler.h"

int populate_symtab(SYMB_T **symb_tab,char *symbol_name,void *value,char *section,int data_type,int size,int *symtab_index, int flag,int line)
{

  (*symb_tab)=(SYMB_T*)realloc((*symb_tab),((*symtab_index)+1)*sizeof(SYMB_T));
  (*symb_tab)[*(symtab_index)].name=(char *)malloc((strlen(symbol_name))*sizeof(char));
  strcpy((*symb_tab)[(*symtab_index)].name,symbol_name);

  (*symb_tab)[(*symtab_index)].type=data_type;
  if(value!=NULL)
    (*symb_tab)[(*symtab_index)].value=(void *)malloc((size/data_type + 1)*data_type);
  
  (*symb_tab)[(*symtab_index)].value=value;
  (*symb_tab)[(*symtab_index)].section=(char *)malloc((strlen(section)+2)*sizeof(char));
  strcpy((*symb_tab)[(*symtab_index)].section,section);
  (*symb_tab)[(*symtab_index)].size=size;
  (*symb_tab)[(*symtab_index)].flag=flag;
  (*symb_tab)[(*symtab_index)].line=line;
  (*symtab_index)++;
  printf("%s Inserted in Symbtab\n",symbol_name);
  return 0;
}

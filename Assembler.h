#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "Ass_struct.c"

#define EMPTY_STR ""
char *isSymbol(char *val,SYMB_T *symb_tab,int symtab_index,int *entry_no,int *err_no,int dst_flag,int src_flag);
char* isRegister(char *val,int *entry_no);
int throw_err(int err_no,int line_no,ERROR_T *err_tab);
int validate_lable(char *lable,SYMB_T *symb_tab,int symtab_index,int *err_no);
int validate_Datatype(char *datatype,int *err_no,char *section,int *data_size);
int validate_Data(char **data,int data_size,int *err_no,char *section,int tokencnt);
int search_mnem(char *val,OPTAB *op_tab);
int search_opcode(OPTAB *op_tab,int mnem_indx,int op_key,char *mode,int *oplen);
int populate_symtab(SYMB_T **symb_tab,char *symbol_name,void *value,char *section,int data_type,int size,int *symtab_index, int flag,int line);
int isImmediate(char *val,LIT_T **lit_tab,int *lit_indx,int *err_no);
int tokenize(char *buffer,char ***tokenarr,int *tokencnt);
int tyni_tokenize(char *buffer,char ***tyni_tokenarr,int *tyni_tokencnt);
int optab_Initialization(OPTAB *op_tab,char **tokenarr);
int hash_On_Optab(char *key);
int errtab_Initialisation(ERROR_T *err_tab,char **tokenarr,int tokencnt);
char* bin_hex(char* oprnd);
int bin_dec(char* oprnd);

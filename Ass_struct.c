typedef struct opcode
{
  char *opcode,*mode;
  struct opcode *link;
}OPCODE;

typedef struct optab
{
  char *mnem;
  OPCODE *opt_arr;
}OPTAB;

typedef struct error_t
{
  int err_code;
  char *err_type;
}ERROR_T;

typedef struct reg_t
{
  char *RR_RI;
  char *RM_MR;
}REG_T;

typedef struct symb_t
{
  char *name;
  int type;
  char *section;
  void *value;
  int size;
  int flag;
  int line;
}SYMB_T;

typedef struct lit_t
{
  int value;
}LIT_T;

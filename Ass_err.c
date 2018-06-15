#include "Assembler.h"

int throw_err(int err_no,int line_no,ERROR_T *err_tab)
{
  printf("line %d: error: %s\n",line_no,err_tab[err_no].err_type);
}

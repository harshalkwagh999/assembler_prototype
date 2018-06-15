#include "Assembler.h"

int main(int argc,char **argv)
{  
  FILE *fp,*inputf,*interf,*outputf;
  OPTAB *op_tab;
  OPCODE *obj; obj=(OPCODE*)malloc(sizeof(OPCODE));
  ERROR_T *err_tab;
  REG_T *reg_tab;
  SYMB_T *symb_tab=NULL;
  LIT_T *lit_tab;  lit_tab=(LIT_T*)malloc(sizeof(LIT_T));

  char *buffer,**tokenarr=NULL,*lable,*mode,*mode1,*mode2,*str,*str2,*ipfile,*opfile,**tyni_tokenarr=NULL,*oprtr,**tmp1,*oprnd;
  str=(char*)malloc(sizeof(char)*5); str2=(char*)malloc(sizeof(char)*5);
  int tokencnt=0,key,i,j,n=1,sec_flag,line_no,symtab_index=0,ret,err_no=(-1),data_size,total_size,*tmp_arr=NULL,mnem_indx,cntr,entry_no,pos,entry_no2,lit_indx=0,oplen=0,tyni_tokencnt=0,temp=0,r_no=0;

  // OPTAB INITIALIZATION
  fp=fopen("optab.txt","r");//open optab.txt in read mode
  op_tab=(OPTAB *)malloc(12*sizeof(OPTAB));//alocating mem for optab
  for(i=0;i<12;i++)//handling 12 instructions
    {
        op_tab[i].mnem=NULL;//mnemonic is initialize to null
        op_tab[i].opt_arr=(OPCODE *)malloc(15*sizeof(OPCODE));//alocated mem for opcode array
        for(j=0;j<15;j++)
	{
	  op_tab[i].opt_arr[j].opcode=NULL;//initialized to null
	  op_tab[i].opt_arr[j].mode=NULL;//initialized to null
	  op_tab[i].opt_arr[j].link=NULL;//initialized to null
	}
    }
  buffer=(char*)malloc(sizeof(char));// allocated mem for single char
  while((getline(&buffer,(size_t*)&n,fp))!=(-1))//reading optab.txt line by line
    {
      tokenize(buffer,&tokenarr,&tokencnt);//called to tokenizer to create tokens
      
      optab_Initialization(op_tab,tokenarr);//called to optab initialization
	
      for(i=0;i<tokencnt;i++)//free the tokenerr
        {
          free(tokenarr[i]);
        }
      free(tokenarr);      
  }
  fclose(fp);//close file pointer

  /* for(i=0;i<12;i++) */
  /*   { */
  /*     printf("Mnem: %s\n",op_tab[i].mnem); */
  /*     for(j=0;j<15;j++) */
  /* 	{ */
  /* 	  printf("opcode: %s\n",op_tab[i].opt_arr[j].opcode); */
  /* 	} */
  /*   } */

  // ERROR TABLE INITIALIZATION
  fp=fopen("errortable.txt","r");
  err_tab=(ERROR_T *)malloc(15*sizeof(ERROR_T));// alloacating mem for error table
  n=1;
  buffer=(char*)malloc(sizeof(char));
  while((getline(&buffer,(size_t*)&n,fp))!=(-1))
    {
      tokenize(buffer,&tokenarr,&tokencnt);
      errtab_Initialisation(err_tab,tokenarr,tokencnt);

      for(i=0;i<tokencnt;i++)
        {
          free(tokenarr[i]);
        }
      free(tokenarr);
    }
  fclose(fp);
  
  /* for(i=0;i<13;i++) */
  /*   { */
  /*     printf("ErrorNo: %d   Error: %s\n",err_tab[i].err_code,err_tab[i].err_type); */
  /*   } */

  // REG TABLE INITIIALIZATION
  fp=fopen("regtab.txt","r");
  reg_tab=(REG_T *)malloc(10*sizeof(REG_T));// allocating mem for reg table 10 entries(more for future use)
  n=1; j=0;
  buffer=(char*)malloc(sizeof(char));
  while((getline(&buffer,(size_t*)&n,fp))!=(-1))
    {
      tokenize(buffer,&tokenarr,&tokencnt);
      reg_tab[j].RR_RI=(char*)malloc(sizeof(char)*strlen(tokenarr[0]));// allocating mem for RR_RI mode
      strcpy(reg_tab[j].RR_RI,tokenarr[0]);// storing into RR_RM from tokenerr[0]

      reg_tab[j].RM_MR=(char*)malloc(sizeof(char)*strlen(tokenarr[1]));// allocating mem for RM_MR mode
      strcpy(reg_tab[j].RM_MR,tokenarr[1]);////storing into RR_RM from tokenerr[1]
      j++;//increamenting pointer to next entry 

      for(i=0;i<tokencnt;i++)//free tokenarr
        {
          free(tokenarr[i]);
        }
      free(tokenarr);
    }
  fclose(fp);

  ipfile=(char*)malloc(sizeof(argv[1]));
  strcpy(ipfile,argv[1]);

  inputf=fopen(ipfile,"r");
  interf=fopen("intermediate.txt","w");
  n=1;line_no=0;
  while(getline(&buffer,(size_t*)&n,inputf)!=(-1))
    {
      printf("\n%s\n",buffer);
      line_no++;
      if(strcmp(buffer,"section .data\n")==0)
	{
	  sec_flag=0;
	  continue;
	}
      if(strcmp(buffer,"section .bss\n")==0)
	{
	  sec_flag=1;
	  continue;
	}
      if(strcmp(buffer,"section .text\n")==0)
	{
	  sec_flag=2;
	  continue;
	}

      tokenize(buffer,&tokenarr,&tokencnt);

      switch(sec_flag)
	{
	case 0:  // data section
	  if(tokencnt<3)
	    { throw_err(7,line_no,err_tab);   exit(0);     }
	  else
	    { 
	      ret=validate_lable(tokenarr[0],symb_tab,symtab_index,&err_no);
	      if(ret==(-1))
		{
		  throw_err(err_no,line_no,err_tab);
		  exit(0);
		}
	      else
		{
		  ret=validate_Datatype(tokenarr[1],&err_no,".data",&data_size);
		  if(ret==(-1))
		    {
		      throw_err(err_no,line_no,err_tab);
		      exit(0);
		    }
		  else
		    {
		      ret=validate_Data(tokenarr,data_size,&err_no,".data",tokencnt);
		      if(ret==(-1)) // Data validation Fail
			{
			  throw_err(err_no,line_no,err_tab);
			  exit(0);
			}
		      else         // Data validate
			{total_size=0;
			  if(data_size==1)    // byte type data
			    {
			      total_size=strlen(tokenarr[2]);
			      populate_symtab(&symb_tab,tokenarr[0],(void*)tokenarr[2],".data",data_size,total_size,&symtab_index,1,line_no);//1 is initialization flag
			    }
			  else 
			    {
			      if(tokencnt-2 == 1)   // single Number
				{
				  total_size=data_size;
				  populate_symtab(&symb_tab,tokenarr[0],(void*)atoi(tokenarr[2]),".data",data_size,total_size,&symtab_index,1,line_no);
				}
			      else    // Number array
				{
				  for(i=2;i<tokencnt;i++)
				    { 
				      tmp_arr=(int*)realloc(tmp_arr,sizeof(int)*(i-1)); // because i=2 so i-1=1 
				      tmp_arr[i-2]=atoi(tokenarr[i]);
				      total_size += data_size;				     
				    }
				  populate_symtab(&symb_tab,tokenarr[0],(void*)tmp_arr,".data",data_size,total_size,&symtab_index,1,line_no);
				}
			    }
			}
		    }
		}
	    }
	  break;
	case 1:   // bss section
	  if(tokencnt!=3)
	    { throw_err(7,line_no,err_tab);   exit(0);     }
	  else
	    {
	      ret=validate_lable(tokenarr[0],symb_tab,symtab_index,&err_no);
	      if(ret==(-1))
		{
		  throw_err(err_no,line_no,err_tab);
		  exit(0);
		}
	      else
		{
		  ret=validate_Datatype(tokenarr[1],&err_no,".bss",&data_size);
		  if(ret==(-1))
		    {
		      throw_err(err_no,line_no,err_tab);
		      exit(0);
		    }
		  else
		    {
		      ret=validate_Data(tokenarr,data_size,&err_no,".bss",tokencnt);
		      if(ret==(-1))
			{
			  throw_err(err_no,line_no,err_tab);
			  exit(0);
			}
		      else
			{
			  total_size= data_size*atoi(tokenarr[2]);
			  populate_symtab(&symb_tab,tokenarr[0],NULL,".bss",data_size,total_size,&symtab_index,0,line_no);
			}
		    }
		}
	    }
	  break;
	case 2:  // text section
	  if((strcmp(tokenarr[0],"global")==0 && strcmp(tokenarr[1],"main")==0) || strcmp(tokenarr[0],"extern")==0)
	    {
	      continue;    // control goes to next line
	    }
	  switch(tokencnt)
	    {
	    case 1:   // only label
	      if(tokenarr[0][strlen(tokenarr[0])-1]==':')//if last charector is :
		{
		  lable=(char*)malloc(sizeof(char)*(strlen(tokenarr[0])));//alocating size for lable
		  strncpy(lable,tokenarr[0],(strlen(tokenarr[0])-1));//copy lable
		  lable[strlen(tokenarr[0])-1]='\0';
		  ret=validate_lable(lable,symb_tab,symtab_index,&err_no);//call to validate lable
		  if(ret==(-1))
		    {
		      throw_err(err_no,line_no,err_tab);
		      exit(0);
		    }
		  populate_symtab(&symb_tab,lable,NULL,".text",0,0,&symtab_index,1,line_no);
		}
	      else//if not :
		{
		  throw_err(3,line_no,err_tab);
		  exit(0);
		}
	      break;
	    case 2: // Unary instructions
	      if(isdigit(tokenarr[1][0]))//unary instruction does not allow immediate value itself
		{
		  throw_err(7,line_no,err_tab);
		  exit(0);
		}
	      mnem_indx=search_mnem(tokenarr[0],op_tab);//to check the index of mnemonic 
	      //printf("mnemonic: %d\n",mnem_indx);
	      if(mnem_indx==(-1))//not present in optab
		{
		  throw_err(1,line_no,err_tab);
		  exit(0);
		}
	      if(0 <= mnem_indx && mnem_indx <= 6)//if binary instruction
		{
		  throw_err(7,line_no,err_tab);
		  exit(0);
		}
	      if(7 <= mnem_indx && mnem_indx <= 11)//if unary instruction
		{
		  mode1=(char*)malloc(sizeof(char)*5);//min required 3 but extended to 5
		  mode1=isRegister(tokenarr[1],&entry_no);//checking for register
		  if(entry_no==(-1))//if not register check in symbol table
		    {
		      mode1=isSymbol(tokenarr[1],symb_tab,symtab_index,&entry_no,&err_no,0,1);
		      if(entry_no==(-1))//if isSymbol fail
		      	{
		      	  throw_err(err_no,line_no,err_tab);
		      	  exit(0);
		      	}
		      else//isSymbol success
			{   strcpy(str,"ST");   }
		    }
		  else
		    {  strcpy(str,"RT");  }
		  
		  key=hash_On_Optab(mode1);//call to hash_On_Optab
		  pos=search_opcode(op_tab,mnem_indx,key,mode1,&oplen);

		  if(strcmp(str,"RT") == 0)//if register table
		    { 
		      fprintf(interf,"%d#%d#%d %s#%d#%d\n",mnem_indx,key,pos,str,entry_no,0);//wrint to intermidiate file
		    }
		  else//if in symbole table
		    {
		      fprintf(interf,"%d#%d#%d %s#%d\n",mnem_indx,key,pos,str,entry_no);//write to intermidiate file
		    }
		}
	      break;
	    case 3: // Unary instruction with lable OR Binary instruction
	      if(tokenarr[0][strlen(tokenarr[0])-1]==':')//checking for token and :
		{ 
		  lable=(char*)malloc(sizeof(char)*strlen(tokenarr[0]));//allocate mem for token 
		  strncpy(lable,tokenarr[0],(strlen(tokenarr[0])-1));//coping lable excepting :
		  lable[strlen(tokenarr[0])-1]='\0';//append '\0'
		  ret=validate_lable(lable,symb_tab,symtab_index,&err_no);		  
		  if(ret==(-1))
		    {
		      throw_err(err_no,line_no,err_tab);
		      exit(0);
		    }
		  populate_symtab(&symb_tab,lable,NULL,".text",0,0,&symtab_index,1,line_no);
		  if(isdigit(tokenarr[2][0]))//if digit error**
		    {
		      throw_err(7,line_no,err_tab);
		      exit(0);
		    }
		  mnem_indx=search_mnem(tokenarr[1],op_tab);
		  // printf("mnemonic: %d\n",mnem_indx);
		  if(mnem_indx==(-1))
		    {
		      throw_err(1,line_no,err_tab);
		      exit(0);
		    }
		  if(0 <= mnem_indx && mnem_indx <= 6)// binary instruction
		    {
		      throw_err(7,line_no,err_tab);
		      exit(0);
		    }
		  if(7 <= mnem_indx && mnem_indx <= 11)// unary instruction
		    { mode1=(char*)malloc(sizeof(char)*5);
		      mode1=isRegister(tokenarr[2],&entry_no);//check for register
		      if(entry_no==(-1))//not register
			{
			  mode1=isSymbol(tokenarr[2],symb_tab,symtab_index,&entry_no,&err_no,0,1);//check for symbol
			  if(entry_no==(-1))
			    {
			      throw_err(err_no,line_no,err_tab);
			      exit(0);
			    }
			  else
			    {   strcpy(str,"ST");//if symbol copy "ST" to str
			    }
			} 
		      else
			{  strcpy(str,"RT");  }//if register copy "RT" to str
		      
		      key=hash_On_Optab(mode1);//call to hash_On_Optab to get location of opcode 		      
		      pos=search_opcode(op_tab,mnem_indx,key,mode1,&oplen);//call search_opcode to get bucket address

		      if(strcmp(str,"RT") == 0)
			{//if str="RT"
			  fprintf(interf,"%d#%d#%d %s#%d#%d\n",mnem_indx,key,pos,str,entry_no,1);
			}
		      else
			{//str="ST"
			  fprintf(interf,"%d#%d#%d %s#%d\n",mnem_indx,key,pos,str,entry_no);
			}
		    }
		}
	      else//Binary instruction
		{
		  mnem_indx=search_mnem(tokenarr[0],op_tab);//search for mnemonic
		  //printf("mnemonic: %d\n",mnem_indx);
		  if(mnem_indx==(-1))//if not found error
		    {
		      throw_err(1,line_no,err_tab);
		      exit(0);
		    }
		  if(0 <= mnem_indx && mnem_indx <= 6)//check for binary instruction 
		    { 
                      mode1=(char*)malloc(sizeof(char)*5);//alocate mem for mode1
		      mode1=isRegister(tokenarr[1],&entry_no);//check for register
		      if(entry_no==(-1))//not register
			{
			  mode1=isSymbol(tokenarr[1],symb_tab,symtab_index,&entry_no,&err_no,1,0);//check for symbol
			  if(entry_no==(-1))//not symbol error
			    {
			      throw_err(err_no,line_no,err_tab);
			      exit(0);
			    }
			  else
			    {   strcpy(str,"ST");   }//symbol	  
			}
		      else
			{  strcpy(str,"RT");  }//register
		    }
		  if(7 <= mnem_indx && mnem_indx <= 11)//check for unary instruction if yes error
		    {
		      throw_err(7,line_no,err_tab);
		      exit(0);
		    }
		  mode2=(char*)malloc(sizeof(char)*5);//allocate mem for mode2
		  mode2=isRegister(tokenarr[2],&entry_no2);//check mode if register
	
		  if(entry_no2==(-1))
		    {
		      mode2=isSymbol(tokenarr[2],symb_tab,symtab_index,&entry_no2,&err_no,0,1);//check for symbol
		      //printf("IN MAIN  err_no: %d, entry_no: %d \n",err_no,entry_no2);
		      
		      if(entry_no2==(-1))
			{
			  if(err_no==8)
			    {
			      throw_err(err_no,line_no,err_tab);
			      exit(0);			      
			    }
			  ret=isImmediate(tokenarr[2],&lit_tab,&lit_indx,&err_no);//check for immediate value

			  if(ret==(-1))//if not immediate:error
			    {
			      throw_err(err_no,line_no,err_tab);
			      exit(0);
			    }
			  else//immediate value
			    {
			      lit_tab=(LIT_T*)realloc(lit_tab,sizeof(LIT_T)*(lit_indx+1));//reallocate mem for lit_tab by 1 more loaction
			      lit_tab[lit_indx++].value=atoi(tokenarr[2]);//convert to integer and assign to lit_tab.value
			      strcpy(mode2,mode1);//copy mode1 to mode2 Bcos mode1 and mode2 must be same size:eg-mode1=r32
			      mode2[0]='i';//replace 1st charector of mode2 by "i":eg-now mode2=i32 
			      strcpy(str2,"LT");//str2="LT"
			    }
			}
		      else
			strcpy(str2,"ST");//or str="ST"
		    }
		  else
		    strcpy(str2,"RT");//or str="RT"
		  
		  if(mode1[0]=='m' && mode2[0]=='m')//if mode1 and mode2 are memory:error:not allowed
		    {
		      throw_err(7,line_no,err_tab);
		      exit(0);
		    }
		  if(strcmp(mode1+1,mode2+1)!=0)//mode1=r32 & mode2=m32(if both are not same size 32):error
		    {
		      throw_err(10,line_no,err_tab);
		      exit(0);		      
		    }
		  mode=(char*)malloc(sizeof(char)*5);//alocate mem for mode
		  strcpy(mode,mode1);//copy mode1 to mode:eg-r32
		  strcpy((mode+1),mode2);//copy mode2 to mode after 1st cherector:eg-rr32
		  mode[0]=mode[0]-32;//convert 1st cheractor to Upper case:eg-Rr32
		  key=hash_On_Optab(mode);//return location in Opcode array
		  pos=search_opcode(op_tab,mnem_indx,key,mode,&oplen);//return location of bucket

		  if((strcmp(str,"RT")==0 && strcmp(str2,"RT")==0))//if both are register
		    {
		      fprintf(interf,"%d#%d#%d %s#%d#%d %s#%d#%d\n",mnem_indx,key,pos,str,entry_no,0,str2,entry_no2,0);
		    }
		  if((strcmp(str,"RT")==0 && strcmp(str2,"ST")==0))//1st-reg 2nd-mem
		    {
		      fprintf(interf,"%d#%d#%d %s#%d#%d %s#%d\n",mnem_indx,key,pos,str,entry_no,1,str2,entry_no2);
		    }
		  if((strcmp(str,"ST")==0 && strcmp(str2,"RT")==0))//1st-mem 2nd-reg
		    {
		      fprintf(interf,"%d#%d#%d %s#%d#%d %s#%d\n",mnem_indx,key,pos,str2,entry_no2,1,str,entry_no);
		    }
		  if((strcmp(str,"RT")==0 && strcmp(str2,"LT")==0))//1st-reg 2nd-immediate
		    {
		      fprintf(interf,"%d#%d#%d %s#%d#%d %s#%d\n",mnem_indx,key,pos,str,entry_no,0,str2,(lit_indx-1));
		    }
		  if((strcmp(str,"ST")==0 && strcmp(str2,"LT")==0))//1st-mem 2nd-immediate
		    {
		      fprintf(interf,"%d#%d#%d %s#%d %s#%d\n",mnem_indx,key,pos,str,entry_no,str2,(lit_indx-1));
		    }
		}
	      break;
	    case 4:  // Binary instruction
	      if(tokenarr[0][strlen(tokenarr[0])-1]==':')
		{ 
		  lable=(char*)malloc(sizeof(char)*strlen(tokenarr[0]));
		  strncpy(lable,tokenarr[0],(strlen(tokenarr[0])-1));
		  lable[strlen(tokenarr[0])-1]='\0';
		  ret=validate_lable(lable,symb_tab,symtab_index,&err_no);
		  
		  if(ret==(-1))
		    {
		      throw_err(err_no,line_no,err_tab);
		      exit(0);
		    }
		  populate_symtab(&symb_tab,lable,NULL,".text",0,0,&symtab_index,1,line_no);
		  mnem_indx=search_mnem(tokenarr[1],op_tab);
		  //printf("mnemonic: %d\n",mnem_indx);
		  if(mnem_indx==(-1))
		    {
		      throw_err(1,line_no,err_tab);
		      exit(0);
		    }
		  if(0 <= mnem_indx && mnem_indx <= 6)
		    { mode1=(char*)malloc(sizeof(char)*5);
		      mode1=isRegister(tokenarr[2],&entry_no);

		      if(entry_no==(-1))
			{
			  mode1=isSymbol(tokenarr[2],symb_tab,symtab_index,&entry_no,&err_no,1,0);

			  if(entry_no==(-1))
			    {
			      throw_err(err_no,line_no,err_tab);
			      exit(0);
			    }
			  else
			    {   strcpy(str,"ST");   }			  
			}
		      else
			{  strcpy(str,"RT");  }
		    }
		  if(7 <= mnem_indx && mnem_indx <= 11)
		    {
		      throw_err(7,line_no,err_tab);
		      exit(0);
		    }
		  mode2=(char*)malloc(sizeof(char)*5);
		  mode2=isRegister(tokenarr[3],&entry_no2);

		  if(entry_no2==(-1))
		    {
		      mode2=isSymbol(tokenarr[3],symb_tab,symtab_index,&entry_no2,&err_no,0,1);
		      
		      if(entry_no2==(-1))
			{
			  ret=isImmediate(tokenarr[3],&lit_tab,&lit_indx,&err_no);

			  if(ret==(-1))
			    {
			      throw_err(err_no,line_no,err_tab);
			      exit(0);
			    }
			  else
			    {
			      lit_tab=(LIT_T*)realloc(lit_tab,sizeof(LIT_T)*(lit_indx+1));
			      lit_tab[lit_indx++].value=atoi(tokenarr[3]);
			      strcpy(mode2,mode1);
			      mode2[0]='i';
			      strcpy(str2,"LT");
			    }
			}
		      else
			strcpy(str2,"ST");
		    }
		  else
		    strcpy(str2,"RT");
		  if(mode1[0]=='m' && mode2[0]=='m')
		    {
		      throw_err(7,line_no,err_tab);
		      exit(0);
		    }
		  mode=(char*)malloc(sizeof(char)*5);
		  strcpy(mode,mode1);
		  strcpy((mode+1),mode2);
		  mode[0]=mode[0]-32;
		  key=hash_On_Optab(mode);
		  pos=search_opcode(op_tab,mnem_indx,key,mode,&oplen);

		  if((strcmp(str,"RT")==0 && strcmp(str2,"RT")==0))
		    {
		      fprintf(interf,"%d#%d#%d %s#%d#%d %s#%d#%d\n",mnem_indx,key,pos,str,entry_no,0,str2,entry_no2,0);
		    }
		  if((strcmp(str,"RT")==0 && strcmp(str2,"ST")==0))
		    {
		      fprintf(interf,"%d#%d#%d %s#%d#%d %s#%d\n",mnem_indx,key,pos,str,entry_no,1,str2,entry_no2);
		    }
		  if((strcmp(str,"ST")==0 && strcmp(str2,"RT")==0))
		    {
		      fprintf(interf,"%d#%d#%d %s#%d#%d %s#%d\n",mnem_indx,key,pos,str2,entry_no2,1,str,entry_no);
		    }
		  if((strcmp(str,"RT")==0 && strcmp(str2,"LT")==0))
		    {
		      fprintf(interf,"%d#%d#%d %s#%d#%d %s#%d\n",mnem_indx,key,pos,str,entry_no,0,str2,(lit_indx-1));
		    }
		  if((strcmp(str,"ST")==0 && strcmp(str2,"LT")==0))
		    {
		      fprintf(interf,"%d#%d#%d %s#%d %s#%d\n",mnem_indx,key,pos,str,entry_no,str2,(lit_indx-1));
		    }
		}
	      break;
	    }
	}
    }
  fclose(inputf);
  fclose(interf);

  // PASS 2 STARTS HERE .....

  interf=fopen("intermediate.txt","r");//open intermediate file in read mode
  if(interf==NULL)//if error in file opening
    {
      printf("FAIL TO OPEN INTERMEDIATE\n");
      exit(0);
    }
  outputf=fopen("output.obj","w");//open output file in write mode
  
  while(getline(&buffer,(size_t*)&n,interf)!=(-1))//read intermediate file
    {
     //printf("buff: %s\n",buffer);//print buffer
      tokenize(buffer,&tokenarr,&tokencnt);//call to tokenizer for retrive big token(string) 
      tyni_tokenize(tokenarr[0],&tyni_tokenarr,&tyni_tokencnt);//call tyni_tokenizer to split token into small tokens and stores in tyni_tokenerr

      entry_no=atoi(tyni_tokenarr[0]);//store mnemonic index in entry_no 
      obj=&(op_tab[atoi(tyni_tokenarr[0])].opt_arr[atoi(tyni_tokenarr[1])]);//store optab.opt_arr[index]

      for(i=0;i<atoi(tyni_tokenarr[2]);i++)//traverse through bucket in optab.opt_arr
	{
	  obj=obj->link;  
	}
      oprtr=(char*)malloc(sizeof(char)*strlen(obj->opcode));//allocate mem for operator
      strcpy(oprtr,obj->opcode);//store opcode in operator

      if(tokencnt==3)//means binary instruction
      	{
      	  tmp1=(char**)malloc(sizeof(char*)*2);//allocate mem for tmp1 2D string array to store operands 
      	  for(i=1;i<tokencnt;i++)//operate on token_arr[]
      	    {
      	      tyni_tokenize(tokenarr[i],&tyni_tokenarr,&tyni_tokencnt);//call to tyni_tokenizer to operat on tokenarr[1](operand1)and [2](operand2)
      	      switch(tyni_tokenarr[0][0])//compaire with 1st character of tyni_tokenarr[]
      	      	{
      	      	case 'R'://if register
		  if(atoi(tyni_tokenarr[2])==0)//check for RR_RI
		    {
		      tmp1[i-1]=(char*)malloc(sizeof(char)*strlen(reg_tab[atoi(tyni_tokenarr[1])].RR_RI));//alocate mem for RR_RI(mode) 
		      strcpy(tmp1[i-1],reg_tab[atoi(tyni_tokenarr[1])].RR_RI);//store RR_RI(mode)in to tmp1
		    }
		  else if(atoi(tyni_tokenarr[2])==1)//check for RM_MR
		    {
		      tmp1[i-1]=(char*)malloc(sizeof(char)*strlen(reg_tab[atoi(tyni_tokenarr[1])].RM_MR));//alocate mem for RR_RI(mode) 
		      strcpy(tmp1[i-1],reg_tab[atoi(tyni_tokenarr[1])].RM_MR);//store RM_MR(mode)in to tmp1
		    }
      	      	  break;
      	      	case 'S'://if symbol(variable/memory)
      	      	  tmp1[i-1]=(char*)malloc(sizeof(char)*10);//allocate mem for symbol:may be lable
      	      	  sprintf(tmp1[i-1],"%d",symb_tab[atoi(tyni_tokenarr[1])].line);//store line no in tmp1 as integer 
      	      	  break;
		case 'L'://if literal mins immediate value
		  tmp1[i-1]=(char*)malloc(sizeof(char)*10);//allocate mem for literal 
		  sprintf(tmp1[i-1],"%d",lit_tab[atoi(tyni_tokenarr[1])].value);//store literal value in tmp1
      	      	}

	      for(j=0;j<tyni_tokencnt;j++)//free the mem aloacated for tyni_tokenarr 2D string array 
		{
		  free(tyni_tokenarr[j]);
		}
	      free(tyni_tokenarr);
      	    }

	  if(tokenarr[1][0]=='R' && tokenarr[2][0]=='R')//check for operator-1 & operator-2 are registers
	    {
	      oprnd=(char*)malloc(sizeof(char)*10);//alocate size for oprnd
	      strcpy(oprnd,"11");//copy mode in oprnd
	      strcat(oprnd,tmp1[1]);//copy operand-2 in oprnd:eg-111
	      strcat(oprnd,tmp1[0]);//copy operand-1 in oprnd:eg-101
	      strcpy(oprnd,bin_hex(oprnd));//convert oprnd from binary to hex
	      fprintf(outputf,"\t%s%s\n",oprtr,oprnd);//write oprtr and oprnd to output file in hex formate

	      free(oprnd);//free mem of oprnd
	    }
	  else if(tokenarr[1][0]=='R' && tokenarr[2][0]=='S')//check for operator-1 is register & operator-2 is symbol
	    {
	      oprnd=(char*)malloc(sizeof(char)*20);//alocate size for oprnd
	      strcpy(oprnd,tmp1[0]);//copy operand-1 in oprnd
	      strcat(oprnd,"[");//append '[' to oprnd
	      sprintf(str,"%X",atoi(tmp1[1]));//convert and store operand-2 to str in hex formate
	      strcat(oprnd,str);//append hex formate symbol to oprnd
	      strcat(oprnd,"]");//append '[' to oprnd
	      fprintf(outputf,"\t%s%s\n",oprtr,oprnd);//write to output file
	    }
	  else if(tokenarr[1][0]=='R' && tokenarr[2][0]=='L')//check for operator-1 is register & operator-2 is literal
	    {
	      oprnd=(char*)malloc(sizeof(char)*20);//alocate mem for oprnd
	      sprintf(str,"%d",bin_dec(tmp1[0]));//convert operator-1 to decimal formate and store in str(as per the nasm formate)
	      strcpy(oprnd,str);//copy to oprnd
	      sprintf(str,"%X",atoi(tmp1[1]));//convert operand-2 to integer and store in str
	      /* if(strlen(str)<=1) */
	      /* 	strcat(oprnd,"0"); */
	      strcat(oprnd,str);//concat str to oprnd
	      fprintf(outputf,"\t%s%s\n",oprtr,oprnd);//write to output file
	    }
	  else if(tokenarr[1][0]=='S' && tokenarr[2][0]=='L')////check for operator-1 is symbol & operator-2 is literal
	    {
	      oprnd=(char*)malloc(sizeof(char)*20);//alocate mem for oprnd
	      strcpy(oprnd,"[");//stote '['in oprnd
	      sprintf(str,"%X",atoi(tmp1[0]));//convert oprator-1 to integer and store in hex formate
	      strcat(oprnd,str);//append str to oprnd
	      strcat(oprnd,"]");//append ']' to oprnd 
	      sprintf(str,"%X",atoi(tmp1[1]));//convert oprator-2 to integer and store in hex formate
	      if(strlen(str)<=1)//if hex value is single digit then append 0 to bigining
		strcat(oprnd,"0");//apend 0 
	      strcat(oprnd,str);//append str
	      fprintf(outputf,"\t%s%s\n",oprtr,oprnd);//write to output file
	    }	  
	}
      else if(tokencnt == 2)//if unary instrction
	{
	  tmp1=(char**)malloc(sizeof(char*)*2);//alocate mem for tmp1 2D string array
	  tyni_tokenize(tokenarr[1],&tyni_tokenarr,&tyni_tokencnt);//call tyni_tokenizer to split the token into small tokens
	  if(tyni_tokenarr[0][0]=='R')//if register
	    {
	      switch(entry_no)//from 7-11 unary instructions 
		{
		case 7:// NOT
		  tmp1[0]=(char*)malloc(sizeof(char)*strlen(reg_tab[atoi(tyni_tokenarr[1])].RR_RI));//alocate mem for tmp1[0] RR_RI
		  strcpy(tmp1[0],reg_tab[atoi(tyni_tokenarr[1])].RR_RI);//copy RR_RI of 1st operand
		  tmp1[1]=(char*)malloc(sizeof(char)*strlen(reg_tab[2].RR_RI));//allocate mem for tmp1[1] RR_RI
		  strcpy(tmp1[1],reg_tab[2].RR_RI);//copy RR_RI of destination register D
		  
		  oprnd=(char*)malloc(sizeof(char)*10);//aloacte mem foe oprnd
		  strcpy(oprnd,"11");//copy mode '11' to oprnd
		  strcat(oprnd,tmp1[1]);//copy  source register 
		  strcat(oprnd,tmp1[0]);//copy destination
		  strcpy(oprnd,bin_hex(oprnd));//convert oprnd from bin. to hex
		  fprintf(outputf,"\t%s%s\n",oprtr,oprnd);//write to output file
		  free(oprnd);//free the memory
 		  break;
		case 8:// INC
		  temp=atoi(oprtr); // oprator opcode value converted to int eg: 64
		  tmp1[0]=(char*)malloc(sizeof(char)*strlen(reg_tab[atoi(tyni_tokenarr[1])].RR_RI));
		  strcpy(tmp1[0],reg_tab[atoi(tyni_tokenarr[1])].RR_RI);	      
		  r_no=bin_dec(tmp1[0]); // 7 (111)
		  temp=temp+r_no; //eg: 64 + 7 (111)=71
		  sprintf(str,"%X",temp);//convert 71 to hex
		  fprintf(outputf,"\t%s\n",str);
		  break;
		case 9:// DEC
		  temp=atoi(oprtr);//convert opcode of oprtr DEC into integer
		  tmp1[0]=(char*)malloc(sizeof(char)*strlen(reg_tab[atoi(tyni_tokenarr[1])].RR_RI));//alocate mem for RR_RI
		  strcpy(tmp1[0],reg_tab[atoi(tyni_tokenarr[1])].RR_RI);//copy RR_RI to tmp1[0] of operand-1	      
		  r_no=bin_dec(tmp1[0]);
		  temp=temp+r_no;
		  sprintf(str,"%X",temp);
		  fprintf(outputf,"\t%s\n",str);
		  break;
		case 10:// MUL
		  tmp1[0]=(char*)malloc(sizeof(char)*strlen(reg_tab[atoi(tyni_tokenarr[1])].RR_RI));
		  strcpy(tmp1[0],reg_tab[atoi(tyni_tokenarr[1])].RR_RI);
		  tmp1[1]=(char*)malloc(sizeof(char)*strlen(reg_tab[4].RR_RI)); // (Implicit)source = AH register
		  strcpy(tmp1[1],reg_tab[4].RR_RI);
		  
		  oprnd=(char*)malloc(sizeof(char)*10);
		  strcpy(oprnd,"11");//copy mode
		  strcat(oprnd,tmp1[1]);
		  strcat(oprnd,tmp1[0]);
		  strcpy(oprnd,bin_hex(oprnd));
		  fprintf(outputf,"\t%s%s\n",oprtr,oprnd);
		  free(oprnd);
		  break;
		case 11:// DIV
		  tmp1[0]=(char*)malloc(sizeof(char)*strlen(reg_tab[atoi(tyni_tokenarr[1])].RR_RI));
		  strcpy(tmp1[0],reg_tab[atoi(tyni_tokenarr[1])].RR_RI);
		  tmp1[1]=(char*)malloc(sizeof(char)*strlen(reg_tab[6].RR_RI)); // source = DH register
		  strcpy(tmp1[1],reg_tab[6].RR_RI);
		  
		  oprnd=(char*)malloc(sizeof(char)*10);
		  strcpy(oprnd,"11");
		  strcat(oprnd,tmp1[1]);
		  strcat(oprnd,tmp1[0]);
		  strcpy(oprnd,bin_hex(oprnd));
		  fprintf(outputf,"\t%s%s\n",oprtr,oprnd);
		  free(oprnd);
		  break;
		}
	    }
	  else if(tyni_tokenarr[0][0]=='S')
	    {
	      tmp1[0]=(char*)malloc(sizeof(char)*10);
	      sprintf(tmp1[0],"%d",symb_tab[atoi(tyni_tokenarr[1])].line);
	      
	      oprnd=(char*)malloc(sizeof(char)*20);
	      strcpy(oprnd,"[");
	      sprintf(str,"%X",atoi(tmp1[0]));
	      strcat(oprnd,str);
	      strcat(oprnd,"]");
	      fprintf(outputf,"\t%s%s\n",oprtr,oprnd);
	    }

            for(j=0;j<tyni_tokencnt;j++)//free the mem aloacated for tyni_tokenarr 2D string array 
            {
              free(tyni_tokenarr[j]);
            }
              free(tyni_tokenarr);
	}
      
      for(i=0;i<tokencnt;i++)
        {
          free(tokenarr[i]);
        }
      free(tokenarr);
    }
  
  free(op_tab);
  free(symb_tab);
  free(err_tab);
  free(reg_tab);  
}

all:libasm.a test
libasm.a:Ass_err.o Ass_hashOpt.o Ass_initErrtab.o Ass_initOptab.o Ass_isImmediate.o Ass_isRegister.o Ass_isSymbole.o Ass_populateSymtab.o Ass_searchMnem.o Ass_searchOpcode.o Ass_struct.o Ass_tokenize.o Ass_validateData.o Ass_validateDatatype.o Ass_validateLable.o Ass_tyniTokenize.o Ass_binToHex.o Ass_binToDec.o
	ar -cvq libasm.a Ass_err.o Ass_hashOpt.o Ass_initErrtab.o Ass_initOptab.o Ass_isImmediate.o Ass_isRegister.o Ass_isSymbole.o Ass_populateSymtab.o Ass_searchMnem.o Ass_searchOpcode.o Ass_struct.o Ass_tokenize.o Ass_validateData.o Ass_validateDatatype.o Ass_validateLable.o Ass_tyniTokenize.o Ass_binToHex.o Ass_binToDec.o

Ass_err.o:Ass_err.c
	gcc -c -g3 Ass_err.c  
Ass_hashOpt.o:Ass_hashOpt.c
	gcc -c -g3 Ass_hashOpt.c  
Ass_initErrtab.o:Ass_initErrtab.c
	gcc -c -g3 Ass_initErrtab.c  
Ass_initOptab.o:Ass_initOptab.c
	gcc -c -g3 Ass_initOptab.c  
Ass_isImmediate.o:Ass_isImmediate.c
	gcc -c -g3 Ass_isImmediate.c  
Ass_isRegister.o:Ass_isRegister.c
	gcc -c -g3 Ass_isRegister.c  
Ass_isSymbole.o:Ass_isSymbole.c
	gcc -c -g3 Ass_isSymbole.c  
Ass_populateSymtab.o:Ass_populateSymtab.c
	gcc -c -g3 Ass_populateSymtab.c  
Ass_searchMnem.o:Ass_searchMnem.c
	gcc -c -g3 Ass_searchMnem.c  
Ass_searchOpcode.o:Ass_searchOpcode.c
	gcc -c -g3 Ass_searchOpcode.c  
Ass_struct.o:Ass_struct.c
	gcc -c -g3 Ass_struct.c  
Ass_tokenize.o:Ass_tokenize.c
	gcc -c -g3 Ass_tokenize.c  
Ass_validateData.o:Ass_validateData.c
	gcc -c -g3 Ass_validateData.c
Ass_validateDatatype.o:Ass_validateDatatype.c
	gcc -c -g3 Ass_validateDatatype.c  
Ass_validateLable.o:Ass_validateLable.c
	gcc -c -g3 Ass_validateLable.c
Ass_tyniTokenize.o:Ass_tyniTokenize.c
	gcc -c -g3 Ass_tyniTokenize.c    
Ass_binToHex.o:Ass_binToHex.c
	gcc -c -g3 Ass_binToHex.c    
Ass_binToDec.o:Ass_binToDec.c
	gcc -c -g3 Ass_binToDec.c    
test:Ass_main.c libasm.a
	gcc -g3 -o asmProto Ass_main.c libasm.a -lm

clean:
	rm *.o *.a *~ \#* asmProto intermediate.txt


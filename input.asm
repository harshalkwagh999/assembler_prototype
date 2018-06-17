section .data
	dvar dd 15
	dvar1 dd 10,40,30
	dvar2 db "Harshal",10,0
	dvar3 dw 105
	dvar4 dq 1434
section .bss
	bvar1 resb 10
	bvar2 resd 1
	bvar3 resw 1
section .text
	global main
main:
	mov bx,cx
	mov eax,ebx
	mov ebx,dword[dvar]
	mov dword[dvar],ebx
	mov bx,word[dvar3]
	mov word[dvar3],bx
	mov eax,20
	mov dword[dvar],100
	add bx,cx
	add eax,ebx
	add ebx,dword[dvar]
	add dword[dvar],ebx
	add bx,word[dvar3]
	add word[dvar3],bx
	add eax,20
	add dword[dvar],10
        sub bx,cx
	sub eax,ebx
	sub ebx,dword[dvar]
	sub dword[dvar],ebx
	sub bx,word[dvar3]
	sub word[dvar3],bx
	sub eax,20
	sub dword[dvar],10
	cmp bx,cx
	cmp eax,ebx
	cmp ebx,dword[dvar]
	cmp dword[dvar],ebx
	cmp bx,word[dvar3]
	cmp word[dvar3],bx
	cmp eax,20
	cmp dword[dvar],10	
	mul bx
	mul edx
	mul dword[dvar]
	div bx
	div ebx
	div word[dvar3]
	inc ebx
	inc edx
	inc dword[dvar]
	dec ebx
	dec dword[dvar]
	not ebx
	not dword[dvar]

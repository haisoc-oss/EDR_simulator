.data
	
    dwReturnLength      QWORD 0
	oldProtect			DWORD 0
	rsp_save			QWORD 0
    Return_adress_save	QWORD 0


	NtAlloc_str			db "NtAllocateVirtualMemory", 0
	NtDll_str			db "ntdll.dll", 0
.code
Tao_ban_day PROC
	mov rax,				rsp
	mov rsp_save,			rax
	mov rax,				[rsp]
	mov Return_adress_save, rax
	sub rsp,				40

	lea rax,				[NtDll_str]


Tao_ban_day ENDP
END
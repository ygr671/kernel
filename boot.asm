; MULTIBOOT STUFF
MB_MAGIC equ 0x1BADB002
MB_FLAGS equ 1 << 0 | 1 << 1
MB_CHKSM equ -(MB_MAGIC + MB_FLAGS)

section .multiboot
	dd MB_MAGIC
	dd MB_FLAGS
	dd MB_CHKSM

section .text
extern kmain

global _start
global outportb
global inportb

_start:
	mov esp, stack_top
	call kmain
	cli

.hang:
	hlt
	jmp .hang

outportb:
    mov edx, [esp + 4]
    mov al,  [esp + 8]
    out dx, al        
    ret

inportb:
    mov edx, [esp + 4]
    in al, dx         
    ret	

section .bss
align 16
stack_bottom:
	resb 16384
stack_top:

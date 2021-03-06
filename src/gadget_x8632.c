/*
** RopGadget - Release v3.4.2
** Jonathan Salwan - http://twitter.com/JonathanSalwan
** http://shell-storm.org
** 2012-11-11
**
** This program is free software; you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation; either version 2 of the License, or
** (at your option) any later version.
**
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with this program; if not, write to the Free Software
** Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

#include "ropgadget.h"

#define NB_GADGET   (sizeof(tab_x8632) / sizeof(tab_x8632[0])) - 2

/*
** If you want, you can add your gadgets in tab_x8632[]
** {FLAG, ADDR, INSTRUCTION ATT, INSTRUCTION INTEL, HEX INSTRUCTION, SIZE OPCODE}
*/
t_asm tab_x8632[] =
{
  /* hard opcode */
  {0, 0, "int $0x80", "int 0x80", "\xcd\x80", 2},
  {0, 0, "sysenter", "sysenter", "\x0f\x34", 2},
  {0, 0, "call *%eax", "call eax", "\xff\xd0", 2},
  {0, 0, "call *%ebx", "call ebx", "\xff\xd3", 2},
  {0, 0, "call *%ecx", "call ecx", "\xff\xd1", 2},
  {0, 0, "call *%edx", "call edx", "\xff\xd2", 2},
  {0, 0, "call *%esi", "call esi", "\xff\xd6", 2},
  {0, 0, "call *%edi", "call edi", "\xff\xd7", 2},
  {0, 0, "call *(%eax)", "call dword ptr [eax]", "\xff\x10", 2},
  {0, 0, "call *(%ebx)", "call dword ptr [ebx]", "\xff\x13", 2},
  {0, 0, "call *(%ecx)", "call dword ptr [ecx]", "\xff\x11", 2},
  {0, 0, "call *(%edx)", "call dword ptr [edx]", "\xff\x12", 2},
  {0, 0, "call *(%esi)", "call dword ptr [esi]", "\xff\x16", 2},
  {0, 0, "call *(%edi)", "call dword ptr [edi]", "\xff\x17", 2},
  {0, 0, "call eip+1 ; pop %eax ; ret", "call eip+1 ; pop eax ; ret", "\xe8\x00\x00\x00\x00\x58\xc3", 7},
  {0, 0, "call eip+1 ; pop %ebx ; ret", "call eip+1 ; pop ebx ; ret", "\xe8\x00\x00\x00\x00\x5b\xc3", 7},
  {0, 0, "call eip+1 ; pop %ecx ; ret", "call eip+1 ; pop ecx ; ret", "\xe8\x00\x00\x00\x00\x59\xc3", 7},
  {0, 0, "call eip+1 ; pop %edx ; ret", "call eip+1 ; pop edx ; ret", "\xe8\x00\x00\x00\x00\x5a\xc3", 7},
  {0, 0, "call eip+1 ; pop %esi ; ret", "call eip+1 ; pop esi ; ret", "\xe8\x00\x00\x00\x00\x5e\xc3", 7},
  {0, 0, "call eip+1 ; pop %edi ; ret", "call eip+1 ; pop edi ; ret", "\xe8\x00\x00\x00\x00\x5f\xc3", 7},
  {0, 0, "call eip+1 ; pop %ebp ; ret", "call eip+1 ; pop ebp ; ret", "\xe8\x00\x00\x00\x00\x5d\xc3", 7},
  {0, 0, "call *%gs:0x10", "call dword ptr gs:[0x00000010]", "\x65\xff\x15\x10\x00\x00\x00", 7},
  {0, 0, "jmp *%eax", "jmp eax", "\xff\xe0", 2},
  {0, 0, "jmp *%ebx", "jmp ebx", "\xff\xe3", 2},
  {0, 0, "jmp *%ecx", "jmp ecx", "\xff\xe1", 2},
  {0, 0, "jmp *%edx", "jmp edx", "\xff\xe2", 2},
  {0, 0, "jmp *%esi", "jmp esi", "\xff\xe6", 2},
  {0, 0, "jmp *%edi", "jmp edi", "\xff\xe7", 2},
  {0, 0, "jmp *(%eax)", "jmp dword ptr [eax]", "\xff\x20", 2},
  {0, 0, "jmp *(%ebx)", "jmp dword ptr [ebx]", "\xff\x23", 2},
  {0, 0, "jmp *(%ecx)", "jmp dword ptr [ecx]", "\xff\x21", 2},
  {0, 0, "jmp *(%edx)", "jmp dword ptr [edx]", "\xff\x22", 2},
  {0, 0, "jmp *(%esi)", "jmp dword ptr [esi]", "\xff\x26", 2},
  {0, 0, "jmp *(%edi)", "jmp dword ptr [edi]", "\xff\x27", 2},
  {0, 0, "pusha | ret", "pusha | ret", "\x60\xc3", 2},
  {0, 0, "popa | ret", "popa | ret", "\x61\xc3", 2},
  {0, 0, "push %eax ; ret", "push eax ; ret", "\x50\xc3", 2},
  {0, 0, "push %ebx ; ret", "push ebx ; ret", "\x53\xc3", 2},
  {0, 0, "push %ecx ; ret", "push ecx ; ret", "\x51\xc3", 2},
  {0, 0, "push %edx ; ret", "push edx ; ret", "\x52\xc3", 2},
  {0, 0, "push %esi ; ret", "push esi ; ret", "\x56\xc3", 2},
  {0, 0, "push %edi ; ret", "push edi ; ret", "\x57\xc3", 2},
  {0, 0, "push %ebp ; ret", "push ebp ; ret", "\x55\xc3", 2},
  {0, 0, "push %esp ; ret", "push esp ; ret", "\x54\xc3", 2},
  {0, 0, "pop %esp ; ret", "pop esp ; ret", "\x5c\xc3", 2},
  {0, 0, "pop %ebp ; ret", "pop ebp ; ret", "\x5d\xc3", 2},
  {0, 0, "pop %eax ; ret", "pop eax ; ret", "\x58\xc3", 2},
  {0, 0, "pop %ebx ; ret", "pop ebx ; ret", "\x5b\xc3", 2},
  {0, 0, "pop %ecx ; ret", "pop ecx ; ret", "\x59\xc3", 2},
  {0, 0, "pop %edx ; ret", "pop edx ; ret", "\x5a\xc3", 2},
  {0, 0, "pop %esi ; ret", "pop esi ; ret", "\x5e\xc3", 2},
  {0, 0, "pop %edi ; ret", "pop edi ; ret", "\x5f\xc3", 2},
  {0, 0, "pop %ebx ; pop %ebp ; ret", "pop ebx ; pop ebp ; ret", "\x5b\x5d\xc3", 3},
  {0, 0, "pop %eax ; pop %ebx ; pop %esi ; pop %edi ; ret", 
         "pop eax ; pop ebx ; pop esi ; pop edi ; ret", "\x58\x5b\x5e\x5f\xc3", 5},
  {0, 0, "pop %ebx ; pop %esi ; pop %ebp ; ret", "pop ebx ; pop esi ; pop ebp ; ret", "\x5b\x5e\x5d\xc3", 4},
  {0, 0, "pop %ebx ; pop %esi ; pop %edi ; pop %ebp ; ret", 
         "pop ebx ; pop esi ; pop edi ; pop ebp ; ret", "\x5b\x5e\x5f\x5d\xc3", 5},
  {0, 0, "pop %esi ; pop %ebx ; pop %edx ; ret", "pop esi ; pop ebx ; pop edx ; ret", "\x5e\x5b\x5a\xc3", 4},
  {0, 0, "pop %edx ; pop %ecx ; pop %ebx ; ret", "pop edx ; pop ecx ; pop ebx ; ret", "\x5a\x59\x5b\xc3", 4},
  {0, 0, "xor %eax,%eax ; ret", "xor eax, eax ; ret", "\x31\xc0\xc3", 3},
  {0, 0, "xor %ebx,%ebx ; ret", "xor ebx, ebx ; ret", "\x31\xdb\xc3", 3},
  {0, 0, "xor %ecx,%ecx ; ret", "xor ecx, ecx ; ret", "\x31\xc9\xc3", 3},
  {0, 0, "xor %edx,%edx ; ret", "xor edx, edx ; ret", "\x31\xd2\xc3", 3},
  {0, 0, "xor %esi,%esi ; ret", "xor esi, esi ; ret", "\x31\xf6\xc3", 3},
  {0, 0, "xor %edi,%edi ; ret", "xor edi, edi ; ret", "\x31\xf7\xc3", 3},
  {0, 0, "xor %eax,%eax ; pop %ebx ; pop %ebp ; ret", 
         "xor eax, eax ; pop ebx ; pop ebp ; ret", "\x31\xc0\x5b\x5d\xc3", 5},
  {0, 0, "xor %eax,%eax ; pop %ebx ; pop %esi ; pop %edi ; pop %ebp ; ret", 
         "xor eax, eax ; pop ebx ; pop esi ; pop edi ; pop ebp ; ret", "\x31\xc0\x5b\x5e\x5f\x5d\xc3", 7},
  {0, 0, "xor %eax,%eax ; pop %edi ; ret", "xor eax, eax ; pop edi ; ret", "\x31\xc0\x5f\xc3", 4},
  {0, 0, "xor %eax,%eax ; pop %ebx ; ret", "xor eax, eax ; pop ebx ; ret", "\x31\xc0\x5b\xc3", 4},
  {0, 0, "xor %eax,%eax ; mov %esp, %ebp ; pop %ebp ; ret", 
         "xor eax, eax ; mov ebp, esp ; pop ebp ; ret", "\x31\xc0\x89\xe5\x5d\xc3", 6},
  {0, 0, "inc %eax ; ret", "inc eax ; ret",  "\x40\xc3", 2},
  {0, 0, "inc %ebx ; ret", "inc ebx ; ret",  "\x43\xc3", 2},
  {0, 0, "inc %ecx ; ret", "inc ecx ; ret",  "\x41\xc3", 2},
  {0, 0, "inc %edx ; ret", "inc edx ; ret",  "\x42\xc3", 2},
  {0, 0, "inc %esi ; ret", "inc esi ; ret",  "\x46\xc3", 2},
  {0, 0, "inc %edi ; ret", "inc edi ; ret",  "\x47\xc3", 2},
  {0, 0, "dec %eax ; ret", "dec eax ; ret",  "\x48\xc3", 2},
  {0, 0, "dec %ebx ; ret", "dec ebx ; ret",  "\x4b\xc3", 2},
  {0, 0, "dec %ecx ; ret", "dec ecx ; ret",  "\x49\xc3", 2},
  {0, 0, "dec %edx ; ret", "dec edx ; ret",  "\x4a\xc3", 2},
  {0, 0, "dec %esi ; ret", "dec esi ; ret",  "\x4e\xc3", 2},
  {0, 0, "dec %edi ; ret", "dec edi ; ret",  "\x4f\xc3", 2},
  {0, 0, "inc %eax ; pop %edi ; pop %esi ; ret", "inc eax ; pop edi ; pop esi ; ret",  "\x40\x5f\x5e\xc3", 4},
  {0, 0, "inc %eax ; pop %edi ; ret", "inc eax ; pop edi ; ret",  "\x40\x5f\xc3", 3},
  {0, 0, "inc %eax ; inc %eax ; inc %eax ; ret", "inc eax ; inc eax ; inc eax ; ret",  "\x40\x40\x40\xc3", 4},
  {0, 0, "inc %eax ; inc %eax ; ret", "inc eax ; inc eax ; ret",  "\x40\x40\xc3", 3},
  {0, 0, "sub $0x01,%eax ; pop %ebx ; pop %esi ; pop %ebp ; ret", 
         "sub eax, 0x01 ; pop ebx ; pop esi ; pop ebp ; ret",  "\x83\xe8\x01\x5b\x5e\x5d\xc3", 7},
  {0, 0, "sub %ebx,%eax ; pop %ebx ; pop %esi ; pop %edi ; pop %ebp ; ret", 
         "sub eax, ebx ; pop ebx ; pop esi ; pop edi ; pop ebp ; ret",  "\x29\xd8\x5b\x5e\x5f\x5d\xc3", 7},
  {0, 0, "sub $0x01,%eax ; pop %ebp ; ret", "sub eax, 0x01 ; pop ebp ; ret",  "\x89\xe8\x01\x5d\xc3", 5},
  {0, 0, "add %ebx,%eax ; pop %ebx ; pop %ebp ; ret", "add eax, ebx ; pop ebx ; pop ebp ; ret",  "\x01\xd8\x5b\x5d\xc3", 5},
  {0, 0, "mul %eax ; ret", "mul eax ; ret",  "\xf7\xe0\xc3", 3},
  {0, 0, "mul %ebx ; ret", "mul ebx ; ret",  "\xf7\xe3\xc3", 3},
  {0, 0, "mul %ecx ; ret", "mul ecx ; ret",  "\xf7\xe1\xc3", 3},
  {0, 0, "mul %edx ; ret", "mul edx ; ret",  "\xf7\xe2\xc3", 3},
  {0, 0, "mul %esi ; ret", "mul esi ; ret",  "\xf7\xe6\xc3", 3},
  {0, 0, "mul %edi ; ret", "mul edi ; ret",  "\xf7\xe7\xc3", 3},
  {0, 0, "mul %eax ; pop %ebp ; ret", "mul eax ; pop ebp ; ret",  "\xf7\xe0\x5d\xc3", 4},
  {0, 0, "mul %ebx ; pop %ebp ; ret", "mul ebx ; pop ebp ; ret",  "\xf7\xe3\x5d\xc3", 4},
  {0, 0, "mul %ecx ; pop %ebp ; ret", "mul ecx ; pop ebp ; ret",  "\xf7\xe1\x5d\xc3", 4},
  {0, 0, "mul %edx ; pop %ebp ; ret", "mul edx ; pop ebp ; ret",  "\xf7\xe2\x5d\xc3", 4},
  {0, 0, "mul %esi ; pop %ebp ; ret", "mul esi ; pop ebp ; ret",  "\xf7\xe6\x5d\xc3", 4},
  {0, 0, "mul %edi ; pop %ebp ; ret", "mul edi ; pop ebp ; ret",  "\xf7\xe7\x5d\xc3", 4},
  {0, 0, "div %eax ; ret", "div eax ; ret",  "\xf7\xf0\xc3", 3},
  {0, 0, "div %ebx ; ret", "div ebx ; ret",  "\xf7\xf3\xc3", 3},
  {0, 0, "div %ecx ; ret", "div ecx ; ret",  "\xf7\xf1\xc3", 3},
  {0, 0, "div %edx ; ret", "div edx ; ret",  "\xf7\xf2\xc3", 3},
  {0, 0, "div %esi ; ret", "div esi ; ret",  "\xf7\xf6\xc3", 3},
  {0, 0, "div %edi ; ret", "div edi ; ret",  "\xf7\xf7\xc3", 3},
  {0, 0, "div %eax ; pop %ebp ; ret", "div eax ; pop ebp ; ret",  "\xf7\xf0\x5d\xc3", 4},
  {0, 0, "div %ebx ; pop %ebp ; ret", "div ebx ; pop ebp ; ret",  "\xf7\xf3\x5d\xc3", 4},
  {0, 0, "div %ecx ; pop %ebp ; ret", "div ecx ; pop ebp ; ret",  "\xf7\xf1\x5d\xc3", 4},
  {0, 0, "div %edx ; pop %ebp ; ret", "div edx ; pop ebp ; ret",  "\xf7\xf2\x5d\xc3", 4},
  {0, 0, "div %esi ; pop %ebp ; ret", "div esi ; pop ebp ; ret",  "\xf7\xf6\x5d\xc3", 4},
  {0, 0, "div %edi ; pop %ebp ; ret", "div edi ; pop ebp ; ret",  "\xf7\xf7\x5d\xc3", 4},
  {0, 0, "neg %eax | ret", "neg eax | ret",  "\xf7\xd8\xc3", 3},
  {0, 0, "neg %ebx | ret", "neg ebx | ret",  "\xf7\xdb\xc3", 3},
  {0, 0, "neg %ecx | ret", "neg ecx | ret",  "\xf7\xd9\xc3", 3},
  {0, 0, "neg %edx | ret", "neg edx | ret",  "\xf7\xda\xc3", 3},
  {0, 0, "neg %esi | ret", "neg esi | ret",  "\xf7\xde\xc3", 3},
  {0, 0, "neg %edi | ret", "neg edi | ret",  "\xf7\xdf\xc3", 3},
  {0, 0, "neg %eax | pop %ebp ; ret", "neg eax | pop ebp ; ret",  "\xf7\xd8\x5d\xc3", 4},
  {0, 0, "neg %ebx | pop %ebp ; ret", "neg ebx | pop ebp ; ret",  "\xf7\xdb\x5d\xc3", 4},
  {0, 0, "neg %ecx | pop %ebp ; ret", "neg ecx | pop ebp ; ret",  "\xf7\xd9\x5d\xc3", 4},
  {0, 0, "neg %edx | pop %ebp ; ret", "neg edx | pop ebp ; ret",  "\xf7\xda\x5d\xc3", 4},
  {0, 0, "neg %esi | pop %ebp ; ret", "neg esi | pop ebp ; ret",  "\xf7\xde\x5d\xc3", 4},
  {0, 0, "neg %edi | pop %ebp ; ret", "neg edi | pop ebp ; ret",  "\xf7\xdf\x5d\xc3", 4},
  {0, 0, "not %eax | ret", "not eax | ret",  "\xf7\xd0\xc3", 3},
  {0, 0, "not %ebx | ret", "not ebx | ret",  "\xf7\xd3\xc3", 3},
  {0, 0, "not %ecx | ret", "not ecx | ret",  "\xf7\xd1\xc3", 3},
  {0, 0, "not %edx | ret", "not edx | ret",  "\xf7\xd2\xc3", 3},
  {0, 0, "not %esi | ret", "not esi | ret",  "\xf7\xd6\xc3", 3},
  {0, 0, "not %edi | ret", "not edi | ret",  "\xf7\xd7\xc3", 3},
  {0, 0, "not %eax | pop %ebp ; ret", "not eax | pop ebp ; ret",  "\xf7\xd0\x5d\xc3", 4},
  {0, 0, "not %ebx | pop %ebp ; ret", "not ebx | pop ebp ; ret",  "\xf7\xd3\x5d\xc3", 4},
  {0, 0, "not %ecx | pop %ebp ; ret", "not ecx | pop ebp ; ret",  "\xf7\xd1\x5d\xc3", 4},
  {0, 0, "not %edx | pop %ebp ; ret", "not edx | pop ebp ; ret",  "\xf7\xd2\x5d\xc3", 4},
  {0, 0, "not %esi | pop %ebp ; ret", "not esi | pop ebp ; ret",  "\xf7\xd6\x5d\xc3", 4},
  {0, 0, "not %edi | pop %ebp ; ret", "not edi | pop ebp ; ret",  "\xf7\xd7\x5d\xc3", 4},
  {0, 0, "shr %eax ; ret", "shr eax ; ret",  "\xd1\xe8\xc3", 3},
  {0, 0, "shr %ebx ; ret", "shr ebx ; ret",  "\xd1\xeb\xc3", 3},
  {0, 0, "shr %ecx ; ret", "shr ecx ; ret",  "\xd1\xe9\xc3", 3},
  {0, 0, "shr %edx ; ret", "shr edx ; ret",  "\xd1\xea\xc3", 3},
  {0, 0, "shr %esi ; ret", "shr esi ; ret",  "\xd1\xee\xc3", 3},
  {0, 0, "shr %edi ; ret", "shr edi ; ret",  "\xd1\xef\xc3", 3},
  {0, 0, "shl %eax ; ret", "shl eax ; ret",  "\xd1\xe0\xc3", 3},
  {0, 0, "shl %ebx ; ret", "shl ebx ; ret",  "\xd1\xe3\xc3", 3},
  {0, 0, "shl %ecx ; ret", "shl ecx ; ret",  "\xd1\xe1\xc3", 3},
  {0, 0, "shl %edx ; ret", "shl edx ; ret",  "\xd1\xe2\xc3", 3},
  {0, 0, "shl %esi ; ret", "shl esi ; ret",  "\xd1\xe6\xc3", 3},
  {0, 0, "shl %edi ; ret", "shl edi ; ret",  "\xd1\xe7\xc3", 3},
  {0, 0, "ror %eax ; ret", "ror eax ; ret",  "\xd1\xc8\xc3", 3},
  {0, 0, "ror %ebx ; ret", "ror ebx ; ret",  "\xd1\xcb\xc3", 3},
  {0, 0, "ror %ecx ; ret", "ror ecx ; ret",  "\xd1\xc9\xc3", 3},
  {0, 0, "ror %edx ; ret", "ror edx ; ret",  "\xd1\xca\xc3", 3},
  {0, 0, "ror %esi ; ret", "ror esi ; ret",  "\xd1\xce\xc3", 3},
  {0, 0, "ror %edi ; ret", "ror edi ; ret",  "\xd1\xcf\xc3", 3},
  {0, 0, "rol %eax ; ret", "rol eax ; ret",  "\xd1\xc0\xc3", 3},
  {0, 0, "rol %ebx ; ret", "rol ebx ; ret",  "\xd1\xc3\xc3", 3},
  {0, 0, "rol %ecx ; ret", "rol ecx ; ret",  "\xd1\xc1\xc3", 3},
  {0, 0, "rol %edx ; ret", "rol edx ; ret",  "\xd1\xc2\xc3", 3},
  {0, 0, "rol %esi ; ret", "rol esi ; ret",  "\xd1\xc6\xc3", 3},
  {0, 0, "rol %edi ; ret", "rol edi ; ret",  "\xd1\xc7\xc3", 3},
  {0, 0, "xchg %eax,%esp ; ret", "xchg esp, eax ; ret",  "\x94\xc3", 2},
  {0, 0, "xchg %eax,%ebx ; ret", "xchg ebx, eax ; ret",  "\x93\xc3", 2},
  {0, 0, "xchg %eax,%ecx ; ret", "xchg ecx, eax ; ret",  "\x91\xc3", 2},
  {0, 0, "xchg %eax,%edx ; ret", "xchg edx, eax ; ret",  "\x92\xc3", 2},
  {0, 0, "xchg %eax,%esi ; ret", "xchg esi, eax ; ret",  "\x96\xc3", 2},
  {0, 0, "xchg %eax,%edi ; ret", "xchg edi, eax ; ret",  "\x97\xc3", 2},
  {0, 0, "xchg %eax,%ebp ; ret", "xchg ebp, eax ; ret",  "\x95\xc3", 2},
  {0, 0, "xchg %eax,%esp ; pop %ebp ; ret", "xchg esp, eax ; pop ebp ; ret",  "\x94\x5d\xc3", 3},
  {0, 0, "xchg %eax,%ebx ; pop %ebp ; ret", "xchg ebx, eax ; pop ebp ; ret",  "\x93\x5d\xc3", 3},
  {0, 0, "xchg %eax,%ecx ; pop %ebp ; ret", "xchg ecx, eax ; pop ebp ; ret",  "\x91\x5d\xc3", 3},
  {0, 0, "xchg %eax,%edx ; pop %ebp ; ret", "xchg edx, eax ; pop ebp ; ret",  "\x92\x5d\xc3", 3},
  {0, 0, "xchg %eax,%esi ; pop %ebp ; ret", "xchg esi, eax ; pop ebp ; ret",  "\x96\x5d\xc3", 3},
  {0, 0, "xchg %eax,%edi ; pop %ebp ; ret", "xchg edi, eax ; pop ebp ; ret",  "\x97\x5d\xc3", 3},
  {0, 0, "xchg %eax,%ebp ; pop %ebp ; ret", "xchg ebp, eax ; pop ebp ; ret",  "\x95\x5d\xc3", 3},
  {0, 0, "bswap %eax ; ret", "bswap eax ; ret",  "\x0f\xc8\xc3", 3},
  {0, 0, "bswap %ebx ; ret", "bswap ebx ; ret",  "\x0f\xcb\xc3", 3},
  {0, 0, "bswap %ecx ; ret", "bswap ecx ; ret",  "\x0f\xc9\xc3", 3},
  {0, 0, "bswap %edx ; ret", "bswap edx ; ret",  "\x0f\xca\xc3", 3},
  {0, 0, "bswap %esi ; ret", "bswap esi ; ret",  "\x0f\xce\xc3", 3},
  {0, 0, "bswap %edi ; ret", "bswap edi ; ret",  "\x0f\xcf\xc3", 3},
  {0, 0, "bswap %eax ; pop %ebp ; ret", "bswap eax ; pop ebp ; ret",  "\x0f\xc8\x5d\xc3", 3},
  {0, 0, "bswap %ebx ; pop %ebp ; ret", "bswap ebx ; pop ebp ; ret",  "\x0f\xcb\x5d\xc3", 3},
  {0, 0, "bswap %ecx ; pop %ebp ; ret", "bswap ecx ; pop ebp ; ret",  "\x0f\xc9\x5d\xc3", 3},
  {0, 0, "bswap %edx ; pop %ebp ; ret", "bswap edx ; pop ebp ; ret",  "\x0f\xca\x5d\xc3", 3},
  {0, 0, "bswap %esi ; pop %ebp ; ret", "bswap esi ; pop ebp ; ret",  "\x0f\xce\x5d\xc3", 3},
  {0, 0, "bswap %edi ; pop %ebp ; ret", "bswap edi ; pop ebp ; ret",  "\x0f\xcf\x5d\xc3", 3},
  {0, 0, "mov %ebx,%eax ; pop %ebx ; pop %ebp ; ret", "mov eax, ebx ; pop ebx ; pop ebp ; ret",  "\x89\xd8\x5b\x5d\xc3", 5},
  {0, 0, "mov %edx,%eax ; pop %ebx ; pop %esi ; pop %edi ; pop %ebp ; ret", 
         "mov eax, edx ; pop ebx ; pop esi ; pop edi ; pop ebp ; ret",  "\x89\xd0\x5b\x5e\x5f\x5d\xc3", 7},
  {0, 0, "mov %edi,%eax ; pop %ebx ; pop %esi ; pop %edi ; pop %ebp ; ret", 
         "mov eax, edi ; pop ebx ; pop esi ; pop edi ; pop ebp ; ret",  "\x89\xf8\x5b\x5e\x5f\x5d\xc3", 7},
  {0, 0, "mov %ebx,%eax ; pop %ebx ; pop %esi ; pop %edi ; pop %ebp ; ret", 
         "mov eax, ebx ; pop ebx ; pop esi ; pop edi ; pop ebp ; ret",  "\x89\xd8\x5b\x5e\x5f\x5d\xc3", 7},
  {0, 0, "mov %esi,%eax ; pop %ebx ; pop %esi ; pop %edi ; pop %ebp ; ret", 
         "mov eax, esi ; pop ebx ; pop esi ; pop edi ; pop ebp ; ret",  "\x89\xf0\x5b\x5e\x5f\x5d\xc3", 7},
  {0, 0, "mov %ecx,%eax ; pop %ebx ; pop %esi ; pop %edi ; pop %ebp ; ret", 
         "mov eax, ecx ; pop ebx ; pop esi ; pop edi ; pop ebp ; ret",  "\x89\xc8\x5b\x5e\x5f\x5d\xc3", 7},
  {0, 0, "mov %ebx,%eax ; pop %ebx ; pop %esi ; pop %ebp ; ret", 
         "mov eax, ebx ; pop ebx ; pop esi ; pop ebp ; ret",  "\x89\xd8\x5b\x5e\x5d\xc3", 6},
  {0, 0, "mov %ebp,%esp ; pop %ebp ; ret", "mov esp, ebp ; pop ebp ; ret",  "\x89\xec\x5d\xc3", 4},
  {0, 0, "mov %esp,%eax ; ret", "mov eax, esp ; ret",  "\x89\xe0\xc3", 3},
  {0, 0, "mov %esp,%ebx ; ret", "mov ebx, esp ; ret",  "\x89\xe3\xc3", 3},
  {0, 0, "mov %esp,%ecx ; ret", "mov ecx, esp ; ret",  "\x89\xe1\xc3", 3},
  {0, 0, "mov %esp,%edx ; ret", "mov edx, esp ; ret",  "\x89\xe2\xc3", 3},
  {0, 0, "mov %esp,%ebp ; ret", "mov ebp, esp ; ret",  "\x89\xe5\xc3", 3},
  {0, 0, "mov %eax,%ebx ; ret", "mov ebx, eax ; ret",  "\x89\xc3\xc3", 3},
  {0, 0, "mov %eax,%ecx ; ret", "mov ecx, eax ; ret",  "\x89\xc1\xc3", 3},
  {0, 0, "mov %eax,%edx ; ret", "mov edx, eax ; ret",  "\x89\xc2\xc3", 3},
  {0, 0, "mov %eax,%esi ; ret", "mov esi, eax ; ret",  "\x89\xc6\xc3", 3},
  {0, 0, "mov %eax,%edi ; ret", "mov edi, eax ; ret",  "\x89\xc7\xc3", 3},
  {0, 0, "mov %ebx,%eax ; ret", "mov eax, ebx ; ret",  "\x89\xd8\xc3", 3},
  {0, 0, "mov %ebx,%ecx ; ret", "mov ecx, ebx ; ret",  "\x89\xd9\xc3", 3},
  {0, 0, "mov %ebx,%edx ; ret", "mov edx, ebx ; ret",  "\x89\xda\xc3", 3},
  {0, 0, "mov %ebx,%esi ; ret", "mov esi, ebx ; ret",  "\x89\xde\xc3", 3},
  {0, 0, "mov %ebx,%edi ; ret", "mov edi, ebx ; ret",  "\x89\xdf\xc3", 3},
  {0, 0, "mov %ecx,%eax ; ret", "mov eax, ecx ; ret",  "\x89\xc8\xc3", 3},
  {0, 0, "mov %ecx,%ebx ; ret", "mov ebx, ecx ; ret",  "\x89\xcb\xc3", 3},
  {0, 0, "mov %ecx,%edx ; ret", "mov edx, ecx ; ret",  "\x89\xca\xc3", 3},
  {0, 0, "mov %ecx,%esi ; ret", "mov esi, ecx ; ret",  "\x89\xce\xc3", 3},
  {0, 0, "mov %ecx,%edi ; ret", "mov edi, ecx ; ret",  "\x89\xcf\xc3", 3},
  {0, 0, "mov %edx,%eax ; ret", "mov eax, edx ; ret",  "\x89\xd0\xc3", 3},
  {0, 0, "mov %edx,%ebx ; ret", "mov ebx, edx ; ret",  "\x89\xd3\xc3", 3},
  {0, 0, "mov %edx,%ecx ; ret", "mov ecx, edx ; ret",  "\x89\xd1\xc3", 3},
  {0, 0, "mov %edx,%esi ; ret", "mov esi, edx ; ret",  "\x89\xd6\xc3", 3},
  {0, 0, "mov %edx,%edi ; ret", "mov edi, edx ; ret",  "\x89\xd7\xc3", 3},
  {0, 0, "mov %esi,%eax ; ret", "mov eax, esi ; ret",  "\x89\xf0\xc3", 3},
  {0, 0, "mov %esi,%ebx ; ret", "mov ebx, esi ; ret",  "\x89\xf3\xc3", 3},
  {0, 0, "mov %esi,%ecx ; ret", "mov ecx, esi ; ret",  "\x89\xf1\xc3", 3},
  {0, 0, "mov %esi,%edx ; ret", "mov edx, esi ; ret",  "\x89\xf2\xc3", 3},
  {0, 0, "mov %esi,%edi ; ret", "mov edi, esi ; ret",  "\x89\xf7\xc3", 3},
  {0, 0, "mov %edi,%eax ; ret", "mov eax, edi ; ret",  "\x89\xf8\xc3", 3},
  {0, 0, "mov %edi,%ebx ; ret", "mov ebx, edi ; ret",  "\x89\xfb\xc3", 3},
  {0, 0, "mov %edi,%ecx ; ret", "mov ecx, edi ; ret",  "\x89\xf9\xc3", 3},
  {0, 0, "mov %edi,%edx ; ret", "mov edx, edi ; ret",  "\x89\xfa\xc3", 3},
  {0, 0, "mov %edi,%esi ; ret", "mov esi, edi ; ret",  "\x89\xfe\xc3", 3},
  {0, 0, "mov %esp,%eax ; pop %ebp ; ret", "mov eax, esp ; pop ebp ; ret",  "\x89\xe0\x5d\xc3", 4},
  {0, 0, "mov %esp,%ebx ; pop %ebp ; ret", "mov ebx, esp ; pop ebp ; ret",  "\x89\xe3\x5d\xc3", 4},
  {0, 0, "mov %esp,%ecx ; pop %ebp ; ret", "mov ecx, esp ; pop ebp ; ret",  "\x89\xe1\x5d\xc3", 4},
  {0, 0, "mov %esp,%edx ; pop %ebp ; ret", "mov edx, esp ; pop ebp ; ret",  "\x89\xe2\x5d\xc3", 4},
  {0, 0, "mov %esp,%ebp ; pop %ebp ; ret", "mov ebp, esp ; pop ebp ; ret",  "\x89\xe5\x5d\xc3", 4},
  {0, 0, "mov %eax,%ebx ; pop %ebp ; ret", "mov ebx, eax ; pop ebp ; ret",  "\x89\xc3\x5d\xc3", 4},
  {0, 0, "mov %eax,%ecx ; pop %ebp ; ret", "mov ecx, eax ; pop ebp ; ret",  "\x89\xc1\x5d\xc3", 4},
  {0, 0, "mov %eax,%edx ; pop %ebp ; ret", "mov edx, eax ; pop ebp ; ret",  "\x89\xc2\x5d\xc3", 4},
  {0, 0, "mov %eax,%esi ; pop %ebp ; ret", "mov esi, eax ; pop ebp ; ret",  "\x89\xc6\x5d\xc3", 4},
  {0, 0, "mov %eax,%edi ; pop %ebp ; ret", "mov edi, eax ; pop ebp ; ret",  "\x89\xc7\x5d\xc3", 4},
  {0, 0, "mov %ebx,%eax ; pop %ebp ; ret", "mov eax, ebx ; pop ebp ; ret",  "\x89\xd8\x5d\xc3", 4},
  {0, 0, "mov %ebx,%ecx ; pop %ebp ; ret", "mov ecx, ebx ; pop ebp ; ret",  "\x89\xd9\x5d\xc3", 4},
  {0, 0, "mov %ebx,%edx ; pop %ebp ; ret", "mov edx, ebx ; pop ebp ; ret",  "\x89\xda\x5d\xc3", 4},
  {0, 0, "mov %ebx,%esi ; pop %ebp ; ret", "mov esi, ebx ; pop ebp ; ret",  "\x89\xde\x5d\xc3", 4},
  {0, 0, "mov %ebx,%edi ; pop %ebp ; ret", "mov edi, ebx ; pop ebp ; ret",  "\x89\xdf\x5d\xc3", 4},
  {0, 0, "mov %ecx,%eax ; pop %ebp ; ret", "mov eax, ecx ; pop ebp ; ret",  "\x89\xc8\x5d\xc3", 4},
  {0, 0, "mov %ecx,%ebx ; pop %ebp ; ret", "mov ebx, ecx ; pop ebp ; ret",  "\x89\xcb\x5d\xc3", 4},
  {0, 0, "mov %ecx,%edx ; pop %ebp ; ret", "mov edx, ecx ; pop ebp ; ret",  "\x89\xca\x5d\xc3", 4},
  {0, 0, "mov %ecx,%esi ; pop %ebp ; ret", "mov esi, ecx ; pop ebp ; ret",  "\x89\xce\x5d\xc3", 4},
  {0, 0, "mov %ecx,%edi ; pop %ebp ; ret", "mov edi, ecx ; pop ebp ; ret",  "\x89\xcf\x5d\xc3", 4},
  {0, 0, "mov %edx,%eax ; pop %ebp ; ret", "mov eax, edx ; pop ebp ; ret",  "\x89\xd0\x5d\xc3", 4},
  {0, 0, "mov %edx,%ebx ; pop %ebp ; ret", "mov ebx, edx ; pop ebp ; ret",  "\x89\xd3\x5d\xc3", 4},
  {0, 0, "mov %edx,%ecx ; pop %ebp ; ret", "mov ecx, edx ; pop ebp ; ret",  "\x89\xd1\x5d\xc3", 4},
  {0, 0, "mov %edx,%esi ; pop %ebp ; ret", "mov esi, edx ; pop ebp ; ret",  "\x89\xd6\x5d\xc3", 4},
  {0, 0, "mov %edx,%edi ; pop %ebp ; ret", "mov edi, edx ; pop ebp ; ret",  "\x89\xd7\x5d\xc3", 4},
  {0, 0, "mov %esi,%eax ; pop %ebp ; ret", "mov eax, esi ; pop ebp ; ret",  "\x89\xf0\x5d\xc3", 4},
  {0, 0, "mov %esi,%ebx ; pop %ebp ; ret", "mov ebx, esi ; pop ebp ; ret",  "\x89\xf3\x5d\xc3", 4},
  {0, 0, "mov %esi,%ecx ; pop %ebp ; ret", "mov ecx, esi ; pop ebp ; ret",  "\x89\xf1\x5d\xc3", 4},
  {0, 0, "mov %esi,%edx ; pop %ebp ; ret", "mov edx, esi ; pop ebp ; ret",  "\x89\xf2\x5d\xc3", 4},
  {0, 0, "mov %esi,%edi ; pop %ebp ; ret", "mov edi, esi ; pop ebp ; ret",  "\x89\xf7\x5d\xc3", 4},
  {0, 0, "mov %edi,%eax ; pop %ebp ; ret", "mov eax, edi ; pop ebp ; ret",  "\x89\xf8\x5d\xc3", 4},
  {0, 0, "mov %edi,%ebx ; pop %ebp ; ret", "mov ebx, edi ; pop ebp ; ret",  "\x89\xfb\x5d\xc3", 4},
  {0, 0, "mov %edi,%ecx ; pop %ebp ; ret", "mov ecx, edi ; pop ebp ; ret",  "\x89\xf9\x5d\xc3", 4},
  {0, 0, "mov %edi,%edx ; pop %ebp ; ret", "mov edx, edi ; pop ebp ; ret",  "\x89\xfa\x5d\xc3", 4},
  {0, 0, "mov %edi,%esi ; pop %ebp ; ret", "mov esi, edi ; pop ebp ; ret",  "\x89\xfe\x5d\xc3", 4},
  {0, 0, "mov (%eax),%ebx ; ret", "mov ebx, dword ptr [eax] ; ret",  "\x8b\x18\xc3", 3},
  {0, 0, "mov (%eax),%ecx ; ret", "mov ecx, dword ptr [eax] ; ret",  "\x8b\x08\xc3", 3},
  {0, 0, "mov (%eax),%edx ; ret", "mov edx, dword ptr [eax] ; ret",  "\x8b\x10\xc3", 3},
  {0, 0, "mov (%eax),%esi ; ret", "mov esi, dword ptr [eax] ; ret",  "\x8b\x30\xc3", 3},
  {0, 0, "mov (%eax),%edi ; ret", "mov edi, dword ptr [eax] ; ret",  "\x8b\x38\xc3", 3},
  {0, 0, "mov (%ebx),%eax ; ret", "mov eax, dword ptr [ebx] ; ret",  "\x8b\x03\xc3", 3},
  {0, 0, "mov (%ebx),%ebx ; ret", "mov ebx, dword ptr [ebx] ; ret",  "\x8b\x1b\xc3", 3},
  {0, 0, "mov (%ebx),%ecx ; ret", "mov ecx, dword ptr [ebx] ; ret",  "\x8b\x0b\xc3", 3},
  {0, 0, "mov (%ebx),%edx ; ret", "mov edx, dword ptr [ebx] ; ret",  "\x8b\x13\xc3", 3},
  {0, 0, "mov (%ebx),%esi ; ret", "mov esi, dword ptr [ebx] ; ret",  "\x8b\x33\xc3", 3},
  {0, 0, "mov (%ebx),%edi ; ret", "mov edi, dword ptr [ebx] ; ret",  "\x8b\x3b\xc3", 3},
  {0, 0, "mov (%ecx),%eax ; ret", "mov eax, dword ptr [ecx] ; ret",  "\x8b\x01\xc3", 3},
  {0, 0, "mov (%ecx),%ebx ; ret", "mov ebx, dword ptr [ecx] ; ret",  "\x8b\x19\xc3", 3},
  {0, 0, "mov (%ecx),%ecx ; ret", "mov ecx, dword ptr [ecx] ; ret",  "\x8b\x09\xc3", 3},
  {0, 0, "mov (%ecx),%edx ; ret", "mov edx, dword ptr [ecx] ; ret",  "\x8b\x11\xc3", 3},
  {0, 0, "mov (%ecx),%esi ; ret", "mov esi, dword ptr [ecx] ; ret",  "\x8b\x31\xc3", 3},
  {0, 0, "mov (%ecx),%edi ; ret", "mov edi, dword ptr [ecx] ; ret",  "\x8b\x39\xc3", 3},
  {0, 0, "mov (%edx),%eax ; ret", "mov eax, dword ptr [edx] ; ret",  "\x8b\x02\xc3", 3},
  {0, 0, "mov (%edx),%ebx ; ret", "mov ebx, dword ptr [edx] ; ret",  "\x8b\x1a\xc3", 3},
  {0, 0, "mov (%edx),%ecx ; ret", "mov edx, dword ptr [edx] ; ret",  "\x8b\x0a\xc3", 3},
  {0, 0, "mov (%edx),%edx ; ret", "mov ecx, dword ptr [edx] ; ret",  "\x8b\x12\xc3", 3},
  {0, 0, "mov (%edx),%esi ; ret", "mov esi, dword ptr [edx] ; ret",  "\x8b\x32\xc3", 3},
  {0, 0, "mov (%edx),%edi ; ret", "mov edi, dword ptr [edx] ; ret",  "\x8b\x3a\xc3", 3},
  {0, 0, "mov (%esi),%eax ; ret", "mov eax, dword ptr [esi] ; ret",  "\x8b\x06\xc3", 3},
  {0, 0, "mov (%esi),%ebx ; ret", "mov ebx, dword ptr [esi] ; ret",  "\x8b\x1e\xc3", 3},
  {0, 0, "mov (%esi),%ecx ; ret", "mov ecx, dword ptr [esi] ; ret",  "\x8b\x0e\xc3", 3},
  {0, 0, "mov (%esi),%edx ; ret", "mov edx, dword ptr [esi] ; ret",  "\x8b\x16\xc3", 3},
  {0, 0, "mov (%esi),%esi ; ret", "mov esi, dword ptr [esi] ; ret",  "\x8b\x36\xc3", 3},
  {0, 0, "mov (%esi),%edi ; ret", "mov edi, dword ptr [esi] ; ret",  "\x8b\x3e\xc3", 3},
  {0, 0, "mov (%edi),%eax ; ret", "mov eax, dword ptr [edi] ; ret",  "\x8b\x07\xc3", 3},
  {0, 0, "mov (%edi),%ebx ; ret", "mov ebx, dword ptr [edi] ; ret",  "\x8b\x1f\xc3", 3},
  {0, 0, "mov (%edi),%ecx ; ret", "mov ecx, dword ptr [edi] ; ret",  "\x8b\x0f\xc3", 3},
  {0, 0, "mov (%edi),%edx ; ret", "mov edx, dword ptr [edi] ; ret",  "\x8b\x17\xc3", 3},
  {0, 0, "mov (%edi),%esi ; ret", "mov esi, dword ptr [edi] ; ret",  "\x8b\x37\xc3", 3},
  {0, 0, "mov (%edi),%edi ; ret", "mov edi, dword ptr [edi] ; ret",  "\x8b\x3f\xc3", 3}, 
  {0, 0, "mov (%eax),%ebx ; pop %ebp ; ret", "mov ebx, dword ptr [eax] ; pop ebp ; ret",  "\x8b\x18\x5d\xc3", 4},
  {0, 0, "mov (%eax),%ecx ; pop %ebp ; ret", "mov ecx, dword ptr [eax] ; pop ebp ; ret",  "\x8b\x08\x5d\xc3", 4},
  {0, 0, "mov (%eax),%edx ; pop %ebp ; ret", "mov edx, dword ptr [eax] ; pop ebp ; ret",  "\x8b\x10\x5d\xc3", 4},
  {0, 0, "mov (%eax),%esi ; pop %ebp ; ret", "mov esi, dword ptr [eax] ; pop ebp ; ret",  "\x8b\x30\x5d\xc3", 4},
  {0, 0, "mov (%eax),%edi ; pop %ebp ; ret", "mov edi, dword ptr [eax] ; pop ebp ; ret",  "\x8b\x38\x5d\xc3", 4},
  {0, 0, "mov (%ebx),%eax ; pop %ebp ; ret", "mov eax, dword ptr [ebx] ; pop ebp ; ret",  "\x8b\x03\x5d\xc3", 4},
  {0, 0, "mov (%ebx),%ebx ; pop %ebp ; ret", "mov ebx, dword ptr [ebx] ; pop ebp ; ret",  "\x8b\x1b\x5d\xc3", 4},
  {0, 0, "mov (%ebx),%ecx ; pop %ebp ; ret", "mov ecx, dword ptr [ebx] ; pop ebp ; ret",  "\x8b\x0b\x5d\xc3", 4},
  {0, 0, "mov (%ebx),%edx ; pop %ebp ; ret", "mov edx, dword ptr [ebx] ; pop ebp ; ret",  "\x8b\x13\x5d\xc3", 4},
  {0, 0, "mov (%ebx),%esi ; pop %ebp ; ret", "mov esi, dword ptr [ebx] ; pop ebp ; ret",  "\x8b\x33\x5d\xc3", 4},
  {0, 0, "mov (%ebx),%edi ; pop %ebp ; ret", "mov edi, dword ptr [ebx] ; pop ebp ; ret",  "\x8b\x3b\x5d\xc3", 4},
  {0, 0, "mov (%ecx),%eax ; pop %ebp ; ret", "mov eax, dword ptr [ecx] ; pop ebp ; ret",  "\x8b\x01\x5d\xc3", 4},
  {0, 0, "mov (%ecx),%ebx ; pop %ebp ; ret", "mov ebx, dword ptr [ecx] ; pop ebp ; ret",  "\x8b\x19\x5d\xc3", 4},
  {0, 0, "mov (%ecx),%ecx ; pop %ebp ; ret", "mov ecx, dword ptr [ecx] ; pop ebp ; ret",  "\x8b\x09\x5d\xc3", 4},
  {0, 0, "mov (%ecx),%edx ; pop %ebp ; ret", "mov edx, dword ptr [ecx] ; pop ebp ; ret",  "\x8b\x11\x5d\xc3", 4},
  {0, 0, "mov (%ecx),%esi ; pop %ebp ; ret", "mov esi, dword ptr [ecx] ; pop ebp ; ret",  "\x8b\x31\x5d\xc3", 4},
  {0, 0, "mov (%ecx),%edi ; pop %ebp ; ret", "mov edi, dword ptr [ecx] ; pop ebp ; ret",  "\x8b\x39\x5d\xc3", 4},
  {0, 0, "mov (%edx),%eax ; pop %ebp ; ret", "mov eax, dword ptr [edx] ; pop ebp ; ret",  "\x8b\x02\x5d\xc3", 4},
  {0, 0, "mov (%edx),%ebx ; pop %ebp ; ret", "mov ebx, dword ptr [edx] ; pop ebp ; ret",  "\x8b\x1a\x5d\xc3", 4},
  {0, 0, "mov (%edx),%ecx ; pop %ebp ; ret", "mov edx, dword ptr [edx] ; pop ebp ; ret",  "\x8b\x0a\x5d\xc3", 4},
  {0, 0, "mov (%edx),%edx ; pop %ebp ; ret", "mov ecx, dword ptr [edx] ; pop ebp ; ret",  "\x8b\x12\x5d\xc3", 4},
  {0, 0, "mov (%edx),%esi ; pop %ebp ; ret", "mov esi, dword ptr [edx] ; pop ebp ; ret",  "\x8b\x32\x5d\xc3", 4},
  {0, 0, "mov (%edx),%edi ; pop %ebp ; ret", "mov edi, dword ptr [edx] ; pop ebp ; ret",  "\x8b\x3a\x5d\xc3", 4},
  {0, 0, "mov (%esi),%eax ; pop %ebp ; ret", "mov eax, dword ptr [esi] ; pop ebp ; ret",  "\x8b\x06\x5d\xc3", 4},
  {0, 0, "mov (%esi),%ebx ; pop %ebp ; ret", "mov ebx, dword ptr [esi] ; pop ebp ; ret",  "\x8b\x1e\x5d\xc3", 4},
  {0, 0, "mov (%esi),%ecx ; pop %ebp ; ret", "mov ecx, dword ptr [esi] ; pop ebp ; ret",  "\x8b\x0e\x5d\xc3", 4},
  {0, 0, "mov (%esi),%edx ; pop %ebp ; ret", "mov edx, dword ptr [esi] ; pop ebp ; ret",  "\x8b\x16\x5d\xc3", 4},
  {0, 0, "mov (%esi),%esi ; pop %ebp ; ret", "mov esi, dword ptr [esi] ; pop ebp ; ret",  "\x8b\x36\x5d\xc3", 4},
  {0, 0, "mov (%esi),%edi ; pop %ebp ; ret", "mov edi, dword ptr [esi] ; pop ebp ; ret",  "\x8b\x3e\x5d\xc3", 4},
  {0, 0, "mov (%edi),%eax ; pop %ebp ; ret", "mov eax, dword ptr [edi] ; pop ebp ; ret",  "\x8b\x07\x5d\xc3", 4},
  {0, 0, "mov (%edi),%ebx ; pop %ebp ; ret", "mov ebx, dword ptr [edi] ; pop ebp ; ret",  "\x8b\x1f\x5d\xc3", 4},
  {0, 0, "mov (%edi),%ecx ; pop %ebp ; ret", "mov ecx, dword ptr [edi] ; pop ebp ; ret",  "\x8b\x0f\x5d\xc3", 4},
  {0, 0, "mov (%edi),%edx ; pop %ebp ; ret", "mov edx, dword ptr [edi] ; pop ebp ; ret",  "\x8b\x17\x5d\xc3", 4},
  {0, 0, "mov (%edi),%esi ; pop %ebp ; ret", "mov esi, dword ptr [edi] ; pop ebp ; ret",  "\x8b\x37\x5d\xc3", 4},
  {0, 0, "mov (%edi),%edi ; pop %ebp ; ret", "mov edi, dword ptr [edi] ; pop ebp ; ret",  "\x8b\x3f\x5d\xc3", 4},
  {0, 0, "mov %eax,(%edx) ; ret", "mov dword ptr [edx], eax ; ret",  "\x89\x02\xc3", 3},
  {0, 0, "mov %eax,(%ebx) ; ret", "mov dword ptr [ebx], eax ; ret",  "\x89\x03\xc3", 3},
  {0, 0, "mov %eax,(%ecx) ; ret", "mov dword ptr [ecx], eax ; ret",  "\x89\x01\xc3", 3},
  {0, 0, "mov %eax,(%esi) ; ret", "mov dword ptr [esi], eax ; ret",  "\x89\x06\xc3", 3},
  {0, 0, "mov %eax,(%edi) ; ret", "mov dword ptr [edi], eax ; ret",  "\x89\x07\xc3", 3},
  {0, 0, "mov %ebx,(%eax) ; ret", "mov dword ptr [eax], ebx ; ret",  "\x89\x18\xc3", 3},
  {0, 0, "mov %ebx,(%ecx) ; ret", "mov dword ptr [ecx], ebx ; ret",  "\x89\x19\xc3", 3},
  {0, 0, "mov %ebx,(%edx) ; ret", "mov dword ptr [edx], ebx ; ret",  "\x89\x1a\xc3", 3},
  {0, 0, "mov %ebx,(%esi) ; ret", "mov dword ptr [esi], ebx ; ret",  "\x89\x1e\xc3", 3},
  {0, 0, "mov %ebx,(%edi) ; ret", "mov dword ptr [edi], ebx ; ret",  "\x89\x1f\xc3", 3},
  {0, 0, "mov %ecx,(%eax) ; ret", "mov dword ptr [eax], ecx ; ret",  "\x89\x08\xc3", 3},
  {0, 0, "mov %ecx,(%ebx) ; ret", "mov dword ptr [ebx], ecx",  "\x89\x0b\xc3", 3},
  {0, 0, "mov %ecx,(%edx) ; ret", "mov dword ptr [edx], ecx",  "\x89\x0a\xc3", 3},
  {0, 0, "mov %ecx,(%esi) ; ret", "mov dword ptr [esi], ecx",  "\x89\x0e\xc3", 3},
  {0, 0, "mov %ecx,(%edi) ; ret", "mov dword ptr [edi], ecx",  "\x89\x0f\xc3", 3},
  {0, 0, "mov %edx,(%eax) ; ret", "mov dword ptr [eax], edx",  "\x89\x10\xc3", 3},
  {0, 0, "mov %edx,(%ebx) ; ret", "mov dword ptr [ebx], edx",  "\x89\x13\xc3", 3},
  {0, 0, "mov %edx,(%ecx) ; ret", "mov dword ptr [ecx], edx",  "\x89\x11\xc3", 3},
  {0, 0, "mov %edx,(%esi) ; ret", "mov dword ptr [esi], edx",  "\x89\x16\xc3", 3},
  {0, 0, "mov %edx,(%edi) ; ret", "mov dword ptr [edi], edx",  "\x89\x17\xc3", 3},
  {0, 0, "mov (%esp),%eax ; ret", "mov eax, dword ptr [esp] ; ret",  "\x8b\x04\x24\xc3", 4},
  {0, 0, "mov (%esp),%ebx ; ret", "mov ebx, dword ptr [esp] ; ret",  "\x8b\x1c\x24\xc3", 4},
  {0, 0, "mov (%esp),%ecx ; ret", "mov ecx, dword ptr [esp] ; ret",  "\x8b\x0c\x24\xc3", 4},
  {0, 0, "mov (%esp),%edx ; ret", "mov edx, dword ptr [esp] ; ret",  "\x8b\x14\x24\xc3", 4},
  {0, 0, "mov (%esp),%esi ; ret", "mov esi, dword ptr [esp] ; ret",  "\x8b\x34\x24\xc3", 4},
  {0, 0, "mov (%esp),%edi ; ret", "mov edi, dword ptr [esp] ; ret",  "\x8b\x3c\x24\xc3", 4},
  {0, 0, "mov (%esp),%ebp ; ret", "mov ebp, dword ptr [esp] ; ret",  "\x8b\x2c\x24\xc3", 4},
  {0, 0, "mov %eax,(%edx) ; pop %ebp ; ret", "mov dword ptr [edx], eax ; pop ebp ; ret",  "\x89\x02\x5d\xc3", 4},
  {0, 0, "mov %eax,(%ebx) ; pop %ebp ; ret", "mov dword ptr [ebx], eax ; pop ebp ; ret",  "\x89\x03\x5d\xc3", 4},
  {0, 0, "mov %eax,(%ecx) ; pop %ebp ; ret", "mov dword ptr [ecx], eax ; pop ebp ; ret",  "\x89\x01\x5d\xc3", 4},
  {0, 0, "mov %eax,(%esi) ; pop %ebp ; ret", "mov dword ptr [esi], eax ; pop ebp ; ret",  "\x89\x06\x5d\xc3", 4},
  {0, 0, "mov %eax,(%edi) ; pop %ebp ; ret", "mov dword ptr [edi], eax ; pop ebp ; ret",  "\x89\x07\x5d\xc3", 4},
  {0, 0, "mov %ebx,(%eax) ; pop %ebp ; ret", "mov dword ptr [eax], ebx ; pop ebp ; ret",  "\x89\x18\x5d\xc3", 4},
  {0, 0, "mov %ebx,(%ecx) ; pop %ebp ; ret", "mov dword ptr [ecx], ebx ; pop ebp ; ret",  "\x89\x19\x5d\xc3", 4},
  {0, 0, "mov %ebx,(%edx) ; pop %ebp ; ret", "mov dword ptr [edx], ebx ; pop ebp ; ret",  "\x89\x1a\x5d\xc3", 4},
  {0, 0, "mov %ebx,(%esi) ; pop %ebp ; ret", "mov dword ptr [esi], ebx ; pop ebp ; ret",  "\x89\x1e\x5d\xc3", 4},
  {0, 0, "mov %ebx,(%edi) ; pop %ebp ; ret", "mov dword ptr [edi], ebx ; pop ebp ; ret",  "\x89\x1f\x5d\xc3", 4},
  {0, 0, "mov %ecx,(%eax) ; pop %ebp ; ret", "mov dword ptr [eax], ecx ; pop ebp ; ret",  "\x89\x08\x5d\xc3", 4},
  {0, 0, "mov %ecx,(%ebx) ; pop %ebp ; ret", "mov dword ptr [ebx], ecx ; pop ebp ; ret",  "\x89\x0b\x5d\xc3", 4},
  {0, 0, "mov %ecx,(%edx) ; pop %ebp ; ret", "mov dword ptr [edx], ecx ; pop ebp ; ret",  "\x89\x0a\x5d\xc3", 4},
  {0, 0, "mov %ecx,(%esi) ; pop %ebp ; ret", "mov dword ptr [esi], ecx ; pop ebp ; ret",  "\x89\x0e\x5d\xc3", 4},
  {0, 0, "mov %ecx,(%edi) ; pop %ebp ; ret", "mov dword ptr [edi], ecx ; pop ebp ; ret",  "\x89\x0f\x5d\xc3", 4},
  {0, 0, "mov %edx,(%eax) ; pop %ebp ; ret", "mov dword ptr [eax], edx ; pop ebp ; ret",  "\x89\x10\x5d\xc3", 4},
  {0, 0, "mov %edx,(%ebx) ; pop %ebp ; ret", "mov dword ptr [ebx], edx ; pop ebp ; ret",  "\x89\x13\x5d\xc3", 4},
  {0, 0, "mov %edx,(%ecx) ; pop %ebp ; ret", "mov dword ptr [ecx], edx ; pop ebp ; ret",  "\x89\x11\x5d\xc3", 4},
  {0, 0, "mov %edx,(%esi) ; pop %ebp ; ret", "mov dword ptr [esi], edx ; pop ebp ; ret",  "\x89\x16\x5d\xc3", 4},
  {0, 0, "mov %edx,(%edi) ; pop %ebp ; ret", "mov dword ptr [edi], edx ; pop ebp ; ret",  "\x89\x17\x5d\xc3", 4},
  {0, 0, "mov %edx,%eax ; pop %ebx ; pop %esi ; pop %edi ; pop %ebp ; ret", 
         "mov eax, edx ; pop ebx ; pop esi ; pop edi ; pop ebp ; ret",  "\x89\xd0\x5b\x5e\x5f\x5d\xc3", 7},
  {0, 0, "mov %eax,%edi ; mov %edi,%eax ; pop %edi ; pop %ebp ; ret", 
         "mov edi, eax ; mov eax, edi ; pop edi ; pop ebp ; ret",  "\x89\xc7\x89\xf8\x5f\x5d\xc3", 7},
  {0, 0, "mov (%edx),%eax ; mov (%esp),%ebx ; mov %ebp,%esp ; pop %ebp ; ret", 
         "add eax, dword ptr [edx] ; mov ebx, dword ptr [esp] ; mov esp, ebp ; pop ebp ; ret",  "\x03\x02\x8b\x1c\x24\x89\xec\x5d\xc3", 9},
  {0, 0, "mov %eax,(%edi) ; pop %eax ; pop %ebx ; pop %esi ; pop %edi ; ret", 
         "mov dword ptr [edi], eax ; pop eax ; pop ebx ; pop esi ; pop edi ; ret",  "\x89\x07\x58\x5b\x5e\x5f\xc3", 7},
  {0, 0, "mov %ebx,(%edi) ; pop %ebx ; pop %esi ; pop %edi ; ret", 
         "mov dword ptr [edi], ebx ; pop ebx ; pop esi ; pop edi ; ret",  "\x89\x1f\x5b\x5e\x5f\xc3", 6},
  {0, 0, "mov %eax,(%ecx) ; mov %ebx,%eax ; pop %ebx ; pop %ebp ; ret", 
         "mov dword ptr [ecx], eax ; mov eax, ebx ; pop ebx ; pop ebp ; ret",  "\x89\x01\x89\xd8\x5b\x5d\xc3", 7},
  {0, 0, "mov %ebp,%eax ; pop %ebx ; pop %esi ; pop %edi ; pop %ebp ; ret", 
         "mov eax, ebp ; pop ebx ; pop esi ; pop edi ; pop ebp ; ret",  "\x89\xe8\x5b\x5e\x5f\x5d\xc3", 7},
  {0, 0, "mov %ebx,%eax ; pop %ebx ; pop %esi ; pop %edi ; ret", "mov eax, ebx ; pop ebx ; pop esi ; pop edi ; ret",  "\x89\xd8\x5b\x5e\x5f\xc3", 6},
  {0, 0, "mov %edi,%eax ; pop %ebx ; pop %esi ; pop %edi ; ret", "mov eax, edi ; pop ebx ; pop esi ; pop edi ; ret",  "\x89\xf8\x5b\x5e\x5f\xc3", 6},
  {0, 0, "mov %ebx,%eax ; pop %ebx ; ret", "mov eax, ebx ; pop ebx ; ret",  "\x89\xd8\x5b\xc3", 4},
  /* EOF hard opcode */

  /*
  ** Variable opcode
  ** ---------------
  **
  ** '?' is for 1 any byte direct value
  ** '#' if for 4 any bytes direct value
  */
  {0, 0, "add $0x?,%al | ret", "add al, 0x? ; ret",  "\x04?\xc3", 3},
  {0, 0, "add $0x?,%bl | ret", "add bl, 0x? ; ret",  "\x80\xc3?\xc3", 4},
  {0, 0, "add $0x?,%cl | ret", "add vl, 0x? ; ret",  "\x80\xc1?\xc3", 4},
  {0, 0, "add $0x?,%dl | ret", "add dl, 0x? ; ret",  "\x80\xc2?\xc3", 4},
  {0, 0, "add $0x?,%ax | ret", "add al, 0x? ; ret",  "\x66\x83\xc0?\xc3", 5},
  {0, 0, "add $0x?,%bx | ret", "add bx, 0x? ; ret",  "\x66\x83\xc3?\xc3", 5},
  {0, 0, "add $0x?,%cx | ret", "add cx, 0x? ; ret",  "\x66\x83\xc1?\xc3", 5},
  {0, 0, "add $0x?,%dx | ret", "add dx, 0x? ; ret",  "\x66\x83\xc2?\xc3", 5},
  {0, 0, "add $0x?,%eax | ret", "add eax, 0x? ; ret",  "\x83\xc0?\xc3", 4},
  {0, 0, "add $0x?,%ebx | ret", "add ebx, 0x? ; ret",  "\x83\xc3?\xc3", 4},
  {0, 0, "add $0x?,%ecx | ret", "add ecx, 0x? ; ret",  "\x83\xc1?\xc3", 4},
  {0, 0, "add $0x?,%edx | ret", "add edx, 0x? ; ret",  "\x83\xc2?\xc3", 4},
  {0, 0, "add $0x?,%esi | ret", "add esi, 0x? ; ret",  "\x83\xc6?\xc3", 4},
  {0, 0, "add $0x?,%edi | ret", "add edi, 0x? ; ret",  "\x83\xc7?\xc3", 4},
  {0, 0, "add $0x?,%ebp | ret", "add ebp, 0x? ; ret",  "\x83\xc5?\xc3", 4},
  {0, 0, "add $0x?,%esp | ret", "add esp, 0x? ; ret",  "\x83\xc4?\xc3", 4},
  {0, 0, "add $0x?,%esp | pop %ebp ; ret", "add esp, 0x? ; pop ebp ; ret",  "\x83\xc4?\x5d\xc3", 5},
  {0, 0, "add $0x?,%esp | pop %ebx ; ret", "add esp, 0x? ; pop ebx ; ret",  "\x83\xc4?\x5b\xc3", 5},
  {0, 0, "add $0x?,%esp | pop %ebx ; pop %ebp ; ret", 
         "add esp, 0x? ; pop ebx ; pop ebp ; ret",  "\x83\xc4?\x5b\x5d\xc3", 6},
  {0, 0, "sub $0x?,%al | ret", "sub al, 0x? ; ret",  "\x2c?\xc3", 3},
  {0, 0, "sub $0x?,%bl | ret", "sub bl, 0x? ; ret",  "\x80\xeb?\xc3", 4},
  {0, 0, "sub $0x?,%cl | ret", "sub vl, 0x? ; ret",  "\x80\xe9?\xc3", 4},
  {0, 0, "sub $0x?,%dl | ret", "sub dl, 0x? ; ret",  "\x80\xea?\xc3", 4},
  {0, 0, "sub $0x?,%ax | ret", "sub al, 0x? ; ret",  "\x66\x83\xe8?\xc3", 5},
  {0, 0, "sub $0x?,%bx | ret", "sub bx, 0x? ; ret",  "\x66\x83\xeb?\xc3", 5},
  {0, 0, "sub $0x?,%cx | ret", "sub cx, 0x? ; ret",  "\x66\x83\xe9?\xc3", 5},
  {0, 0, "sub $0x?,%dx | ret", "sub dx, 0x? ; ret",  "\x66\x83\xea?\xc3", 5},
  {0, 0, "sub $0x?,%eax | ret", "sub eax, 0x? ; ret",  "\x83\xe8?\xc3", 4},
  {0, 0, "sub $0x?,%ebx | ret", "sub ebx, 0x? ; ret",  "\x83\xeb?\xc3", 4},
  {0, 0, "sub $0x?,%ecx | ret", "sub ecx, 0x? ; ret",  "\x83\xe9?\xc3", 4},
  {0, 0, "sub $0x?,%edx | ret", "sub edx, 0x? ; ret",  "\x83\xea?\xc3", 4},
  {0, 0, "sub $0x?,%esi | ret", "sub esi, 0x? ; ret",  "\x83\xee?\xc3", 4},
  {0, 0, "sub $0x?,%edi | ret", "sub edi, 0x? ; ret",  "\x83\xef?\xc3", 4},
  {0, 0, "sub $0x?,%ebp | ret", "sub ebp, 0x? ; ret",  "\x83\xed?\xc3", 4},
  {0, 0, "sub $0x?,%esp | ret", "sub esp, 0x? ; ret",  "\x83\xec?\xc3", 4},
  {0, 0, "sub $0x?,%ebx ; call *%eax", "sub ebx, 0x? ; call eax",  "\x83\xeb?\xff\xd0", 5},
  {0, 0, "mov $0x?,%al | ret", "mov al, 0x? ; ret",  "\xb0?\xc3", 3},
  {0, 0, "mov $0x?,%bl | ret", "mov bl, 0x? ; ret",  "\xb3?\xc3", 3},
  {0, 0, "mov $0x?,%cl | ret", "mov cl, 0x? ; ret",  "\xb2?\xc3", 3},
  {0, 0, "mov $0x?,%dl | ret", "mov dl, 0x? ; ret",  "\xb1?\xc3", 3},
  {0, 0, "xor $0x?,%eax | ret", "xor eax, 0x? ; ret",  "\x83\xf0?\xc3", 4},
  {0, 0, "xor $0x?,%ebx | ret", "xor ebx, 0x? ; ret",  "\x83\xf3?\xc3", 4},
  {0, 0, "xor $0x?,%ecx | ret", "xor ecx, 0x? ; ret",  "\x83\xf1?\xc3", 4},
  {0, 0, "xor $0x?,%edx | ret", "xor edx, 0x? ; ret",  "\x83\xf2?\xc3", 4},
  {0, 0, "xor $0x?,%esi | ret", "xor esi, 0x? ; ret",  "\x83\xf6?\xc3", 4},
  {0, 0, "xor $0x?,%edi | ret", "xor edi, 0x? ; ret",  "\x83\xf7?\xc3", 4},
  {0, 0, "xor $0x?,%eax | pop %ebp ; ret", "xor eax, 0x? ; pop ebp ; ret",  "\x83\xf0?\x5d\xc3", 4},
  {0, 0, "xor $0x?,%ebx | pop %ebp ; ret", "xor ebx, 0x? ; pop ebp ; ret",  "\x83\xf3?\x5d\xc3", 4},
  {0, 0, "xor $0x?,%ecx | pop %ebp ; ret", "xor ecx, 0x? ; pop ebp ; ret",  "\x83\xf1?\x5d\xc3", 4},
  {0, 0, "xor $0x?,%edx | pop %ebp ; ret", "xor edx, 0x? ; pop ebp ; ret",  "\x83\xf2?\x5d\xc3", 4},
  {0, 0, "xor $0x?,%esi | pop %ebp ; ret", "xor esi, 0x? ; pop ebp ; ret",  "\x83\xf6?\x5d\xc3", 4},
  {0, 0, "xor $0x?,%edi | pop %ebp ; ret", "xor edi, 0x? ; pop ebp ; ret",  "\x83\xf7?\x5d\xc3", 4},

  /* 4 any bytes */
  {0, 0, "mov $0x#,%eax | ret", "mov eax, 0x# ; ret",  "\xb8####\xc3", 6},
  {0, 0, "mov $0x#,%ebx | ret", "mov ebx, 0x# ; ret",  "\xbb####\xc3", 6},
  {0, 0, "mov $0x#,%ecx | ret", "mov ecx, 0x# ; ret",  "\xb9####\xc3", 6},
  {0, 0, "mov $0x#,%edx | ret", "mov edx, 0x# ; ret",  "\xba####\xc3", 6},
  {0, 0, "mov $0x#,%esi | ret", "mov esi, 0x# ; ret",  "\xbe####\xc3", 6},
  {0, 0, "mov $0x#,%edi | ret", "mov edi, 0x# ; ret",  "\xbf####\xc3", 6},
  {0, 0, "mov $0x#,%ebp | ret", "mov ebp, 0x# ; ret",  "\xbd####\xc3", 6},
  {0, 0, "mov $0x#,%esp | ret", "mov esp, 0x# ; ret",  "\xbc####\xc3", 6},
  {0, 0, "mov $0x#,%eax | pop %ebp ; ret", "mov eax, 0x# ; pop ebp ; ret",  "\xb8####\x5d\xc3", 7},
  {0, 0, "mov $0x#,%ebx | pop %ebp ; ret", "mov ebx, 0x# ; pop ebp ; ret",  "\xbb####\x5d\xc3", 7},
  {0, 0, "mov $0x#,%ecx | pop %ebp ; ret", "mov ecx, 0x# ; pop ebp ; ret",  "\xb9####\x5d\xc3", 7},
  {0, 0, "mov $0x#,%edx | pop %ebp ; ret", "mov edx, 0x# ; pop ebp ; ret",  "\xba####\x5d\xc3", 7},
  {0, 0, "mov $0x#,%esi | pop %ebp ; ret", "mov esi, 0x# ; pop ebp ; ret",  "\xbe####\x5d\xc3", 7},
  {0, 0, "mov $0x#,%edi | pop %ebp ; ret", "mov edi, 0x# ; pop ebp ; ret",  "\xbf####\x5d\xc3", 7},
  {0, 0, "mov $0x#,%ebp | pop %ebp ; ret", "mov ebp, 0x# ; pop ebp ; ret",  "\xbd####\x5d\xc3", 7},
  {0, 0, "mov $0x#,%esp | pop %ebp ; ret", "mov esp, 0x# ; pop ebp ; ret",  "\xbc####\x5d\xc3", 7},
  {0, 0, "xor $0x#,%eax | ret", "xor eax, 0x# ; ret",  "\x35####\xc3", 6},
  {0, 0, "xor $0x#,%ebx | ret", "xor ebx, 0x# ; ret",  "\x81\xf3####\xc3", 7},
  {0, 0, "xor $0x#,%ecx | ret", "xor ecx, 0x# ; ret",  "\x81\xf1####\xc3", 7},
  {0, 0, "xor $0x#,%edx | ret", "xor edx, 0x# ; ret",  "\x81\xf2####\xc3", 7},
  {0, 0, "xor $0x#,%esi | ret", "xor esi, 0x# ; ret",  "\x81\xf6####\xc3", 7},
  {0, 0, "xor $0x#,%edi | ret", "xor edi, 0x# ; ret",  "\x81\xf7####\xc3", 7},
  {0, 0, "xor $0x#,%eax | pop %ebp ; ret", "xor eax, 0x# ; pop ebp ; ret",  "\x35####\x5d\xc3", 7},
  {0, 0, "xor $0x#,%ebx | pop %ebp ; ret", "xor ebx, 0x# ; pop ebp ; ret",  "\x81\xf3####\x5d\xc3", 8},
  {0, 0, "xor $0x#,%ecx | pop %ebp ; ret", "xor ecx, 0x# ; pop ebp ; ret",  "\x81\xf1####\x5d\xc3", 8},
  {0, 0, "xor $0x#,%edx | pop %ebp ; ret", "xor edx, 0x# ; pop ebp ; ret",  "\x81\xf2####\x5d\xc3", 8},
  {0, 0, "xor $0x#,%esi | pop %ebp ; ret", "xor esi, 0x# ; pop ebp ; ret",  "\x81\xf6####\x5d\xc3", 8},
  {0, 0, "xor $0x#,%edi | pop %ebp ; ret", "xor edi, 0x# ; pop ebp ; ret",  "\x81\xf7####\x5d\xc3", 8},
  {0, 0, "add $0x#,%eax | ret", "add eax, 0x# ; ret",  "\x05####\xc3", 6},
  {0, 0, "add $0x#,%ebx | ret", "add ebx, 0x# ; ret",  "\x81\xc3####\xc3", 7},
  {0, 0, "add $0x#,%ecx | ret", "add ecx, 0x# ; ret",  "\x81\xc1####\xc3", 7},
  {0, 0, "add $0x#,%edx | ret", "add edx, 0x# ; ret",  "\x81\xc2####\xc3", 7},
  {0, 0, "add $0x#,%esi | ret", "add esi, 0x# ; ret",  "\x81\xc6####\xc3", 7},
  {0, 0, "add $0x#,%edi | ret", "add edi, 0x# ; ret",  "\x81\xc7####\xc3", 7},
  {0, 0, "add $0x#,%eax | pop %ebp ; ret", "add eax, 0x# ; pop ebp ; ret",  "\x05####\x5d\xc3", 7},
  {0, 0, "add $0x#,%ebx | pop %ebp ; ret", "add ebx, 0x# ; pop ebp ; ret",  "\x81\xc3####\x5d\xc3", 8},
  {0, 0, "add $0x#,%ecx | pop %ebp ; ret", "add ecx, 0x# ; pop ebp ; ret",  "\x81\xc1####\x5d\xc3", 8},
  {0, 0, "add $0x#,%edx | pop %ebp ; ret", "add edx, 0x# ; pop ebp ; ret",  "\x81\xc2####\x5d\xc3", 8},
  {0, 0, "add $0x#,%esi | pop %ebp ; ret", "add esi, 0x# ; pop ebp ; ret",  "\x81\xc6####\x5d\xc3", 8},
  {0, 0, "add $0x#,%edi | pop %ebp ; ret", "add edi, 0x# ; pop ebp ; ret",  "\x81\xc7####\x5d\xc3", 8},
  {0, 0, "sub $0x#,%eax | ret", "sub eax, 0x# ; ret",  "\x2d####\xc3", 6},
  {0, 0, "sub $0x#,%ebx | ret", "sub ebx, 0x# ; ret",  "\x81\xeb####\xc3", 7},
  {0, 0, "sub $0x#,%ecx | ret", "sub ecx, 0x# ; ret",  "\x81\xe9####\xc3", 7},
  {0, 0, "sub $0x#,%edx | ret", "sub edx, 0x# ; ret",  "\x81\xea####\xc3", 7},
  {0, 0, "sub $0x#,%esi | ret", "sub esi, 0x# ; ret",  "\x81\xee####\xc3", 7},
  {0, 0, "sub $0x#,%edi | ret", "sub edi, 0x# ; ret",  "\x81\xef####\xc3", 7},
  {0, 0, "sub $0x#,%eax | pop %ebp ; ret", "sub eax, 0x# ; pop ebp ; ret",  "\x2d####\x5d\xc3", 7},
  {0, 0, "sub $0x#,%ebx | pop %ebp ; ret", "sub ebx, 0x# ; pop ebp ; ret",  "\x81\xeb####\x5d\xc3", 8},
  {0, 0, "sub $0x#,%ecx | pop %ebp ; ret", "sub ecx, 0x# ; pop ebp ; ret",  "\x81\xe9####\x5d\xc3", 8},
  {0, 0, "sub $0x#,%edx | pop %ebp ; ret", "sub edx, 0x# ; pop ebp ; ret",  "\x81\xea####\x5d\xc3", 8},
  {0, 0, "sub $0x#,%esi | pop %ebp ; ret", "sub esi, 0x# ; pop ebp ; ret",  "\x81\xee####\x5d\xc3", 8},
  {0, 0, "sub $0x#,%edi | pop %ebp ; ret", "sub edi, 0x# ; pop ebp ; ret",  "\x81\xef####\x5d\xc3", 8},
  /* EOF variable opcode */

  {0, 0, NULL, NULL, NULL, 0}
};

void gadget_x8632(unsigned char *data, unsigned int cpt, Elf32_Addr offset, int i, t_maps_exec *maps_exec)
{
  char *varopins  = NULL;
  char *syntax = NULL;

  /* set display syntax */
  if (syntaxins.type == INTEL)
    syntax = tab_x8632[i].instruction_intel;
  else
    syntax = tab_x8632[i].instruction;

  if (importsc_mode.flag == 1 && !check_exec_maps(maps_exec, (Elf32_Addr)(cpt + offset)))
    save_octet(data, (Elf32_Addr)(cpt + offset));

  if(!match2((const char *)data, tab_x8632[i].value, tab_x8632[i].size)
     && !check_exec_maps(maps_exec, (Elf32_Addr)(cpt + offset)))
    {
      /* no '?' & no '#' */
      if (!check_interrogation(syntax))
        fprintf(stdout, "%s0x%.8x%s: %s%s%s\n", RED, (cpt + offset), ENDC, GREEN, syntax, ENDC);
      /* if '?' */
      else if (interrogation_or_diese(syntax) == 1)
        {
          varopins = ret_instruction_interrogation((pMapElf + cpt), syntax, tab_x8632[i].value, tab_x8632[i].size);
          if (!check_if_varop_was_printed(varopins))
            {
              fprintf(stdout, "%s0x%.8x%s: %s%s%s\n", RED, (cpt + offset), ENDC, GREEN, varopins, ENDC);
              pVarop = add_element_varop(pVarop, varopins, (cpt + offset));
            }
          else
            {
              free(varopins);
              NbGadFound--;
            }
        }
      /* if '#' */
      else if (interrogation_or_diese(syntax) == 2)
        {
          varopins = ret_instruction_diese((pMapElf + cpt), syntax, tab_x8632[i].value, tab_x8632[i].size);
          if (!check_if_varop_was_printed(varopins))
            {
              fprintf(stdout, "%s0x%.8x%s: %s%s%s\n", RED, (cpt + offset), ENDC, GREEN, varopins, ENDC);
              pVarop = add_element_varop(pVarop, varopins, (cpt + offset));
            }
          else
            {
              free(varopins);
              NbGadFound--;
            }
        }

      if (!check_interrogation(syntax))
        tab_x8632[i].flag = 1;
      tab_x8632[i].addr = (Elf32_Addr)(cpt + offset);
      NbGadFound++;
      NbTotalGadFound++;
    }
}

void x8632(unsigned char *data, unsigned int size_data, t_maps_exec *maps_exec, t_maps_read *maps_read)
{
  int i              = 0;
  unsigned int cpt   = 0;
  Elf32_Addr  offset;
  char *real_string;

  pGadgets = tab_x8632;
  NbTotalGadFound = 0;
  NbGadFound = 0;
  pVarop = NULL;
  importsc_mode.poctet = NULL;
  offset = (pElf32_Phdr->p_vaddr - pElf32_Phdr->p_offset); /* base addr */
  cpt = set_cpt_if_mapmode(cpt); /* mapmode */
  while(cpt < size_data && (int)NbGadFound != limitmode.value && (int)NbTotalGadFound != limitmode.value && !check_end_mapmode(cpt))
    {
      i = 0;
      /* opcode mode */
      if (opcode_mode.flag == 1)
        {
          if(!search_opcode((const char *)data, (char *)opcode_mode.opcode, opcode_mode.size)
            && !check_exec_maps(maps_exec, (Elf32_Addr)(cpt + offset)))
            {
              fprintf(stdout, "%s0x%.8x%s: \"%s", RED, (cpt + offset), ENDC, GREEN);
              print_opcode();
              fprintf(stdout, "%s\"\n", ENDC);
              NbTotalGadFound++;
            }
        }
      /* string mode */
      else if (stringmode.flag == 1)
        {
          if(!match2((const char *)data, (char *)stringmode.string, stringmode.size)
              && !check_read_maps(maps_read, (Elf32_Addr)(cpt + offset)))
            {
              real_string = real_string_stringmode(stringmode.string, data);
              fprintf(stdout, "%s0x%.8x%s: \"%s", RED, (cpt + offset), ENDC, GREEN);
              print_real_string(real_string);
              fprintf(stdout, "%s\"\n", ENDC);
              NbTotalGadFound++;
              free(real_string);
            }
        }
      /* simple gadget mode */
      else
        {
          while (i <= (int)NB_GADGET)
            {
              if (syntaxins.type == INTEL)
                {
                  if (pGadgets[i].flag != 1 && !no_filtered(pGadgets[i].instruction_intel) && onlymode(pGadgets[i].instruction_intel))
                    gadget_x8632(data, cpt, offset, i, maps_exec);
                }
              else
                {
                  if (pGadgets[i].flag != 1 && !no_filtered(pGadgets[i].instruction) && onlymode(pGadgets[i].instruction))
                    gadget_x8632(data, cpt, offset, i, maps_exec);
                }
              i++;
            }
        }

      cpt++;
      data++;
    }
  how_many_found();
}

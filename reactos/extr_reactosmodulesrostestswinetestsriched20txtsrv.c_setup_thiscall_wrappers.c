#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */

__attribute__((used)) static void setup_thiscall_wrappers(void)
{
#ifdef __i386__
    void** pVtable;
    void** pVtableEnd;
    THISCALL_TO_STDCALL_THUNK *thunk;
    STDCALL_TO_THISCALL_THUNK *thunk2;

    wrapperCodeMem = VirtualAlloc(NULL,
                                  (sizeof(ITextHostVtbl)/sizeof(void*) - 3)
                                    * sizeof(THISCALL_TO_STDCALL_THUNK)
                                  +(sizeof(ITextServicesVtbl)/sizeof(void*) - 3)
                                    * sizeof(STDCALL_TO_THISCALL_THUNK),
                                  MEM_COMMIT, PAGE_EXECUTE_READWRITE);
    thunk = wrapperCodeMem;

    /* Wrap all ITextHostImpl methods with code to perform a thiscall to
     * stdcall conversion. The thiscall calling convention places the This
     * pointer in ecx on the x86 platform, and the stdcall calling convention
     * pushes the This pointer on the stack as the first argument.
     *
     * The byte code does the conversion then jumps to the real function.
     *
     * Each wrapper needs to be modified so that the function to jump to is
     * modified in the byte code. */

    /* Skip QueryInterface, AddRef, and Release native actually
     * defined them with the stdcall calling convention. */
    pVtable = (void**)&itextHostVtbl + 3;
    pVtableEnd = (void**)(&itextHostVtbl + 1);
    while (pVtable != pVtableEnd) {
        /* write byte code to executable memory */
        thunk->pop_eax = 0x58;  /* popl  %eax  */
        thunk->push_ecx = 0x51; /* pushl %ecx  */
        thunk->push_eax = 0x50; /* pushl %eax  */
        thunk->jmp_func = 0xe9; /* jmp   $func */
        /* The address needs to be relative to the end of the jump instructions. */
        thunk->func = (char*)*pVtable - (char*)(&thunk->func + 1);
        *pVtable = thunk;
        pVtable++;
        thunk++;
    }

    /* Setup an ITextServices standard call vtable that will call the
     * native thiscall vtable when the methods are called. */

    /* QueryInterface, AddRef, and Release should be called directly on the
     * real vtable since they use the stdcall calling convention. */
    thunk2 = (STDCALL_TO_THISCALL_THUNK *)thunk;
    pVtable = (void**)&itextServicesStdcallVtbl + 3;
    pVtableEnd = (void**)(&itextServicesStdcallVtbl + 1);
    while (pVtable != pVtableEnd) {
        /* write byte code to executable memory */
        thunk2->pop_eax = 0x58;               /* popl  %eax */
        thunk2->pop_ecx = 0x59;               /* popl  %ecx */
        thunk2->push_eax = 0x50;              /* pushl %eax */
        thunk2->mov_vtable_eax[0] = 0x8b;     /* movl (%ecx), %eax */
        thunk2->mov_vtable_eax[1] = 0x01;
        thunk2->jmp_eax[0] = 0xff;            /* jmp *$vtablefunc_offset(%eax) */
        thunk2->jmp_eax[1] = 0xa0;
        thunk2->vtablefunc_offset = (char*)pVtable - (char*)&itextServicesStdcallVtbl;
        *pVtable = thunk2;
        pVtable++;
        thunk2++;
    }
#endif /* __i386__ */
}
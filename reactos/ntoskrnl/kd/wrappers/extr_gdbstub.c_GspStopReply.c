#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int ULONG ;
struct TYPE_4__ {int /*<<< orphan*/  Eip; int /*<<< orphan*/  Ebp; } ;
typedef  TYPE_1__* PKTRAP_FRAME ;
typedef  char* PCHAR ;
typedef  int NTSTATUS ;
typedef  int /*<<< orphan*/  LONG ;

/* Variables and functions */
 size_t EBP ; 
 size_t ESP ; 
 int /*<<< orphan*/  GspGetEspFromTrapFrame (TYPE_1__*) ; 
 char* GspMem2Hex (char*,char*,int,int /*<<< orphan*/ ) ; 
 char* GspOutBuffer ; 
 void** HexChars ; 
 size_t PC ; 
#define  STATUS_ACCESS_VIOLATION 136 
#define  STATUS_ARRAY_BOUNDS_EXCEEDED 135 
#define  STATUS_BREAKPOINT 134 
#define  STATUS_DATATYPE_MISALIGNMENT 133 
#define  STATUS_ILLEGAL_INSTRUCTION 132 
#define  STATUS_INTEGER_DIVIDE_BY_ZERO 131 
#define  STATUS_INTEGER_OVERFLOW 130 
#define  STATUS_SINGLE_STEP 129 
#define  STATUS_STACK_OVERFLOW 128 

__attribute__((used)) static void
GspStopReply(NTSTATUS ExceptionCode, PKTRAP_FRAME TrapFrame)
{
    PCHAR ptr = GspOutBuffer;
    ULONG SigVal;
    LONG Esp;

    switch (ExceptionCode)
    {
        case STATUS_INTEGER_DIVIDE_BY_ZERO:
            SigVal = 8; /* divide by zero */
            break;
        case STATUS_SINGLE_STEP:
        case STATUS_BREAKPOINT:
            SigVal = 5; /* breakpoint */
            break;
        case STATUS_INTEGER_OVERFLOW:
        case STATUS_ARRAY_BOUNDS_EXCEEDED:
            SigVal = 16; /* bound instruction */
            break;
        case STATUS_ILLEGAL_INSTRUCTION:
            SigVal = 4; /* Invalid opcode */
            break;
        case STATUS_STACK_OVERFLOW:
        case STATUS_DATATYPE_MISALIGNMENT:
        case STATUS_ACCESS_VIOLATION:
            SigVal = 11; /* access violation */
            break;
        default:
            SigVal = 7; /* "software generated" */
    }

    ptr = GspOutBuffer;

    *ptr++ = 'T'; /* notify gdb with signo, PC, FP and SP */
    *ptr++ = HexChars[(SigVal >> 4) & 0xf];
    *ptr++ = HexChars[SigVal & 0xf];

    *ptr++ = HexChars[ESP];
    *ptr++ = ':';

    Esp = GspGetEspFromTrapFrame(TrapFrame); /* SP */
    ptr = GspMem2Hex((PCHAR)&Esp, ptr, 4, 0);
    *ptr++ = ';';

    *ptr++ = HexChars[EBP];
    *ptr++ = ':';
    ptr = GspMem2Hex((PCHAR)&TrapFrame->Ebp, ptr, 4, 0); /* FP */
    *ptr++ = ';';

    *ptr++ = HexChars[PC];
    *ptr++ = ':';
    ptr = GspMem2Hex((PCHAR)&TrapFrame->Eip, ptr, 4, 0); /* PC */
    *ptr++ = ';';

    *ptr = '\0';
}
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
typedef  int ULONG ;
typedef  int NTSTATUS ;

/* Variables and functions */
#define  STATUS_ACCESS_VIOLATION 136 
#define  STATUS_ARRAY_BOUNDS_EXCEEDED 135 
#define  STATUS_BREAKPOINT 134 
#define  STATUS_DATATYPE_MISALIGNMENT 133 
#define  STATUS_ILLEGAL_INSTRUCTION 132 
#define  STATUS_INTEGER_DIVIDE_BY_ZERO 131 
#define  STATUS_INTEGER_OVERFLOW 130 
#define  STATUS_SINGLE_STEP 129 
#define  STATUS_STACK_OVERFLOW 128 

ULONG
GspComputeSignal(NTSTATUS ExceptionCode)
{
    ULONG SigVal;

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
    return SigVal;
}
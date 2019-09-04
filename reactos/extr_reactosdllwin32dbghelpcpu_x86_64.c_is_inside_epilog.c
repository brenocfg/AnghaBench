#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct cpu_stack_walk {int dummy; } ;
struct TYPE_3__ {scalar_t__ EndAddress; scalar_t__ BeginAddress; } ;
typedef  TYPE_1__ RUNTIME_FUNCTION ;
typedef  int LONG ;
typedef  scalar_t__ DWORD64 ;
typedef  int BYTE ;
typedef  int BOOL ;

/* Variables and functions */
 int FALSE ; 
 int TRUE ; 
 int /*<<< orphan*/  sw_read_mem (struct cpu_stack_walk*,scalar_t__,int*,int) ; 

__attribute__((used)) static BOOL is_inside_epilog(struct cpu_stack_walk* csw, DWORD64 pc,
                             DWORD64 base, const RUNTIME_FUNCTION *function )
{
    BYTE op0, op1, op2;
    LONG val32;

    if (!sw_read_mem(csw, pc, &op0, 1)) return FALSE;

    /* add or lea must be the first instruction, and it must have a rex.W prefix */
    if ((op0 & 0xf8) == 0x48)
    {
        if (!sw_read_mem(csw, pc + 1, &op1, 1)) return FALSE;
        if (!sw_read_mem(csw, pc + 2, &op2, 1)) return FALSE;
        switch (op1)
        {
        case 0x81: /* add $nnnn,%rsp */
            if (op0 == 0x48 && op2 == 0xc4)
            {
                pc += 7;
                break;
            }
            return FALSE;
        case 0x83: /* add $n,%rsp */
            if (op0 == 0x48 && op2 == 0xc4)
            {
                pc += 4;
                break;
            }
            return FALSE;
        case 0x8d: /* lea n(reg),%rsp */
            if (op0 & 0x06) return FALSE;  /* rex.RX must be cleared */
            if (((op2 >> 3) & 7) != 4) return FALSE;  /* dest reg mus be %rsp */
            if ((op2 & 7) == 4) return FALSE;  /* no SIB byte allowed */
            if ((op2 >> 6) == 1)  /* 8-bit offset */
            {
                pc += 4;
                break;
            }
            if ((op2 >> 6) == 2)  /* 32-bit offset */
            {
                pc += 7;
                break;
            }
            return FALSE;
        }
    }

    /* now check for various pop instructions */
    for (;;)
    {
        if (!sw_read_mem(csw, pc, &op0, 1)) return FALSE;
        if ((op0 & 0xf0) == 0x40)  /* rex prefix */
        {
            if (!sw_read_mem(csw, ++pc, &op0, 1)) return FALSE;
        }

        switch (op0)
        {
        case 0x58: /* pop %rax/%r8 */
        case 0x59: /* pop %rcx/%r9 */
        case 0x5a: /* pop %rdx/%r10 */
        case 0x5b: /* pop %rbx/%r11 */
        case 0x5c: /* pop %rsp/%r12 */
        case 0x5d: /* pop %rbp/%r13 */
        case 0x5e: /* pop %rsi/%r14 */
        case 0x5f: /* pop %rdi/%r15 */
            pc++;
            continue;
        case 0xc2: /* ret $nn */
        case 0xc3: /* ret */
            return TRUE;
        case 0xe9: /* jmp nnnn */
            if (!sw_read_mem(csw, pc + 1, &val32, sizeof(LONG))) return FALSE;
            pc += 5 + val32;
            if (pc - base >= function->BeginAddress && pc - base < function->EndAddress)
                continue;
            break;
        case 0xeb: /* jmp n */
            if (!sw_read_mem(csw, pc + 1, &op1, 1)) return FALSE;
            pc += 2 + (signed char)op1;
            if (pc - base >= function->BeginAddress && pc - base < function->EndAddress)
                continue;
            break;
        case 0xf3: /* rep; ret (for amd64 prediction bug) */
            if (!sw_read_mem(csw, pc + 1, &op1, 1)) return FALSE;
            return op1 == 0xc3;
        }
        return FALSE;
    }
}
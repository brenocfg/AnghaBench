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
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 unsigned int CV_REG_CS ; 
 unsigned int CV_REG_CTRL ; 
 unsigned int CV_REG_DS ; 
 unsigned int CV_REG_EAX ; 
 unsigned int CV_REG_EBP ; 
 unsigned int CV_REG_EBX ; 
 unsigned int CV_REG_ECX ; 
 unsigned int CV_REG_EDI ; 
 unsigned int CV_REG_EDX ; 
 unsigned int CV_REG_EFLAGS ; 
 unsigned int CV_REG_EIP ; 
 unsigned int CV_REG_ES ; 
 unsigned int CV_REG_ESI ; 
 unsigned int CV_REG_ESP ; 
 unsigned int CV_REG_FPCS ; 
 unsigned int CV_REG_FPDO ; 
 unsigned int CV_REG_FPDS ; 
 unsigned int CV_REG_FPIP ; 
 unsigned int CV_REG_FS ; 
 unsigned int CV_REG_GS ; 
 unsigned int CV_REG_MXCSR ; 
 unsigned int CV_REG_SS ; 
 int /*<<< orphan*/  CV_REG_ST0 ; 
 unsigned int CV_REG_STAT ; 
 unsigned int CV_REG_TAG ; 
 int /*<<< orphan*/  CV_REG_XMM0 ; 
 int /*<<< orphan*/  FIXME (char*,unsigned int) ; 

__attribute__((used)) static unsigned i386_map_dwarf_register(unsigned regno, BOOL eh_frame)
{
    unsigned    reg;

    switch (regno)
    {
    case  0: reg = CV_REG_EAX; break;
    case  1: reg = CV_REG_ECX; break;
    case  2: reg = CV_REG_EDX; break;
    case  3: reg = CV_REG_EBX; break;
    case  4:
    case  5:
#ifdef __APPLE__
        /* On OS X, DWARF eh_frame uses a different mapping for the registers.  It's
           apparently the mapping as emitted by GCC, at least at some point in its history. */
        if (eh_frame)
            reg = (regno == 4) ? CV_REG_EBP : CV_REG_ESP;
        else
#endif
            reg = (regno == 4) ? CV_REG_ESP : CV_REG_EBP;
        break;
    case  6: reg = CV_REG_ESI; break;
    case  7: reg = CV_REG_EDI; break;
    case  8: reg = CV_REG_EIP; break;
    case  9: reg = CV_REG_EFLAGS; break;
    case 10: reg = CV_REG_CS;  break;
    case 11: reg = CV_REG_SS;  break;
    case 12: reg = CV_REG_DS;  break;
    case 13: reg = CV_REG_ES;  break;
    case 14: reg = CV_REG_FS;  break;
    case 15: reg = CV_REG_GS;  break;
    case 16: case 17: case 18: case 19:
    case 20: case 21: case 22: case 23:
        reg = CV_REG_ST0 + regno - 16; break;
    case 24: reg = CV_REG_CTRL; break;
    case 25: reg = CV_REG_STAT; break;
    case 26: reg = CV_REG_TAG; break;
    case 27: reg = CV_REG_FPCS; break;
    case 28: reg = CV_REG_FPIP; break;
    case 29: reg = CV_REG_FPDS; break;
    case 30: reg = CV_REG_FPDO; break;
/*
reg: fop   31
*/
    case 32: case 33: case 34: case 35:
    case 36: case 37: case 38: case 39:
        reg = CV_REG_XMM0 + regno - 32; break;
    case 40: reg = CV_REG_MXCSR; break;
    default:
        FIXME("Don't know how to map register %d\n", regno);
        return 0;
    }
    return reg;
}
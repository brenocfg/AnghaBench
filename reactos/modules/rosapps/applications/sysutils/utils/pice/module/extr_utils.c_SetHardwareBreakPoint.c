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

/* Variables and functions */
 int /*<<< orphan*/  DPRINT (int /*<<< orphan*/ ) ; 

void SetHardwareBreakPoint(ULONG ulAddress,ULONG ulReg)
{
    ULONG mask = 0x300;
    ULONG enable_mask = 0x3;

    DPRINT((0,"SetHardwareBreakPoint(%x,DR%x)\n",ulAddress,ulReg));

    enable_mask <<= (ulReg*2);
    mask |= enable_mask;

    DPRINT((0,"mask = %x\n",mask));

	__asm__ __volatile__
	("\n\t \
		xorl %%eax,%%eax\n\t \
		mov %%eax,%%dr6\n\t \
        mov %%dr7,%%eax\n\t \
        orl %0,%%eax\n\t \
		mov %%eax,%%dr7\n\t \
	"
	:
	:"m" (mask)
	:"eax");

    switch(ulReg)
    {
        case 0:
            __asm__ __volatile__
            ("\n\t \
        		mov %0,%%eax\n\t \
		        mov %%eax,%%dr0\n\t \
             "
             :
             :"m" (ulAddress)
             :"eax");
             break;
        case 1:
            __asm__ __volatile__
            ("\n\t \
        		mov %0,%%eax\n\t \
		        mov %%eax,%%dr1\n\t \
             "
             :
             :"m" (ulAddress)
             :"eax");
             break;
        case 2:
            __asm__ __volatile__
            ("\n\t \
        		mov %0,%%eax\n\t \
		        mov %%eax,%%dr2\n\t \
             "
             :
             :"m" (ulAddress)
             :"eax");
             break;
        case 3:
            __asm__ __volatile__
            ("\n\t \
        		mov %0,%%eax\n\t \
		        mov %%eax,%%dr3\n\t \
             "
             :
             :"m" (ulAddress)
             :"eax");
             break;
    }
}
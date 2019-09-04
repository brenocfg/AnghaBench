#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int ULONG ;
struct TYPE_2__ {int LinearAddress; int /*<<< orphan*/  Virtual; scalar_t__ Used; scalar_t__ Active; } ;
typedef  int* PULONG ;

/* Variables and functions */
 TYPE_1__* Bp ; 
 int /*<<< orphan*/  DPRINT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENTER_FUNC () ; 
 int /*<<< orphan*/  LEAVE_FUNC () ; 

void SetHardwareBreakPoints(void)
{
ULONG i;
ULONG mask;
ULONG LinAddr0,LinAddr1,LinAddr2,LinAddr3;
PULONG LinAddr[4]={&LinAddr0,&LinAddr1,&LinAddr2,&LinAddr3};

    ENTER_FUNC();

	// cancel all debug activity
	__asm__("\n\t \
		pushl %eax\n\t \
		xorl %eax,%eax\n\t \
		mov %eax,%dr6\n\t \
		mov %eax,%dr7\n\t \
		popl %eax");
	// build DR7 mask
	for(mask=0,i=0;i<4;i++)
	{
		mask<<=2;
		if(Bp[i].Active && Bp[i].Used && !Bp[i].Virtual)
		{
			mask|=0x03;
			*LinAddr[3-i]=Bp[i].LinearAddress;
			DPRINT((0,"breakpoint %u at %.8X\n",i,Bp[i].LinearAddress));
		}
	}
	if(mask)
	{
		__asm__("\n\t \
			pushl %%eax\n\t \
			movl %0,%%eax\n\t \
			andl $0x000000FF,%%eax\n\t \
			orl $0x300,%%eax\n\t \
			mov %%eax,%%dr7\n\t \
			mov %1,%%eax\n\t \
			mov %%eax,%%dr0\n\t \
			mov %2,%%eax\n\t \
			mov %%eax,%%dr1\n\t \
			mov %3,%%eax\n\t \
			mov %%eax,%%dr2\n\t \
			mov %4,%%eax\n\t \
			mov %%eax,%%dr3\n\t \
			popl %%eax"
			:
			:"m" (mask),"m" (LinAddr0),"m" (LinAddr1),"m" (LinAddr2),"m" (LinAddr3));
	}

    LEAVE_FUNC();
}
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
typedef  int /*<<< orphan*/  PULONG ;

/* Variables and functions */
 int /*<<< orphan*/  cli () ; 
 int inl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outl (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  restore_flags (int) ; 
 int /*<<< orphan*/  save_flags (int) ; 

void EnablePassThrough(void)
{
	ULONG oldCF8,flags;

	save_flags(flags);
	cli();

	oldCF8 = inl((PULONG)0xcf8);
	outl(0x80000050,(PULONG)0xcf8);
	outl(inl((PULONG)0xcfc)|0x00000020,(PULONG)0xcfc);
	outl(oldCF8,(PULONG)0xcf8);

	restore_flags(flags);
}
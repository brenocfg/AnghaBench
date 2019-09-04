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
struct cpuflags {int id; int std; int std2; int ext; } ;

/* Variables and functions */
 scalar_t__ cpu_3dnow (struct cpuflags) ; 
 scalar_t__ cpu_3dnowext (struct cpuflags) ; 
 scalar_t__ cpu_i586 (struct cpuflags) ; 
 scalar_t__ cpu_mmx (struct cpuflags) ; 
 scalar_t__ cpu_sse (struct cpuflags) ; 
 scalar_t__ cpu_sse2 (struct cpuflags) ; 
 scalar_t__ cpu_sse3 (struct cpuflags) ; 
 int /*<<< orphan*/  getcpuflags (struct cpuflags*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

int main()
{
	int family;
	struct cpuflags flags;
	if(!getcpuflags(&flags)){ printf("CPU won't do cpuid (some old i386 or i486)\n"); return 0; }
	family = (flags.id & 0xf00)>>8;
	printf("family: %i\n", family);
	printf("stdcpuflags:  0x%08x\n", flags.std);
	printf("std2cpuflags: 0x%08x\n", flags.std2);
	printf("extcpuflags:  0x%08x\n", flags.ext);
	if(cpu_i586(flags))
	{
		printf("A i586 or better cpu with:");
		if(cpu_mmx(flags)) printf(" mmx");
		if(cpu_3dnow(flags)) printf(" 3dnow");
		if(cpu_3dnowext(flags)) printf(" 3dnowext");
		if(cpu_sse(flags)) printf(" sse");
		if(cpu_sse2(flags)) printf(" sse2");
		if(cpu_sse3(flags)) printf(" sse3");
		printf("\n");
	}
	else printf("I guess you have some i486\n");
	return 0;
}
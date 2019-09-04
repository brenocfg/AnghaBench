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

__attribute__((used)) static inline void do_cpuid( unsigned int ax, unsigned int *p )
{
#ifdef __i386__
#ifdef _MSC_VER
    __cpuid(p, ax);
#else
    __asm__("pushl %%ebx\n\t"
                "cpuid\n\t"
                "movl %%ebx, %%esi\n\t"
                "popl %%ebx"
                : "=a" (p[0]), "=S" (p[1]), "=c" (p[2]), "=d" (p[3])
                :  "0" (ax));
#endif
#endif
}
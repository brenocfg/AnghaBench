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
typedef  int /*<<< orphan*/  Int16 ;

/* Variables and functions */
 void* chmc_syscat_mem (void*,void*,int) ; 

__attribute__((used)) static void *chmc_syscat_entry(Int16 code, void *d, void *s, Int16 len)
{
	d = chmc_syscat_mem(d, &code, 2);
	d = chmc_syscat_mem(d, &len, 2);

	return chmc_syscat_mem(d, s, len);
}
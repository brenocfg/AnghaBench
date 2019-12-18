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
typedef  int /*<<< orphan*/  desc ;

/* Variables and functions */
 scalar_t__ vmm_stat_desc_copy (int,char*,int) ; 

const char *
xh_vm_get_stat_desc(int index)
{
	static char desc[128];

	if (vmm_stat_desc_copy(index, ((char *) &desc), sizeof(desc)) == 0) {
		return (desc);
	} else {
		return (NULL);
	}
}
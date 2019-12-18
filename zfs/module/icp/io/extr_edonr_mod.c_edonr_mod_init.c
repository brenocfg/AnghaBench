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
 int mod_install (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  modlinkage ; 

int
edonr_mod_init(void)
{
	int error;

	if ((error = mod_install(&modlinkage)) != 0)
		return (error);

	return (0);
}
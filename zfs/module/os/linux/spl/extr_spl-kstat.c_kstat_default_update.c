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
typedef  int /*<<< orphan*/  kstat_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int EACCES ; 
 int KSTAT_WRITE ; 

__attribute__((used)) static int
kstat_default_update(kstat_t *ksp, int rw)
{
	ASSERT(ksp != NULL);

	if (rw == KSTAT_WRITE)
		return (EACCES);

	return (0);
}
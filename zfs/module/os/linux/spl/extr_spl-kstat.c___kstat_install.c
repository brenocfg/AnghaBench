#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int mode_t ;
struct TYPE_7__ {int /*<<< orphan*/  kpe_name; } ;
struct TYPE_6__ {TYPE_2__ ks_proc; } ;
typedef  TYPE_1__ kstat_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (TYPE_1__*) ; 
 int /*<<< orphan*/  KSTAT_STRLEN ; 
 int /*<<< orphan*/  kstat_proc_entry_install (TYPE_2__*,int,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  proc_kstat_operations ; 
 scalar_t__ strncmp (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

void
__kstat_install(kstat_t *ksp)
{
	ASSERT(ksp);
	mode_t mode;
	/* Specify permission modes for different kstats */
	if (strncmp(ksp->ks_proc.kpe_name, "dbufs", KSTAT_STRLEN) == 0) {
		mode = 0600;
	} else {
		mode = 0644;
	}
	kstat_proc_entry_install(
	    &ksp->ks_proc, mode, &proc_kstat_operations, ksp);
}
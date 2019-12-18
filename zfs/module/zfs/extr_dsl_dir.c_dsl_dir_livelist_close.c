#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  dd_pending_frees; int /*<<< orphan*/  dd_pending_allocs; int /*<<< orphan*/  dd_livelist; } ;
typedef  TYPE_1__ dsl_dir_t ;

/* Variables and functions */
 int /*<<< orphan*/  bplist_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dsl_deadlist_close (int /*<<< orphan*/ *) ; 

void
dsl_dir_livelist_close(dsl_dir_t *dd)
{
	dsl_deadlist_close(&dd->dd_livelist);
	bplist_destroy(&dd->dd_pending_allocs);
	bplist_destroy(&dd->dd_pending_frees);
}
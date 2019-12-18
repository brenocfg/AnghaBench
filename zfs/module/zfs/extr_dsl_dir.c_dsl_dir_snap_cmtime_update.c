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
typedef  int /*<<< orphan*/  inode_timespec_t ;
struct TYPE_3__ {int /*<<< orphan*/  dd_lock; int /*<<< orphan*/  dd_snap_cmtime; } ;
typedef  TYPE_1__ dsl_dir_t ;

/* Variables and functions */
 int /*<<< orphan*/  gethrestime (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 

void
dsl_dir_snap_cmtime_update(dsl_dir_t *dd)
{
	inode_timespec_t t;

	gethrestime(&t);
	mutex_enter(&dd->dd_lock);
	dd->dd_snap_cmtime = t;
	mutex_exit(&dd->dd_lock);
}
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
struct TYPE_3__ {int /*<<< orphan*/  dd_myname; int /*<<< orphan*/  dd_lock; struct TYPE_3__* dd_parent; } ;
typedef  TYPE_1__ dsl_dir_t ;

/* Variables and functions */
 int /*<<< orphan*/  MUTEX_HELD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 scalar_t__ strlen (int /*<<< orphan*/ ) ; 

int
dsl_dir_namelen(dsl_dir_t *dd)
{
	int result = 0;

	if (dd->dd_parent) {
		/* parent's name + 1 for the "/" */
		result = dsl_dir_namelen(dd->dd_parent) + 1;
	}

	if (!MUTEX_HELD(&dd->dd_lock)) {
		/* see dsl_dir_name */
		mutex_enter(&dd->dd_lock);
		result += strlen(dd->dd_myname);
		mutex_exit(&dd->dd_lock);
	} else {
		result += strlen(dd->dd_myname);
	}

	return (result);
}
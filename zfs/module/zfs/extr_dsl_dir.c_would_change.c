#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int64_t ;
struct TYPE_7__ {struct TYPE_7__* dd_parent; int /*<<< orphan*/  dd_lock; } ;
typedef  TYPE_1__ dsl_dir_t ;
struct TYPE_8__ {int /*<<< orphan*/  dd_used_bytes; } ;

/* Variables and functions */
 TYPE_5__* dsl_dir_phys (TYPE_1__*) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  parent_delta (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int64_t
would_change(dsl_dir_t *dd, int64_t delta, dsl_dir_t *ancestor)
{
	if (dd == ancestor)
		return (delta);

	mutex_enter(&dd->dd_lock);
	delta = parent_delta(dd, dsl_dir_phys(dd)->dd_used_bytes, delta);
	mutex_exit(&dd->dd_lock);
	return (would_change(dd->dd_parent, delta, ancestor));
}
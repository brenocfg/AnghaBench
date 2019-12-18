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
typedef  int /*<<< orphan*/  zfs_iter_f ;
typedef  int /*<<< orphan*/  zfs_handle_t ;
struct TYPE_3__ {int /*<<< orphan*/  first; void* data; int /*<<< orphan*/  func; int /*<<< orphan*/ * stack; int /*<<< orphan*/  allowrecursion; } ;
typedef  TYPE_1__ iter_dependents_arg_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_TRUE ; 
 int iter_dependents_cb (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  zfs_handle_dup (int /*<<< orphan*/ *) ; 

int
zfs_iter_dependents(zfs_handle_t *zhp, boolean_t allowrecursion,
    zfs_iter_f func, void *data)
{
	iter_dependents_arg_t ida;
	ida.allowrecursion = allowrecursion;
	ida.stack = NULL;
	ida.func = func;
	ida.data = data;
	ida.first = B_TRUE;
	return (iter_dependents_cb(zfs_handle_dup(zhp), &ida));
}
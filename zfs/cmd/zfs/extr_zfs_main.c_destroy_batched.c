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
struct TYPE_3__ {int /*<<< orphan*/  cb_batchedsnaps; } ;
typedef  TYPE_1__ destroy_cbdata_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  fnvlist_alloc () ; 
 int /*<<< orphan*/  fnvlist_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_zfs ; 
 int zfs_destroy_snaps_nvl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
destroy_batched(destroy_cbdata_t *cb)
{
	int error = zfs_destroy_snaps_nvl(g_zfs,
	    cb->cb_batchedsnaps, B_FALSE);
	fnvlist_free(cb->cb_batchedsnaps);
	cb->cb_batchedsnaps = fnvlist_alloc();
	return (error);
}
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
struct TYPE_3__ {int /*<<< orphan*/  spc_refcnt; } ;
typedef  TYPE_1__ scan_prefetch_ctx_t ;

/* Variables and functions */
 int /*<<< orphan*/  zfs_refcount_add (int /*<<< orphan*/ *,void*) ; 

__attribute__((used)) static void
scan_prefetch_ctx_add_ref(scan_prefetch_ctx_t *spc, void *tag)
{
	zfs_refcount_add(&spc->spc_refcnt, tag);
}
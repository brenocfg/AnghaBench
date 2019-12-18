#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  objset_t ;
struct TYPE_5__ {int dbi_len; int dbi_err; void* dbi_buf; void* dbi_vp; } ;
typedef  TYPE_1__ dump_bytes_io_t ;

/* Variables and functions */
 int /*<<< orphan*/  TQ_SLEEP ; 
 int /*<<< orphan*/  ZIO_TASKQ_ISSUE ; 
 int /*<<< orphan*/  ZIO_TYPE_FREE ; 
 int /*<<< orphan*/  dmu_objset_spa (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dump_bytes_cb (TYPE_1__*) ; 
 int /*<<< orphan*/  spa_taskq_dispatch_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  (*) (TYPE_1__*),TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
dump_bytes(objset_t *os, void *buf, int len, void *arg)
{
	dump_bytes_io_t dbi;

	dbi.dbi_vp = arg;
	dbi.dbi_buf = buf;
	dbi.dbi_len = len;

#if defined(HAVE_LARGE_STACKS)
	dump_bytes_cb(&dbi);
#else
	/*
	 * The vn_rdwr() call is performed in a taskq to ensure that there is
	 * always enough stack space to write safely to the target filesystem.
	 * The ZIO_TYPE_FREE threads are used because there can be a lot of
	 * them and they are used in vdev_file.c for a similar purpose.
	 */
	spa_taskq_dispatch_sync(dmu_objset_spa(os), ZIO_TYPE_FREE,
	    ZIO_TASKQ_ISSUE, dump_bytes_cb, &dbi, TQ_SLEEP);
#endif /* HAVE_LARGE_STACKS */

	return (dbi.dbi_err);
}
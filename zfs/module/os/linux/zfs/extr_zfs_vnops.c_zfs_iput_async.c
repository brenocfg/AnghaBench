#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  task_func_t ;
struct inode {int /*<<< orphan*/  i_count; } ;
typedef  int /*<<< orphan*/  objset_t ;
struct TYPE_2__ {int /*<<< orphan*/ * z_os; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 TYPE_1__* ITOZSB (struct inode*) ; 
 scalar_t__ TASKQID_INVALID ; 
 int /*<<< orphan*/  TQ_SLEEP ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dmu_objset_pool (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dsl_pool_iput_taskq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 scalar_t__ taskq_dispatch (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct inode*,int /*<<< orphan*/ ) ; 

void
zfs_iput_async(struct inode *ip)
{
	objset_t *os = ITOZSB(ip)->z_os;

	ASSERT(atomic_read(&ip->i_count) > 0);
	ASSERT(os != NULL);

	if (atomic_read(&ip->i_count) == 1)
		VERIFY(taskq_dispatch(dsl_pool_iput_taskq(dmu_objset_pool(os)),
		    (task_func_t *)iput, ip, TQ_SLEEP) != TASKQID_INVALID);
	else
		iput(ip);
}
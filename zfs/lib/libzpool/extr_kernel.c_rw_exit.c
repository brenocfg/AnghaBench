#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  rw_lock; scalar_t__ rw_owner; int /*<<< orphan*/  rw_readers; } ;
typedef  TYPE_1__ krwlock_t ;

/* Variables and functions */
 scalar_t__ RW_READ_HELD (TYPE_1__*) ; 
 int /*<<< orphan*/  VERIFY0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_dec_uint (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_rwlock_unlock (int /*<<< orphan*/ *) ; 

void
rw_exit(krwlock_t *rwlp)
{
	if (RW_READ_HELD(rwlp))
		atomic_dec_uint(&rwlp->rw_readers);
	else
		rwlp->rw_owner = 0;

	VERIFY0(pthread_rwlock_unlock(&rwlp->rw_lock));
}
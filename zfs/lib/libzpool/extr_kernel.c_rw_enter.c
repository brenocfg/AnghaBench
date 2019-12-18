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
struct TYPE_3__ {int /*<<< orphan*/  rw_owner; int /*<<< orphan*/  rw_lock; int /*<<< orphan*/  rw_readers; } ;
typedef  TYPE_1__ krwlock_t ;
typedef  scalar_t__ krw_t ;

/* Variables and functions */
 scalar_t__ RW_READER ; 
 int /*<<< orphan*/  VERIFY0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_inc_uint (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_rwlock_rdlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_rwlock_wrlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_self () ; 

void
rw_enter(krwlock_t *rwlp, krw_t rw)
{
	if (rw == RW_READER) {
		VERIFY0(pthread_rwlock_rdlock(&rwlp->rw_lock));
		atomic_inc_uint(&rwlp->rw_readers);
	} else {
		VERIFY0(pthread_rwlock_wrlock(&rwlp->rw_lock));
		rwlp->rw_owner = pthread_self();
	}
}
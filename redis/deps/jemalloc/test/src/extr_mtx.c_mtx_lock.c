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
struct TYPE_3__ {int /*<<< orphan*/  lock; } ;
typedef  TYPE_1__ mtx_t ;

/* Variables and functions */
 int /*<<< orphan*/  EnterCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OSSpinLockLock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  os_unfair_lock_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 

void
mtx_lock(mtx_t *mtx) {
#ifdef _WIN32
	EnterCriticalSection(&mtx->lock);
#elif (defined(JEMALLOC_OS_UNFAIR_LOCK))
	os_unfair_lock_lock(&mtx->lock);
#elif (defined(JEMALLOC_OSSPIN))
	OSSpinLockLock(&mtx->lock);
#else
	pthread_mutex_lock(&mtx->lock);
#endif
}
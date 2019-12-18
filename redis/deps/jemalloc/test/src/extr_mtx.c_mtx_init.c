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
typedef  int /*<<< orphan*/  pthread_mutexattr_t ;
struct TYPE_3__ {scalar_t__ lock; } ;
typedef  TYPE_1__ mtx_t ;

/* Variables and functions */
 int /*<<< orphan*/  InitializeCriticalSectionAndSpinCount (scalar_t__*,int /*<<< orphan*/ ) ; 
 scalar_t__ OS_UNFAIR_LOCK_INIT ; 
 int /*<<< orphan*/  PTHREAD_MUTEX_DEFAULT ; 
 int /*<<< orphan*/  _CRT_SPINCOUNT ; 
 scalar_t__ pthread_mutex_init (scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutexattr_destroy (int /*<<< orphan*/ *) ; 
 scalar_t__ pthread_mutexattr_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutexattr_settype (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

bool
mtx_init(mtx_t *mtx) {
#ifdef _WIN32
	if (!InitializeCriticalSectionAndSpinCount(&mtx->lock,
	    _CRT_SPINCOUNT)) {
		return true;
	}
#elif (defined(JEMALLOC_OS_UNFAIR_LOCK))
	mtx->lock = OS_UNFAIR_LOCK_INIT;
#elif (defined(JEMALLOC_OSSPIN))
	mtx->lock = 0;
#else
	pthread_mutexattr_t attr;

	if (pthread_mutexattr_init(&attr) != 0) {
		return true;
	}
	pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_DEFAULT);
	if (pthread_mutex_init(&mtx->lock, &attr) != 0) {
		pthread_mutexattr_destroy(&attr);
		return true;
	}
	pthread_mutexattr_destroy(&attr);
#endif
	return false;
}
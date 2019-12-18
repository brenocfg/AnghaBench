#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int uint_t ;
struct TYPE_6__ {int tp_minimum; int tp_maximum; int tp_linger; struct TYPE_6__* tp_back; struct TYPE_6__* tp_forw; int /*<<< orphan*/  tp_attr; int /*<<< orphan*/  tp_waitcv; int /*<<< orphan*/  tp_workcv; int /*<<< orphan*/  tp_busycv; int /*<<< orphan*/  tp_mutex; } ;
typedef  TYPE_1__ tpool_t ;
typedef  int /*<<< orphan*/  pthread_attr_t ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  PTHREAD_CREATE_DETACHED ; 
 size_t PTHREAD_STACK_MIN ; 
 TYPE_1__* calloc (int,int) ; 
 int errno ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int pthread_attr_clone (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ pthread_attr_getstack (int /*<<< orphan*/ *,void**,size_t*) ; 
 int /*<<< orphan*/  pthread_attr_setdetachstate (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_cond_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  thread_pool_lock ; 
 TYPE_1__* thread_pools ; 

tpool_t	*
tpool_create(uint_t min_threads, uint_t max_threads, uint_t linger,
    pthread_attr_t *attr)
{
	tpool_t	*tpool;
	void *stackaddr;
	size_t stacksize;
	size_t minstack;
	int error;

	if (min_threads > max_threads || max_threads < 1) {
		errno = EINVAL;
		return (NULL);
	}
	if (attr != NULL) {
		if (pthread_attr_getstack(attr, &stackaddr, &stacksize) != 0) {
			errno = EINVAL;
			return (NULL);
		}
		/*
		 * Allow only one thread in the pool with a specified stack.
		 * Require threads to have at least the minimum stack size.
		 */
		minstack = PTHREAD_STACK_MIN;
		if (stackaddr != NULL) {
			if (stacksize < minstack || max_threads != 1) {
				errno = EINVAL;
				return (NULL);
			}
		} else if (stacksize != 0 && stacksize < minstack) {
			errno = EINVAL;
			return (NULL);
		}
	}

	tpool = calloc(1, sizeof (*tpool));
	if (tpool == NULL) {
		errno = ENOMEM;
		return (NULL);
	}
	(void) pthread_mutex_init(&tpool->tp_mutex, NULL);
	(void) pthread_cond_init(&tpool->tp_busycv, NULL);
	(void) pthread_cond_init(&tpool->tp_workcv, NULL);
	(void) pthread_cond_init(&tpool->tp_waitcv, NULL);
	tpool->tp_minimum = min_threads;
	tpool->tp_maximum = max_threads;
	tpool->tp_linger = linger;

	/*
	 * We cannot just copy the attribute pointer.
	 * We need to initialize a new pthread_attr_t structure
	 * with the values from the user-supplied pthread_attr_t.
	 * If the attribute pointer is NULL, we need to initialize
	 * the new pthread_attr_t structure with default values.
	 */
	error = pthread_attr_clone(&tpool->tp_attr, attr);
	if (error) {
		free(tpool);
		errno = error;
		return (NULL);
	}

	/* make all pool threads be detached daemon threads */
	(void) pthread_attr_setdetachstate(&tpool->tp_attr,
	    PTHREAD_CREATE_DETACHED);

	/* insert into the global list of all thread pools */
	pthread_mutex_lock(&thread_pool_lock);
	if (thread_pools == NULL) {
		tpool->tp_forw = tpool;
		tpool->tp_back = tpool;
		thread_pools = tpool;
	} else {
		thread_pools->tp_back->tp_forw = tpool;
		tpool->tp_forw = thread_pools;
		tpool->tp_back = thread_pools->tp_back;
		thread_pools->tp_back = tpool;
	}
	pthread_mutex_unlock(&thread_pool_lock);

	return (tpool);
}
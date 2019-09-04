#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  pthread_t ;
typedef  int /*<<< orphan*/  pthread_attr_t ;

/* Variables and functions */
 int BIO_NUM_OPS ; 
 int /*<<< orphan*/  LL_WARNING ; 
 size_t REDIS_THREAD_STACK_SIZE ; 
 int /*<<< orphan*/  bioProcessBackgroundJobs ; 
 int /*<<< orphan*/ * bio_jobs ; 
 int /*<<< orphan*/ * bio_mutex ; 
 int /*<<< orphan*/ * bio_newjob_cond ; 
 scalar_t__* bio_pending ; 
 int /*<<< orphan*/ * bio_step_cond ; 
 int /*<<< orphan*/ * bio_threads ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  listCreate () ; 
 int /*<<< orphan*/  pthread_attr_getstacksize (int /*<<< orphan*/ *,size_t*) ; 
 int /*<<< orphan*/  pthread_attr_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_attr_setstacksize (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  pthread_cond_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  pthread_mutex_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  serverLog (int /*<<< orphan*/ ,char*) ; 

void bioInit(void) {
    pthread_attr_t attr;
    pthread_t thread;
    size_t stacksize;
    int j;

    /* Initialization of state vars and objects */
    for (j = 0; j < BIO_NUM_OPS; j++) {
        pthread_mutex_init(&bio_mutex[j],NULL);
        pthread_cond_init(&bio_newjob_cond[j],NULL);
        pthread_cond_init(&bio_step_cond[j],NULL);
        bio_jobs[j] = listCreate();
        bio_pending[j] = 0;
    }

    /* Set the stack size as by default it may be small in some system */
    pthread_attr_init(&attr);
    pthread_attr_getstacksize(&attr,&stacksize);
    if (!stacksize) stacksize = 1; /* The world is full of Solaris Fixes */
    while (stacksize < REDIS_THREAD_STACK_SIZE) stacksize *= 2;
    pthread_attr_setstacksize(&attr, stacksize);

    /* Ready to spawn our threads. We use the single argument the thread
     * function accepts in order to pass the job ID the thread is
     * responsible of. */
    for (j = 0; j < BIO_NUM_OPS; j++) {
        void *arg = (void*)(unsigned long) j;
        if (pthread_create(&thread,&attr,bioProcessBackgroundJobs,arg) != 0) {
            serverLog(LL_WARNING,"Fatal: Can't initialize Background Jobs.");
            exit(1);
        }
        bio_threads[j] = thread;
    }
}
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
struct bio_job {scalar_t__ arg3; scalar_t__ arg2; scalar_t__ arg1; } ;
typedef  int /*<<< orphan*/  sigset_t ;
struct TYPE_4__ {struct bio_job* value; } ;
typedef  TYPE_1__ listNode ;

/* Variables and functions */
 unsigned long BIO_AOF_FSYNC ; 
 unsigned long BIO_CLOSE_FILE ; 
 unsigned long BIO_LAZY_FREE ; 
 unsigned long BIO_NUM_OPS ; 
 int /*<<< orphan*/  LL_WARNING ; 
 int /*<<< orphan*/  PTHREAD_CANCEL_ASYNCHRONOUS ; 
 int /*<<< orphan*/  PTHREAD_CANCEL_ENABLE ; 
 int /*<<< orphan*/  SIGALRM ; 
 int /*<<< orphan*/  SIG_BLOCK ; 
 int /*<<< orphan*/ * bio_jobs ; 
 int /*<<< orphan*/ * bio_mutex ; 
 int /*<<< orphan*/ * bio_newjob_cond ; 
 int /*<<< orphan*/ * bio_pending ; 
 int /*<<< orphan*/ * bio_step_cond ; 
 int /*<<< orphan*/  close (long) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  lazyfreeFreeDatabaseFromBioThread (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  lazyfreeFreeObjectFromBioThread (scalar_t__) ; 
 int /*<<< orphan*/  lazyfreeFreeSlotsMapFromBioThread (scalar_t__) ; 
 int /*<<< orphan*/  listDelNode (int /*<<< orphan*/ ,TYPE_1__*) ; 
 TYPE_1__* listFirst (int /*<<< orphan*/ ) ; 
 scalar_t__ listLength (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_cond_broadcast (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_cond_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_setcancelstate (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_setcanceltype (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ pthread_sigmask (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  redis_fsync (long) ; 
 int /*<<< orphan*/  serverLog (int /*<<< orphan*/ ,char*,unsigned long) ; 
 int /*<<< orphan*/  serverPanic (char*) ; 
 int /*<<< orphan*/  sigaddset (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sigemptyset (int /*<<< orphan*/ *) ; 
 unsigned long strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfree (struct bio_job*) ; 

void *bioProcessBackgroundJobs(void *arg) {
    struct bio_job *job;
    unsigned long type = (unsigned long) arg;
    sigset_t sigset;

    /* Check that the type is within the right interval. */
    if (type >= BIO_NUM_OPS) {
        serverLog(LL_WARNING,
            "Warning: bio thread started with wrong type %lu",type);
        return NULL;
    }

    /* Make the thread killable at any time, so that bioKillThreads()
     * can work reliably. */
    pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
    pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);

    pthread_mutex_lock(&bio_mutex[type]);
    /* Block SIGALRM so we are sure that only the main thread will
     * receive the watchdog signal. */
    sigemptyset(&sigset);
    sigaddset(&sigset, SIGALRM);
    if (pthread_sigmask(SIG_BLOCK, &sigset, NULL))
        serverLog(LL_WARNING,
            "Warning: can't mask SIGALRM in bio.c thread: %s", strerror(errno));

    while(1) {
        listNode *ln;

        /* The loop always starts with the lock hold. */
        if (listLength(bio_jobs[type]) == 0) {
            pthread_cond_wait(&bio_newjob_cond[type],&bio_mutex[type]);
            continue;
        }
        /* Pop the job from the queue. */
        ln = listFirst(bio_jobs[type]);
        job = ln->value;
        /* It is now possible to unlock the background system as we know have
         * a stand alone job structure to process.*/
        pthread_mutex_unlock(&bio_mutex[type]);

        /* Process the job accordingly to its type. */
        if (type == BIO_CLOSE_FILE) {
            close((long)job->arg1);
        } else if (type == BIO_AOF_FSYNC) {
            redis_fsync((long)job->arg1);
        } else if (type == BIO_LAZY_FREE) {
            /* What we free changes depending on what arguments are set:
             * arg1 -> free the object at pointer.
             * arg2 & arg3 -> free two dictionaries (a Redis DB).
             * only arg3 -> free the skiplist. */
            if (job->arg1)
                lazyfreeFreeObjectFromBioThread(job->arg1);
            else if (job->arg2 && job->arg3)
                lazyfreeFreeDatabaseFromBioThread(job->arg2,job->arg3);
            else if (job->arg3)
                lazyfreeFreeSlotsMapFromBioThread(job->arg3);
        } else {
            serverPanic("Wrong job type in bioProcessBackgroundJobs().");
        }
        zfree(job);

        /* Lock again before reiterating the loop, if there are no longer
         * jobs to process we'll block again in pthread_cond_wait(). */
        pthread_mutex_lock(&bio_mutex[type]);
        listDelNode(bio_jobs[type],ln);
        bio_pending[type]--;

        /* Unblock threads blocked on bioWaitStepOfType() if any. */
        pthread_cond_broadcast(&bio_step_cond[type]);
    }
}
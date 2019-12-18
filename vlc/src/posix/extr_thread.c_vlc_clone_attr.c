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
struct TYPE_3__ {int /*<<< orphan*/  handle; } ;
typedef  TYPE_1__ vlc_thread_t ;
struct sched_param {scalar_t__ sched_priority; } ;
typedef  int /*<<< orphan*/  sigset_t ;
typedef  int /*<<< orphan*/  pthread_attr_t ;

/* Variables and functions */
 int /*<<< orphan*/  PTHREAD_EXPLICIT_SCHED ; 
 int SCHED_OTHER ; 
 int SCHED_RR ; 
 int /*<<< orphan*/  SIGHUP ; 
 int /*<<< orphan*/  SIGINT ; 
 int /*<<< orphan*/  SIGPIPE ; 
 int /*<<< orphan*/  SIGQUIT ; 
 int /*<<< orphan*/  SIGTERM ; 
 int /*<<< orphan*/  SIG_BLOCK ; 
 int /*<<< orphan*/  SIG_SETMASK ; 
 int /*<<< orphan*/  VLC_STACKSIZE ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  pthread_attr_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_attr_setinheritsched (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_attr_setschedparam (int /*<<< orphan*/ *,struct sched_param*) ; 
 int /*<<< orphan*/  pthread_attr_setschedpolicy (int /*<<< orphan*/ *,int) ; 
 int pthread_attr_setstacksize (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void* (*) (void*),void*) ; 
 int /*<<< orphan*/  pthread_sigmask (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rt_offset ; 
 scalar_t__ rt_priorities ; 
 scalar_t__ sched_get_priority_max (int) ; 
 scalar_t__ sched_get_priority_min (int) ; 
 int /*<<< orphan*/  sigaddset (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sigdelset (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sigemptyset (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int vlc_clone_attr (vlc_thread_t *th, pthread_attr_t *attr,
                           void *(*entry) (void *), void *data, int priority)
{
    int ret;

    /* Block the signals that signals interface plugin handles.
     * If the LibVLC caller wants to handle some signals by itself, it should
     * block these before whenever invoking LibVLC. And it must obviously not
     * start the VLC signals interface plugin.
     *
     * LibVLC will normally ignore any interruption caused by an asynchronous
     * signal during a system call. But there may well be some buggy cases
     * where it fails to handle EINTR (bug reports welcome). Some underlying
     * libraries might also not handle EINTR properly.
     */
    sigset_t oldset;
    {
        sigset_t set;
        sigemptyset (&set);
        sigdelset (&set, SIGHUP);
        sigaddset (&set, SIGINT);
        sigaddset (&set, SIGQUIT);
        sigaddset (&set, SIGTERM);

        sigaddset (&set, SIGPIPE); /* We don't want this one, really! */
        pthread_sigmask (SIG_BLOCK, &set, &oldset);
    }

#if defined (_POSIX_PRIORITY_SCHEDULING) && (_POSIX_PRIORITY_SCHEDULING >= 0) \
 && defined (_POSIX_THREAD_PRIORITY_SCHEDULING) \
 && (_POSIX_THREAD_PRIORITY_SCHEDULING >= 0)
    if (rt_priorities)
    {
        struct sched_param sp = { .sched_priority = priority + rt_offset, };
        int policy;

        if (sp.sched_priority <= 0)
            sp.sched_priority += sched_get_priority_max (policy = SCHED_OTHER);
        else
            sp.sched_priority += sched_get_priority_min (policy = SCHED_RR);

        pthread_attr_setschedpolicy (attr, policy);
        pthread_attr_setschedparam (attr, &sp);
        pthread_attr_setinheritsched (attr, PTHREAD_EXPLICIT_SCHED);
    }
#else
    (void) priority;
#endif

    /* The thread stack size.
     * The lower the value, the less address space per thread, the highest
     * maximum simultaneous threads per process. Too low values will cause
     * stack overflows and weird crashes. Set with caution. Also keep in mind
     * that 64-bits platforms consume more stack than 32-bits one.
     *
     * Thanks to on-demand paging, thread stack size only affects address space
     * consumption. In terms of memory, threads only use what they need
     * (rounded up to the page boundary).
     *
     * For example, on Linux i386, the default is 2 mega-bytes, which supports
     * about 320 threads per processes. */
#define VLC_STACKSIZE (128 * sizeof (void *) * 1024)

#ifdef VLC_STACKSIZE
    ret = pthread_attr_setstacksize (attr, VLC_STACKSIZE);
    assert (ret == 0); /* fails iif VLC_STACKSIZE is invalid */
#endif

    ret = pthread_create(&th->handle, attr, entry, data);
    pthread_sigmask (SIG_SETMASK, &oldset, NULL);
    pthread_attr_destroy (attr);
    return ret;
}
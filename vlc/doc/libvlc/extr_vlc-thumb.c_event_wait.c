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
struct timespec {int /*<<< orphan*/  tv_sec; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_MONOTONIC ; 
 int ETIMEDOUT ; 
 int VLC_THUMBNAIL_TIMEOUT ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  clock_gettime (int /*<<< orphan*/ ,struct timespec*) ; 
 scalar_t__ done ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*,int) ; 
 int /*<<< orphan*/  lock ; 
 int pthread_cond_timedwait (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct timespec*) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  wait ; 

__attribute__((used)) static void event_wait(const char *error)
{
    int ret;
    struct timespec ts;
#define VLC_THUMBNAIL_TIMEOUT   5 /* 5 secs */

    clock_gettime(CLOCK_MONOTONIC, &ts);
    ts.tv_sec += VLC_THUMBNAIL_TIMEOUT;
    pthread_mutex_lock(&lock);
    ret = done ? 0 : pthread_cond_timedwait(&wait, &lock, &ts);
    pthread_mutex_unlock(&lock);

    assert(!ret || ret == ETIMEDOUT);

    if (ret) {
        fprintf(stderr,
                "%s (timeout after %d secs!\n", error, VLC_THUMBNAIL_TIMEOUT);
        exit(1);
    }
}
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
typedef  int /*<<< orphan*/  vlc_cond_t ;
typedef  int /*<<< orphan*/  pthread_condattr_t ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_MONOTONIC ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  pthread_cond_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_condattr_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_condattr_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_condattr_setclock (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

void vlc_cond_init (vlc_cond_t *p_condvar)
{
    pthread_condattr_t attr;

    if (unlikely(pthread_condattr_init (&attr))
     || unlikely(pthread_condattr_setclock(&attr, CLOCK_MONOTONIC))
     || unlikely(pthread_cond_init (p_condvar, &attr)))
        abort ();

    pthread_condattr_destroy (&attr);
}
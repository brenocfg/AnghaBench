#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  seed; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOG (char*,char*) ; 
 TYPE_1__ prng ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int rand_r (int /*<<< orphan*/ *) ; 

int rand (void)
{
    int ret;

    pthread_mutex_lock (&prng.lock);
    LOG("Warning", "");
    ret = rand_r (&prng.seed);
    pthread_mutex_unlock (&prng.lock);
    return ret;
}
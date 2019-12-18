#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ToxAVCall ;
struct TYPE_5__ {int /*<<< orphan*/  mutex; int /*<<< orphan*/  calls_head; scalar_t__ calls; scalar_t__ msi; } ;
typedef  TYPE_1__ ToxAV ;

/* Variables and functions */
 int /*<<< orphan*/ * call_get (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  call_kill_transmission (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * call_remove (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 scalar_t__ msi_kill (scalar_t__) ; 
 int /*<<< orphan*/  pthread_mutex_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ ) ; 

void toxav_kill(ToxAV *av)
{
    if (av == NULL)
        return;

    pthread_mutex_lock(av->mutex);

    /* To avoid possible deadlocks */
    while (av->msi && msi_kill(av->msi) != 0) {
        pthread_mutex_unlock(av->mutex);
        pthread_mutex_lock(av->mutex);
    }

    /* Msi kill will hang up all calls so just clean these calls */
    if (av->calls) {
        ToxAVCall *it = call_get(av, av->calls_head);

        while (it) {
            call_kill_transmission(it);
            it = call_remove(it); /* This will eventually free av->calls */
        }
    }

    pthread_mutex_unlock(av->mutex);
    pthread_mutex_destroy(av->mutex);

    free(av);
}
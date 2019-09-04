#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  size; int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ frame ;
struct TYPE_5__ {int /*<<< orphan*/  arb_mutex; int /*<<< orphan*/  arb; } ;
typedef  TYPE_2__ CallControl ;

/* Variables and functions */
 scalar_t__ Pa_IsStreamActive (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Pa_WriteStream (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  adout ; 
 int /*<<< orphan*/  c_sleep (int) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ ) ; 
 scalar_t__ rb_read (int /*<<< orphan*/ ,void**) ; 

void *pa_write_thread (void *d)
{
    /* The purpose of this thread is to make sure Pa_WriteStream will not block
     * toxav_iterate thread
     */
    CallControl *cc = d;

    while (Pa_IsStreamActive(adout)) {
        frame *f;
        pthread_mutex_lock(cc->arb_mutex);

        if (rb_read(cc->arb, (void **)&f)) {
            pthread_mutex_unlock(cc->arb_mutex);
            Pa_WriteStream(adout, f->data, f->size);
            free(f);
        } else {
            pthread_mutex_unlock(cc->arb_mutex);
            c_sleep(10);
        }
    }
}
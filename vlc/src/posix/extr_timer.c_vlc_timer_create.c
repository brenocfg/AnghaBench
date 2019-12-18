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
typedef  struct vlc_timer* vlc_timer_t ;
struct vlc_timer {void (* func ) (void*) ;int /*<<< orphan*/  lock; int /*<<< orphan*/  reschedule; int /*<<< orphan*/  thread; int /*<<< orphan*/  overruns; scalar_t__ interval; scalar_t__ value; void* data; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  VLC_THREAD_PRIORITY_INPUT ; 
 int /*<<< orphan*/  assert (void (*) (void*)) ; 
 int /*<<< orphan*/  atomic_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct vlc_timer*) ; 
 struct vlc_timer* malloc (int) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 scalar_t__ vlc_clone (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct vlc_timer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_cond_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_cond_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_timer_thread ; 

int vlc_timer_create (vlc_timer_t *id, void (*func) (void *), void *data)
{
    struct vlc_timer *timer = malloc (sizeof (*timer));

    if (unlikely(timer == NULL))
        return ENOMEM;
    vlc_mutex_init (&timer->lock);
    vlc_cond_init (&timer->reschedule);
    assert (func);
    timer->func = func;
    timer->data = data;
    timer->value = 0;
    timer->interval = 0;
    atomic_init(&timer->overruns, 0);

    if (vlc_clone (&timer->thread, vlc_timer_thread, timer,
                   VLC_THREAD_PRIORITY_INPUT))
    {
        vlc_cond_destroy (&timer->reschedule);
        vlc_mutex_destroy (&timer->lock);
        free (timer);
        return ENOMEM;
    }

    *id = timer;
    return 0;
}
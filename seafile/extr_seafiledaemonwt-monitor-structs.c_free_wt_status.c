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
struct TYPE_4__ {int /*<<< orphan*/  q_lock; scalar_t__ event_q; } ;
typedef  TYPE_1__ WTStatus ;

/* Variables and functions */
 int /*<<< orphan*/  free_event_cb ; 
 int /*<<< orphan*/  g_free (TYPE_1__*) ; 
 int /*<<< orphan*/  g_queue_foreach (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_queue_free (scalar_t__) ; 
 int /*<<< orphan*/  pthread_mutex_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void free_wt_status (WTStatus *status)
{
    if (status->event_q) {
        g_queue_foreach (status->event_q, free_event_cb, NULL);
        g_queue_free (status->event_q);
    }
    pthread_mutex_destroy (&status->q_lock);
    g_free (status);
}
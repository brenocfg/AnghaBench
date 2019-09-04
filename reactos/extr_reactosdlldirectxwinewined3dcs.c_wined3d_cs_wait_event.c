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
struct wined3d_cs {int /*<<< orphan*/  event; int /*<<< orphan*/  waiting_for_event; int /*<<< orphan*/ * queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  INFINITE ; 
 scalar_t__ InterlockedCompareExchange (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InterlockedExchange (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 size_t WINED3D_CS_QUEUE_DEFAULT ; 
 size_t WINED3D_CS_QUEUE_MAP ; 
 int /*<<< orphan*/  WaitForSingleObject (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ wined3d_cs_queue_is_empty (struct wined3d_cs*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void wined3d_cs_wait_event(struct wined3d_cs *cs)
{
    InterlockedExchange(&cs->waiting_for_event, TRUE);

    /* The main thread might have enqueued a command and blocked on it after
     * the CS thread decided to enter wined3d_cs_wait_event(), but before
     * "waiting_for_event" was set.
     *
     * Likewise, we can race with the main thread when resetting
     * "waiting_for_event", in which case we would need to call
     * WaitForSingleObject() because the main thread called SetEvent(). */
    if (!(wined3d_cs_queue_is_empty(cs, &cs->queue[WINED3D_CS_QUEUE_DEFAULT])
            && wined3d_cs_queue_is_empty(cs, &cs->queue[WINED3D_CS_QUEUE_MAP]))
            && InterlockedCompareExchange(&cs->waiting_for_event, FALSE, TRUE))
        return;

    WaitForSingleObject(cs->event, INFINITE);
}
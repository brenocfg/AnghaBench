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
struct TYPE_3__ {int /*<<< orphan*/  cond; int /*<<< orphan*/  mutex; int /*<<< orphan*/  p_events; int /*<<< orphan*/ * pp_last_event; } ;
typedef  TYPE_1__ OmxEventQueue ;

/* Variables and functions */
 int /*<<< orphan*/  vlc_cond_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_init (int /*<<< orphan*/ *) ; 

void InitOmxEventQueue(OmxEventQueue *queue)
{
    queue->pp_last_event = &queue->p_events;
    vlc_mutex_init(&queue->mutex);
    vlc_cond_init(&queue->cond);
}
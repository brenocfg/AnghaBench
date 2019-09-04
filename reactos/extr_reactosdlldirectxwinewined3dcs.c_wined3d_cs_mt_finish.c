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
struct wined3d_cs {scalar_t__ thread_id; TYPE_1__* queue; } ;
typedef  enum wined3d_cs_queue_id { ____Placeholder_wined3d_cs_queue_id } wined3d_cs_queue_id ;
struct TYPE_2__ {scalar_t__ volatile head; int /*<<< orphan*/  tail; } ;
typedef  scalar_t__ LONG ;

/* Variables and functions */
 scalar_t__ GetCurrentThreadId () ; 
 int /*<<< orphan*/  wined3d_cs_st_finish (struct wined3d_cs*,int) ; 
 int /*<<< orphan*/  wined3d_pause () ; 

__attribute__((used)) static void wined3d_cs_mt_finish(struct wined3d_cs *cs, enum wined3d_cs_queue_id queue_id)
{
    if (cs->thread_id == GetCurrentThreadId())
    {
        wined3d_cs_st_finish(cs, queue_id);
        return;
    }

    while (cs->queue[queue_id].head != *(volatile LONG *)&cs->queue[queue_id].tail)
        wined3d_pause();
}
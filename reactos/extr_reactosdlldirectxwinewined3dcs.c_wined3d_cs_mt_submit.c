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
struct wined3d_cs {scalar_t__ thread_id; int /*<<< orphan*/ * queue; } ;
typedef  enum wined3d_cs_queue_id { ____Placeholder_wined3d_cs_queue_id } wined3d_cs_queue_id ;

/* Variables and functions */
 scalar_t__ GetCurrentThreadId () ; 
 int /*<<< orphan*/  wined3d_cs_queue_submit (int /*<<< orphan*/ *,struct wined3d_cs*) ; 
 int /*<<< orphan*/  wined3d_cs_st_submit (struct wined3d_cs*,int) ; 

__attribute__((used)) static void wined3d_cs_mt_submit(struct wined3d_cs *cs, enum wined3d_cs_queue_id queue_id)
{
    if (cs->thread_id == GetCurrentThreadId())
    {
        wined3d_cs_st_submit(cs, queue_id);
        return;
    }

    wined3d_cs_queue_submit(&cs->queue[queue_id], cs);
}
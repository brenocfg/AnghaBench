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
struct TYPE_4__ {scalar_t__ remain_files; struct TYPE_4__* new_path; struct TYPE_4__* path; } ;
typedef  TYPE_1__ WTEvent ;

/* Variables and functions */
 int /*<<< orphan*/  free_path ; 
 int /*<<< orphan*/  g_free (TYPE_1__*) ; 
 int /*<<< orphan*/  g_queue_foreach (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_queue_free (scalar_t__) ; 

void wt_event_free (WTEvent *event)
{
    g_free (event->path);
    g_free (event->new_path);
    if (event->remain_files) {
        g_queue_foreach (event->remain_files, free_path, NULL);
        g_queue_free (event->remain_files);
    }
    g_free (event);
}
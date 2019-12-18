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
struct inotify_event {int mask; } ;
typedef  int gboolean ;
struct TYPE_3__ {int mask; } ;
typedef  TYPE_1__ EventInfo ;

/* Variables and functions */
 int IN_CLOSE_WRITE ; 
 int IN_MODIFY ; 

__attribute__((used)) inline static gboolean
is_modify_close_write (EventInfo *e1, struct inotify_event *e2)
{
    return ((e1->mask & IN_MODIFY) && (e2->mask & IN_CLOSE_WRITE));
}
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
struct TYPE_4__ {int /*<<< orphan*/ * data; } ;
struct TYPE_5__ {TYPE_1__ pl_item_names; } ;
typedef  TYPE_2__ intf_sys_t ;

/* Variables and functions */
 scalar_t__ strcasestr (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int SubSearchPlaylist(intf_sys_t *sys, char *searchstring,
                             int i_start, int i_stop)
{
    for (int i = i_start + 1; i < i_stop; i++)
        if (strcasestr(sys->pl_item_names.data[i], searchstring))
            return i;
    return -1;
}
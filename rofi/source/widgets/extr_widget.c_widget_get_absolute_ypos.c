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
struct TYPE_3__ {struct TYPE_3__* parent; scalar_t__ y; } ;
typedef  TYPE_1__ widget ;

/* Variables and functions */

int widget_get_absolute_ypos ( widget *wid )
{
    int retv = 0;
    if ( wid ) {
        retv += wid->y;
        if ( wid->parent ) {
            retv += widget_get_absolute_ypos ( wid->parent );
        }
    }
    return retv;
}
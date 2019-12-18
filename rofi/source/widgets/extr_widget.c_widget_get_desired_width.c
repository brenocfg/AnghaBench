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
struct TYPE_4__ {int (* get_desired_width ) (TYPE_1__*) ;int w; } ;
typedef  TYPE_1__ widget ;

/* Variables and functions */
 int stub1 (TYPE_1__*) ; 

int widget_get_desired_width ( widget *wid )
{
    if ( wid == NULL ) {
        return 0;
    }
    if ( wid->get_desired_width ) {
        return wid->get_desired_width ( wid );
    }
    return wid->w;
}
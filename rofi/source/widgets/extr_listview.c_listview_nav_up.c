#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ reverse; } ;
typedef  TYPE_1__ listview ;

/* Variables and functions */
 int /*<<< orphan*/  listview_nav_down_int (TYPE_1__*) ; 
 int /*<<< orphan*/  listview_nav_up_int (TYPE_1__*) ; 

void listview_nav_up ( listview *lv )
{
    if ( lv == NULL ) {
        return;
    }
    if ( lv->reverse ) {
        listview_nav_down_int ( lv );
    }
    else {
        listview_nav_up_int ( lv );
    }
}
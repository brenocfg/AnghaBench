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
typedef  int /*<<< orphan*/  widget ;
struct TYPE_2__ {scalar_t__ type; } ;
typedef  TYPE_1__ listview ;
typedef  int /*<<< orphan*/  cairo_t ;

/* Variables and functions */
 scalar_t__ LISTVIEW ; 
 int /*<<< orphan*/  barview_draw (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  listview_draw (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void _listview_draw ( widget *wid, cairo_t *draw )
{
    listview *lv = (listview *) wid;
    if ( lv->type == LISTVIEW ) {
        listview_draw ( wid, draw );
    }
    else {
        barview_draw ( wid, draw );
    }
}
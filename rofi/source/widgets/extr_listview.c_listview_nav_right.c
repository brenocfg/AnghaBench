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
struct TYPE_5__ {scalar_t__ type; int selected; int max_rows; int req_elements; } ;
typedef  TYPE_1__ listview ;

/* Variables and functions */
 scalar_t__ BARVIEW ; 
 int /*<<< orphan*/  WIDGET (TYPE_1__*) ; 
 int /*<<< orphan*/  listview_nav_down_int (TYPE_1__*) ; 
 int /*<<< orphan*/  widget_queue_redraw (int /*<<< orphan*/ ) ; 

void listview_nav_right ( listview *lv )
{
    if ( lv == NULL ) {
        return;
    }
    if ( lv->type == BARVIEW ) {
        listview_nav_down_int ( lv );
        return;
    }
    if ( ( lv->selected + lv->max_rows ) < lv->req_elements ) {
        lv->selected += lv->max_rows;
        widget_queue_redraw ( WIDGET ( lv ) );
    }
    else if ( lv->selected < ( lv->req_elements - 1 ) ) {
        // We do not want to move to last item, UNLESS the last column is only
        // partially filled, then we still want to move column and select last entry.
        // First check the column we are currently in.
        int col = lv->selected / lv->max_rows;
        // Check total number of columns.
        int ncol = lv->req_elements / lv->max_rows;
        // If there is an extra column, move.
        if ( col != ncol ) {
            lv->selected = lv->req_elements - 1;
            widget_queue_redraw ( WIDGET ( lv ) );
        }
    }
}
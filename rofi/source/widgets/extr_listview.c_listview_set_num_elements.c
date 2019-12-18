#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {unsigned int req_elements; int /*<<< orphan*/  selected; } ;
typedef  TYPE_1__ listview ;

/* Variables and functions */
 int /*<<< orphan*/  WIDGET (TYPE_1__*) ; 
 int /*<<< orphan*/  listview_recompute_elements (TYPE_1__*) ; 
 int /*<<< orphan*/  listview_set_selected (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  widget_queue_redraw (int /*<<< orphan*/ ) ; 

void listview_set_num_elements ( listview *lv, unsigned int rows )
{
    if ( lv == NULL ) {
        return;
    }
    lv->req_elements = rows;
    listview_set_selected ( lv, lv->selected );
    listview_recompute_elements ( lv );
    widget_queue_redraw ( WIDGET ( lv ) );
}
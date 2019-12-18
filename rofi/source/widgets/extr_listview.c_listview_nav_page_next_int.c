#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {unsigned int cur_visible; int /*<<< orphan*/  direction; } ;
struct TYPE_6__ {scalar_t__ req_elements; scalar_t__ type; unsigned int last_offset; scalar_t__ selected; scalar_t__ max_elements; TYPE_1__ barview; } ;
typedef  TYPE_2__ listview ;

/* Variables and functions */
 scalar_t__ BARVIEW ; 
 int /*<<< orphan*/  LEFT_TO_RIGHT ; 
 scalar_t__ MIN (unsigned int,scalar_t__) ; 
 int /*<<< orphan*/  WIDGET (TYPE_2__*) ; 
 int /*<<< orphan*/  widget_queue_redraw (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void listview_nav_page_next_int ( listview *lv )
{
    if ( lv == NULL ) {
        return;
    }
    if ( lv->req_elements == 0 ) {
        return;
    }
    if ( lv->type == BARVIEW ) {
        unsigned int new = lv->last_offset + lv->barview.cur_visible;
        lv->selected          = MIN ( new, lv->req_elements - 1 );
        lv->barview.direction = LEFT_TO_RIGHT;

        widget_queue_redraw ( WIDGET ( lv ) );
        return;
    }
    lv->selected += ( lv->max_elements );
    if ( lv->selected >= lv->req_elements ) {
        lv->selected = lv->req_elements - 1;
    }
    widget_queue_redraw ( WIDGET ( lv ) );
}
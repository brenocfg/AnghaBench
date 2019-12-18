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
struct TYPE_5__ {int /*<<< orphan*/  direction; } ;
struct TYPE_6__ {scalar_t__ type; scalar_t__ last_offset; scalar_t__ selected; scalar_t__ max_elements; TYPE_1__ barview; } ;
typedef  TYPE_2__ listview ;

/* Variables and functions */
 scalar_t__ BARVIEW ; 
 int /*<<< orphan*/  RIGHT_TO_LEFT ; 
 int /*<<< orphan*/  WIDGET (TYPE_2__*) ; 
 int /*<<< orphan*/  widget_queue_redraw (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void listview_nav_page_prev_int ( listview *lv )
{
    if ( lv == NULL ) {
        return;
    }
    if ( lv->type == BARVIEW ) {
        if ( lv->last_offset == 0 ) {
            lv->selected = 0;
        }
        else {
            lv->selected = lv->last_offset - 1;
        }
        lv->barview.direction = RIGHT_TO_LEFT;
        widget_queue_redraw ( WIDGET ( lv ) );
        return;
    }

    if ( lv->selected < lv->max_elements ) {
        lv->selected = 0;
    }
    else{
        lv->selected -= ( lv->max_elements );
    }
    widget_queue_redraw ( WIDGET ( lv ) );
}
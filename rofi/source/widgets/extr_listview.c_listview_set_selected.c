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
struct TYPE_6__ {scalar_t__ req_elements; TYPE_1__ barview; int /*<<< orphan*/  selected; } ;
typedef  TYPE_2__ listview ;

/* Variables and functions */
 int /*<<< orphan*/  LEFT_TO_RIGHT ; 
 int /*<<< orphan*/  MIN (unsigned int,scalar_t__) ; 
 int /*<<< orphan*/  WIDGET (TYPE_2__*) ; 
 int /*<<< orphan*/  widget_queue_redraw (int /*<<< orphan*/ ) ; 

void listview_set_selected ( listview *lv, unsigned int selected )
{
    if ( lv && lv->req_elements > 0 ) {
        lv->selected          = MIN ( selected, lv->req_elements - 1 );
        lv->barview.direction = LEFT_TO_RIGHT;
        widget_queue_redraw ( WIDGET ( lv ) );
    }
}
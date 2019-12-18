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
struct TYPE_6__ {scalar_t__ req_elements; scalar_t__ selected; TYPE_1__ barview; int /*<<< orphan*/  cycle; } ;
typedef  TYPE_2__ listview ;

/* Variables and functions */
 int /*<<< orphan*/  RIGHT_TO_LEFT ; 
 int /*<<< orphan*/  WIDGET (TYPE_2__*) ; 
 int /*<<< orphan*/  widget_queue_redraw (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void listview_nav_up_int ( listview *lv )
{
    if ( lv == NULL ) {
        return;
    }
    if ( lv->req_elements == 0 || ( lv->selected == 0 && !lv->cycle ) ) {
        return;
    }
    if ( lv->selected == 0 ) {
        lv->selected = lv->req_elements;
    }
    lv->selected--;
    lv->barview.direction = RIGHT_TO_LEFT;
    widget_queue_redraw ( WIDGET ( lv ) );
}
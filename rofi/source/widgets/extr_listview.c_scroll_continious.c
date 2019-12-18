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
struct TYPE_3__ {int max_rows; unsigned int selected; unsigned int req_elements; unsigned int cur_page; int /*<<< orphan*/  rchanged; } ;
typedef  TYPE_1__ listview ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static unsigned int scroll_continious ( listview *lv )
{
    unsigned int middle = ( lv->max_rows - ( ( lv->max_rows & 1 ) == 0 ) ) / 2;
    unsigned int offset = 0;
    if ( lv->selected > middle ) {
        if ( lv->selected < ( lv->req_elements - ( lv->max_rows - middle ) ) ) {
            offset = lv->selected - middle;
        }
        // Don't go below zero.
        else if ( lv->req_elements > lv->max_rows ) {
            offset = lv->req_elements - lv->max_rows;
        }
    }
    if ( offset != lv->cur_page ) {
        //scrollbar_set_handle ( lv->scrollbar, offset );
        lv->cur_page = offset;
        lv->rchanged = TRUE;
    }
    return offset;
}
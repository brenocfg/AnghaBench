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
struct TYPE_3__ {scalar_t__ selected; scalar_t__ last_offset; scalar_t__ max_elements; unsigned int cur_page; int /*<<< orphan*/  rchanged; } ;
typedef  TYPE_1__ listview ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static unsigned int scroll_per_page ( listview * lv )
{
    int offset = 0;

    // selected row is always visible.
    // If selected is visible do not scroll.
    if ( ( ( lv->selected - ( lv->last_offset ) ) < ( lv->max_elements ) ) && ( lv->selected >= ( lv->last_offset ) ) ) {
        offset = lv->last_offset;
    }
    else{
        // Do paginating
        unsigned int page = ( lv->max_elements > 0 ) ? ( lv->selected / lv->max_elements ) : 0;
        offset = page * lv->max_elements;
        if ( page != lv->cur_page ) {
            lv->cur_page = page;
            lv->rchanged = TRUE;
        }
        // Set the position
        //scrollbar_set_handle ( lv->scrollbar, page * lv->max_elements );
    }
    return offset;
}
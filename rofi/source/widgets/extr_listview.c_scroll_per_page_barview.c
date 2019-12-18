#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {unsigned int cur_visible; } ;
struct TYPE_5__ {unsigned int last_offset; unsigned int selected; void* rchanged; TYPE_1__ barview; } ;
typedef  TYPE_2__ listview ;

/* Variables and functions */
 void* TRUE ; 

__attribute__((used)) static unsigned int scroll_per_page_barview ( listview *lv )
{
    unsigned int offset = lv->last_offset;

    // selected row is always visible.
    // If selected is visible do not scroll.
    if ( lv->selected < lv->last_offset ) {
        offset       = lv->selected;
        lv->rchanged = TRUE;
    }
    else if ( lv->selected >= ( lv->last_offset + lv->barview.cur_visible ) ) {
        offset       = lv->selected;
        lv->rchanged = TRUE;
    }
    return offset;
}
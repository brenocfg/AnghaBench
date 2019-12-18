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
struct TYPE_5__ {scalar_t__ emode; unsigned int cur_elements; TYPE_1__* boxes; } ;
typedef  TYPE_2__ listview ;
struct TYPE_4__ {int /*<<< orphan*/  textbox; } ;
typedef  scalar_t__ PangoEllipsizeMode ;

/* Variables and functions */
 scalar_t__ PANGO_ELLIPSIZE_END ; 
 scalar_t__ PANGO_ELLIPSIZE_MIDDLE ; 
 scalar_t__ PANGO_ELLIPSIZE_START ; 
 int /*<<< orphan*/  textbox_set_ellipsize (int /*<<< orphan*/ ,scalar_t__) ; 

void listview_toggle_ellipsizing ( listview *lv )
{
    if ( lv ) {
        PangoEllipsizeMode mode =  lv->emode;
        if ( mode == PANGO_ELLIPSIZE_START ) { 
            mode = PANGO_ELLIPSIZE_MIDDLE;
        } else if ( mode == PANGO_ELLIPSIZE_MIDDLE ) {
            mode = PANGO_ELLIPSIZE_END;
        } else if ( mode == PANGO_ELLIPSIZE_END ) {
            mode = PANGO_ELLIPSIZE_START;
        }
        lv->emode = mode;
        for ( unsigned int i = 0; i < lv->cur_elements; i++ ) {
            textbox_set_ellipsize ( lv->boxes[i].textbox, mode );
        }
    }
}
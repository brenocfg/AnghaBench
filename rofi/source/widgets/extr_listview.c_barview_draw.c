#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  widget ;
struct TYPE_8__ {int cur_visible; scalar_t__ direction; } ;
struct TYPE_7__ {int w; } ;
struct TYPE_9__ {unsigned int last_offset; scalar_t__ cur_elements; int rchanged; TYPE_4__* boxes; TYPE_2__ barview; int /*<<< orphan*/  element_height; TYPE_1__ widget; scalar_t__ req_elements; int /*<<< orphan*/  spacing; } ;
typedef  TYPE_3__ listview ;
typedef  int /*<<< orphan*/  cairo_t ;
struct TYPE_10__ {int /*<<< orphan*/  box; int /*<<< orphan*/  textbox; } ;
typedef  TYPE_4__ _listview_row ;

/* Variables and functions */
 void* FALSE ; 
 scalar_t__ LEFT_TO_RIGHT ; 
 unsigned int MIN (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  ROFI_ORIENTATION_HORIZONTAL ; 
 void* TRUE ; 
 int /*<<< orphan*/  WIDGET (int /*<<< orphan*/ ) ; 
 int distance_get_pixel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int scroll_per_page_barview (TYPE_3__*) ; 
 int textbox_get_desired_width (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  update_element (TYPE_3__*,unsigned int,unsigned int,void*) ; 
 int /*<<< orphan*/  widget_draw (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  widget_move (int /*<<< orphan*/ ,int,int) ; 
 int widget_padding_get_left (int /*<<< orphan*/ *) ; 
 scalar_t__ widget_padding_get_padding_width (int /*<<< orphan*/ *) ; 
 int widget_padding_get_right (int /*<<< orphan*/ *) ; 
 int widget_padding_get_top (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  widget_resize (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void barview_draw ( widget *wid, cairo_t *draw )
{
    unsigned int offset = 0;
    listview     *lv    = (listview *) wid;
    offset          = scroll_per_page_barview ( lv );
    lv->last_offset = offset;
    int spacing_hori = distance_get_pixel ( lv->spacing, ROFI_ORIENTATION_HORIZONTAL );

    int left_offset  = widget_padding_get_left ( wid );
    int right_offset = lv->widget.w - widget_padding_get_right ( wid );
    int top_offset   = widget_padding_get_top ( wid );
    if ( lv->cur_elements > 0 ) {
        // Set new x/y position.
        unsigned int max = MIN ( lv->cur_elements, lv->req_elements - offset );
        if ( lv->rchanged ) {
            int first = TRUE;
            int width = lv->widget.w;
            lv->barview.cur_visible = 0;
            width                  -= widget_padding_get_padding_width ( wid );
            if ( lv->barview.direction == LEFT_TO_RIGHT ) {
                for ( unsigned int i = 0; i < max && width > 0; i++ ) {
                    update_element ( lv, i, i + offset, TRUE );
                    int twidth = textbox_get_desired_width ( WIDGET ( lv->boxes[i].textbox ) );
                    if ( twidth >= width ) {
                        if ( !first ) {
                            break;
                        }
                        twidth = width;
                    }
                    widget_move ( WIDGET(lv->boxes[i].box), left_offset, top_offset);
                    widget_resize ( WIDGET (lv->boxes[i].box), twidth, lv->element_height);

                    widget_draw ( WIDGET ( lv->boxes[i].box ), draw );
                    width       -= twidth + spacing_hori;
                    left_offset += twidth + spacing_hori;
                    first        = FALSE;
                    lv->barview.cur_visible++;
                }
            }
            else {
                for ( unsigned int i = 0; i < lv->cur_elements && width > 0 && i <= offset; i++ ) {
                    update_element ( lv, i, offset - i, TRUE );
                    int twidth = textbox_get_desired_width ( WIDGET ( lv->boxes[i].textbox ) );
                    if ( twidth >= width ) {
                        if ( !first ) {
                            break;
                        }
                        twidth = width;
                    }
                    right_offset -= twidth;
                    widget_move ( WIDGET(lv->boxes[i].box), right_offset, top_offset);
                    widget_resize ( WIDGET (lv->boxes[i].box), twidth, lv->element_height);

                    widget_draw ( WIDGET ( lv->boxes[i].box ), draw );
                    width        -= twidth + spacing_hori;
                    right_offset -= spacing_hori;
                    first         = FALSE;
                    lv->barview.cur_visible++;
                }
                offset         -= lv->barview.cur_visible - 1;
                lv->last_offset = offset;
                for  ( unsigned int i = 0; i < ( lv->barview.cur_visible / 2 ); i++ ) {
                    _listview_row  temp = lv->boxes[i];
                    int  sw     = lv->barview.cur_visible - i - 1;
                    lv->boxes[i]  = lv->boxes[sw];
                    lv->boxes[sw] = temp;
                }
            }
            lv->rchanged = FALSE;
        }
        else {
            for ( unsigned int i = 0; i < lv->barview.cur_visible; i++ ) {
                update_element ( lv, i, i + offset, FALSE );
                widget_draw ( WIDGET ( lv->boxes[i].box ), draw );
            }
        }
    }
}
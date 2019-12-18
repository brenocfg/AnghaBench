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
typedef  int /*<<< orphan*/  widget ;
struct TYPE_4__ {scalar_t__ enabled; } ;
struct TYPE_5__ {int menu_lines; int req_elements; int max_displayed_lines; scalar_t__ type; int element_height; int /*<<< orphan*/  fixed_num_lines; scalar_t__ dynamic; int /*<<< orphan*/  spacing; TYPE_1__ widget; } ;
typedef  TYPE_2__ listview ;

/* Variables and functions */
 scalar_t__ BARVIEW ; 
 scalar_t__ FALSE ; 
 int MIN (int,int) ; 
 int /*<<< orphan*/  ROFI_ORIENTATION_VERTICAL ; 
 int /*<<< orphan*/  WIDGET (TYPE_2__*) ; 
 int distance_get_pixel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int widget_padding_get_padding_height (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int listview_get_desired_height ( widget *wid )
{
    listview *lv = (listview *) wid;
    if ( lv == NULL || lv->widget.enabled == FALSE ) {
        return 0;
    }
    int spacing = distance_get_pixel ( lv->spacing, ROFI_ORIENTATION_VERTICAL );
    int h       = lv->menu_lines;
    if ( !( lv->fixed_num_lines ) ) {
        if ( lv->dynamic ) {
            h = MIN ( lv->menu_lines, lv->req_elements );
        }
        else {
            h = MIN ( lv->menu_lines, lv->max_displayed_lines );
        }
    }
    if ( lv->type == BARVIEW ) {
        h = MIN ( h, 1 );
    }
    if ( h == 0 ) {
        if ( lv->dynamic && !lv->fixed_num_lines ) {
            // Hide widget fully.
            return 0;
        }
        return widget_padding_get_padding_height ( WIDGET ( lv ) );
    }
    int height = widget_padding_get_padding_height ( WIDGET ( lv ) );
    height += h * ( lv->element_height + spacing ) - spacing;
    return height;
}
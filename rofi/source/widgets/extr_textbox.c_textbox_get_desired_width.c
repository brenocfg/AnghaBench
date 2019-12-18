#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ expand; } ;
typedef  TYPE_1__ widget ;
struct TYPE_8__ {int flags; int /*<<< orphan*/  layout; } ;
typedef  TYPE_2__ textbox ;
typedef  int /*<<< orphan*/  RofiDistance ;

/* Variables and functions */
 unsigned int DOT_OFFSET ; 
 int /*<<< orphan*/  ROFI_ORIENTATION_HORIZONTAL ; 
 int TB_AUTOWIDTH ; 
 int TB_INDICATOR ; 
 int /*<<< orphan*/  WIDGET (TYPE_2__*) ; 
 int distance_get_pixel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int pango_layout_get_width (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pango_layout_set_width (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rofi_theme_get_distance (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int textbox_get_font_width (TYPE_2__*) ; 
 int widget_padding_get_left (int /*<<< orphan*/ ) ; 
 int widget_padding_get_padding_width (TYPE_1__*) ; 
 scalar_t__ widget_padding_get_right (int /*<<< orphan*/ ) ; 

int textbox_get_desired_width ( widget *wid )
{
    if ( wid == NULL ) {
        return 0;
    }
    textbox      *tb    = (textbox *) wid;
    unsigned int offset = ( ( tb->flags & TB_INDICATOR ) ? DOT_OFFSET : 0 );
    if ( wid->expand && tb->flags & TB_AUTOWIDTH ) {
        return textbox_get_font_width ( tb ) + widget_padding_get_padding_width ( wid ) + offset;
    }
    RofiDistance w  = rofi_theme_get_distance ( WIDGET ( tb ), "width", 0 );
    int          wi = distance_get_pixel ( w, ROFI_ORIENTATION_HORIZONTAL );
    if ( wi > 0 ) {
        return wi;
    }
    int padding = widget_padding_get_left ( WIDGET ( tb ) );
    padding += widget_padding_get_right ( WIDGET ( tb ) );
    int old_width = pango_layout_get_width ( tb->layout );
    pango_layout_set_width ( tb->layout, -1 );
    int width = textbox_get_font_width ( tb );
    // Restore.
    pango_layout_set_width ( tb->layout, old_width );
    return width + padding + offset;
}
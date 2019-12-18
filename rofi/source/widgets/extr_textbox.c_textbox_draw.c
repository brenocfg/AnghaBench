#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  widget ;
struct TYPE_7__ {int h; scalar_t__ w; } ;
struct TYPE_8__ {int flags; double yalign; double xalign; int tbft; TYPE_1__ widget; int /*<<< orphan*/  layout; int /*<<< orphan*/  cursor; scalar_t__ blink; int /*<<< orphan*/  metrics; scalar_t__ changed; } ;
typedef  TYPE_2__ textbox ;
typedef  int /*<<< orphan*/  cairo_t ;
struct TYPE_9__ {int x; int y; int height; } ;
typedef  TYPE_3__ PangoRectangle ;

/* Variables and functions */
 int /*<<< orphan*/  CAIRO_OPERATOR_OVER ; 
 double DOT_OFFSET ; 
 int MAX (int /*<<< orphan*/ ,scalar_t__) ; 
 int MIN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 double M_PI ; 
 int PANGO_SCALE ; 
 int SELECTED ; 
 int TB_EDITABLE ; 
 int TB_INDICATOR ; 
 int /*<<< orphan*/  WIDGET (TYPE_2__*) ; 
 int /*<<< orphan*/  __textbox_update_pango_text (TYPE_2__*) ; 
 int /*<<< orphan*/  cairo_arc (int /*<<< orphan*/ *,double,double,double,int /*<<< orphan*/ ,double) ; 
 int /*<<< orphan*/  cairo_fill (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cairo_move_to (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  cairo_rectangle (int /*<<< orphan*/ *,int,int,int,int) ; 
 int /*<<< orphan*/  cairo_set_operator (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cairo_set_source_rgb (int /*<<< orphan*/ *,double,double,double) ; 
 char* g_utf8_offset_to_pointer (char const*,int) ; 
 int /*<<< orphan*/  g_utf8_strlen (char const*,int) ; 
 int /*<<< orphan*/  pango_cairo_show_layout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int pango_font_metrics_get_ascent (int /*<<< orphan*/ ) ; 
 int pango_layout_get_baseline (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pango_layout_get_cursor_pos (int /*<<< orphan*/ ,int,TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pango_layout_get_pixel_size (int /*<<< orphan*/ ,int*,int*) ; 
 char* pango_layout_get_text (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rofi_theme_get_color (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int widget_padding_get_bottom (int /*<<< orphan*/ ) ; 
 int widget_padding_get_left (int /*<<< orphan*/ ) ; 
 scalar_t__ widget_padding_get_padding_width (int /*<<< orphan*/ ) ; 
 int widget_padding_get_top (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void textbox_draw ( widget *wid, cairo_t *draw )
{
    if ( wid == NULL ) {
        return;
    }
    textbox      *tb    = (textbox *) wid;
    unsigned int offset = ( ( tb->flags & TB_INDICATOR ) ? DOT_OFFSET : 0 );

    if ( tb->changed ) {
        __textbox_update_pango_text ( tb );
    }

    // Skip the side MARGIN on the X axis.
    int x = widget_padding_get_left ( WIDGET ( tb ) );
    int top = widget_padding_get_top ( WIDGET ( tb ) );
    int y = ( pango_font_metrics_get_ascent ( tb->metrics ) - pango_layout_get_baseline ( tb->layout ) ) / PANGO_SCALE;
    int line_width = 0, line_height = 0;
    // Get actual width.
    pango_layout_get_pixel_size ( tb->layout, &line_width, &line_height );

    if ( tb->yalign > 0.001 ) {
        int bottom = widget_padding_get_bottom ( WIDGET ( tb ) );
        top = ( tb->widget.h - bottom - line_height - top ) * tb->yalign + top;
    }
    y += top;

    x += offset;

    if ( tb->xalign > 0.001 ) {
        int rem = MAX ( 0, tb->widget.w - widget_padding_get_padding_width ( WIDGET ( tb ) ) - line_width );
        x = tb->xalign * rem + widget_padding_get_left ( WIDGET ( tb ) );
    }
    // TODO check if this is still needed after flatning.
    cairo_set_operator ( draw, CAIRO_OPERATOR_OVER );
    cairo_set_source_rgb ( draw, 0.0, 0.0, 0.0 );
    rofi_theme_get_color ( WIDGET ( tb ), "text-color", draw );
    // draw the cursor
    if ( tb->flags & TB_EDITABLE && tb->blink ) {
        // We want to place the cursor based on the text shown.
        const char     *text = pango_layout_get_text ( tb->layout );
        // Clamp the position, should not be needed, but we are paranoid.
        int            cursor_offset = MIN ( tb->cursor, g_utf8_strlen ( text, -1 ) );
        PangoRectangle pos;
        // convert to byte location.
        char           *offset = g_utf8_offset_to_pointer ( text, cursor_offset );
        pango_layout_get_cursor_pos ( tb->layout, offset - text, &pos, NULL );
        int            cursor_x      = pos.x / PANGO_SCALE;
        int            cursor_y      = pos.y / PANGO_SCALE;
        int            cursor_height = pos.height / PANGO_SCALE;
        int            cursor_width  = 2;
        cairo_rectangle ( draw, x + cursor_x, y + cursor_y, cursor_width, cursor_height );
        cairo_fill ( draw );
    }

    // Set ARGB
    // We need to set over, otherwise subpixel hinting wont work.
    cairo_move_to ( draw, x, top );
    pango_cairo_show_layout ( draw, tb->layout );

    if ( ( tb->flags & TB_INDICATOR ) == TB_INDICATOR && ( tb->tbft & ( SELECTED ) ) ) {
        cairo_arc ( draw, DOT_OFFSET / 2.0, tb->widget.h / 2.0, 2.0, 0, 2.0 * M_PI );
        cairo_fill ( draw );
    }
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {unsigned int h; } ;
typedef  TYPE_1__ widget ;
struct TYPE_10__ {unsigned int length; double pos; scalar_t__ pos_length; } ;
typedef  TYPE_2__ scrollbar ;
typedef  int /*<<< orphan*/  cairo_t ;

/* Variables and functions */
 unsigned int MAX (int,unsigned int) ; 
 unsigned int MIN (unsigned int,unsigned int) ; 
 int /*<<< orphan*/  WIDGET (TYPE_2__*) ; 
 int /*<<< orphan*/  cairo_fill (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cairo_rectangle (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  rofi_theme_get_color (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  widget_padding_get_left (TYPE_1__*) ; 
 unsigned int widget_padding_get_remaining_height (TYPE_1__*) ; 
 int /*<<< orphan*/  widget_padding_get_remaining_width (TYPE_1__*) ; 
 scalar_t__ widget_padding_get_top (TYPE_1__*) ; 

__attribute__((used)) static void scrollbar_draw ( widget *wid, cairo_t *draw )
{
    scrollbar    *sb = (scrollbar *) wid;
    unsigned int wh  = widget_padding_get_remaining_height ( wid );
    // Calculate position and size.
    unsigned int r      = ( sb->length * wh ) / ( (double) ( sb->length + sb->pos_length ) );
    unsigned int handle = wid->h - r;
    double       sec    = ( ( r ) / (double) ( sb->length - 1 ) );
    unsigned int height = handle;
    unsigned int y      = sb->pos * sec;
    // Set max pos.
    y = MIN ( y, wh - handle );
    // Never go out of bar.
    height = MAX ( 2, height );
    // Cap length;
    rofi_theme_get_color ( WIDGET ( sb ), "handle-color", draw );

    cairo_rectangle ( draw,
                      widget_padding_get_left ( wid ),
                      widget_padding_get_top ( wid ) + y,
                      widget_padding_get_remaining_width ( wid ),
                      height );
    cairo_fill ( draw );
}
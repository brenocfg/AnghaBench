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
struct TYPE_4__ {int w; int h; } ;
struct TYPE_5__ {scalar_t__ icon_fetch_id; int xalign; int yalign; int /*<<< orphan*/ * icon; TYPE_1__ widget; scalar_t__ size; } ;
typedef  TYPE_2__ icon ;
typedef  int /*<<< orphan*/  cairo_t ;

/* Variables and functions */
 int MAX (int,int) ; 
 int /*<<< orphan*/  WIDGET (TYPE_2__*) ; 
 int cairo_image_surface_get_height (int /*<<< orphan*/ *) ; 
 int cairo_image_surface_get_width (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cairo_paint (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cairo_restore (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cairo_save (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cairo_scale (int /*<<< orphan*/ *,double,double) ; 
 int /*<<< orphan*/  cairo_set_source_surface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cairo_surface_reference (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cairo_translate (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/ * rofi_icon_fetcher_get (scalar_t__) ; 
 int widget_padding_get_bottom (int /*<<< orphan*/ ) ; 
 int widget_padding_get_left (int /*<<< orphan*/ ) ; 
 int widget_padding_get_right (int /*<<< orphan*/ ) ; 
 int widget_padding_get_top (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void icon_draw ( widget *wid, cairo_t *draw )
{
    icon *b = (icon *) wid;
    // If no icon is loaded. quit.
    if ( b->icon == NULL && b->icon_fetch_id > 0 ) {
        b->icon = rofi_icon_fetcher_get ( b->icon_fetch_id );
        if ( b->icon ) {
            cairo_surface_reference ( b->icon );
        }
    }
    if ( b->icon == NULL  ) {
        return;
    }
    int    iconh = cairo_image_surface_get_height ( b->icon );
    int    iconw = cairo_image_surface_get_width ( b->icon );
    int    icons = MAX ( iconh, iconw );
    double scale = (double) b->size / icons;

    int lpad = widget_padding_get_left   ( WIDGET ( b ) ) ;
    int rpad = widget_padding_get_right  ( WIDGET ( b ) ) ;
    int tpad = widget_padding_get_top    ( WIDGET ( b ) ) ;
    int bpad = widget_padding_get_bottom ( WIDGET ( b ) ) ;

    cairo_save ( draw );

    cairo_translate ( draw,
            lpad + ( b->widget.w - iconw * scale - lpad -rpad )*b->xalign,
            tpad + ( b->widget.h- iconh * scale -tpad - bpad )*b->yalign );
    cairo_scale ( draw, scale, scale );
    cairo_set_source_surface ( draw, b->icon, 0, 0 );
    cairo_paint ( draw );
    cairo_restore ( draw );
}
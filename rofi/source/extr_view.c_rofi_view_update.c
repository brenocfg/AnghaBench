#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ gboolean ;
typedef  int /*<<< orphan*/  cairo_t ;
struct TYPE_5__ {scalar_t__ y; scalar_t__ x; } ;
struct TYPE_7__ {int /*<<< orphan*/  edit_surf; TYPE_1__ mon; int /*<<< orphan*/ * fake_bg; scalar_t__ fake_bgrel; int /*<<< orphan*/ * edit_draw; } ;
struct TYPE_6__ {int /*<<< orphan*/  main_window; scalar_t__ y; scalar_t__ x; } ;
typedef  TYPE_2__ RofiViewState ;

/* Variables and functions */
 int /*<<< orphan*/  CAIRO_OPERATOR_OVER ; 
 int /*<<< orphan*/  CAIRO_OPERATOR_SOURCE ; 
 TYPE_4__ CacheState ; 
 int /*<<< orphan*/  TICK () ; 
 int /*<<< orphan*/  TICK_N (char*) ; 
 int /*<<< orphan*/  WIDGET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cairo_paint (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cairo_set_operator (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cairo_set_source_rgba (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,double) ; 
 int /*<<< orphan*/  cairo_set_source_surface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,double,double) ; 
 int /*<<< orphan*/  cairo_surface_flush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_debug (char*) ; 
 int /*<<< orphan*/  rofi_view_queue_redraw () ; 
 int /*<<< orphan*/  widget_draw (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  widget_need_redraw (int /*<<< orphan*/ ) ; 

void rofi_view_update ( RofiViewState *state, gboolean qr )
{
    if ( !widget_need_redraw ( WIDGET ( state->main_window ) ) ) {
        return;
    }
    g_debug ( "Redraw view" );
    TICK ();
    cairo_t *d = CacheState.edit_draw;
    cairo_set_operator ( d, CAIRO_OPERATOR_SOURCE );
    if ( CacheState.fake_bg != NULL ) {
        if ( CacheState.fake_bgrel ) {
            cairo_set_source_surface ( d, CacheState.fake_bg, 0.0, 0.0 );
        }
        else {
            cairo_set_source_surface ( d, CacheState.fake_bg,
                                       -(double) ( state->x - CacheState.mon.x ),
                                       -(double) ( state->y - CacheState.mon.y ) );
        }
        cairo_paint ( d );
        cairo_set_operator ( d, CAIRO_OPERATOR_OVER );
    }
    else {
        // Paint the background transparent.
        cairo_set_source_rgba ( d, 0, 0, 0, 0.0 );
        cairo_paint ( d );
    }
    TICK_N ( "Background" );

    // Always paint as overlay over the background.
    cairo_set_operator ( d, CAIRO_OPERATOR_OVER );
    widget_draw ( WIDGET ( state->main_window ), d );

    TICK_N ( "widgets" );
    cairo_surface_flush ( CacheState.edit_surf );
    if ( qr ) {
        rofi_view_queue_redraw ();
    }
}
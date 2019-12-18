#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {double w; } ;
struct TYPE_9__ {TYPE_1__ mon; scalar_t__ fullscreen; } ;
struct TYPE_8__ {double menu_width; } ;
struct TYPE_7__ {double width; int /*<<< orphan*/  main_window; } ;
typedef  TYPE_2__ RofiViewState ;
typedef  int /*<<< orphan*/  RofiDistance ;

/* Variables and functions */
 TYPE_5__ CacheState ; 
 int /*<<< orphan*/  ROFI_ORIENTATION_HORIZONTAL ; 
 int /*<<< orphan*/  WIDGET (int /*<<< orphan*/ ) ; 
 TYPE_4__ config ; 
 float distance_get_pixel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rofi_theme_get_distance (int /*<<< orphan*/ ,char*,float) ; 
 double textbox_get_estimated_char_width () ; 
 scalar_t__ widget_padding_get_padding_width (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rofi_view_calculate_window_width ( RofiViewState *state )
{
    if ( CacheState.fullscreen ) {
        state->width = CacheState.mon.w;
        return;
    }
    if ( config.menu_width < 0 ) {
        double fw = textbox_get_estimated_char_width ( );
        state->width  = -( fw * config.menu_width );
        state->width += widget_padding_get_padding_width ( WIDGET ( state->main_window ) );
    }
    else{
        // Calculate as float to stop silly, big rounding down errors.
        state->width = config.menu_width < 101 ? ( CacheState.mon.w / 100.0f ) * ( float ) config.menu_width : config.menu_width;
    }
    // Use theme configured width, if set.
    RofiDistance width = rofi_theme_get_distance ( WIDGET ( state->main_window ), "width", state->width );
    state->width = distance_get_pixel ( width, ROFI_ORIENTATION_HORIZONTAL );
}
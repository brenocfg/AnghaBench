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
typedef  int /*<<< orphan*/  widget ;
struct TYPE_5__ {int h; } ;
struct TYPE_7__ {scalar_t__ fullscreen; TYPE_1__ mon; } ;
struct TYPE_6__ {int /*<<< orphan*/  main_window; } ;
typedef  TYPE_2__ RofiViewState ;
typedef  int /*<<< orphan*/  RofiDistance ;

/* Variables and functions */
 TYPE_4__ CacheState ; 
 int /*<<< orphan*/  ROFI_ORIENTATION_VERTICAL ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/ * WIDGET (int /*<<< orphan*/ ) ; 
 unsigned int distance_get_pixel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rofi_theme_get_distance (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int widget_get_desired_height (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int rofi_view_calculate_height ( RofiViewState *state )
{
    if ( CacheState.fullscreen == TRUE ) {
        return CacheState.mon.h;
    }

    RofiDistance h      = rofi_theme_get_distance ( WIDGET ( state->main_window ), "height", 0 );
    unsigned int height = distance_get_pixel ( h, ROFI_ORIENTATION_VERTICAL );
    // If height is set, return it.
    if ( height > 0 ) {
        return height;
    }
    // Autosize based on widgets.
    widget *main_window = WIDGET ( state->main_window );
    return widget_get_desired_height ( main_window );
}
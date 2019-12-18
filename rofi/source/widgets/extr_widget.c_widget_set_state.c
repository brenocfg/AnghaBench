#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {char const* state; int /*<<< orphan*/  def_border_radius; void* border_radius; int /*<<< orphan*/  def_border; void* border; } ;
typedef  TYPE_1__ widget ;

/* Variables and functions */
 scalar_t__ g_strcmp0 (char const*,char const*) ; 
 void* rofi_theme_get_padding (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  widget_queue_redraw (TYPE_1__*) ; 

void widget_set_state ( widget *widget, const char *state )
{
    if ( g_strcmp0 ( widget->state, state ) ) {
        widget->state = state;
        // Update border.
        widget->border        = rofi_theme_get_padding ( widget, "border", widget->def_border );
        widget->border_radius = rofi_theme_get_padding ( widget, "border-radius", widget->def_border_radius );

        widget_queue_redraw ( widget );
    }
}
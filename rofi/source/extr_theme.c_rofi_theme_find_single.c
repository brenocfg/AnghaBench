#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {unsigned int num_widgets; struct TYPE_4__** widgets; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ ThemeWidget ;

/* Variables and functions */
 scalar_t__ g_strcmp0 (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static inline ThemeWidget *rofi_theme_find_single ( ThemeWidget *widget, const char *name )
{
    for ( unsigned int j = 0; widget && j < widget->num_widgets; j++ ) {
        if ( g_strcmp0 ( widget->widgets[j]->name, name ) == 0 ) {
            return widget->widgets[j];
        }
    }
    return widget;
}
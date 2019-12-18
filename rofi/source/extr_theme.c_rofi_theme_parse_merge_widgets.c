#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {unsigned int num_widgets; struct TYPE_8__** widgets; int /*<<< orphan*/  properties; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ ThemeWidget ;

/* Variables and functions */
 int /*<<< orphan*/  g_assert (int /*<<< orphan*/ ) ; 
 scalar_t__ g_strcmp0 (int /*<<< orphan*/ ,char*) ; 
 TYPE_1__* rofi_theme ; 
 TYPE_1__* rofi_theme_find_or_create_name (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rofi_theme_widget_add_properties (TYPE_1__*,int /*<<< orphan*/ ) ; 

void rofi_theme_parse_merge_widgets ( ThemeWidget *parent, ThemeWidget *child )
{
    g_assert ( parent != NULL );
    g_assert ( child != NULL );

    if ( parent == rofi_theme && g_strcmp0(child->name, "*") == 0 ){
        rofi_theme_widget_add_properties ( parent, child->properties);
        return;
    }

    ThemeWidget *w = rofi_theme_find_or_create_name ( parent, child->name);
    rofi_theme_widget_add_properties ( w, child->properties);
    for ( unsigned int i =0; i < child->num_widgets; i++) {
        rofi_theme_parse_merge_widgets ( w, child->widgets[i]);
    }
}
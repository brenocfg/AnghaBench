#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * properties; } ;
typedef  TYPE_1__ ThemeWidget ;
typedef  int /*<<< orphan*/  GHashTable ;
typedef  int /*<<< orphan*/  GDestroyNotify ;

/* Variables and functions */
 int /*<<< orphan*/  g_hash_table_foreach (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * g_hash_table_new_full (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_str_equal ; 
 int /*<<< orphan*/  g_str_hash ; 
 int /*<<< orphan*/  rofi_theme_copy_property_int ; 
 scalar_t__ rofi_theme_property_free ; 

void rofi_theme_widget_add_properties ( ThemeWidget *widget, GHashTable *table )
{
    if ( table == NULL ) {
        return;
    }
    if ( widget->properties == NULL ) {
        widget->properties = g_hash_table_new_full ( g_str_hash, g_str_equal, NULL, (GDestroyNotify) rofi_theme_property_free );
    }
    g_hash_table_foreach ( table, rofi_theme_copy_property_int, widget->properties );
}
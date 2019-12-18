#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  ThemeWidget ;

/* Variables and functions */
 char* PACKAGE_VERSION ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  rofi_theme_print_index (int /*<<< orphan*/ *) ; 

void rofi_theme_print ( ThemeWidget *widget )
{
    if ( widget != NULL ) {
        printf ( "/**\n * rofi -dump-theme output.\n * Rofi version: %s\n **/\n", PACKAGE_VERSION );
        rofi_theme_print_index ( widget );
    }
}
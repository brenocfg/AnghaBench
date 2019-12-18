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
struct TYPE_4__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  ThemeWidget ; 
 TYPE_1__* g_slice_new0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_strdup (char*) ; 
 TYPE_1__* rofi_theme ; 
 int /*<<< orphan*/  rofi_theme_free (TYPE_1__*) ; 
 int /*<<< orphan*/  rofi_theme_insert_listview_backwards_fix () ; 

void rofi_theme_reset ( void )
{
    rofi_theme_free ( rofi_theme );
    rofi_theme       = g_slice_new0 ( ThemeWidget );
    rofi_theme->name = g_strdup ( "Root" );
    // Hack to fix backwards compatibility.
    rofi_theme_insert_listview_backwards_fix ( );
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  gboolean ;
struct TYPE_2__ {scalar_t__ num_widgets; int /*<<< orphan*/ * properties; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 TYPE_1__* rofi_theme ; 

gboolean rofi_theme_is_empty ( void )
{
    if ( rofi_theme == NULL ) {
        return TRUE;
    }
    if ( rofi_theme->properties == NULL && rofi_theme->num_widgets == 0 ) {
        return TRUE;
    }

    return FALSE;
}
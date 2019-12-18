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
typedef  scalar_t__ gboolean ;
typedef  int /*<<< orphan*/  ThemeWidget ;

/* Variables and functions */
 int FALSE ; 
 int TRUE ; 
 int /*<<< orphan*/  g_free (char*) ; 
 char* g_strdup (char const*) ; 
 int /*<<< orphan*/ * rofi_theme_find_single (int /*<<< orphan*/ *,char const*) ; 
 char* strtok_r (char*,char*,char**) ; 

__attribute__((used)) static ThemeWidget *rofi_theme_find ( ThemeWidget *widget, const char *name, const gboolean exact )
{
    if ( widget == NULL || name == NULL ) {
        return widget;
    }
    char *tname   = g_strdup ( name );
    char *saveptr = NULL;
    int  found    = TRUE;
    for ( const char *iter = strtok_r ( tname, ".", &saveptr ); iter != NULL; iter = strtok_r ( NULL, ".", &saveptr ) ) {
        found = FALSE;
        ThemeWidget *f = rofi_theme_find_single ( widget, iter );
        if ( f != widget ) {
            widget = f;
            found  = TRUE;
        }
        else if ( exact ) {
            break;
        }
    }
    g_free ( tname );
    if ( !exact || found ) {
        return widget;
    }
    else {
        return NULL;
    }
}
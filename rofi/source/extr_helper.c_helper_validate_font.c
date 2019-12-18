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
typedef  int /*<<< orphan*/  gboolean ;
typedef  int /*<<< orphan*/  PangoFontDescription ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  g_debug (char*,char const*,...) ; 
 char* pango_font_description_get_family (int /*<<< orphan*/ *) ; 
 int pango_font_description_get_size (int /*<<< orphan*/ *) ; 

gboolean helper_validate_font ( PangoFontDescription *pfd, const char *font )
{
    const char *fam = pango_font_description_get_family ( pfd );
    int        size = pango_font_description_get_size ( pfd );
    if ( fam == NULL || size == 0 ) {
        g_debug ( "Pango failed to parse font: '%s'", font );
        g_debug ( "Got family: <b>%s</b> at size: <b>%d</b>", fam ? fam : "{unknown}", size );
        return FALSE;
    }
    return TRUE;
}
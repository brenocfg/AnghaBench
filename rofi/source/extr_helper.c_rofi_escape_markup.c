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
typedef  int /*<<< orphan*/  gchar ;

/* Variables and functions */
 int /*<<< orphan*/  g_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * g_markup_escape_text (int /*<<< orphan*/ *,int) ; 

gchar *rofi_escape_markup ( gchar *text )
{
    if ( text == NULL ) {
        return NULL;
    }
    gchar *ret = g_markup_escape_text ( text, -1 );
    g_free ( text );
    return ret;
}
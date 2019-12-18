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
typedef  int /*<<< orphan*/  gssize ;
typedef  int /*<<< orphan*/  gsize ;

/* Variables and functions */
 char* g_convert_with_fallback (char const*,int /*<<< orphan*/ ,char*,char*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

char * rofi_latin_to_utf8_strdup ( const char *input, gssize length )
{
    gsize slength = 0;
    return g_convert_with_fallback ( input, length, "UTF-8", "latin1", "\uFFFD", NULL, &slength, NULL );
}
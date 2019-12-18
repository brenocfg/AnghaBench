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

/* Variables and functions */
 char* strdup (char const*) ; 
 int /*<<< orphan*/  vlc_css_unescape (char*) ; 

char * vlc_css_unescaped( const char *psz )
{
    char *psz_ret = strdup( psz );
    vlc_css_unescape( psz_ret );
    return psz_ret;
}
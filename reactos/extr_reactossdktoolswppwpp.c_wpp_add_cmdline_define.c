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
 int /*<<< orphan*/  free (char*) ; 
 char* pp_xstrdup (char const*) ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  wpp_add_define (char*,char*) ; 

int wpp_add_cmdline_define( const char *value )
{
    char *p;
    char *str = pp_xstrdup(value);
    if(!str)
        return 1;
    p = strchr( str, '=' );
    if (p) *p++ = 0;
    wpp_add_define( str, p );
    free( str );
    return 0;
}
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
 char* strpbrk (char*,char const*) ; 

char *strsep( char **ppsz_string, const char *psz_delimiters )
{
    char *psz_string = *ppsz_string;
    if( !psz_string )
        return NULL;

    char *p = strpbrk( psz_string, psz_delimiters );
    if( !p )
    {
        *ppsz_string = NULL;
        return psz_string;
    }
    *p++ = '\0';

    *ppsz_string = p;
    return psz_string;
}
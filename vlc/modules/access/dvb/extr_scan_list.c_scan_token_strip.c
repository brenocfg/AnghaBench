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

__attribute__((used)) static void scan_token_strip( const char **ppsz, size_t *pi_len )
{
    const char *p = *ppsz;
    size_t i_len = *pi_len;

    for ( ; *p <= ' ' && *p ; p++ )
        i_len--;

    for( ; i_len > 0; i_len-- )
    {
        const char c = p[ i_len - 1 ];
        if( c > ' ' || c == '\0' )
            break;
    }

    *ppsz = p;
    *pi_len = i_len;
}
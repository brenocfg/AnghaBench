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
 int strlen (char*) ; 

__attribute__((used)) static char *Trim( char *psz_text )
{
    int i_first_char = -1;
    int i_last_char = -1;
    int i_len = strlen( psz_text );

    for( int i = 0; i < i_len; ++i )
    {
        if( psz_text[i] != ' ')
        {
            if( i_first_char == -1 )
                i_first_char = i;
            i_last_char = i;
        }
    }

    psz_text[ i_last_char + 1 ] = 0;
    if( i_first_char != -1 ) psz_text = psz_text + i_first_char;

    return psz_text;
}
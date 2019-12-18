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
 scalar_t__ strncmp (char const*,char const*,size_t) ; 

__attribute__((used)) static bool exactMatch( const char *psz_target, const char *psz_string,
                        size_t i_len )
{
    if ( strncmp( psz_target, psz_string, i_len ) )
        return false;
    else
        return ( psz_target[i_len] < 'a' || psz_target[i_len] > 'z' );
}
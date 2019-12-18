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
 char const DIR_SEP_CHAR ; 
 int strlen (char const*) ; 

__attribute__((used)) static const char *BaseName( const char *psz_path )
{
    const char *psz_name = psz_path + strlen( psz_path );

    /* skip superfluous separators at the end */
    while( psz_name > psz_path && psz_name[-1] == DIR_SEP_CHAR )
        --psz_name;

    /* skip last component */
    while( psz_name > psz_path && psz_name[-1] != DIR_SEP_CHAR )
        --psz_name;

    return psz_name;
}
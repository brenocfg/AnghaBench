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
 char const** ppsz_lua_exts ; 
 int /*<<< orphan*/  strcmp (char const*,char const*) ; 
 int strlen (char const*) ; 

__attribute__((used)) static int file_select( const char *file )
{
    int i = strlen( file );
    int j;
    for( j = 0; ppsz_lua_exts[j]; j++ )
    {
        int l = strlen( ppsz_lua_exts[j] );
        if( i >= l && !strcmp( file+i-l, ppsz_lua_exts[j] ) )
            return 1;
    }
    return 0;
}
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
typedef  int /*<<< orphan*/  lua_State ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 scalar_t__ luaL_checkudata (int /*<<< orphan*/ *,int,char*) ; 

__attribute__((used)) static int vlclua_io_file_close( lua_State *L )
{
    FILE **pp_file = (FILE**)luaL_checkudata( L, 1, "io_file" );
    if ( *pp_file )
    {
        fclose( *pp_file );
        *pp_file = NULL;
    }
    return 0;
}
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

/* Variables and functions */
 int /*<<< orphan*/  GetConsole (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MAX_LINE_LENGTH ; 
 int /*<<< orphan*/  ReadWin32 (int /*<<< orphan*/ ,unsigned char*,int*) ; 
 int /*<<< orphan*/  lua_pushlstring (int /*<<< orphan*/ *,char*,int) ; 

__attribute__((used)) static int vlclua_console_read( lua_State *L )
{
    char psz_buffer[MAX_LINE_LENGTH+1];
    int i_size = 0;
    ReadWin32( GetConsole( L ), (unsigned char*)psz_buffer, &i_size );
    lua_pushlstring( L, psz_buffer, i_size );

    return 1;
}
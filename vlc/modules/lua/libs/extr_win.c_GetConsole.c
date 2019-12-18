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
typedef  scalar_t__ HANDLE ;

/* Variables and functions */
 scalar_t__ GetStdHandle (int /*<<< orphan*/ ) ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 int /*<<< orphan*/  STD_INPUT_HANDLE ; 
 int /*<<< orphan*/  luaL_error (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static HANDLE GetConsole( lua_State *L )
{
    /* Get the file descriptor of the console input */
    HANDLE hConsoleIn = GetStdHandle(STD_INPUT_HANDLE);
    if( hConsoleIn == INVALID_HANDLE_VALUE )
        luaL_error( L, "couldn't find user input handle" );
    return hConsoleIn;
}
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
 int /*<<< orphan*/  free (char*) ; 
 char* input_item_GetName (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pushstring (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  vlclua_input_item_get_internal (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int vlclua_input_item_name( lua_State *L )
{
    char *name = input_item_GetName( vlclua_input_item_get_internal( L ) );
    lua_pushstring( L, name );
    free( name );
    return 1;
}
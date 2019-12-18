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
typedef  int /*<<< orphan*/  input_item_t ;

/* Variables and functions */
 int /*<<< orphan*/ ** luaL_checkudata (int /*<<< orphan*/ *,int,char*) ; 
 int vlclua_sd_delete_common (int /*<<< orphan*/ **) ; 

__attribute__((used)) static int vlclua_sd_item_delete( lua_State *L )
{
    input_item_t **pp_item = luaL_checkudata( L, 1, "input_item_t" );

    return vlclua_sd_delete_common( pp_item );
}
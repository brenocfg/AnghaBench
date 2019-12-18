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
typedef  int /*<<< orphan*/  services_discovery_t ;
typedef  int /*<<< orphan*/  lua_State ;
typedef  int /*<<< orphan*/  input_item_t ;

/* Variables and functions */
 int /*<<< orphan*/  input_item_Release (int /*<<< orphan*/ *) ; 
 int luaL_error (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  services_discovery_RemoveItem (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ vlclua_get_this (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int vlclua_sd_remove_common( lua_State *L, input_item_t **pp_item )
{
    services_discovery_t *p_sd = (services_discovery_t *)vlclua_get_this( L );

    if (pp_item == NULL)
        return luaL_error( L, "expected item" );

    input_item_t *p_item = *pp_item;
    if (*pp_item == NULL)
        return luaL_error( L, "already removed item" );

    services_discovery_RemoveItem( p_sd, p_item );
    input_item_Release( p_item );
    /* Make sure we won't try to remove it again */
    *pp_item = NULL;
    return 1;
}
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
typedef  int /*<<< orphan*/  mp_buf ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  mp_encode_lua_table_as_array (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mp_encode_lua_table_as_map (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 scalar_t__ table_is_an_array (int /*<<< orphan*/ *) ; 

void mp_encode_lua_table(lua_State *L, mp_buf *buf, int level) {
    if (table_is_an_array(L))
        mp_encode_lua_table_as_array(L,buf,level);
    else
        mp_encode_lua_table_as_map(L,buf,level);
}
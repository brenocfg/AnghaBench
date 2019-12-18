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
typedef  scalar_t__ lua_Number ;

/* Variables and functions */
 scalar_t__ IS_INT64_EQUIVALENT (scalar_t__) ; 
 scalar_t__ lua_tonumber (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mp_encode_double (int /*<<< orphan*/ *,int /*<<< orphan*/ *,double) ; 
 int /*<<< orphan*/  mp_encode_lua_integer (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void mp_encode_lua_number(lua_State *L, mp_buf *buf) {
    lua_Number n = lua_tonumber(L,-1);

    if (IS_INT64_EQUIVALENT(n)) {
        mp_encode_lua_integer(L, buf);
    } else {
        mp_encode_double(L,buf,(double)n);
    }
}
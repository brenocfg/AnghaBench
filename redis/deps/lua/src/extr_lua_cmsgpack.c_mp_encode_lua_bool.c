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
 scalar_t__ lua_toboolean (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mp_buf_append (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned char*,int) ; 

void mp_encode_lua_bool(lua_State *L, mp_buf *buf) {
    unsigned char b = lua_toboolean(L,-1) ? 0xc3 : 0xc2;
    mp_buf_append(L,buf,&b,1);
}
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
 char* lua_tolstring (int /*<<< orphan*/ *,int,size_t*) ; 
 int /*<<< orphan*/  mp_encode_bytes (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned char const*,size_t) ; 

void mp_encode_lua_string(lua_State *L, mp_buf *buf) {
    size_t len;
    const char *s;

    s = lua_tolstring(L,-1,&len);
    mp_encode_bytes(L,buf,(const unsigned char*)s,len);
}
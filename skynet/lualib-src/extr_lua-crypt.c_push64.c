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
typedef  int uint8_t ;
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  lua_pushlstring (int /*<<< orphan*/ *,char const*,int) ; 

__attribute__((used)) static void
push64(lua_State *L, uint64_t r) {
	uint8_t tmp[8];
	tmp[0] = r & 0xff;
	tmp[1] = (r >> 8 )& 0xff;
	tmp[2] = (r >> 16 )& 0xff;
	tmp[3] = (r >> 24 )& 0xff;
	tmp[4] = (r >> 32 )& 0xff;
	tmp[5] = (r >> 40 )& 0xff;
	tmp[6] = (r >> 48 )& 0xff;
	tmp[7] = (r >> 56 )& 0xff;

	lua_pushlstring(L, (const char *)tmp, 8);
}
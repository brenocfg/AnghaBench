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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  G ; 
 scalar_t__ luaL_checklstring (int /*<<< orphan*/ *,int,size_t*) ; 
 int luaL_error (int /*<<< orphan*/ *,char*) ; 
 int powmodp (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  push64 (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
ldhexchange(lua_State *L) {
	size_t sz = 0;
	const uint8_t *x = (const uint8_t *)luaL_checklstring(L, 1, &sz);
	if (sz != 8) {
		luaL_error(L, "Invalid dh uint64 key");
	}
	uint32_t xx[2];
	xx[0] = x[0] | x[1]<<8 | x[2]<<16 | x[3]<<24;
	xx[1] = x[4] | x[5]<<8 | x[6]<<16 | x[7]<<24;

	uint64_t x64 = (uint64_t)xx[0] | (uint64_t)xx[1]<<32;
	if (x64 == 0)
		return luaL_error(L, "Can't be 0");

	uint64_t r = powmodp(G,	x64);
	push64(L, r);
	return 1;
}
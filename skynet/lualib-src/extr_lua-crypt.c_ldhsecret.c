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
typedef  int uint64_t ;
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int luaL_error (int /*<<< orphan*/ *,char*) ; 
 int powmodp (int,int) ; 
 int /*<<< orphan*/  push64 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  read64 (int /*<<< orphan*/ *,scalar_t__*,scalar_t__*) ; 

__attribute__((used)) static int
ldhsecret(lua_State *L) {
	uint32_t x[2], y[2];
	read64(L, x, y);
	uint64_t xx = (uint64_t)x[0] | (uint64_t)x[1]<<32;
	uint64_t yy = (uint64_t)y[0] | (uint64_t)y[1]<<32;
	if (xx == 0 || yy == 0)
		return luaL_error(L, "Can't be 0");
	uint64_t r = powmodp(xx, yy);

	push64(L, r);

	return 1;
}
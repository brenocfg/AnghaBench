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
typedef  scalar_t__ uint32_t ;
struct mc_package {void* data; scalar_t__ size; scalar_t__ reference; } ;
typedef  int /*<<< orphan*/  ret ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  lua_pushinteger (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushlightuserdata (int /*<<< orphan*/ *,struct mc_package**) ; 
 void* skynet_malloc (int) ; 

__attribute__((used)) static int
pack(lua_State *L, void *data, size_t size) {
	struct mc_package * pack = skynet_malloc(sizeof(struct mc_package));
	pack->reference = 0;
	pack->size = (uint32_t)size;
	pack->data = data;
	struct mc_package ** ret = skynet_malloc(sizeof(*ret));
	*ret = pack;
	lua_pushlightuserdata(L, ret);
	lua_pushinteger(L, sizeof(ret));
	return 2;
}
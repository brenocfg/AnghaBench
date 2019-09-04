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
struct bson_reader {int size; } ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  luaL_error (int /*<<< orphan*/ *,char*,int,int) ; 

__attribute__((used)) static inline void
check_reader(lua_State *L, struct bson_reader *br, int sz) {
	if (br->size < sz) {
		luaL_error(L, "Invalid bson block (%d:%d)", br->size, sz);
	}
}
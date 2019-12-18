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
struct bson {scalar_t__ size; } ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 scalar_t__ lua_next (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushnil (int /*<<< orphan*/ *) ; 
 int lua_type (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pack_dict_data (int /*<<< orphan*/ *,struct bson*,int,int) ; 
 int reserve_length (struct bson*) ; 
 int /*<<< orphan*/  write_byte (struct bson*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_length (struct bson*,scalar_t__,int) ; 

__attribute__((used)) static void
pack_simple_dict(lua_State *L, struct bson *b, int depth) {
	int length = reserve_length(b);
	lua_pushnil(L);
	while(lua_next(L,-2) != 0) {
		int kt = lua_type(L, -2);
		pack_dict_data(L, b, depth, kt);
	}
	write_byte(b,0);
	write_length(b, b->size - length, length);
}
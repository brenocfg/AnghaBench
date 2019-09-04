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
struct boxstm {int /*<<< orphan*/  obj; } ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  lua_pushlightuserdata (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct boxstm* lua_touserdata (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stm_grab (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
lcopy(lua_State *L) {
	struct boxstm * box = lua_touserdata(L, 1);
	stm_grab(box->obj);
	lua_pushlightuserdata(L, box->obj);
	return 1;
}
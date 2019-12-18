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
struct mc_package {struct mc_package* data; int /*<<< orphan*/  reference; } ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int ATOM_DEC (int /*<<< orphan*/ *) ; 
 int luaL_error (int /*<<< orphan*/ *,char*,int) ; 
 struct mc_package* lua_touserdata (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  skynet_free (struct mc_package*) ; 

__attribute__((used)) static int
mc_closelocal(lua_State *L) {
	struct mc_package *pack = lua_touserdata(L,1);

	int ref = ATOM_DEC(&pack->reference);
	if (ref <= 0) {
		skynet_free(pack->data);
		skynet_free(pack);
		if (ref < 0) {
			return luaL_error(L, "Invalid multicast package reference %d", ref);
		}
	}

	return 0;
}
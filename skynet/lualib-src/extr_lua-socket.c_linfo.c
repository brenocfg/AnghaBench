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
struct socket_info {struct socket_info* next; } ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  getinfo (int /*<<< orphan*/ *,struct socket_info*) ; 
 int /*<<< orphan*/  lua_newtable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_seti (int /*<<< orphan*/ *,int,int) ; 
 struct socket_info* skynet_socket_info () ; 
 int /*<<< orphan*/  socket_info_release (struct socket_info*) ; 

__attribute__((used)) static int
linfo(lua_State *L) {
	lua_newtable(L);
	struct socket_info * si = skynet_socket_info();
	struct socket_info * temp = si;
	int n = 0;
	while (temp) {
		getinfo(L, temp);
		lua_seti(L, -2, ++n);
		temp = temp->next;
	}
	socket_info_release(si);
	return 1;
}
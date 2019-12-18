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
typedef  scalar_t__ t_socket ;
typedef  int /*<<< orphan*/  lua_State ;
typedef  int lua_Number ;
typedef  int /*<<< orphan*/  fd_set ;

/* Variables and functions */
 scalar_t__ FD_ISSET (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_gettable (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushnumber (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_settable (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void return_fd(lua_State *L, fd_set *set, t_socket max_fd, 
        int itab, int tab, int start) {
    t_socket fd;
    for (fd = 0; fd < max_fd; fd++) {
        if (FD_ISSET(fd, set)) {
            lua_pushnumber(L, ++start);
            lua_pushnumber(L, (lua_Number) fd);
            lua_gettable(L, itab);
            lua_settable(L, tab);
        }
    }
}
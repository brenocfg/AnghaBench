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
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 scalar_t__ EAGAIN ; 
 scalar_t__ EINTR ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  luaL_error (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int send (int,char const*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strerror (scalar_t__) ; 

__attribute__((used)) static void
block_send(lua_State *L, int fd, const char * buffer, int sz) {
	while(sz > 0) {
		int r = send(fd, buffer, sz, 0);
		if (r < 0) {
			if (errno == EAGAIN || errno == EINTR)
				continue;
			luaL_error(L, "socket error: %s", strerror(errno));
		}
		buffer += r;
		sz -= r;
	}
}
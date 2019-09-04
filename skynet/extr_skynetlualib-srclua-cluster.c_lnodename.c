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
typedef  scalar_t__ pid_t ;
typedef  int /*<<< orphan*/  lua_State ;
typedef  int /*<<< orphan*/  hostname ;

/* Variables and functions */
 scalar_t__ gethostname (char*,int) ; 
 scalar_t__ getpid () ; 
 int /*<<< orphan*/  lua_pushfstring (int /*<<< orphan*/ *,char*,...) ; 

__attribute__((used)) static int
lnodename(lua_State *L) {
	pid_t pid = getpid();
	char hostname[256];
	if (gethostname(hostname, sizeof(hostname))==0) {
		lua_pushfstring(L, "%s%d", hostname, (int)pid);
	} else {
		lua_pushfstring(L, "noname%d", (int)pid);
	}
	return 1;
}
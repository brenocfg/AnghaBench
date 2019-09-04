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
struct socket_info {int type; char* name; int /*<<< orphan*/  wtime; int /*<<< orphan*/  rtime; int /*<<< orphan*/  wbuffer; int /*<<< orphan*/  write; int /*<<< orphan*/  read; int /*<<< orphan*/  opaque; int /*<<< orphan*/  id; } ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
#define  SOCKET_INFO_BIND 131 
#define  SOCKET_INFO_LISTEN 130 
#define  SOCKET_INFO_TCP 129 
#define  SOCKET_INFO_UDP 128 
 int /*<<< orphan*/  lua_newtable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pushinteger (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pushstring (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  lua_setfield (int /*<<< orphan*/ *,int,char*) ; 

__attribute__((used)) static void
getinfo(lua_State *L, struct socket_info *si) {
	lua_newtable(L);
	lua_pushinteger(L, si->id);
	lua_setfield(L, -2, "id");
	lua_pushinteger(L, si->opaque);
	lua_setfield(L, -2, "address");
	switch(si->type) {
	case SOCKET_INFO_LISTEN:
		lua_pushstring(L, "LISTEN");
		lua_setfield(L, -2, "type");
		lua_pushinteger(L, si->read);
		lua_setfield(L, -2, "accept");
		lua_pushinteger(L, si->rtime);
		lua_setfield(L, -2, "rtime");
		if (si->name[0]) {
			lua_pushstring(L, si->name);
			lua_setfield(L, -2, "sock");
		}
		return;
	case SOCKET_INFO_TCP:
		lua_pushstring(L, "TCP");
		break;
	case SOCKET_INFO_UDP:
		lua_pushstring(L, "UDP");
		break;
	case SOCKET_INFO_BIND:
		lua_pushstring(L, "BIND");
		break;
	default:
		lua_pushstring(L, "UNKNOWN");
		lua_setfield(L, -2, "type");
		return;
	}
	lua_setfield(L, -2, "type");
	lua_pushinteger(L, si->read);
	lua_setfield(L, -2, "read");
	lua_pushinteger(L, si->write);
	lua_setfield(L, -2, "write");
	lua_pushinteger(L, si->wbuffer);
	lua_setfield(L, -2, "wbuffer");
	lua_pushinteger(L, si->rtime);
	lua_setfield(L, -2, "rtime");
	lua_pushinteger(L, si->wtime);
	lua_setfield(L, -2, "wtime");
	if (si->name[0]) {
		lua_pushstring(L, si->name);
		lua_setfield(L, -2, "peer");
	}
}
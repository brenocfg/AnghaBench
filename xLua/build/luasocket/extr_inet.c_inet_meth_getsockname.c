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
struct sockaddr_storage {int dummy; } ;
struct sockaddr {int dummy; } ;
typedef  int socklen_t ;
typedef  int /*<<< orphan*/  peer ;
typedef  int /*<<< orphan*/ * p_socket ;
typedef  int /*<<< orphan*/  lua_State ;
typedef  int /*<<< orphan*/  SA ;

/* Variables and functions */
 int INET6_ADDRSTRLEN ; 
 int NI_NUMERICHOST ; 
 int NI_NUMERICSERV ; 
 int PF_INET ; 
 int PF_INET6 ; 
 int /*<<< orphan*/  errno ; 
 char* gai_strerror (int) ; 
 int getnameinfo (struct sockaddr*,int,char*,int,char*,int,int) ; 
 scalar_t__ getsockname (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  lua_pushliteral (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  lua_pushnil (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pushstring (int /*<<< orphan*/ *,char*) ; 
 char* socket_strerror (int /*<<< orphan*/ ) ; 

int inet_meth_getsockname(lua_State *L, p_socket ps, int family)
{
    int err;
    struct sockaddr_storage peer;
    socklen_t peer_len = sizeof(peer);
    char name[INET6_ADDRSTRLEN];
    char port[6]; /* 65535 = 5 bytes + 0 to terminate it */
    if (getsockname(*ps, (SA *) &peer, &peer_len) < 0) {
        lua_pushnil(L);
        lua_pushstring(L, socket_strerror(errno));
        return 2;
    }
	err=getnameinfo((struct sockaddr *)&peer, peer_len, 
		name, INET6_ADDRSTRLEN, port, 6, NI_NUMERICHOST | NI_NUMERICSERV);
    if (err) {
        lua_pushnil(L);
        lua_pushstring(L, gai_strerror(err));
        return 2;
    }
    lua_pushstring(L, name);
    lua_pushstring(L, port);
    if (family == PF_INET) {
        lua_pushliteral(L, "inet");
    } else if (family == PF_INET6) {
        lua_pushliteral(L, "inet6");
    } else {
        lua_pushliteral(L, "uknown family");
    }
    return 3;
}
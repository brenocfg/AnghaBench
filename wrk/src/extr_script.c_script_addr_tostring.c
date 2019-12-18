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
struct addrinfo {int /*<<< orphan*/  ai_addrlen; int /*<<< orphan*/  ai_addr; } ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int NI_MAXHOST ; 
 int NI_MAXSERV ; 
 int NI_NUMERICHOST ; 
 int NI_NUMERICSERV ; 
 struct addrinfo* checkaddr (int /*<<< orphan*/ *) ; 
 char* gai_strerror (int) ; 
 int getnameinfo (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,char*,int,int) ; 
 int luaL_error (int /*<<< orphan*/ *,char*,char const*) ; 
 int /*<<< orphan*/  lua_pushfstring (int /*<<< orphan*/ *,char*,char*,char*) ; 

__attribute__((used)) static int script_addr_tostring(lua_State *L) {
    struct addrinfo *addr = checkaddr(L);
    char host[NI_MAXHOST];
    char service[NI_MAXSERV];

    int flags = NI_NUMERICHOST | NI_NUMERICSERV;
    int rc = getnameinfo(addr->ai_addr, addr->ai_addrlen, host, NI_MAXHOST, service, NI_MAXSERV, flags);
    if (rc != 0) {
        const char *msg = gai_strerror(rc);
        return luaL_error(L, "addr tostring failed %s", msg);
    }

    lua_pushfstring(L, "%s:%s", host, service);
    return 1;
}
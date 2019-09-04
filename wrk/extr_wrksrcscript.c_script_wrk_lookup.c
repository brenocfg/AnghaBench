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
struct addrinfo {struct addrinfo* ai_next; int /*<<< orphan*/  ai_socktype; int /*<<< orphan*/  ai_family; } ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  AF_UNSPEC ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*,char const*,char const*) ; 
 int /*<<< orphan*/  freeaddrinfo (struct addrinfo*) ; 
 char* gai_strerror (int) ; 
 int getaddrinfo (char const*,char const*,struct addrinfo*,struct addrinfo**) ; 
 int /*<<< orphan*/  lua_newtable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_rawseti (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 char* lua_tostring (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  script_addr_clone (int /*<<< orphan*/ *,struct addrinfo*) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static int script_wrk_lookup(lua_State *L) {
    struct addrinfo *addrs;
    struct addrinfo hints = {
        .ai_family   = AF_UNSPEC,
        .ai_socktype = SOCK_STREAM
    };
    int rc, index = 1;

    const char *host    = lua_tostring(L, -2);
    const char *service = lua_tostring(L, -1);

    if ((rc = getaddrinfo(host, service, &hints, &addrs)) != 0) {
        const char *msg = gai_strerror(rc);
        fprintf(stderr, "unable to resolve %s:%s %s\n", host, service, msg);
        exit(1);
    }

    lua_newtable(L);
    for (struct addrinfo *addr = addrs; addr != NULL; addr = addr->ai_next) {
        script_addr_clone(L, addr);
        lua_rawseti(L, -2, index++);
    }

    freeaddrinfo(addrs);
    return 1;
}
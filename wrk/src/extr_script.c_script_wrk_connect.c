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
struct addrinfo {int /*<<< orphan*/  ai_addrlen; int /*<<< orphan*/  ai_addr; int /*<<< orphan*/  ai_protocol; int /*<<< orphan*/  ai_socktype; int /*<<< orphan*/  ai_family; } ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 struct addrinfo* checkaddr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ connect (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pushboolean (int /*<<< orphan*/ *,int) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int script_wrk_connect(lua_State *L) {
    struct addrinfo *addr = checkaddr(L);
    int fd, connected = 0;
    if ((fd = socket(addr->ai_family, addr->ai_socktype, addr->ai_protocol)) != -1) {
        connected = connect(fd, addr->ai_addr, addr->ai_addrlen) == 0;
        close(fd);
    }
    lua_pushboolean(L, connected);
    return 1;
}
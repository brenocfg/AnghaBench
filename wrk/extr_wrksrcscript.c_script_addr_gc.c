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
struct addrinfo {int /*<<< orphan*/  ai_addr; } ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 struct addrinfo* checkaddr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfree (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int script_addr_gc(lua_State *L) {
    struct addrinfo *addr = checkaddr(L);
    zfree(addr->ai_addr);
    return 0;
}
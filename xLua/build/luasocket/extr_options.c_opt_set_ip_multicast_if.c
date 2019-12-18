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
typedef  int /*<<< orphan*/  val ;
struct in_addr {int /*<<< orphan*/  s_addr; } ;
typedef  int /*<<< orphan*/  p_socket ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  INADDR_ANY ; 
 int /*<<< orphan*/  IPPROTO_IP ; 
 int /*<<< orphan*/  IP_MULTICAST_IF ; 
 int /*<<< orphan*/  htonl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inet_aton (char const*,struct in_addr*) ; 
 int /*<<< orphan*/  luaL_argerror (int /*<<< orphan*/ *,int,char*) ; 
 char* luaL_checkstring (int /*<<< orphan*/ *,int) ; 
 int opt_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ strcmp (char const*,char*) ; 

int opt_set_ip_multicast_if(lua_State *L, p_socket ps)
{
    const char *address = luaL_checkstring(L, 3);    /* obj, name, ip */
    struct in_addr val;
    val.s_addr = htonl(INADDR_ANY);
    if (strcmp(address, "*") && !inet_aton(address, &val))
        luaL_argerror(L, 3, "ip expected");
    return opt_set(L, ps, IPPROTO_IP, IP_MULTICAST_IF, 
        (char *) &val, sizeof(val));
}
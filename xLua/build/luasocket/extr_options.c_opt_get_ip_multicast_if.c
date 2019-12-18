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
struct in_addr {int dummy; } ;
typedef  int socklen_t ;
typedef  int /*<<< orphan*/ * p_socket ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  IPPROTO_IP ; 
 int /*<<< orphan*/  IP_MULTICAST_IF ; 
 scalar_t__ getsockopt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int*) ; 
 char* inet_ntoa (struct in_addr) ; 
 int /*<<< orphan*/  lua_pushnil (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pushstring (int /*<<< orphan*/ *,char*) ; 

int opt_get_ip_multicast_if(lua_State *L, p_socket ps)
{
    struct in_addr val;
    socklen_t len = sizeof(val);
    if (getsockopt(*ps, IPPROTO_IP, IP_MULTICAST_IF, (char *) &val, &len) < 0) {
        lua_pushnil(L);
        lua_pushstring(L, "getsockopt failed");
        return 2;
    }
    lua_pushstring(L, inet_ntoa(val));
    return 1;
}
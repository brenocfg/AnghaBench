#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  yes ;
typedef  int /*<<< orphan*/  t_udp ;
typedef  int /*<<< orphan*/  t_socket ;
typedef  TYPE_1__* p_udp ;
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_2__ {int family; int /*<<< orphan*/  tm; int /*<<< orphan*/  sock; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPPROTO_IPV6 ; 
 int /*<<< orphan*/  IPV6_V6ONLY ; 
 int PF_INET6 ; 
 int /*<<< orphan*/  SOCK_DGRAM ; 
 int /*<<< orphan*/  auxiliar_setclass (int /*<<< orphan*/ *,char*,int) ; 
 char* inet_trycreate (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_newuserdata (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushnil (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pushstring (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  setsockopt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int) ; 
 int /*<<< orphan*/  socket_setnonblocking (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timeout_init (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static int udp_create(lua_State *L, int family) {
    t_socket sock;
    const char *err = inet_trycreate(&sock, family, SOCK_DGRAM);
    /* try to allocate a system socket */
    if (!err) {
        /* allocate udp object */
        p_udp udp = (p_udp) lua_newuserdata(L, sizeof(t_udp));
        auxiliar_setclass(L, "udp{unconnected}", -1);
        /* initialize remaining structure fields */
        socket_setnonblocking(&sock);
        if (family == PF_INET6) {
            int yes = 1;
            setsockopt(sock, IPPROTO_IPV6, IPV6_V6ONLY,
                (void *)&yes, sizeof(yes));
        }
        udp->sock = sock;
        timeout_init(&udp->tm, -1, -1);
        udp->family = family;
        return 1;
    } else {
        lua_pushnil(L);
        lua_pushstring(L, err);
        return 2;
    }
}
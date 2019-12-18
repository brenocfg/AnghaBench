#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  yes ;
typedef  int /*<<< orphan*/  t_tcp ;
typedef  int /*<<< orphan*/  t_socket ;
typedef  TYPE_1__* p_tcp ;
typedef  int /*<<< orphan*/  p_send ;
typedef  int /*<<< orphan*/  p_recv ;
typedef  int /*<<< orphan*/  p_error ;
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_3__ {int family; int /*<<< orphan*/  tm; int /*<<< orphan*/  io; int /*<<< orphan*/  buf; int /*<<< orphan*/  sock; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPPROTO_IPV6 ; 
 int /*<<< orphan*/  IPV6_V6ONLY ; 
 int PF_INET6 ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int /*<<< orphan*/  auxiliar_setclass (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  buffer_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* inet_trycreate (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  io_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_newuserdata (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushnil (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pushstring (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  setsockopt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int) ; 
 scalar_t__ socket_ioerror ; 
 scalar_t__ socket_recv ; 
 scalar_t__ socket_send ; 
 int /*<<< orphan*/  socket_setnonblocking (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timeout_init (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static int tcp_create(lua_State *L, int family) {
    t_socket sock;
    const char *err = inet_trycreate(&sock, family, SOCK_STREAM);
    /* try to allocate a system socket */
    if (!err) {
        /* allocate tcp object */
        p_tcp tcp = (p_tcp) lua_newuserdata(L, sizeof(t_tcp));
        memset(tcp, 0, sizeof(t_tcp));
        /* set its type as master object */
        auxiliar_setclass(L, "tcp{master}", -1);
        /* initialize remaining structure fields */
        socket_setnonblocking(&sock);
        if (family == PF_INET6) {
            int yes = 1;
            setsockopt(sock, IPPROTO_IPV6, IPV6_V6ONLY,
                (void *)&yes, sizeof(yes));
        }
        tcp->sock = sock;
        io_init(&tcp->io, (p_send) socket_send, (p_recv) socket_recv,
                (p_error) socket_ioerror, &tcp->sock);
        timeout_init(&tcp->tm, -1, -1);
        buffer_init(&tcp->buf, &tcp->io, &tcp->tm);
        tcp->family = family;
        return 1;
    } else {
        lua_pushnil(L);
        lua_pushstring(L, err);
        return 2;
    }
}
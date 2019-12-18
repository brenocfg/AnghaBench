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
typedef  int /*<<< orphan*/  t_tcp ;
typedef  int /*<<< orphan*/  t_socket ;
typedef  int /*<<< orphan*/  p_timeout ;
typedef  TYPE_1__* p_tcp ;
typedef  int /*<<< orphan*/  p_send ;
typedef  int /*<<< orphan*/  p_recv ;
typedef  int /*<<< orphan*/  p_error ;
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_3__ {int /*<<< orphan*/  family; int /*<<< orphan*/  tm; int /*<<< orphan*/  io; int /*<<< orphan*/  buf; int /*<<< orphan*/  sock; } ;

/* Variables and functions */
 int /*<<< orphan*/  auxiliar_checkclass (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  auxiliar_setclass (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  buffer_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* inet_tryaccept (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  io_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_newuserdata (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushnil (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pushstring (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ socket_ioerror ; 
 scalar_t__ socket_recv ; 
 scalar_t__ socket_send ; 
 int /*<<< orphan*/  socket_setnonblocking (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timeout_init (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  timeout_markstart (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int meth_accept(lua_State *L)
{
    p_tcp server = (p_tcp) auxiliar_checkclass(L, "tcp{server}", 1);
    p_timeout tm = timeout_markstart(&server->tm);
    t_socket sock;
    const char *err = inet_tryaccept(&server->sock, server->family, &sock, tm);
    /* if successful, push client socket */
    if (err == NULL) {
        p_tcp clnt = (p_tcp) lua_newuserdata(L, sizeof(t_tcp));
        auxiliar_setclass(L, "tcp{client}", -1);
        /* initialize structure fields */
        memset(clnt, 0, sizeof(t_tcp));
        socket_setnonblocking(&sock);
        clnt->sock = sock;
        io_init(&clnt->io, (p_send) socket_send, (p_recv) socket_recv,
                (p_error) socket_ioerror, &clnt->sock);
        timeout_init(&clnt->tm, -1, -1);
        buffer_init(&clnt->buf, &clnt->io, &clnt->tm);
        clnt->family = server->family;
        return 1;
    } else {
        lua_pushnil(L);
        lua_pushstring(L, err);
        return 2;
    }
}
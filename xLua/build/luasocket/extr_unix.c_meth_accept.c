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
typedef  int /*<<< orphan*/  t_unix ;
typedef  int /*<<< orphan*/  t_socket ;
typedef  TYPE_1__* p_unix ;
typedef  int /*<<< orphan*/  p_timeout ;
typedef  int /*<<< orphan*/  p_send ;
typedef  int /*<<< orphan*/  p_recv ;
typedef  int /*<<< orphan*/  p_error ;
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_2__ {int /*<<< orphan*/  tm; int /*<<< orphan*/  io; int /*<<< orphan*/  buf; int /*<<< orphan*/  sock; } ;

/* Variables and functions */
 int IO_DONE ; 
 int /*<<< orphan*/  auxiliar_checkclass (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  auxiliar_setclass (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  buffer_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  io_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_newuserdata (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushnil (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pushstring (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int socket_accept (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ socket_ioerror ; 
 scalar_t__ socket_recv ; 
 scalar_t__ socket_send ; 
 int /*<<< orphan*/  socket_setnonblocking (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  socket_strerror (int) ; 
 int /*<<< orphan*/  timeout_init (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  timeout_markstart (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int meth_accept(lua_State *L) {
    p_unix server = (p_unix) auxiliar_checkclass(L, "unix{server}", 1);
    p_timeout tm = timeout_markstart(&server->tm);
    t_socket sock;
    int err = socket_accept(&server->sock, &sock, NULL, NULL, tm);
    /* if successful, push client socket */
    if (err == IO_DONE) {
        p_unix clnt = (p_unix) lua_newuserdata(L, sizeof(t_unix));
        auxiliar_setclass(L, "unix{client}", -1);
        /* initialize structure fields */
        socket_setnonblocking(&sock);
        clnt->sock = sock;
        io_init(&clnt->io, (p_send)socket_send, (p_recv)socket_recv, 
                (p_error) socket_ioerror, &clnt->sock);
        timeout_init(&clnt->tm, -1, -1);
        buffer_init(&clnt->buf, &clnt->io, &clnt->tm);
        return 1;
    } else {
        lua_pushnil(L); 
        lua_pushstring(L, socket_strerror(err));
        return 2;
    }
}
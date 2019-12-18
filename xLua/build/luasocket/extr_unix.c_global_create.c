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
typedef  int /*<<< orphan*/  p_send ;
typedef  int /*<<< orphan*/  p_recv ;
typedef  int /*<<< orphan*/  p_error ;
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_2__ {int /*<<< orphan*/  tm; int /*<<< orphan*/  io; int /*<<< orphan*/  buf; int /*<<< orphan*/  sock; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_UNIX ; 
 int IO_DONE ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int /*<<< orphan*/  auxiliar_setclass (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  buffer_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  io_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_newuserdata (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushnil (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pushstring (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int socket_create (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ socket_ioerror ; 
 scalar_t__ socket_recv ; 
 scalar_t__ socket_send ; 
 int /*<<< orphan*/  socket_setnonblocking (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  socket_strerror (int) ; 
 int /*<<< orphan*/  timeout_init (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static int global_create(lua_State *L) {
    t_socket sock;
    int err = socket_create(&sock, AF_UNIX, SOCK_STREAM, 0);
    /* try to allocate a system socket */
    if (err == IO_DONE) { 
        /* allocate unix object */
        p_unix un = (p_unix) lua_newuserdata(L, sizeof(t_unix));
        /* set its type as master object */
        auxiliar_setclass(L, "unix{master}", -1);
        /* initialize remaining structure fields */
        socket_setnonblocking(&sock);
        un->sock = sock;
        io_init(&un->io, (p_send) socket_send, (p_recv) socket_recv, 
                (p_error) socket_ioerror, &un->sock);
        timeout_init(&un->tm, -1, -1);
        buffer_init(&un->buf, &un->io, &un->tm);
        return 1;
    } else {
        lua_pushnil(L);
        lua_pushstring(L, socket_strerror(err));
        return 2;
    }
}
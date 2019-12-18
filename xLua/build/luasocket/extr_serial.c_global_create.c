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
typedef  scalar_t__ t_socket ;
typedef  TYPE_1__* p_unix ;
typedef  int /*<<< orphan*/  p_send ;
typedef  int /*<<< orphan*/  p_recv ;
typedef  int /*<<< orphan*/  p_error ;
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_2__ {int /*<<< orphan*/  tm; int /*<<< orphan*/  io; int /*<<< orphan*/  buf; scalar_t__ sock; } ;

/* Variables and functions */
 int O_NOCTTY ; 
 int O_RDWR ; 
 int /*<<< orphan*/  auxiliar_setclass (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  buffer_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  io_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 char* luaL_checkstring (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_newuserdata (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushnil (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pushnumber (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pushstring (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ open (char const*,int) ; 
 scalar_t__ socket_ioerror ; 
 scalar_t__ socket_read ; 
 int /*<<< orphan*/  socket_setnonblocking (scalar_t__*) ; 
 int /*<<< orphan*/  socket_strerror (int /*<<< orphan*/ ) ; 
 scalar_t__ socket_write ; 
 int /*<<< orphan*/  timeout_init (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static int global_create(lua_State *L) {
    const char* path = luaL_checkstring(L, 1);

    /* allocate unix object */
    p_unix un = (p_unix) lua_newuserdata(L, sizeof(t_unix));

    /* open serial device */
    t_socket sock = open(path, O_NOCTTY|O_RDWR);

    /*printf("open %s on %d\n", path, sock);*/

    if (sock < 0)  {
        lua_pushnil(L);
        lua_pushstring(L, socket_strerror(errno));
        lua_pushnumber(L, errno);
        return 3;
    }
    /* set its type as client object */
    auxiliar_setclass(L, "serial{client}", -1);
    /* initialize remaining structure fields */
    socket_setnonblocking(&sock);
    un->sock = sock;
    io_init(&un->io, (p_send) socket_write, (p_recv) socket_read, 
            (p_error) socket_ioerror, &un->sock);
    timeout_init(&un->tm, -1, -1);
    buffer_init(&un->buf, &un->io, &un->tm);
    return 1;
}
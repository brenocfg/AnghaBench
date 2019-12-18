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
typedef  int /*<<< orphan*/  t_tcp ;
struct addrinfo {int family; int ai_family; int /*<<< orphan*/  sock; int /*<<< orphan*/  tm; void* ai_socktype; int /*<<< orphan*/  ai_flags; int /*<<< orphan*/  io; int /*<<< orphan*/  buf; } ;
typedef  struct addrinfo* p_tcp ;
typedef  int /*<<< orphan*/  p_send ;
typedef  int /*<<< orphan*/  p_recv ;
typedef  int /*<<< orphan*/  p_error ;
typedef  int /*<<< orphan*/  lua_State ;
typedef  int /*<<< orphan*/  connecthints ;
typedef  int /*<<< orphan*/  bindhints ;

/* Variables and functions */
 int /*<<< orphan*/  AI_PASSIVE ; 
 int PF_UNSPEC ; 
 int /*<<< orphan*/  SOCKET_INVALID ; 
 void* SOCK_STREAM ; 
 int /*<<< orphan*/  auxiliar_setclass (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  buffer_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int inet_optfamily (int /*<<< orphan*/ *,int,char*) ; 
 char* inet_trybind (int /*<<< orphan*/ *,char const*,char const*,struct addrinfo*) ; 
 char* inet_tryconnect (int /*<<< orphan*/ *,int*,char const*,char const*,int /*<<< orphan*/ *,struct addrinfo*) ; 
 int /*<<< orphan*/  io_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 char* luaL_checkstring (int /*<<< orphan*/ *,int) ; 
 char* luaL_optstring (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  lua_newuserdata (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushnil (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pushstring (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  memset (struct addrinfo*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  socket_destroy (int /*<<< orphan*/ *) ; 
 scalar_t__ socket_ioerror ; 
 scalar_t__ socket_recv ; 
 scalar_t__ socket_send ; 
 int /*<<< orphan*/  timeout_init (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static int global_connect(lua_State *L) {
    const char *remoteaddr = luaL_checkstring(L, 1);
    const char *remoteserv = luaL_checkstring(L, 2);
    const char *localaddr  = luaL_optstring(L, 3, NULL);
    const char *localserv  = luaL_optstring(L, 4, "0");
    int family = inet_optfamily(L, 5, "unspec");
    p_tcp tcp = (p_tcp) lua_newuserdata(L, sizeof(t_tcp));
    struct addrinfo bindhints, connecthints;
    const char *err = NULL;
    /* initialize tcp structure */
    memset(tcp, 0, sizeof(t_tcp));
    io_init(&tcp->io, (p_send) socket_send, (p_recv) socket_recv,
            (p_error) socket_ioerror, &tcp->sock);
    timeout_init(&tcp->tm, -1, -1);
    buffer_init(&tcp->buf, &tcp->io, &tcp->tm);
    tcp->sock = SOCKET_INVALID;
    tcp->family = PF_UNSPEC;
    /* allow user to pick local address and port */
    memset(&bindhints, 0, sizeof(bindhints));
    bindhints.ai_socktype = SOCK_STREAM;
    bindhints.ai_family = family;
    bindhints.ai_flags = AI_PASSIVE;
    if (localaddr) {
        err = inet_trybind(&tcp->sock, localaddr, localserv, &bindhints);
        if (err) {
            lua_pushnil(L);
            lua_pushstring(L, err);
            return 2;
        }
        tcp->family = bindhints.ai_family;
    }
    /* try to connect to remote address and port */
    memset(&connecthints, 0, sizeof(connecthints));
    connecthints.ai_socktype = SOCK_STREAM;
    /* make sure we try to connect only to the same family */
    connecthints.ai_family = bindhints.ai_family;
    err = inet_tryconnect(&tcp->sock, &tcp->family, remoteaddr, remoteserv,
         &tcp->tm, &connecthints);
    if (err) {
        socket_destroy(&tcp->sock);
        lua_pushnil(L);
        lua_pushstring(L, err);
        return 2;
    }
    auxiliar_setclass(L, "tcp{client}", -1);
    return 1;
}
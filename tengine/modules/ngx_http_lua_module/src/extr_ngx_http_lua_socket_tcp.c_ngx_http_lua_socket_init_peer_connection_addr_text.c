#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  socklen; TYPE_4__* sockaddr; int /*<<< orphan*/  log; TYPE_3__* connection; } ;
typedef  TYPE_2__ ngx_peer_connection_t ;
struct TYPE_6__ {int /*<<< orphan*/ * data; int /*<<< orphan*/  len; } ;
struct TYPE_8__ {TYPE_1__ addr_text; int /*<<< orphan*/  pool; } ;
typedef  TYPE_3__ ngx_connection_t ;
struct TYPE_9__ {int sa_family; } ;

/* Variables and functions */
#define  AF_INET 130 
#define  AF_INET6 129 
#define  AF_UNIX 128 
 size_t NGX_INET6_ADDRSTRLEN ; 
 size_t NGX_INET_ADDRSTRLEN ; 
 int /*<<< orphan*/  NGX_LOG_ERR ; 
 size_t NGX_SOCKADDR_STRLEN ; 
 size_t NGX_UNIX_ADDRSTRLEN ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * ngx_pnalloc (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  ngx_sock_ntop (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ngx_http_lua_socket_init_peer_connection_addr_text(ngx_peer_connection_t *pc)
{
    ngx_connection_t            *c;
    size_t                       addr_text_max_len;

    c = pc->connection;

    switch (pc->sockaddr->sa_family) {

#if (NGX_HAVE_INET6)
    case AF_INET6:
        addr_text_max_len = NGX_INET6_ADDRSTRLEN;
        break;
#endif

#if (NGX_HAVE_UNIX_DOMAIN)
    case AF_UNIX:
        addr_text_max_len = NGX_UNIX_ADDRSTRLEN;
        break;
#endif

    case AF_INET:
        addr_text_max_len = NGX_INET_ADDRSTRLEN;
        break;

    default:
        addr_text_max_len = NGX_SOCKADDR_STRLEN;
        break;
    }

    c->addr_text.data = ngx_pnalloc(c->pool, addr_text_max_len);
    if (c->addr_text.data == NULL) {
        ngx_log_error(NGX_LOG_ERR, pc->log, 0,
                      "init peer connection addr_text failed: no memory");
        return;
    }

    c->addr_text.len = ngx_sock_ntop(pc->sockaddr, pc->socklen,
                                     c->addr_text.data,
                                     addr_text_max_len, 0);
}
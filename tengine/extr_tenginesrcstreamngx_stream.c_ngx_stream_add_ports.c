#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct sockaddr {scalar_t__ sa_family; } ;
typedef  size_t ngx_uint_t ;
struct TYPE_12__ {struct sockaddr sockaddr; } ;
struct TYPE_13__ {scalar_t__ type; TYPE_1__ sockaddr; } ;
typedef  TYPE_2__ ngx_stream_listen_t ;
struct TYPE_17__ {size_t nelts; TYPE_3__* elts; } ;
struct TYPE_14__ {scalar_t__ type; scalar_t__ family; TYPE_6__ addrs; int /*<<< orphan*/  port; } ;
typedef  TYPE_3__ ngx_stream_conf_port_t ;
struct TYPE_15__ {TYPE_2__ opt; } ;
typedef  TYPE_4__ ngx_stream_conf_addr_t ;
typedef  scalar_t__ ngx_int_t ;
struct TYPE_16__ {int /*<<< orphan*/  temp_pool; } ;
typedef  TYPE_5__ ngx_conf_t ;
typedef  TYPE_6__ ngx_array_t ;
typedef  int /*<<< orphan*/  in_port_t ;

/* Variables and functions */
 scalar_t__ NGX_ERROR ; 
 scalar_t__ NGX_OK ; 
 scalar_t__ ngx_array_init (TYPE_6__*,int /*<<< orphan*/ ,int,int) ; 
 void* ngx_array_push (TYPE_6__*) ; 
 int /*<<< orphan*/  ngx_inet_get_port (struct sockaddr*) ; 

__attribute__((used)) static ngx_int_t
ngx_stream_add_ports(ngx_conf_t *cf, ngx_array_t *ports,
    ngx_stream_listen_t *listen)
{
    in_port_t                p;
    ngx_uint_t               i;
    struct sockaddr         *sa;
    ngx_stream_conf_port_t  *port;
    ngx_stream_conf_addr_t  *addr;
#if (NGX_STREAM_SNI)
    ngx_stream_core_srv_conf_t *cscf;
#endif

    sa = &listen->sockaddr.sockaddr;
    p = ngx_inet_get_port(sa);

    port = ports->elts;
    for (i = 0; i < ports->nelts; i++) {

        if (p == port[i].port
            && listen->type == port[i].type
            && sa->sa_family == port[i].family)
        {
            /* a port is already in the port list */

            port = &port[i];
            goto found;
        }
    }

    /* add a port to the port list */

    port = ngx_array_push(ports);
    if (port == NULL) {
        return NGX_ERROR;
    }

    port->family = sa->sa_family;
    port->type = listen->type;
    port->port = p;

    if (ngx_array_init(&port->addrs, cf->temp_pool, 2,
                       sizeof(ngx_stream_conf_addr_t))
        != NGX_OK)
    {
        return NGX_ERROR;
    }

found:
#if (NGX_STREAM_SNI)

    cscf = listen->ctx->srv_conf[ngx_stream_core_module.ctx_index];
    addr = port->addrs.elts;

    for (i = 0; i < port->addrs.nelts; i++) {
        if (ngx_cmp_sockaddr(&listen->sockaddr.sockaddr, listen->socklen,
            &addr[i].opt.sockaddr.sockaddr,
            addr[i].opt.socklen, 0)
            != NGX_OK)
        {
            continue;
        }

        /* the address is already in the address list */

        if (ngx_stream_add_server(cf, cscf, &addr[i]) != NGX_OK) {
            return NGX_ERROR;
        }

        if (listen->default_server) {

            if (addr[i].opt.default_server) {
                ngx_conf_log_error(NGX_LOG_EMERG, cf, 0,
                        "a duplicate default server for");
                return NGX_ERROR;
            }
            addr[i].default_server = cscf;
            addr[i].opt.default_server = 1;
        }
        return NGX_OK;
    }

    addr = ngx_array_push(&port->addrs);
    if (addr == NULL) {
        return NGX_ERROR;
    }
    ngx_memset(addr, 0, sizeof(ngx_stream_conf_addr_t));
    addr->opt = *listen;
    addr->default_server = cscf;

    return ngx_stream_add_server(cf, cscf, &addr[i]);

#else

    addr = ngx_array_push(&port->addrs);
    if (addr == NULL) {
        return NGX_ERROR;
    }

    addr->opt = *listen;

    return NGX_OK;
#endif
}
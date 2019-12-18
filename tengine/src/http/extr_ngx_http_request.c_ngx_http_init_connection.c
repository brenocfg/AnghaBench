#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_44__   TYPE_9__ ;
typedef  struct TYPE_43__   TYPE_8__ ;
typedef  struct TYPE_42__   TYPE_7__ ;
typedef  struct TYPE_41__   TYPE_6__ ;
typedef  struct TYPE_40__   TYPE_5__ ;
typedef  struct TYPE_39__   TYPE_4__ ;
typedef  struct TYPE_38__   TYPE_3__ ;
typedef  struct TYPE_37__   TYPE_2__ ;
typedef  struct TYPE_36__   TYPE_1__ ;
typedef  struct TYPE_35__   TYPE_16__ ;
typedef  struct TYPE_34__   TYPE_15__ ;
typedef  struct TYPE_33__   TYPE_14__ ;
typedef  struct TYPE_32__   TYPE_12__ ;
typedef  struct TYPE_31__   TYPE_11__ ;
typedef  struct TYPE_30__   TYPE_10__ ;

/* Type definitions */
struct sockaddr_in6 {int /*<<< orphan*/  sin6_addr; } ;
struct TYPE_36__ {int /*<<< orphan*/  s_addr; } ;
struct sockaddr_in {TYPE_1__ sin_addr; } ;
typedef  int ngx_uint_t ;
struct TYPE_43__ {int enable; } ;
typedef  TYPE_8__ ngx_http_v2_srv_conf_t ;
struct TYPE_44__ {scalar_t__ enable; } ;
typedef  TYPE_9__ ngx_http_ssl_srv_conf_t ;
struct TYPE_30__ {int naddrs; TYPE_12__* addrs; } ;
typedef  TYPE_10__ ngx_http_port_t ;
struct TYPE_31__ {int /*<<< orphan*/ * current_request; int /*<<< orphan*/ * request; TYPE_16__* connection; } ;
typedef  TYPE_11__ ngx_http_log_ctx_t ;
struct TYPE_40__ {scalar_t__ proxy_protocol; scalar_t__ ssl; scalar_t__ http2; TYPE_3__* default_server; } ;
struct TYPE_32__ {TYPE_5__ conf; int /*<<< orphan*/  addr; int /*<<< orphan*/  addr6; } ;
typedef  TYPE_12__ ngx_http_in_addr_t ;
typedef  TYPE_12__ ngx_http_in6_addr_t ;
struct TYPE_33__ {int ssl; int proxy_protocol; TYPE_5__* addr_conf; int /*<<< orphan*/  conf_ctx; } ;
typedef  TYPE_14__ ngx_http_connection_t ;
struct TYPE_34__ {int /*<<< orphan*/  (* handler ) (TYPE_15__*) ;scalar_t__ ready; } ;
typedef  TYPE_15__ ngx_event_t ;
struct TYPE_35__ {TYPE_7__* listening; TYPE_6__* log; TYPE_4__* write; TYPE_15__* read; int /*<<< orphan*/  log_error; int /*<<< orphan*/  number; int /*<<< orphan*/  pool; TYPE_2__* local_sockaddr; TYPE_14__* data; } ;
typedef  TYPE_16__ ngx_connection_t ;
struct TYPE_42__ {int /*<<< orphan*/  post_accept_timeout; TYPE_10__* servers; } ;
struct TYPE_41__ {char* action; TYPE_11__* data; int /*<<< orphan*/  handler; int /*<<< orphan*/  connection; } ;
struct TYPE_39__ {int /*<<< orphan*/  handler; } ;
struct TYPE_38__ {int /*<<< orphan*/  ctx; } ;
struct TYPE_37__ {int sa_family; } ;

/* Variables and functions */
#define  AF_INET6 128 
 int /*<<< orphan*/  NGX_ERROR_INFO ; 
 scalar_t__ NGX_OK ; 
 int /*<<< orphan*/  ngx_add_timer (TYPE_15__*,int /*<<< orphan*/ ) ; 
 scalar_t__ ngx_connection_local_sockaddr (TYPE_16__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ ngx_handle_read_event (TYPE_15__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_close_connection (TYPE_16__*) ; 
 int /*<<< orphan*/  ngx_http_empty_handler ; 
 void* ngx_http_get_module_srv_conf (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_log_error ; 
 int /*<<< orphan*/  ngx_http_ssl_handshake (TYPE_15__*) ; 
 int /*<<< orphan*/  ngx_http_ssl_module ; 
 int /*<<< orphan*/  ngx_http_v2_init (TYPE_15__*) ; 
 int /*<<< orphan*/  ngx_http_v2_module ; 
 int /*<<< orphan*/  ngx_http_wait_request_handler (TYPE_15__*) ; 
 int /*<<< orphan*/  ngx_memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 TYPE_11__* ngx_palloc (int /*<<< orphan*/ ,int) ; 
 TYPE_14__* ngx_pcalloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ngx_post_event (TYPE_15__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_posted_events ; 
 int /*<<< orphan*/  ngx_reusable_connection (TYPE_16__*,int) ; 
 scalar_t__ ngx_use_accept_mutex ; 
 int /*<<< orphan*/  stub1 (TYPE_15__*) ; 

void
ngx_http_init_connection(ngx_connection_t *c)
{
    ngx_uint_t              i;
    ngx_event_t            *rev;
    struct sockaddr_in     *sin;
    ngx_http_port_t        *port;
    ngx_http_in_addr_t     *addr;
    ngx_http_log_ctx_t     *ctx;
    ngx_http_connection_t  *hc;
#if (NGX_HAVE_INET6)
    struct sockaddr_in6    *sin6;
    ngx_http_in6_addr_t    *addr6;
#endif
#if (NGX_HTTP_V2 && T_NGX_HTTP2_SRV_ENABLE)
    ngx_http_v2_srv_conf_t *h2scf;
#endif


    hc = ngx_pcalloc(c->pool, sizeof(ngx_http_connection_t));
    if (hc == NULL) {
        ngx_http_close_connection(c);
        return;
    }

    c->data = hc;

    /* find the server configuration for the address:port */

    port = c->listening->servers;

    if (port->naddrs > 1) {

        /*
         * there are several addresses on this port and one of them
         * is an "*:port" wildcard so getsockname() in ngx_http_server_addr()
         * is required to determine a server address
         */

        if (ngx_connection_local_sockaddr(c, NULL, 0) != NGX_OK) {
            ngx_http_close_connection(c);
            return;
        }

        switch (c->local_sockaddr->sa_family) {

#if (NGX_HAVE_INET6)
        case AF_INET6:
            sin6 = (struct sockaddr_in6 *) c->local_sockaddr;

            addr6 = port->addrs;

            /* the last address is "*" */

            for (i = 0; i < port->naddrs - 1; i++) {
                if (ngx_memcmp(&addr6[i].addr6, &sin6->sin6_addr, 16) == 0) {
                    break;
                }
            }

            hc->addr_conf = &addr6[i].conf;

            break;
#endif

        default: /* AF_INET */
            sin = (struct sockaddr_in *) c->local_sockaddr;

            addr = port->addrs;

            /* the last address is "*" */

            for (i = 0; i < port->naddrs - 1; i++) {
                if (addr[i].addr == sin->sin_addr.s_addr) {
                    break;
                }
            }

            hc->addr_conf = &addr[i].conf;

            break;
        }

    } else {

        switch (c->local_sockaddr->sa_family) {

#if (NGX_HAVE_INET6)
        case AF_INET6:
            addr6 = port->addrs;
            hc->addr_conf = &addr6[0].conf;
            break;
#endif

        default: /* AF_INET */
            addr = port->addrs;
            hc->addr_conf = &addr[0].conf;
            break;
        }
    }

    /* the default server configuration for the address:port */
    hc->conf_ctx = hc->addr_conf->default_server->ctx;

    ctx = ngx_palloc(c->pool, sizeof(ngx_http_log_ctx_t));
    if (ctx == NULL) {
        ngx_http_close_connection(c);
        return;
    }

    ctx->connection = c;
    ctx->request = NULL;
    ctx->current_request = NULL;

    c->log->connection = c->number;
    c->log->handler = ngx_http_log_error;
    c->log->data = ctx;
    c->log->action = "waiting for request";

    c->log_error = NGX_ERROR_INFO;

    rev = c->read;
    rev->handler = ngx_http_wait_request_handler;
    c->write->handler = ngx_http_empty_handler;

#if (NGX_HTTP_V2 && T_NGX_HTTP2_SRV_ENABLE)
    h2scf = ngx_http_get_module_srv_conf(hc->conf_ctx, ngx_http_v2_module);
#endif

#if (NGX_HTTP_V2)
    if (
#if (T_NGX_HTTP2_SRV_ENABLE)
        (
#endif
         hc->addr_conf->http2
#if (T_NGX_HTTP2_SRV_ENABLE)
         && h2scf->enable != 0) || h2scf->enable == 1
#endif
       )
    {
        rev->handler = ngx_http_v2_init;
    }
#endif

#if (NGX_HTTP_SSL)
    {
    ngx_http_ssl_srv_conf_t  *sscf;

    sscf = ngx_http_get_module_srv_conf(hc->conf_ctx, ngx_http_ssl_module);

    if (sscf->enable || hc->addr_conf->ssl) {
        hc->ssl = 1;
        c->log->action = "SSL handshaking";
        rev->handler = ngx_http_ssl_handshake;
    }
    }
#endif

    if (hc->addr_conf->proxy_protocol) {
        hc->proxy_protocol = 1;
        c->log->action = "reading PROXY protocol";
    }

    if (rev->ready) {
        /* the deferred accept(), iocp */

        if (ngx_use_accept_mutex) {
            ngx_post_event(rev, &ngx_posted_events);
            return;
        }

        rev->handler(rev);
        return;
    }

    ngx_add_timer(rev, c->listening->post_accept_timeout);
    ngx_reusable_connection(c, 1);

    if (ngx_handle_read_event(rev, 0) != NGX_OK) {
        ngx_http_close_connection(c);
        return;
    }
}
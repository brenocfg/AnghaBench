#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_42__   TYPE_9__ ;
typedef  struct TYPE_41__   TYPE_8__ ;
typedef  struct TYPE_40__   TYPE_7__ ;
typedef  struct TYPE_39__   TYPE_6__ ;
typedef  struct TYPE_38__   TYPE_5__ ;
typedef  struct TYPE_37__   TYPE_4__ ;
typedef  struct TYPE_36__   TYPE_3__ ;
typedef  struct TYPE_35__   TYPE_2__ ;
typedef  struct TYPE_34__   TYPE_1__ ;
typedef  struct TYPE_33__   TYPE_18__ ;
typedef  struct TYPE_32__   TYPE_13__ ;
typedef  struct TYPE_31__   TYPE_12__ ;
typedef  struct TYPE_30__   TYPE_11__ ;
typedef  struct TYPE_29__   TYPE_10__ ;

/* Type definitions */
typedef  size_t ngx_uint_t ;
struct TYPE_40__ {size_t naddrs; } ;
typedef  TYPE_7__ ngx_stream_port_t ;
struct TYPE_41__ {int /*<<< orphan*/  error_log; } ;
typedef  TYPE_8__ ngx_stream_core_srv_conf_t ;
typedef  int /*<<< orphan*/  ngx_stream_core_main_conf_t ;
struct TYPE_34__ {size_t nelts; TYPE_10__* elts; } ;
struct TYPE_42__ {TYPE_1__ addrs; } ;
typedef  TYPE_9__ ngx_stream_conf_port_t ;
struct TYPE_38__ {int nelts; } ;
struct TYPE_37__ {int bind; TYPE_3__* ctx; int /*<<< orphan*/  reuseport; int /*<<< orphan*/  ipv6only; int /*<<< orphan*/  tcp_keepcnt; int /*<<< orphan*/  tcp_keepintvl; int /*<<< orphan*/  tcp_keepidle; int /*<<< orphan*/  so_keepalive; scalar_t__ wildcard; int /*<<< orphan*/  sndbuf; int /*<<< orphan*/  rcvbuf; int /*<<< orphan*/  backlog; int /*<<< orphan*/  type; int /*<<< orphan*/  socklen; int /*<<< orphan*/  sockaddr; } ;
struct TYPE_29__ {TYPE_5__ servers; TYPE_4__ opt; } ;
typedef  TYPE_10__ ngx_stream_conf_addr_t ;
struct TYPE_35__ {int /*<<< orphan*/  handler; int /*<<< orphan*/ * data; } ;
struct TYPE_30__ {int addr_ntop; int pool_size; TYPE_6__* sockaddr; TYPE_7__* servers; int /*<<< orphan*/  reuseport; int /*<<< orphan*/  ipv6only; int /*<<< orphan*/  keepcnt; int /*<<< orphan*/  keepintvl; int /*<<< orphan*/  keepidle; int /*<<< orphan*/  keepalive; scalar_t__ wildcard; int /*<<< orphan*/  sndbuf; int /*<<< orphan*/  rcvbuf; int /*<<< orphan*/  backlog; TYPE_2__ log; int /*<<< orphan*/  addr_text; int /*<<< orphan*/  logp; int /*<<< orphan*/  type; int /*<<< orphan*/  handler; } ;
typedef  TYPE_11__ ngx_listening_t ;
struct TYPE_31__ {int /*<<< orphan*/  pool; } ;
typedef  TYPE_12__ ngx_conf_t ;
struct TYPE_32__ {size_t nelts; TYPE_9__* elts; } ;
typedef  TYPE_13__ ngx_array_t ;
struct TYPE_39__ {int sa_family; } ;
struct TYPE_36__ {int /*<<< orphan*/ ** main_conf; TYPE_8__** srv_conf; } ;
struct TYPE_33__ {size_t ctx_index; } ;

/* Variables and functions */
#define  AF_INET6 128 
 char* NGX_CONF_ERROR ; 
 char* NGX_CONF_OK ; 
 scalar_t__ NGX_OK ; 
 int /*<<< orphan*/  ngx_accept_log_error ; 
 TYPE_11__* ngx_create_listening (TYPE_12__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_7__* ngx_palloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ngx_sort (TYPE_10__*,size_t,int,int /*<<< orphan*/ ) ; 
 scalar_t__ ngx_stream_add_addrs (TYPE_12__*,TYPE_7__*,TYPE_10__*) ; 
 scalar_t__ ngx_stream_add_addrs6 (TYPE_12__*,TYPE_7__*,TYPE_10__*) ; 
 int /*<<< orphan*/  ngx_stream_cmp_conf_addrs ; 
 TYPE_18__ ngx_stream_core_module ; 
 int /*<<< orphan*/  ngx_stream_init_connection ; 
 scalar_t__ ngx_stream_server_names (TYPE_12__*,int /*<<< orphan*/ *,TYPE_10__*) ; 

__attribute__((used)) static char *
ngx_stream_optimize_servers(ngx_conf_t *cf, ngx_array_t *ports)
{
    ngx_uint_t                   i, p, last, bind_wildcard;
    ngx_listening_t             *ls;
    ngx_stream_port_t           *stport;
    ngx_stream_conf_port_t      *port;
    ngx_stream_conf_addr_t      *addr;
    ngx_stream_core_srv_conf_t  *cscf;

#if (NGX_STREAM_SNI)
    ngx_stream_core_main_conf_t *cmcf;
#endif
    port = ports->elts;
    for (p = 0; p < ports->nelts; p++) {

        ngx_sort(port[p].addrs.elts, (size_t) port[p].addrs.nelts,
                 sizeof(ngx_stream_conf_addr_t), ngx_stream_cmp_conf_addrs);

        addr = port[p].addrs.elts;
        last = port[p].addrs.nelts;

        /*
         * if there is the binding to the "*:port" then we need to bind()
         * to the "*:port" only and ignore the other bindings
         */

        if (addr[last - 1].opt.wildcard) {
            addr[last - 1].opt.bind = 1;
            bind_wildcard = 1;

        } else {
            bind_wildcard = 0;
        }

        i = 0;

        while (i < last) {

            if (bind_wildcard && !addr[i].opt.bind) {
                i++;
                continue;
            }

            ls = ngx_create_listening(cf, addr[i].opt.sockaddr,
                                      addr[i].opt.socklen);
            if (ls == NULL) {
                return NGX_CONF_ERROR;
            }

            ls->addr_ntop = 1;
            ls->handler = ngx_stream_init_connection;
            ls->pool_size = 256;
            ls->type = addr[i].opt.type;

            cscf = addr->opt.ctx->srv_conf[ngx_stream_core_module.ctx_index];

            ls->logp = cscf->error_log;
            ls->log.data = &ls->addr_text;
            ls->log.handler = ngx_accept_log_error;

            ls->backlog = addr[i].opt.backlog;
            ls->rcvbuf = addr[i].opt.rcvbuf;
            ls->sndbuf = addr[i].opt.sndbuf;

            ls->wildcard = addr[i].opt.wildcard;

            ls->keepalive = addr[i].opt.so_keepalive;
#if (NGX_HAVE_KEEPALIVE_TUNABLE)
            ls->keepidle = addr[i].opt.tcp_keepidle;
            ls->keepintvl = addr[i].opt.tcp_keepintvl;
            ls->keepcnt = addr[i].opt.tcp_keepcnt;
#endif

#if (NGX_HAVE_INET6)
            ls->ipv6only = addr[i].opt.ipv6only;
#endif

#if (NGX_HAVE_REUSEPORT)
            ls->reuseport = addr[i].opt.reuseport;
#endif

            stport = ngx_palloc(cf->pool, sizeof(ngx_stream_port_t));
            if (stport == NULL) {
                return NGX_CONF_ERROR;
            }

            ls->servers = stport;

            stport->naddrs = i + 1;

#if (NGX_STREAM_SNI)
            cmcf = addr->opt.ctx->main_conf[ngx_stream_core_module.ctx_index];
            /*Because of ssl_sni_force we have to do this even one server*/
            if (addr[i].servers.nelts >= 1) {
                if (ngx_stream_server_names(cf, cmcf, &addr[i]) != NGX_OK) {
                    return NGX_CONF_ERROR;
                }
            }
#endif

            switch (ls->sockaddr->sa_family) {
#if (NGX_HAVE_INET6)
            case AF_INET6:
                if (ngx_stream_add_addrs6(cf, stport, addr) != NGX_OK) {
                    return NGX_CONF_ERROR;
                }
                break;
#endif
            default: /* AF_INET */
                if (ngx_stream_add_addrs(cf, stport, addr) != NGX_OK) {
                    return NGX_CONF_ERROR;
                }
                break;
            }

            addr++;
            last--;
        }
    }

    return NGX_CONF_OK;
}
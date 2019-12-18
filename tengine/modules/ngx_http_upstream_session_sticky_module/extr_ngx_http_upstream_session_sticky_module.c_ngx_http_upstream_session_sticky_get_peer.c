#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_28__   TYPE_9__ ;
typedef  struct TYPE_27__   TYPE_8__ ;
typedef  struct TYPE_26__   TYPE_7__ ;
typedef  struct TYPE_25__   TYPE_6__ ;
typedef  struct TYPE_24__   TYPE_5__ ;
typedef  struct TYPE_23__   TYPE_4__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;
typedef  struct TYPE_19__   TYPE_13__ ;
typedef  struct TYPE_18__   TYPE_12__ ;
typedef  struct TYPE_17__   TYPE_10__ ;

/* Type definitions */
typedef  size_t ngx_uint_t ;
struct TYPE_24__ {TYPE_3__* name; int /*<<< orphan*/  sockaddr; int /*<<< orphan*/  socklen; } ;
typedef  TYPE_5__ ngx_peer_connection_t ;
typedef  scalar_t__ ngx_int_t ;
struct TYPE_25__ {size_t number; TYPE_8__* server; } ;
typedef  TYPE_6__ ngx_http_upstream_ss_srv_conf_t ;
struct TYPE_18__ {int /*<<< orphan*/  current; } ;
struct TYPE_26__ {scalar_t__ (* get_rr_peer ) (TYPE_5__*,TYPE_12__*) ;TYPE_12__ rrp; TYPE_10__* r; TYPE_6__* sscf; } ;
typedef  TYPE_7__ ngx_http_upstream_ss_peer_data_t ;
struct TYPE_23__ {scalar_t__ len; int /*<<< orphan*/  data; } ;
struct TYPE_27__ {TYPE_4__ sid; TYPE_3__* name; int /*<<< orphan*/  peer; int /*<<< orphan*/  sockaddr; int /*<<< orphan*/  socklen; int /*<<< orphan*/  check_index; } ;
typedef  TYPE_8__ ngx_http_ss_server_t ;
struct TYPE_19__ {scalar_t__ len; int /*<<< orphan*/  data; } ;
struct TYPE_28__ {int frist; scalar_t__ tries; TYPE_13__ sid; TYPE_1__* sscf; } ;
typedef  TYPE_9__ ngx_http_ss_ctx_t ;
struct TYPE_17__ {TYPE_2__* connection; } ;
typedef  TYPE_10__ ngx_http_request_t ;
struct TYPE_22__ {scalar_t__ len; int /*<<< orphan*/  data; } ;
struct TYPE_21__ {int /*<<< orphan*/  log; } ;
struct TYPE_20__ {int flag; } ;

/* Variables and functions */
 scalar_t__ NGX_BUSY ; 
 int NGX_HTTP_SESSION_STICKY_FALLBACK_OFF ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_HTTP ; 
 scalar_t__ NGX_OK ; 
 TYPE_9__* ngx_http_get_module_ctx (TYPE_10__*,int /*<<< orphan*/ ) ; 
 scalar_t__ ngx_http_upstream_check_peer_down (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_upstream_session_sticky_module ; 
 int /*<<< orphan*/  ngx_log_debug1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,TYPE_13__*) ; 
 scalar_t__ ngx_strncmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ stub1 (TYPE_5__*,TYPE_12__*) ; 

__attribute__((used)) static ngx_int_t
ngx_http_upstream_session_sticky_get_peer(ngx_peer_connection_t *pc, void *data)
{
    ngx_int_t                          rc;
    ngx_uint_t                         i, n;
    ngx_http_ss_ctx_t                 *ctx;
    ngx_http_request_t                *r;
    ngx_http_ss_server_t              *server;
    ngx_http_upstream_ss_srv_conf_t   *sscf;
    ngx_http_upstream_ss_peer_data_t  *sspd = data;

    sscf = sspd->sscf;
    r = sspd->r;
    n = sscf->number;
    server = sscf->server;

    ctx = ngx_http_get_module_ctx(r, ngx_http_upstream_session_sticky_module);

    if (ctx->frist == 1 || ctx->sid.len == 0) {
        goto failed;
    }

    if (ctx->tries == 0
        && !(ctx->sscf->flag & NGX_HTTP_SESSION_STICKY_FALLBACK_OFF))
    {
        goto failed;
    }

    for (i = 0; i < n; i++) {
        if (ctx->sid.len == server[i].sid.len
            && ngx_strncmp(ctx->sid.data, server[i].sid.data,
                           ctx->sid.len) == 0)
        {
#if (NGX_HTTP_UPSTREAM_CHECK)
            if (ngx_http_upstream_check_peer_down(server[i].check_index)) {
                if (ctx->sscf->flag & NGX_HTTP_SESSION_STICKY_FALLBACK_OFF) {
                    return NGX_BUSY;

                } else {
                    goto failed;
                }
            }
#endif
            pc->name = server[i].name;
            pc->socklen = server[i].socklen;
            pc->sockaddr = server[i].sockaddr;

            ctx->sid.len = server[i].sid.len;
            ctx->sid.data = server[i].sid.data;
            sspd->rrp.current = server[i].peer;
            ctx->tries--;

            return NGX_OK;
        }
    }

failed:
    if (ctx->frist != 1 &&
        (ctx->sscf->flag & NGX_HTTP_SESSION_STICKY_FALLBACK_OFF))
    {
        return NGX_BUSY;
    }

    ngx_log_debug1(NGX_LOG_DEBUG_HTTP, r->connection->log, 0,
                   "session sticky failed, sid[%V]", &ctx->sid);

    rc = sspd->get_rr_peer(pc, &sspd->rrp);
    if (rc != NGX_OK) {
        return rc;
    }

    for (i = 0; i < n; i++) {
        if (server[i].name->len == pc->name->len
            && ngx_strncmp(server[i].name->data, pc->name->data,
                           pc->name->len) == 0)
        {
            ctx->sid.len = server[i].sid.len;
            ctx->sid.data = server[i].sid.data;
            break;
        }
    }
    ctx->frist = 1;

    return rc;
}
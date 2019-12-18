#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_8__ ;
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
typedef  int ssize_t ;
typedef  int ngx_int_t ;
struct TYPE_18__ {scalar_t__ state; int (* parse ) (TYPE_5__*) ;TYPE_4__* check_peer_addr; TYPE_3__* conf; TYPE_6__* check_data; } ;
typedef  TYPE_5__ ngx_http_upstream_check_peer_t ;
struct TYPE_14__ {int /*<<< orphan*/ * last; int /*<<< orphan*/ * end; int /*<<< orphan*/ * start; int /*<<< orphan*/ * pos; } ;
struct TYPE_19__ {TYPE_1__ recv; } ;
typedef  TYPE_6__ ngx_http_upstream_check_ctx_t ;
struct TYPE_20__ {int /*<<< orphan*/  log; TYPE_8__* data; } ;
typedef  TYPE_7__ ngx_event_t ;
typedef  int /*<<< orphan*/  ngx_err_t ;
struct TYPE_21__ {int (* recv ) (TYPE_8__*,int /*<<< orphan*/ *,int) ;int error; int /*<<< orphan*/  log; int /*<<< orphan*/  pool; int /*<<< orphan*/  read; TYPE_5__* data; } ;
typedef  TYPE_8__ ngx_connection_t ;
struct TYPE_17__ {int /*<<< orphan*/  name; } ;
struct TYPE_16__ {TYPE_2__* check_type_conf; } ;
struct TYPE_15__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
#define  NGX_AGAIN 130 
#define  NGX_ERROR 129 
 scalar_t__ NGX_HTTP_CHECK_RECV_DONE ; 
 scalar_t__ NGX_HTTP_CHECK_SEND_DONE ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_HTTP ; 
 int /*<<< orphan*/  NGX_LOG_ERR ; 
#define  NGX_OK 128 
 scalar_t__ ngx_handle_read_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_upstream_check_clean_event (TYPE_5__*) ; 
 scalar_t__ ngx_http_upstream_check_need_exit () ; 
 int /*<<< orphan*/  ngx_http_upstream_check_status_update (TYPE_5__*,int) ; 
 int /*<<< orphan*/  ngx_log_debug2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int ngx_pagesize ; 
 void* ngx_palloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ngx_socket_errno ; 
 int stub1 (TYPE_8__*,int /*<<< orphan*/ *,int) ; 
 int stub2 (TYPE_5__*) ; 

__attribute__((used)) static void
ngx_http_upstream_check_recv_handler(ngx_event_t *event)
{
    u_char                         *new_buf;
    ssize_t                         size, n;
    ngx_int_t                       rc;
    ngx_connection_t               *c;
    ngx_http_upstream_check_ctx_t  *ctx;
    ngx_http_upstream_check_peer_t *peer;

    if (ngx_http_upstream_check_need_exit()) {
        return;
    }

    c = event->data;
    peer = c->data;

    if (peer->state != NGX_HTTP_CHECK_SEND_DONE) {

        if (ngx_handle_read_event(c->read, 0) != NGX_OK) {
            goto check_recv_fail;
        }

        return;
    }

    ctx = peer->check_data;

    if (ctx->recv.start == NULL) {
        /* half of the page_size, is it enough? */
        ctx->recv.start = ngx_palloc(c->pool, ngx_pagesize / 2);
        if (ctx->recv.start == NULL) {
            goto check_recv_fail;
        }

        ctx->recv.last = ctx->recv.pos = ctx->recv.start;
        ctx->recv.end = ctx->recv.start + ngx_pagesize / 2;
    }

    while (1) {
        n = ctx->recv.end - ctx->recv.last;

        /* buffer not big enough? enlarge it by twice */
        if (n == 0) {
            size = ctx->recv.end - ctx->recv.start;
            new_buf = ngx_palloc(c->pool, size * 2);
            if (new_buf == NULL) {
                goto check_recv_fail;
            }

            ngx_memcpy(new_buf, ctx->recv.start, size);

            ctx->recv.pos = ctx->recv.start = new_buf;
            ctx->recv.last = new_buf + size;
            ctx->recv.end = new_buf + size * 2;

            n = ctx->recv.end - ctx->recv.last;
        }

        size = c->recv(c, ctx->recv.last, n);

#if (NGX_DEBUG)
        {
        ngx_err_t  err;

        err = (size >= 0) ? 0 : ngx_socket_errno;
        ngx_log_debug2(NGX_LOG_DEBUG_HTTP, c->log, err,
                       "http check recv size: %z, peer: %V ",
                       size, &peer->check_peer_addr->name);
        }
#endif

        if (size > 0) {
            ctx->recv.last += size;
            continue;
        } else if (size == 0 || size == NGX_AGAIN) {
            break;
        } else {
            c->error = 1;
            goto check_recv_fail;
        }
    }

    rc = peer->parse(peer);

    ngx_log_debug2(NGX_LOG_DEBUG_HTTP, c->log, 0,
                   "http check parse rc: %i, peer: %V ",
                   rc, &peer->check_peer_addr->name);

    switch (rc) {

    case NGX_AGAIN:
        /* The peer has closed its half side of the connection. */
        return;

    case NGX_ERROR:
        ngx_log_error(NGX_LOG_ERR, event->log, 0,
                      "check protocol %V error with peer: %V ",
                      &peer->conf->check_type_conf->name,
                      &peer->check_peer_addr->name);

        ngx_http_upstream_check_status_update(peer, 0);
        break;

    case NGX_OK:
        /* fall through */

    default:
        ngx_http_upstream_check_status_update(peer, 1);
        break;
    }

    peer->state = NGX_HTTP_CHECK_RECV_DONE;
    ngx_http_upstream_check_clean_event(peer);
    return;

check_recv_fail:

    ngx_http_upstream_check_status_update(peer, 0);
    ngx_http_upstream_check_clean_event(peer);
}
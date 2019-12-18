#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_33__   TYPE_9__ ;
typedef  struct TYPE_32__   TYPE_8__ ;
typedef  struct TYPE_31__   TYPE_7__ ;
typedef  struct TYPE_30__   TYPE_6__ ;
typedef  struct TYPE_29__   TYPE_5__ ;
typedef  struct TYPE_28__   TYPE_4__ ;
typedef  struct TYPE_27__   TYPE_3__ ;
typedef  struct TYPE_26__   TYPE_2__ ;
typedef  struct TYPE_25__   TYPE_1__ ;
typedef  struct TYPE_24__   TYPE_11__ ;
typedef  struct TYPE_23__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
struct TYPE_27__ {int /*<<< orphan*/  id; TYPE_10__* out; } ;
typedef  TYPE_3__ ngx_multi_request_t ;
struct TYPE_26__ {TYPE_1__* connection; } ;
struct TYPE_28__ {TYPE_2__ peer; } ;
typedef  TYPE_4__ ngx_http_upstream_t ;
struct TYPE_29__ {int /*<<< orphan*/  pool; TYPE_4__* upstream; } ;
typedef  TYPE_5__ ngx_http_request_t ;
struct TYPE_30__ {int /*<<< orphan*/  free; TYPE_10__* out; TYPE_8__* connection; } ;
typedef  TYPE_6__ ngx_http_dubbo_ctx_t ;
struct TYPE_31__ {TYPE_9__* data; } ;
typedef  TYPE_7__ ngx_event_t ;
struct TYPE_32__ {int /*<<< orphan*/  log; } ;
typedef  TYPE_8__ ngx_dubbo_connection_t ;
struct TYPE_33__ {TYPE_5__* data; } ;
typedef  TYPE_9__ ngx_connection_t ;
struct TYPE_23__ {struct TYPE_23__* next; TYPE_11__* buf; } ;
typedef  TYPE_10__ ngx_chain_t ;
typedef  scalar_t__ ngx_buf_tag_t ;
struct TYPE_24__ {int last_shadow; scalar_t__ last_in_chain; scalar_t__ last_buf; struct TYPE_24__* shadow; scalar_t__ tag; int /*<<< orphan*/ * start; } ;
typedef  TYPE_11__ ngx_buf_t ;
struct TYPE_25__ {int /*<<< orphan*/  write; } ;

/* Variables and functions */
 scalar_t__ NGX_ERROR ; 
 int /*<<< orphan*/  NGX_LOG_ERR ; 
 int /*<<< orphan*/  NGX_LOG_INFO ; 
 TYPE_10__* ngx_chain_get_free_buf (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_3__* ngx_create_multi_request (TYPE_9__*,TYPE_5__*) ; 
 scalar_t__ ngx_dubbo_encode_ping_request (TYPE_8__*,TYPE_3__*) ; 
 int /*<<< orphan*/  ngx_http_dubbo_body_output_filter ; 
 TYPE_6__* ngx_http_dubbo_get_ctx (TYPE_5__*) ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  ngx_memcpy (TYPE_11__*,TYPE_11__*,int) ; 
 int /*<<< orphan*/  ngx_post_event (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_posted_events ; 

__attribute__((used)) static void
ngx_http_dubbo_ping_handler(ngx_event_t *ev)
{
    ngx_connection_t        *pc;
    ngx_http_request_t      *fake_r;
    ngx_http_upstream_t     *fake_u;
    ngx_multi_request_t     *multi_r;
    ngx_dubbo_connection_t  *dubbo_c;
    ngx_http_dubbo_ctx_t    *ctx;
    u_char                  *start;
    ngx_chain_t             *cl, *tmp, **ll;
    ngx_buf_t               *b;

    pc = ev->data;
    fake_r = pc->data;
    fake_u = fake_r->upstream;

    ctx = ngx_http_dubbo_get_ctx(fake_r);
    dubbo_c = ctx->connection;

    multi_r = ngx_create_multi_request(pc, fake_r);
    if (multi_r == NULL) {
        return;
    }

    if (NGX_ERROR == ngx_dubbo_encode_ping_request(dubbo_c, multi_r)) {
        ngx_log_error(NGX_LOG_ERR, dubbo_c->log, 0,
                      "dubbo: encode ping request failed");
        return;
    }

    for (cl = ctx->out, ll = &ctx->out; cl; cl = cl->next) {
        ll = &cl->next;
    }

    for (cl = multi_r->out; cl; cl = cl->next) {
        tmp = ngx_chain_get_free_buf(fake_r->pool, &ctx->free);
        if (tmp == NULL) {
            return;
        }

        b = tmp->buf;
        start = b->start;

        ngx_memcpy(b, cl->buf, sizeof(ngx_buf_t));

        /*
         * restore b->start to preserve memory allocated in the buffer,
         * to reuse it later for headers and control frames
         */

        b->start = start;

        b->tag = (ngx_buf_tag_t) &ngx_http_dubbo_body_output_filter;
        b->shadow = cl->buf;
        b->last_shadow = 1;

        b->last_buf = 0;
        b->last_in_chain = 0;

        *ll = tmp;
        ll = &tmp->next;
    }

    ngx_post_event(fake_u->peer.connection->write, &ngx_posted_events);
    ngx_log_error(NGX_LOG_INFO, dubbo_c->log, 0,
                  "dubbo: send ping request [%ul] frame to backend", multi_r->id);
    return;
}
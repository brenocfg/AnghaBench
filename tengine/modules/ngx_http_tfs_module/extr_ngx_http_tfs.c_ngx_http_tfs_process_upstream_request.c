#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_32__   TYPE_8__ ;
typedef  struct TYPE_31__   TYPE_7__ ;
typedef  struct TYPE_30__   TYPE_6__ ;
typedef  struct TYPE_29__   TYPE_5__ ;
typedef  struct TYPE_28__   TYPE_4__ ;
typedef  struct TYPE_27__   TYPE_3__ ;
typedef  struct TYPE_26__   TYPE_2__ ;
typedef  struct TYPE_25__   TYPE_21__ ;
typedef  struct TYPE_24__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ngx_int_t ;
struct TYPE_29__ {scalar_t__ parse_state; scalar_t__ (* process_request_body ) (TYPE_5__*) ;TYPE_3__* main_conf; TYPE_8__* recv_chain; int /*<<< orphan*/  request_sent; TYPE_6__* tfs_peer; } ;
typedef  TYPE_5__ ngx_http_tfs_t ;
struct TYPE_28__ {int /*<<< orphan*/  last; } ;
struct TYPE_24__ {int /*<<< orphan*/  name; TYPE_7__* connection; } ;
struct TYPE_30__ {TYPE_4__ body_buffer; int /*<<< orphan*/  peer_addr_text; TYPE_1__ peer; } ;
typedef  TYPE_6__ ngx_http_tfs_peer_connection_t ;
typedef  int /*<<< orphan*/  ngx_http_request_t ;
struct TYPE_31__ {scalar_t__ (* recv_chain ) (TYPE_7__*,TYPE_8__*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  log; TYPE_21__* read; } ;
typedef  TYPE_7__ ngx_connection_t ;
struct TYPE_32__ {TYPE_2__* buf; struct TYPE_32__* next; } ;
typedef  TYPE_8__ ngx_chain_t ;
struct TYPE_27__ {int /*<<< orphan*/  tfs_read_timeout; } ;
struct TYPE_26__ {scalar_t__ last; scalar_t__ end; } ;
struct TYPE_25__ {scalar_t__ timer_set; } ;

/* Variables and functions */
 scalar_t__ NGX_AGAIN ; 
 scalar_t__ NGX_DONE ; 
 scalar_t__ NGX_ERROR ; 
 int /*<<< orphan*/  NGX_HTTP_INTERNAL_SERVER_ERROR ; 
 scalar_t__ NGX_HTTP_TFS_BODY ; 
 scalar_t__ NGX_HTTP_TFS_HEADER ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_HTTP ; 
 int /*<<< orphan*/  NGX_LOG_ERR ; 
 scalar_t__ NGX_OK ; 
 int /*<<< orphan*/  ngx_add_timer (TYPE_21__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_del_timer (TYPE_21__*) ; 
 scalar_t__ ngx_handle_read_event (TYPE_21__*,int /*<<< orphan*/ ) ; 
 scalar_t__ ngx_http_tfs_alloc_buf (TYPE_5__*) ; 
 int /*<<< orphan*/  ngx_http_tfs_finalize_request (int /*<<< orphan*/ *,TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_tfs_finalize_state (TYPE_5__*,scalar_t__) ; 
 int /*<<< orphan*/  ngx_http_tfs_handle_connection_failure (TYPE_5__*,TYPE_6__*) ; 
 int /*<<< orphan*/  ngx_http_tfs_process_buf_overflow (int /*<<< orphan*/ *,TYPE_5__*) ; 
 scalar_t__ ngx_http_tfs_process_header (TYPE_5__*,scalar_t__) ; 
 scalar_t__ ngx_http_tfs_test_connect (TYPE_7__*) ; 
 int /*<<< orphan*/  ngx_log_debug2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ stub1 (TYPE_7__*,TYPE_8__*,int /*<<< orphan*/ ) ; 
 scalar_t__ stub2 (TYPE_5__*) ; 

__attribute__((used)) static void
ngx_http_tfs_process_upstream_request(ngx_http_request_t *r, ngx_http_tfs_t *t)
{
    ngx_int_t                        n, rc;
    ngx_chain_t                     *chain;
    ngx_connection_t                *c;
    ngx_http_tfs_peer_connection_t  *tp;

    tp = t->tfs_peer;
    c = tp->peer.connection;

    ngx_log_debug2(NGX_LOG_DEBUG_HTTP, c->log, 0,
                   "http tfs process request body for %V, addr: %s",
                   tp->peer.name,
                   tp->peer_addr_text);

    /* for test ds retry */
    //if (ngx_strncmp(p->name->data, ds_name.data, p->name->len) == 0) {
    //    ngx_http_tfs_handle_connection_failure(t, tp);
    //    return;
    //}

    if (!t->request_sent && ngx_http_tfs_test_connect(c) != NGX_OK) {
        ngx_http_tfs_handle_connection_failure(t, tp);
        return;
    }

    rc = ngx_http_tfs_alloc_buf(t);
    if (rc == NGX_ERROR) {
        ngx_log_error(NGX_LOG_ERR, c->log, 0,
                      "tfs alloc buf failed");
        ngx_http_tfs_finalize_request(r, t, NGX_HTTP_INTERNAL_SERVER_ERROR);
        return;
    }

    if (c->read->timer_set) {
        ngx_del_timer(c->read);
    }

    for ( ;; ) {

        for (chain = t->recv_chain; chain; chain = chain->next) {
            if (chain->buf->last != chain->buf->end) {
                break;
            }
        }

        if (chain == NULL) {
            /* need send data */
            ngx_http_tfs_process_buf_overflow(r, t);
            return;
        }

        n = c->recv_chain(c, chain, 0);

        if (n == NGX_AGAIN) {
            if (chain->buf->last == chain->buf->end) {
                ngx_http_tfs_process_buf_overflow(r, t);
                return;
            }

            ngx_add_timer(c->read, t->main_conf->tfs_read_timeout);
            if (ngx_handle_read_event(c->read, 0) != NGX_OK) {
                ngx_log_error(NGX_LOG_ERR, c->log, 0,
                              "tfs handle read event failed");
                ngx_http_tfs_finalize_request(r, t,
                                              NGX_HTTP_INTERNAL_SERVER_ERROR);
                return;
            }

            return;
        }

        if (n == 0) {
            ngx_log_error(NGX_LOG_ERR, c->log, 0,
                          "tfs prematurely closed connection");
        }

        if (n == NGX_ERROR || n == 0) {
            ngx_log_error(NGX_LOG_ERR, c->log, 0, "recv chain error");
            ngx_http_tfs_finalize_request(r, t, NGX_HTTP_INTERNAL_SERVER_ERROR);

            return;
        }

        if (t->parse_state == NGX_HTTP_TFS_HEADER) {
            rc = ngx_http_tfs_process_header(t, n);

            if (rc == NGX_AGAIN) {
                continue;
            }

            if (rc < 0 || rc == NGX_DONE) {
                break;
            }

            t->parse_state = NGX_HTTP_TFS_BODY;

        } else {
            tp->body_buffer.last += n;
        }

        rc = t->process_request_body(t);

        if (rc == NGX_AGAIN) {
            continue;
        }

        break;
    }

    /* rc == NGX_OK */
    ngx_http_tfs_finalize_state(t, rc);
}
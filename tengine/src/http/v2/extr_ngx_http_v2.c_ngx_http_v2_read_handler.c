#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_6__ ;
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
typedef  scalar_t__ ssize_t ;
struct TYPE_19__ {int recv_buffer_size; int /*<<< orphan*/ * recv_buffer; } ;
typedef  TYPE_3__ ngx_http_v2_main_conf_t ;
struct TYPE_18__ {int buffer_used; int /*<<< orphan*/ * (* handler ) (TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;scalar_t__ incomplete; int /*<<< orphan*/  buffer; } ;
struct TYPE_20__ {int blocked; int goaway; scalar_t__ pushing; scalar_t__ processing; scalar_t__ last_out; TYPE_2__ state; TYPE_1__* http_connection; } ;
typedef  TYPE_4__ ngx_http_v2_connection_t ;
struct TYPE_21__ {scalar_t__ timer_set; scalar_t__ ready; scalar_t__ timedout; TYPE_6__* data; } ;
typedef  TYPE_5__ ngx_event_t ;
struct TYPE_22__ {scalar_t__ (* recv ) (TYPE_6__*,int /*<<< orphan*/ *,size_t) ;int error; int /*<<< orphan*/  log; scalar_t__ close; TYPE_4__* data; } ;
typedef  TYPE_6__ ngx_connection_t ;
struct TYPE_17__ {int /*<<< orphan*/  conf_ctx; } ;

/* Variables and functions */
 scalar_t__ NGX_AGAIN ; 
 scalar_t__ NGX_ERROR ; 
 int /*<<< orphan*/  NGX_ETIMEDOUT ; 
 int /*<<< orphan*/  NGX_HTTP_V2_INTERNAL_ERROR ; 
 int /*<<< orphan*/  NGX_HTTP_V2_NO_ERROR ; 
 int /*<<< orphan*/  NGX_HTTP_V2_PROTOCOL_ERROR ; 
 int NGX_HTTP_V2_STATE_BUFFER_SIZE ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_HTTP ; 
 int /*<<< orphan*/  NGX_LOG_INFO ; 
 scalar_t__ NGX_OK ; 
 int /*<<< orphan*/  ngx_del_timer (TYPE_5__*) ; 
 scalar_t__ ngx_handle_read_event (TYPE_5__*,int /*<<< orphan*/ ) ; 
 TYPE_3__* ngx_http_get_module_main_conf (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_v2_finalize_connection (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_v2_handle_connection (TYPE_4__*) ; 
 int /*<<< orphan*/  ngx_http_v2_module ; 
 scalar_t__ ngx_http_v2_send_goaway (TYPE_4__*,int /*<<< orphan*/ ) ; 
 scalar_t__ ngx_http_v2_send_output_queue (TYPE_4__*) ; 
 int /*<<< orphan*/  ngx_log_debug0 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ngx_memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ stub1 (TYPE_6__*,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/ * stub2 (TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ngx_http_v2_read_handler(ngx_event_t *rev)
{
    u_char                    *p, *end;
    size_t                     available;
    ssize_t                    n;
    ngx_connection_t          *c;
    ngx_http_v2_main_conf_t   *h2mcf;
    ngx_http_v2_connection_t  *h2c;

    c = rev->data;
    h2c = c->data;

    if (rev->timedout) {
        ngx_log_error(NGX_LOG_INFO, c->log, NGX_ETIMEDOUT, "client timed out");
        ngx_http_v2_finalize_connection(h2c, NGX_HTTP_V2_PROTOCOL_ERROR);
        return;
    }

    ngx_log_debug0(NGX_LOG_DEBUG_HTTP, c->log, 0, "http2 read handler");

    h2c->blocked = 1;

    if (c->close) {
        c->close = 0;

        if (!h2c->goaway) {
            h2c->goaway = 1;

            if (ngx_http_v2_send_goaway(h2c, NGX_HTTP_V2_NO_ERROR)
                == NGX_ERROR)
            {
                ngx_http_v2_finalize_connection(h2c, 0);
                return;
            }

            if (ngx_http_v2_send_output_queue(h2c) == NGX_ERROR) {
                ngx_http_v2_finalize_connection(h2c, 0);
                return;
            }
        }

        h2c->blocked = 0;

        return;
    }

    h2mcf = ngx_http_get_module_main_conf(h2c->http_connection->conf_ctx,
                                          ngx_http_v2_module);

    available = h2mcf->recv_buffer_size - 2 * NGX_HTTP_V2_STATE_BUFFER_SIZE;

    do {
        p = h2mcf->recv_buffer;

        ngx_memcpy(p, h2c->state.buffer, NGX_HTTP_V2_STATE_BUFFER_SIZE);
        end = p + h2c->state.buffer_used;

        n = c->recv(c, end, available);

        if (n == NGX_AGAIN) {
            break;
        }

        if (n == 0
            && (h2c->state.incomplete || h2c->processing || h2c->pushing))
        {
            ngx_log_error(NGX_LOG_INFO, c->log, 0,
                          "client prematurely closed connection");
        }

        if (n == 0 || n == NGX_ERROR) {
            c->error = 1;
            ngx_http_v2_finalize_connection(h2c, 0);
            return;
        }

        end += n;

        h2c->state.buffer_used = 0;
        h2c->state.incomplete = 0;

        do {
            p = h2c->state.handler(h2c, p, end);

            if (p == NULL) {
                return;
            }

        } while (p != end);

    } while (rev->ready);

    if (ngx_handle_read_event(rev, 0) != NGX_OK) {
        ngx_http_v2_finalize_connection(h2c, NGX_HTTP_V2_INTERNAL_ERROR);
        return;
    }

    if (h2c->last_out && ngx_http_v2_send_output_queue(h2c) == NGX_ERROR) {
        ngx_http_v2_finalize_connection(h2c, 0);
        return;
    }

    h2c->blocked = 0;

    if (h2c->processing || h2c->pushing) {
        if (rev->timer_set) {
            ngx_del_timer(rev);
        }

        return;
    }

    ngx_http_v2_handle_connection(h2c);
}
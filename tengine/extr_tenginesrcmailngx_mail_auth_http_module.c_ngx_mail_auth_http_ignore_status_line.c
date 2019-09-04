#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  char u_char ;
struct TYPE_16__ {TYPE_1__* connection; } ;
typedef  TYPE_4__ ngx_mail_session_t ;
struct TYPE_14__ {int /*<<< orphan*/  connection; int /*<<< orphan*/  name; } ;
struct TYPE_17__ {int state; int /*<<< orphan*/  (* handler ) (TYPE_4__*,TYPE_5__*) ;TYPE_3__* response; int /*<<< orphan*/  pool; TYPE_2__ peer; } ;
typedef  TYPE_5__ ngx_mail_auth_http_ctx_t ;
struct TYPE_15__ {char* pos; char* last; char* start; } ;
struct TYPE_13__ {int /*<<< orphan*/  log; } ;

/* Variables and functions */
#define  CR 129 
#define  LF 128 
 int /*<<< orphan*/  NGX_LOG_DEBUG_MAIL ; 
 int /*<<< orphan*/  NGX_LOG_ERR ; 
 int /*<<< orphan*/  ngx_close_connection (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_destroy_pool (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_log_debug0 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_mail_auth_http_process_headers (TYPE_4__*,TYPE_5__*) ; 
 int /*<<< orphan*/  ngx_mail_session_internal_server_error (TYPE_4__*) ; 
 int /*<<< orphan*/  stub1 (TYPE_4__*,TYPE_5__*) ; 

__attribute__((used)) static void
ngx_mail_auth_http_ignore_status_line(ngx_mail_session_t *s,
    ngx_mail_auth_http_ctx_t *ctx)
{
    u_char  *p, ch;
    enum  {
        sw_start = 0,
        sw_H,
        sw_HT,
        sw_HTT,
        sw_HTTP,
        sw_skip,
        sw_almost_done
    } state;

    ngx_log_debug0(NGX_LOG_DEBUG_MAIL, s->connection->log, 0,
                   "mail auth http process status line");

    state = ctx->state;

    for (p = ctx->response->pos; p < ctx->response->last; p++) {
        ch = *p;

        switch (state) {

        /* "HTTP/" */
        case sw_start:
            if (ch == 'H') {
                state = sw_H;
                break;
            }
            goto next;

        case sw_H:
            if (ch == 'T') {
                state = sw_HT;
                break;
            }
            goto next;

        case sw_HT:
            if (ch == 'T') {
                state = sw_HTT;
                break;
            }
            goto next;

        case sw_HTT:
            if (ch == 'P') {
                state = sw_HTTP;
                break;
            }
            goto next;

        case sw_HTTP:
            if (ch == '/') {
                state = sw_skip;
                break;
            }
            goto next;

        /* any text until end of line */
        case sw_skip:
            switch (ch) {
            case CR:
                state = sw_almost_done;

                break;
            case LF:
                goto done;
            }
            break;

        /* end of status line */
        case sw_almost_done:
            if (ch == LF) {
                goto done;
            }

            ngx_log_error(NGX_LOG_ERR, s->connection->log, 0,
                          "auth http server %V sent invalid response",
                          ctx->peer.name);
            ngx_close_connection(ctx->peer.connection);
            ngx_destroy_pool(ctx->pool);
            ngx_mail_session_internal_server_error(s);
            return;
        }
    }

    ctx->response->pos = p;
    ctx->state = state;

    return;

next:

    p = ctx->response->start - 1;

done:

    ctx->response->pos = p + 1;
    ctx->state = 0;
    ctx->handler = ngx_mail_auth_http_process_headers;
    ctx->handler(s, ctx);
}
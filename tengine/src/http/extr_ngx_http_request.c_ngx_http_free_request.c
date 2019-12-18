#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_8__ ;
typedef  struct TYPE_21__   TYPE_7__ ;
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct linger {int l_onoff; scalar_t__ l_linger; } ;
typedef  int /*<<< orphan*/  ngx_pool_t ;
struct TYPE_18__ {char* action; TYPE_6__* data; } ;
typedef  TYPE_4__ ngx_log_t ;
typedef  scalar_t__ ngx_int_t ;
struct TYPE_16__ {scalar_t__ len; } ;
struct TYPE_15__ {scalar_t__ status; } ;
struct TYPE_19__ {int /*<<< orphan*/ * pool; TYPE_3__* connection; TYPE_2__ request_line; int /*<<< orphan*/  logged; TYPE_1__ headers_out; scalar_t__ stat_writing; scalar_t__ stat_reading; TYPE_8__* cleanup; } ;
typedef  TYPE_5__ ngx_http_request_t ;
struct TYPE_20__ {int /*<<< orphan*/ * request; } ;
typedef  TYPE_6__ ngx_http_log_ctx_t ;
struct TYPE_21__ {scalar_t__ reset_timedout_connection; } ;
typedef  TYPE_7__ ngx_http_core_loc_conf_t ;
struct TYPE_22__ {struct TYPE_22__* next; int /*<<< orphan*/  data; int /*<<< orphan*/  (* handler ) (int /*<<< orphan*/ ) ;} ;
typedef  TYPE_8__ ngx_http_cleanup_t ;
struct TYPE_17__ {scalar_t__ sent; int destroyed; int /*<<< orphan*/  fd; scalar_t__ timedout; TYPE_4__* log; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_LOG_ALERT ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_HTTP ; 
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SO_LINGER ; 
 int /*<<< orphan*/  ngx_atomic_fetch_add (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ngx_destroy_pool (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_http_core_module ; 
 TYPE_7__* ngx_http_get_module_loc_conf (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_log_request (TYPE_5__*) ; 
 int /*<<< orphan*/  ngx_log_debug0 (int /*<<< orphan*/ ,TYPE_4__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,TYPE_4__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ngx_socket_errno ; 
 int /*<<< orphan*/  ngx_stat_reading ; 
 int /*<<< orphan*/  ngx_stat_writing ; 
 int setsockopt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void const*,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

void
ngx_http_free_request(ngx_http_request_t *r, ngx_int_t rc)
{
    ngx_log_t                 *log;
    ngx_pool_t                *pool;
    struct linger              linger;
    ngx_http_cleanup_t        *cln;
    ngx_http_log_ctx_t        *ctx;
    ngx_http_core_loc_conf_t  *clcf;

    log = r->connection->log;

    ngx_log_debug0(NGX_LOG_DEBUG_HTTP, log, 0, "http close request");

    if (r->pool == NULL) {
        ngx_log_error(NGX_LOG_ALERT, log, 0, "http request already closed");
        return;
    }

    cln = r->cleanup;
    r->cleanup = NULL;

    while (cln) {
        if (cln->handler) {
            cln->handler(cln->data);
        }

        cln = cln->next;
    }

#if (NGX_STAT_STUB)

    if (r->stat_reading) {
        (void) ngx_atomic_fetch_add(ngx_stat_reading, -1);
    }

    if (r->stat_writing) {
        (void) ngx_atomic_fetch_add(ngx_stat_writing, -1);
    }

#endif

    if (rc > 0 && (r->headers_out.status == 0 || r->connection->sent == 0)) {
        r->headers_out.status = rc;
    }

    if (!r->logged) {
        log->action = "logging request";

        ngx_http_log_request(r);
    }

    log->action = "closing request";

    if (r->connection->timedout) {
        clcf = ngx_http_get_module_loc_conf(r, ngx_http_core_module);

        if (clcf->reset_timedout_connection) {
            linger.l_onoff = 1;
            linger.l_linger = 0;

            if (setsockopt(r->connection->fd, SOL_SOCKET, SO_LINGER,
                           (const void *) &linger, sizeof(struct linger)) == -1)
            {
                ngx_log_error(NGX_LOG_ALERT, log, ngx_socket_errno,
                              "setsockopt(SO_LINGER) failed");
            }
        }
    }

    /* the various request strings were allocated from r->pool */
    ctx = log->data;
    ctx->request = NULL;

    r->request_line.len = 0;

    r->connection->destroyed = 1;

    /*
     * Setting r->pool to NULL will increase probability to catch double close
     * of request since the request object is allocated from its own pool.
     */

    pool = r->pool;
    r->pool = NULL;

    ngx_destroy_pool(pool);
}
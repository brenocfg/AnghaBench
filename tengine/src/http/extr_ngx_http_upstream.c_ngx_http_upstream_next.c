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
typedef  struct TYPE_32__   TYPE_7__ ;
typedef  struct TYPE_31__   TYPE_6__ ;
typedef  struct TYPE_30__   TYPE_5__ ;
typedef  struct TYPE_29__   TYPE_4__ ;
typedef  struct TYPE_28__   TYPE_3__ ;
typedef  struct TYPE_27__   TYPE_2__ ;
typedef  struct TYPE_26__   TYPE_1__ ;
typedef  struct TYPE_25__   TYPE_19__ ;
typedef  struct TYPE_24__   TYPE_10__ ;

/* Type definitions */
typedef  int ngx_uint_t ;
typedef  scalar_t__ ngx_msec_t ;
typedef  scalar_t__ ngx_int_t ;
struct TYPE_33__ {scalar_t__ tries; scalar_t__ start_time; scalar_t__ resolved; TYPE_10__* connection; scalar_t__ cached; int /*<<< orphan*/ * sockaddr; int /*<<< orphan*/  data; int /*<<< orphan*/  (* free ) (TYPE_9__*,int /*<<< orphan*/ ,int) ;} ;
struct TYPE_30__ {scalar_t__ cache_status; scalar_t__ (* reinit_request ) (TYPE_6__*) ;TYPE_9__ peer; TYPE_2__* conf; scalar_t__ request_sent; TYPE_1__* state; scalar_t__ multi; } ;
typedef  TYPE_5__ ngx_http_upstream_t ;
struct TYPE_31__ {int method; TYPE_19__* connection; TYPE_3__* cache; scalar_t__ request_body_no_buffering; } ;
typedef  TYPE_6__ ngx_http_request_t ;
struct TYPE_32__ {scalar_t__ retry_cached_connection; } ;
typedef  TYPE_7__ ngx_http_core_loc_conf_t ;
struct TYPE_29__ {int no_wait_shutdown; int no_send_shutdown; } ;
struct TYPE_28__ {scalar_t__ stale_error; } ;
struct TYPE_27__ {scalar_t__ next_upstream_timeout; int next_upstream; int cache_use_stale; } ;
struct TYPE_26__ {int status; int /*<<< orphan*/  bytes_sent; } ;
struct TYPE_25__ {int /*<<< orphan*/  log; scalar_t__ error; } ;
struct TYPE_24__ {int fd; scalar_t__ pool; TYPE_4__* ssl; int /*<<< orphan*/  sent; } ;

/* Variables and functions */
 scalar_t__ NGX_DONE ; 
 int /*<<< orphan*/  NGX_ETIMEDOUT ; 
 int NGX_HTTP_BAD_GATEWAY ; 
 scalar_t__ NGX_HTTP_CACHE_EXPIRED ; 
 scalar_t__ NGX_HTTP_CACHE_STALE ; 
 int NGX_HTTP_CLIENT_CLOSED_REQUEST ; 
 int NGX_HTTP_FORBIDDEN ; 
 int NGX_HTTP_GATEWAY_TIME_OUT ; 
 scalar_t__ NGX_HTTP_INTERNAL_SERVER_ERROR ; 
 int NGX_HTTP_LOCK ; 
 int NGX_HTTP_NOT_FOUND ; 
 int NGX_HTTP_PATCH ; 
 int NGX_HTTP_POST ; 
 int NGX_HTTP_SERVICE_UNAVAILABLE ; 
 int NGX_HTTP_TOO_MANY_REQUESTS ; 
 int NGX_HTTP_UPSTREAM_FT_ERROR ; 
#define  NGX_HTTP_UPSTREAM_FT_HTTP_403 134 
#define  NGX_HTTP_UPSTREAM_FT_HTTP_404 133 
#define  NGX_HTTP_UPSTREAM_FT_HTTP_429 132 
#define  NGX_HTTP_UPSTREAM_FT_HTTP_500 131 
#define  NGX_HTTP_UPSTREAM_FT_HTTP_503 130 
#define  NGX_HTTP_UPSTREAM_FT_HTTP_504 129 
 int NGX_HTTP_UPSTREAM_FT_NON_IDEMPOTENT ; 
#define  NGX_HTTP_UPSTREAM_FT_TIMEOUT 128 
 scalar_t__ NGX_HTTP_UPSTREAM_INVALID_HEADER ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_HTTP ; 
 int /*<<< orphan*/  NGX_LOG_ERR ; 
 int /*<<< orphan*/  NGX_LOG_INFO ; 
 scalar_t__ NGX_OK ; 
 int NGX_PEER_FAILED ; 
 int NGX_PEER_NEXT ; 
 int /*<<< orphan*/  ngx_close_connection (TYPE_10__*) ; 
 scalar_t__ ngx_current_msec ; 
 int /*<<< orphan*/  ngx_destroy_pool (scalar_t__) ; 
 int /*<<< orphan*/  ngx_http_core_module ; 
 TYPE_7__* ngx_http_get_module_loc_conf (TYPE_6__*,int /*<<< orphan*/ ) ; 
 scalar_t__ ngx_http_multi_connection_fake (TYPE_6__*) ; 
 int /*<<< orphan*/  ngx_http_multi_upstream_next (TYPE_19__*,int) ; 
 scalar_t__ ngx_http_upstream_cache_send (TYPE_6__*,TYPE_5__*) ; 
 int /*<<< orphan*/  ngx_http_upstream_connect (TYPE_6__*,TYPE_5__*) ; 
 int /*<<< orphan*/  ngx_http_upstream_finalize_request (TYPE_6__*,TYPE_5__*,int) ; 
 int /*<<< orphan*/  ngx_log_debug1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  ngx_ssl_shutdown (TYPE_10__*) ; 
 int /*<<< orphan*/  stub1 (TYPE_9__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ stub2 (TYPE_6__*) ; 

__attribute__((used)) static void
ngx_http_upstream_next(ngx_http_request_t *r, ngx_http_upstream_t *u,
    ngx_uint_t ft_type)
{
    ngx_msec_t  timeout;
    ngx_uint_t  status, state;

#if (T_NGX_HTTP_UPSTREAM_RETRY_CC)
    ngx_http_core_loc_conf_t  *clcf;
#endif

    ngx_log_debug1(NGX_LOG_DEBUG_HTTP, r->connection->log, 0,
                   "http next upstream, %xi", ft_type);

#if (T_NGX_MULTI_UPSTREAM)
    if (u->multi && ngx_http_multi_connection_fake(r)) {
        ngx_log_error(NGX_LOG_INFO, r->connection->log, 0,
                "multi: http next upstream fake_r %p", r);

        ngx_http_multi_upstream_next(r->connection, ft_type);
        return;
    }
#endif

    if (u->peer.sockaddr) {

        if (u->peer.connection) {
            u->state->bytes_sent = u->peer.connection->sent;
        }

        if (ft_type == NGX_HTTP_UPSTREAM_FT_HTTP_403
            || ft_type == NGX_HTTP_UPSTREAM_FT_HTTP_404)
        {
            state = NGX_PEER_NEXT;

        } else {
            state = NGX_PEER_FAILED;
        }

        u->peer.free(&u->peer, u->peer.data, state);
        u->peer.sockaddr = NULL;
    }

    if (ft_type == NGX_HTTP_UPSTREAM_FT_TIMEOUT) {
        ngx_log_error(NGX_LOG_ERR, r->connection->log, NGX_ETIMEDOUT,
                      "upstream timed out");
    }

#if (T_NGX_HTTP_UPSTREAM_RETRY_CC)
    clcf = ngx_http_get_module_loc_conf(r, ngx_http_core_module);
#endif

    if (u->peer.cached && ft_type == NGX_HTTP_UPSTREAM_FT_ERROR
#if (T_NGX_HTTP_UPSTREAM_RETRY_CC)
        && clcf->retry_cached_connection
#endif
       )
    {
        /* TODO: inform balancer instead */
        u->peer.tries++;
    }

    switch (ft_type) {

    case NGX_HTTP_UPSTREAM_FT_TIMEOUT:
    case NGX_HTTP_UPSTREAM_FT_HTTP_504:
        status = NGX_HTTP_GATEWAY_TIME_OUT;
        break;

    case NGX_HTTP_UPSTREAM_FT_HTTP_500:
        status = NGX_HTTP_INTERNAL_SERVER_ERROR;
        break;

    case NGX_HTTP_UPSTREAM_FT_HTTP_503:
        status = NGX_HTTP_SERVICE_UNAVAILABLE;
        break;

    case NGX_HTTP_UPSTREAM_FT_HTTP_403:
        status = NGX_HTTP_FORBIDDEN;
        break;

    case NGX_HTTP_UPSTREAM_FT_HTTP_404:
        status = NGX_HTTP_NOT_FOUND;
        break;

    case NGX_HTTP_UPSTREAM_FT_HTTP_429:
        status = NGX_HTTP_TOO_MANY_REQUESTS;
        break;

    /*
     * NGX_HTTP_UPSTREAM_FT_BUSY_LOCK and NGX_HTTP_UPSTREAM_FT_MAX_WAITING
     * never reach here
     */

    default:
        status = NGX_HTTP_BAD_GATEWAY;
    }

    if (r->connection->error) {
        ngx_http_upstream_finalize_request(r, u,
                                           NGX_HTTP_CLIENT_CLOSED_REQUEST);
        return;
    }

    u->state->status = status;

    timeout = u->conf->next_upstream_timeout;

    if (u->request_sent
        && (r->method & (NGX_HTTP_POST|NGX_HTTP_LOCK|NGX_HTTP_PATCH)))
    {
        ft_type |= NGX_HTTP_UPSTREAM_FT_NON_IDEMPOTENT;
    }

    if (u->peer.tries == 0
        || ((u->conf->next_upstream & ft_type) != ft_type)
        || (u->request_sent && r->request_body_no_buffering)
        || (timeout && ngx_current_msec - u->peer.start_time >= timeout))
    {
#if (NGX_HTTP_CACHE)

        if (u->cache_status == NGX_HTTP_CACHE_EXPIRED
            && ((u->conf->cache_use_stale & ft_type) || r->cache->stale_error))
        {
            ngx_int_t  rc;

            rc = u->reinit_request(r);

            if (rc != NGX_OK) {
                ngx_http_upstream_finalize_request(r, u, rc);
                return;
            }

            u->cache_status = NGX_HTTP_CACHE_STALE;
            rc = ngx_http_upstream_cache_send(r, u);

            if (rc == NGX_DONE) {
                return;
            }

            if (rc == NGX_HTTP_UPSTREAM_INVALID_HEADER) {
                rc = NGX_HTTP_INTERNAL_SERVER_ERROR;
            }

            ngx_http_upstream_finalize_request(r, u, rc);
            return;
        }
#endif

        ngx_http_upstream_finalize_request(r, u, status);
        return;
    }

    if (u->peer.connection) {
        ngx_log_debug1(NGX_LOG_DEBUG_HTTP, r->connection->log, 0,
                       "close http upstream connection: %d",
                       u->peer.connection->fd);
#if (NGX_HTTP_SSL)

        if (u->peer.connection->ssl) {
            u->peer.connection->ssl->no_wait_shutdown = 1;
            u->peer.connection->ssl->no_send_shutdown = 1;

            (void) ngx_ssl_shutdown(u->peer.connection);
        }
#endif

        if (u->peer.connection->pool) {
            ngx_destroy_pool(u->peer.connection->pool);
        }

        ngx_close_connection(u->peer.connection);
        u->peer.connection = NULL;
    }

#if (T_NGX_HTTP_DYNAMIC_RESOLVE)    
    u->peer.resolved = 0;
#endif
    ngx_http_upstream_connect(r, u);
}
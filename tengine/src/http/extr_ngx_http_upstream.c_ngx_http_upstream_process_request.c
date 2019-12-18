#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_7__ ;
typedef  struct TYPE_25__   TYPE_6__ ;
typedef  struct TYPE_24__   TYPE_5__ ;
typedef  struct TYPE_23__   TYPE_4__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;
typedef  struct TYPE_19__   TYPE_16__ ;

/* Type definitions */
typedef  int off_t ;
struct TYPE_23__ {int offset; } ;
typedef  TYPE_4__ ngx_temp_file_t ;
struct TYPE_22__ {scalar_t__ connection; } ;
struct TYPE_20__ {scalar_t__ status_n; int content_length_n; } ;
struct TYPE_24__ {TYPE_3__ peer; scalar_t__ store; scalar_t__ cacheable; TYPE_1__ headers_in; TYPE_7__* pipe; } ;
typedef  TYPE_5__ ngx_http_upstream_t ;
struct TYPE_25__ {TYPE_2__* connection; TYPE_16__* cache; } ;
typedef  TYPE_6__ ngx_http_request_t ;
struct TYPE_26__ {int length; scalar_t__ downstream_error; scalar_t__ upstream_eof; scalar_t__ upstream_done; int /*<<< orphan*/  out; scalar_t__ upstream_error; TYPE_4__* temp_file; scalar_t__ writing; int /*<<< orphan*/  aio; } ;
typedef  TYPE_7__ ngx_event_pipe_t ;
struct TYPE_21__ {int /*<<< orphan*/  log; } ;
struct TYPE_19__ {scalar_t__ body_start; } ;

/* Variables and functions */
 scalar_t__ NGX_ABORT ; 
 int /*<<< orphan*/  NGX_ERROR ; 
 int /*<<< orphan*/  NGX_HTTP_BAD_GATEWAY ; 
 scalar_t__ NGX_HTTP_OK ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_HTTP ; 
 int /*<<< orphan*/  NGX_LOG_ERR ; 
 scalar_t__ ngx_event_pipe (TYPE_7__*,int) ; 
 int /*<<< orphan*/  ngx_http_file_cache_free (TYPE_16__*,TYPE_4__*) ; 
 int /*<<< orphan*/  ngx_http_file_cache_update (TYPE_6__*,TYPE_4__*) ; 
 int /*<<< orphan*/  ngx_http_upstream_finalize_request (TYPE_6__*,TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_upstream_store (TYPE_6__*,TYPE_5__*) ; 
 int /*<<< orphan*/  ngx_log_debug0 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ngx_log_debug1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
ngx_http_upstream_process_request(ngx_http_request_t *r,
    ngx_http_upstream_t *u)
{
    ngx_temp_file_t   *tf;
    ngx_event_pipe_t  *p;

    p = u->pipe;

#if (NGX_THREADS)

    if (p->writing && !p->aio) {

        /*
         * make sure to call ngx_event_pipe()
         * if there is an incomplete aio write
         */

        if (ngx_event_pipe(p, 1) == NGX_ABORT) {
            ngx_http_upstream_finalize_request(r, u, NGX_ERROR);
            return;
        }
    }

    if (p->writing) {
        return;
    }

#endif

    if (u->peer.connection) {

        if (u->store) {

            if (p->upstream_eof || p->upstream_done) {

                tf = p->temp_file;

                if (u->headers_in.status_n == NGX_HTTP_OK
                    && (p->upstream_done || p->length == -1)
                    && (u->headers_in.content_length_n == -1
                        || u->headers_in.content_length_n == tf->offset))
                {
                    ngx_http_upstream_store(r, u);
                }
            }
        }

#if (NGX_HTTP_CACHE)

        if (u->cacheable) {

            if (p->upstream_done) {
                ngx_http_file_cache_update(r, p->temp_file);

            } else if (p->upstream_eof) {

                tf = p->temp_file;

                if (p->length == -1
                    && (u->headers_in.content_length_n == -1
                        || u->headers_in.content_length_n
                           == tf->offset - (off_t) r->cache->body_start))
                {
                    ngx_http_file_cache_update(r, tf);

                } else {
                    ngx_http_file_cache_free(r->cache, tf);
                }

            } else if (p->upstream_error) {
                ngx_http_file_cache_free(r->cache, p->temp_file);
            }
        }

#endif

        if (p->upstream_done || p->upstream_eof || p->upstream_error) {
            ngx_log_debug1(NGX_LOG_DEBUG_HTTP, r->connection->log, 0,
                           "http upstream exit: %p", p->out);

            if (p->upstream_done
                || (p->upstream_eof && p->length == -1))
            {
                ngx_http_upstream_finalize_request(r, u, 0);
                return;
            }

            if (p->upstream_eof) {
                ngx_log_error(NGX_LOG_ERR, r->connection->log, 0,
                              "upstream prematurely closed connection");
            }

            ngx_http_upstream_finalize_request(r, u, NGX_HTTP_BAD_GATEWAY);
            return;
        }
    }

    if (p->downstream_error) {
        ngx_log_debug0(NGX_LOG_DEBUG_HTTP, r->connection->log, 0,
                       "http upstream downstream error");

        if (!u->cacheable && !u->store && u->peer.connection) {
            ngx_http_upstream_finalize_request(r, u, NGX_ERROR);
        }
    }
}
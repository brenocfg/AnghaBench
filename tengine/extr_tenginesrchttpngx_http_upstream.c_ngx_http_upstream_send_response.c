#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_60__   TYPE_9__ ;
typedef  struct TYPE_59__   TYPE_8__ ;
typedef  struct TYPE_58__   TYPE_7__ ;
typedef  struct TYPE_57__   TYPE_6__ ;
typedef  struct TYPE_56__   TYPE_5__ ;
typedef  struct TYPE_55__   TYPE_4__ ;
typedef  struct TYPE_54__   TYPE_41__ ;
typedef  struct TYPE_53__   TYPE_40__ ;
typedef  struct TYPE_52__   TYPE_3__ ;
typedef  struct TYPE_51__   TYPE_2__ ;
typedef  struct TYPE_50__   TYPE_21__ ;
typedef  struct TYPE_49__   TYPE_1__ ;
typedef  struct TYPE_48__   TYPE_16__ ;
typedef  struct TYPE_47__   TYPE_15__ ;
typedef  struct TYPE_46__   TYPE_14__ ;
typedef  struct TYPE_45__   TYPE_13__ ;
typedef  struct TYPE_44__   TYPE_12__ ;
typedef  struct TYPE_43__   TYPE_11__ ;
typedef  struct TYPE_42__   TYPE_10__ ;

/* Type definitions */
typedef  scalar_t__ ssize_t ;
typedef  int /*<<< orphan*/  ngx_temp_file_t ;
typedef  scalar_t__ ngx_int_t ;
struct TYPE_58__ {int recycled; scalar_t__ pos; scalar_t__ last; scalar_t__ start; } ;
struct TYPE_56__ {TYPE_4__* connection; } ;
struct TYPE_52__ {int /*<<< orphan*/  tag; } ;
struct TYPE_44__ {int header_sent; scalar_t__ (* input_filter ) (TYPE_13__*,scalar_t__) ;scalar_t__ (* input_filter_init ) (TYPE_13__*) ;scalar_t__ length; int /*<<< orphan*/  (* read_event_handler ) (TYPE_13__*,TYPE_12__*) ;TYPE_8__* conf; TYPE_7__ buffer; scalar_t__ cacheable; scalar_t__ store; TYPE_5__ peer; TYPE_3__ output; TYPE_15__* pipe; TYPE_13__* input_filter_ctx; TYPE_1__* state; int /*<<< orphan*/  buffering; scalar_t__ upgrade; } ;
typedef  TYPE_12__ ngx_http_upstream_t ;
struct TYPE_45__ {int /*<<< orphan*/  (* write_event_handler ) (TYPE_13__*) ;int /*<<< orphan*/  pool; scalar_t__ limit_rate; TYPE_11__* request_body; int /*<<< orphan*/  preserve_body; struct TYPE_45__* main; scalar_t__ header_only; TYPE_16__* connection; scalar_t__ post_action; } ;
typedef  TYPE_13__ ngx_http_request_t ;
struct TYPE_46__ {int /*<<< orphan*/  send_lowat; int /*<<< orphan*/  send_timeout; scalar_t__ tcp_nodelay; } ;
typedef  TYPE_14__ ngx_http_core_loc_conf_t ;
struct TYPE_47__ {int downstream_error; int cacheable; int single_buf; int free_bufs; int cyclic_temp_file; int length; TYPE_13__* input_ctx; int /*<<< orphan*/  send_lowat; int /*<<< orphan*/  send_timeout; int /*<<< orphan*/  read_timeout; TYPE_40__* buf_to_file; scalar_t__ preread_size; TYPE_41__* preread_bufs; int /*<<< orphan*/  temp_file_write_size; int /*<<< orphan*/  max_temp_file_size; TYPE_21__* temp_file; int /*<<< orphan*/  start_sec; int /*<<< orphan*/  limit_rate; int /*<<< orphan*/  log; int /*<<< orphan*/  pool; TYPE_16__* downstream; TYPE_4__* upstream; int /*<<< orphan*/  busy_size; int /*<<< orphan*/  bufs; int /*<<< orphan*/  tag; TYPE_13__* output_ctx; int /*<<< orphan*/  output_filter; } ;
typedef  TYPE_15__ ngx_event_pipe_t ;
struct TYPE_48__ {scalar_t__ sendfile; int /*<<< orphan*/  log; } ;
typedef  TYPE_16__ ngx_connection_t ;
struct TYPE_60__ {void* fd; } ;
struct TYPE_59__ {int /*<<< orphan*/  read_timeout; scalar_t__ cyclic_temp_file; int /*<<< orphan*/  temp_file_write_size; int /*<<< orphan*/  max_temp_file_size; int /*<<< orphan*/  temp_path; int /*<<< orphan*/  limit_rate; int /*<<< orphan*/  busy_buffers_size; int /*<<< orphan*/  bufs; int /*<<< orphan*/  preserve_output; } ;
struct TYPE_57__ {int /*<<< orphan*/  log; void* fd; } ;
struct TYPE_55__ {TYPE_2__* read; } ;
struct TYPE_54__ {int /*<<< orphan*/ * next; TYPE_7__* buf; } ;
struct TYPE_53__ {int temporary; scalar_t__ last; scalar_t__ pos; scalar_t__ start; } ;
struct TYPE_51__ {scalar_t__ ready; } ;
struct TYPE_50__ {int persistent; char* warn; int /*<<< orphan*/  log_level; int /*<<< orphan*/  pool; int /*<<< orphan*/  path; TYPE_6__ file; } ;
struct TYPE_49__ {int /*<<< orphan*/  response_length; } ;
struct TYPE_43__ {TYPE_10__* temp_file; } ;
struct TYPE_42__ {TYPE_9__ file; } ;

/* Variables and functions */
 scalar_t__ NGX_ERROR ; 
 int /*<<< orphan*/  NGX_HTTP_FLUSH ; 
 void* NGX_INVALID_FILE ; 
 int /*<<< orphan*/  NGX_LOG_WARN ; 
 scalar_t__ NGX_OK ; 
 int NGX_USE_IOCP_EVENT ; 
 TYPE_41__* ngx_alloc_chain_link (int /*<<< orphan*/ ) ; 
 TYPE_40__* ngx_calloc_buf (int /*<<< orphan*/ ) ; 
 int ngx_event_flags ; 
 int /*<<< orphan*/  ngx_http_core_module ; 
 TYPE_14__* ngx_http_get_module_loc_conf (TYPE_13__*,int /*<<< orphan*/ ) ; 
 scalar_t__ ngx_http_send_header (TYPE_13__*) ; 
 scalar_t__ ngx_http_send_special (TYPE_13__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_upstream_finalize_request (TYPE_13__*,TYPE_12__*,scalar_t__) ; 
 scalar_t__ ngx_http_upstream_non_buffered_filter (TYPE_13__*,scalar_t__) ; 
 scalar_t__ ngx_http_upstream_non_buffered_filter_init (TYPE_13__*) ; 
 int /*<<< orphan*/  ngx_http_upstream_output_filter ; 
 int /*<<< orphan*/  ngx_http_upstream_process_downstream (TYPE_13__*) ; 
 int /*<<< orphan*/  ngx_http_upstream_process_non_buffered_downstream (TYPE_13__*) ; 
 int /*<<< orphan*/  ngx_http_upstream_process_non_buffered_upstream (TYPE_13__*,TYPE_12__*) ; 
 int /*<<< orphan*/  ngx_http_upstream_process_upstream (TYPE_13__*,TYPE_12__*) ; 
 int /*<<< orphan*/  ngx_http_upstream_upgrade (TYPE_13__*,TYPE_12__*) ; 
 TYPE_21__* ngx_pcalloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ngx_pool_run_cleanup_file (int /*<<< orphan*/ ,void*) ; 
 scalar_t__ ngx_tcp_nodelay (TYPE_16__*) ; 
 int /*<<< orphan*/  ngx_time () ; 
 scalar_t__ stub1 (TYPE_13__*) ; 
 scalar_t__ stub2 (TYPE_13__*,scalar_t__) ; 
 scalar_t__ stub3 (TYPE_13__*) ; 

__attribute__((used)) static void
ngx_http_upstream_send_response(ngx_http_request_t *r, ngx_http_upstream_t *u)
{
    ssize_t                    n;
    ngx_int_t                  rc;
    ngx_event_pipe_t          *p;
    ngx_connection_t          *c;
    ngx_http_core_loc_conf_t  *clcf;

    rc = ngx_http_send_header(r);

    if (rc == NGX_ERROR || rc > NGX_OK || r->post_action) {
        ngx_http_upstream_finalize_request(r, u, rc);
        return;
    }

    u->header_sent = 1;

    if (u->upgrade) {

#if (NGX_HTTP_CACHE)

        if (r->cache) {
            ngx_http_file_cache_free(r->cache, u->pipe->temp_file);
        }

#endif

        ngx_http_upstream_upgrade(r, u);
        return;
    }

    c = r->connection;

    if (r->header_only) {

        if (!u->buffering) {
            ngx_http_upstream_finalize_request(r, u, rc);
            return;
        }

        if (!u->cacheable && !u->store) {
            ngx_http_upstream_finalize_request(r, u, rc);
            return;
        }

        u->pipe->downstream_error = 1;
    }

    if (r->request_body && r->request_body->temp_file
        && r == r->main && !r->preserve_body
        && !u->conf->preserve_output)
    {
        ngx_pool_run_cleanup_file(r->pool, r->request_body->temp_file->file.fd);
        r->request_body->temp_file->file.fd = NGX_INVALID_FILE;
    }

    clcf = ngx_http_get_module_loc_conf(r, ngx_http_core_module);

    if (!u->buffering) {

#if (NGX_HTTP_CACHE)

        if (r->cache) {
            ngx_http_file_cache_free(r->cache, u->pipe->temp_file);
        }

#endif

        if (u->input_filter == NULL) {
            u->input_filter_init = ngx_http_upstream_non_buffered_filter_init;
            u->input_filter = ngx_http_upstream_non_buffered_filter;
            u->input_filter_ctx = r;
        }

        u->read_event_handler = ngx_http_upstream_process_non_buffered_upstream;
        r->write_event_handler =
                             ngx_http_upstream_process_non_buffered_downstream;

        r->limit_rate = 0;

        if (u->input_filter_init(u->input_filter_ctx) == NGX_ERROR) {
            ngx_http_upstream_finalize_request(r, u, NGX_ERROR);
            return;
        }

        if (clcf->tcp_nodelay && ngx_tcp_nodelay(c) != NGX_OK) {
            ngx_http_upstream_finalize_request(r, u, NGX_ERROR);
            return;
        }

        n = u->buffer.last - u->buffer.pos;

        if (n) {
            u->buffer.last = u->buffer.pos;

            u->state->response_length += n;

            if (u->input_filter(u->input_filter_ctx, n) == NGX_ERROR) {
                ngx_http_upstream_finalize_request(r, u, NGX_ERROR);
                return;
            }

            ngx_http_upstream_process_non_buffered_downstream(r);

        } else {
            u->buffer.pos = u->buffer.start;
            u->buffer.last = u->buffer.start;

            if (ngx_http_send_special(r, NGX_HTTP_FLUSH) == NGX_ERROR) {
                ngx_http_upstream_finalize_request(r, u, NGX_ERROR);
                return;
            }

            if (u->peer.connection->read->ready || u->length == 0) {
                ngx_http_upstream_process_non_buffered_upstream(r, u);
            }
        }

        return;
    }

    /* TODO: preallocate event_pipe bufs, look "Content-Length" */

#if (NGX_HTTP_CACHE)

    if (r->cache && r->cache->file.fd != NGX_INVALID_FILE) {
        ngx_pool_run_cleanup_file(r->pool, r->cache->file.fd);
        r->cache->file.fd = NGX_INVALID_FILE;
    }

    switch (ngx_http_test_predicates(r, u->conf->no_cache)) {

    case NGX_ERROR:
        ngx_http_upstream_finalize_request(r, u, NGX_ERROR);
        return;

    case NGX_DECLINED:
        u->cacheable = 0;
        break;

    default: /* NGX_OK */

        if (u->cache_status == NGX_HTTP_CACHE_BYPASS) {

            /* create cache if previously bypassed */

            if (ngx_http_file_cache_create(r) != NGX_OK) {
                ngx_http_upstream_finalize_request(r, u, NGX_ERROR);
                return;
            }
        }

        break;
    }

    if (u->cacheable) {
        time_t  now, valid;

        now = ngx_time();

        valid = r->cache->valid_sec;

        if (valid == 0) {
            valid = ngx_http_file_cache_valid(u->conf->cache_valid,
                                              u->headers_in.status_n);
            if (valid) {
                r->cache->valid_sec = now + valid;
            }
        }

        if (valid) {
            r->cache->date = now;
            r->cache->body_start = (u_short) (u->buffer.pos - u->buffer.start);

            if (u->headers_in.status_n == NGX_HTTP_OK
                || u->headers_in.status_n == NGX_HTTP_PARTIAL_CONTENT)
            {
                r->cache->last_modified = u->headers_in.last_modified_time;

                if (u->headers_in.etag) {
                    r->cache->etag = u->headers_in.etag->value;

                } else {
                    ngx_str_null(&r->cache->etag);
                }

            } else {
                r->cache->last_modified = -1;
                ngx_str_null(&r->cache->etag);
            }

            if (ngx_http_file_cache_set_header(r, u->buffer.start) != NGX_OK) {
                ngx_http_upstream_finalize_request(r, u, NGX_ERROR);
                return;
            }

        } else {
            u->cacheable = 0;
        }
    }

    ngx_log_debug1(NGX_LOG_DEBUG_HTTP, c->log, 0,
                   "http cacheable: %d", u->cacheable);

    if (u->cacheable == 0 && r->cache) {
        ngx_http_file_cache_free(r->cache, u->pipe->temp_file);
    }

    if (r->header_only && !u->cacheable && !u->store) {
        ngx_http_upstream_finalize_request(r, u, 0);
        return;
    }

#endif

    p = u->pipe;

    p->output_filter = ngx_http_upstream_output_filter;
    p->output_ctx = r;
    p->tag = u->output.tag;
    p->bufs = u->conf->bufs;
    p->busy_size = u->conf->busy_buffers_size;
    p->upstream = u->peer.connection;
    p->downstream = c;
    p->pool = r->pool;
    p->log = c->log;
    p->limit_rate = u->conf->limit_rate;
    p->start_sec = ngx_time();

    p->cacheable = u->cacheable || u->store;

    p->temp_file = ngx_pcalloc(r->pool, sizeof(ngx_temp_file_t));
    if (p->temp_file == NULL) {
        ngx_http_upstream_finalize_request(r, u, NGX_ERROR);
        return;
    }

    p->temp_file->file.fd = NGX_INVALID_FILE;
    p->temp_file->file.log = c->log;
    p->temp_file->path = u->conf->temp_path;
    p->temp_file->pool = r->pool;

    if (p->cacheable) {
        p->temp_file->persistent = 1;

#if (NGX_HTTP_CACHE)
        if (r->cache && !r->cache->file_cache->use_temp_path) {
            p->temp_file->path = r->cache->file_cache->path;
            p->temp_file->file.name = r->cache->file.name;
        }
#endif

    } else {
        p->temp_file->log_level = NGX_LOG_WARN;
        p->temp_file->warn = "an upstream response is buffered "
                             "to a temporary file";
    }

    p->max_temp_file_size = u->conf->max_temp_file_size;
    p->temp_file_write_size = u->conf->temp_file_write_size;

#if (NGX_THREADS)
    if (clcf->aio == NGX_HTTP_AIO_THREADS && clcf->aio_write) {
        p->thread_handler = ngx_http_upstream_thread_handler;
        p->thread_ctx = r;
    }
#endif

    p->preread_bufs = ngx_alloc_chain_link(r->pool);
    if (p->preread_bufs == NULL) {
        ngx_http_upstream_finalize_request(r, u, NGX_ERROR);
        return;
    }

    p->preread_bufs->buf = &u->buffer;
    p->preread_bufs->next = NULL;
    u->buffer.recycled = 1;

    p->preread_size = u->buffer.last - u->buffer.pos;

    if (u->cacheable) {

        p->buf_to_file = ngx_calloc_buf(r->pool);
        if (p->buf_to_file == NULL) {
            ngx_http_upstream_finalize_request(r, u, NGX_ERROR);
            return;
        }

        p->buf_to_file->start = u->buffer.start;
        p->buf_to_file->pos = u->buffer.start;
        p->buf_to_file->last = u->buffer.pos;
        p->buf_to_file->temporary = 1;
    }

    if (ngx_event_flags & NGX_USE_IOCP_EVENT) {
        /* the posted aio operation may corrupt a shadow buffer */
        p->single_buf = 1;
    }

    /* TODO: p->free_bufs = 0 if use ngx_create_chain_of_bufs() */
    p->free_bufs = 1;

    /*
     * event_pipe would do u->buffer.last += p->preread_size
     * as though these bytes were read
     */
    u->buffer.last = u->buffer.pos;

    if (u->conf->cyclic_temp_file) {

        /*
         * we need to disable the use of sendfile() if we use cyclic temp file
         * because the writing a new data may interfere with sendfile()
         * that uses the same kernel file pages (at least on FreeBSD)
         */

        p->cyclic_temp_file = 1;
        c->sendfile = 0;

    } else {
        p->cyclic_temp_file = 0;
    }

    p->read_timeout = u->conf->read_timeout;
    p->send_timeout = clcf->send_timeout;
    p->send_lowat = clcf->send_lowat;

    p->length = -1;

    if (u->input_filter_init
        && u->input_filter_init(p->input_ctx) != NGX_OK)
    {
        ngx_http_upstream_finalize_request(r, u, NGX_ERROR);
        return;
    }

    u->read_event_handler = ngx_http_upstream_process_upstream;
    r->write_event_handler = ngx_http_upstream_process_downstream;

    ngx_http_upstream_process_upstream(r, u);
}
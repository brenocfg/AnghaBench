#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_7__ ;
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ngx_int_t ;
struct TYPE_18__ {int /*<<< orphan*/  pool; scalar_t__ request_body_in_file_only; scalar_t__ request_body_no_buffering; TYPE_5__* request_body; } ;
typedef  TYPE_4__ ngx_http_request_t ;
struct TYPE_19__ {scalar_t__ rest; TYPE_6__* bufs; TYPE_3__* temp_file; int /*<<< orphan*/  free; TYPE_1__* buf; } ;
typedef  TYPE_5__ ngx_http_request_body_t ;
struct TYPE_20__ {TYPE_7__* buf; } ;
typedef  TYPE_6__ ngx_chain_t ;
struct TYPE_21__ {int in_file; scalar_t__ file_last; TYPE_2__* file; } ;
typedef  TYPE_7__ ngx_buf_t ;
struct TYPE_16__ {scalar_t__ offset; } ;
struct TYPE_17__ {TYPE_2__ file; } ;
struct TYPE_15__ {scalar_t__ last; scalar_t__ end; } ;

/* Variables and functions */
 scalar_t__ NGX_HTTP_INTERNAL_SERVER_ERROR ; 
 scalar_t__ NGX_OK ; 
 scalar_t__ ngx_chain_add_copy (int /*<<< orphan*/ ,TYPE_6__**,TYPE_6__*) ; 
 TYPE_6__* ngx_chain_get_free_buf (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ ngx_http_write_request_body (TYPE_4__*) ; 
 int /*<<< orphan*/  ngx_memzero (TYPE_7__*,int) ; 

ngx_int_t
ngx_http_request_body_save_filter(ngx_http_request_t *r, ngx_chain_t *in)
{
    ngx_buf_t                 *b;
    ngx_chain_t               *cl;
    ngx_http_request_body_t   *rb;

    rb = r->request_body;

#if (NGX_DEBUG)

#if 0
    for (cl = rb->bufs; cl; cl = cl->next) {
        ngx_log_debug7(NGX_LOG_DEBUG_EVENT, r->connection->log, 0,
                       "http body old buf t:%d f:%d %p, pos %p, size: %z "
                       "file: %O, size: %O",
                       cl->buf->temporary, cl->buf->in_file,
                       cl->buf->start, cl->buf->pos,
                       cl->buf->last - cl->buf->pos,
                       cl->buf->file_pos,
                       cl->buf->file_last - cl->buf->file_pos);
    }
#endif

    for (cl = in; cl; cl = cl->next) {
        ngx_log_debug7(NGX_LOG_DEBUG_EVENT, r->connection->log, 0,
                       "http body new buf t:%d f:%d %p, pos %p, size: %z "
                       "file: %O, size: %O",
                       cl->buf->temporary, cl->buf->in_file,
                       cl->buf->start, cl->buf->pos,
                       cl->buf->last - cl->buf->pos,
                       cl->buf->file_pos,
                       cl->buf->file_last - cl->buf->file_pos);
    }

#endif

    /* TODO: coalesce neighbouring buffers */

    if (ngx_chain_add_copy(r->pool, &rb->bufs, in) != NGX_OK) {
        return NGX_HTTP_INTERNAL_SERVER_ERROR;
    }

#if (T_NGX_INPUT_BODY_FILTER)
    {
    ngx_int_t                  rc;
    ngx_chain_t               *cl;

    for (cl = in; cl; cl = cl->next) {
        rc = ngx_http_top_input_body_filter(r, cl->buf);
        if (rc != NGX_OK) {
            if (rc > NGX_OK && rc < NGX_HTTP_SPECIAL_RESPONSE) {
                ngx_log_error(NGX_LOG_ERR, r->connection->log, 0,
                              "input filter: return code 1xx or 2xx "
                              "will cause trouble and is converted to 500");
            }

            /**
             * NGX_OK: success and continue;
             * NGX_ERROR: failed and exit;
             * NGX_AGAIN: not ready and retry later.
             */

            if (rc < NGX_HTTP_SPECIAL_RESPONSE && rc != NGX_AGAIN) {
                rc = NGX_HTTP_INTERNAL_SERVER_ERROR;
            }

            return rc;
        }
    }
    }
#endif

    if (r->request_body_no_buffering) {
        return NGX_OK;
    }

    if (rb->rest > 0) {

        if (rb->buf && rb->buf->last == rb->buf->end
            && ngx_http_write_request_body(r) != NGX_OK)
        {
            return NGX_HTTP_INTERNAL_SERVER_ERROR;
        }

        return NGX_OK;
    }

    /* rb->rest == 0 */

    if (rb->temp_file || r->request_body_in_file_only) {

        if (ngx_http_write_request_body(r) != NGX_OK) {
            return NGX_HTTP_INTERNAL_SERVER_ERROR;
        }

        if (rb->temp_file->file.offset != 0) {

            cl = ngx_chain_get_free_buf(r->pool, &rb->free);
            if (cl == NULL) {
                return NGX_HTTP_INTERNAL_SERVER_ERROR;
            }

            b = cl->buf;

            ngx_memzero(b, sizeof(ngx_buf_t));

            b->in_file = 1;
            b->file_last = rb->temp_file->file.offset;
            b->file = &rb->temp_file->file;

            rb->bufs = cl;
        }
    }

    return NGX_OK;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_7__ ;
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  char u_char ;
typedef  scalar_t__ ssize_t ;
typedef  scalar_t__ ngx_int_t ;
struct TYPE_13__ {int /*<<< orphan*/  tag; } ;
struct TYPE_19__ {char* pos; char* last; int flush; int memory; int /*<<< orphan*/  tag; } ;
struct TYPE_15__ {int keepalive; TYPE_1__ output; int /*<<< orphan*/  free_bufs; scalar_t__ length; TYPE_6__* out_bufs; TYPE_7__ buffer; } ;
typedef  TYPE_3__ ngx_http_upstream_t ;
struct TYPE_16__ {TYPE_2__* connection; int /*<<< orphan*/  pool; TYPE_3__* upstream; } ;
typedef  TYPE_4__ ngx_http_request_t ;
struct TYPE_17__ {char* pos; char* last; scalar_t__ state; scalar_t__ type; scalar_t__ length; int padding; } ;
typedef  TYPE_5__ ngx_http_fastcgi_ctx_t ;
struct TYPE_18__ {TYPE_7__* buf; struct TYPE_18__* next; } ;
typedef  TYPE_6__ ngx_chain_t ;
typedef  TYPE_7__ ngx_buf_t ;
struct TYPE_14__ {int /*<<< orphan*/  log; } ;

/* Variables and functions */
 char CR ; 
 char LF ; 
 scalar_t__ NGX_AGAIN ; 
 scalar_t__ NGX_ERROR ; 
 scalar_t__ NGX_HTTP_FASTCGI_END_REQUEST ; 
 scalar_t__ NGX_HTTP_FASTCGI_STDERR ; 
 scalar_t__ NGX_HTTP_FASTCGI_STDOUT ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_HTTP ; 
 int /*<<< orphan*/  NGX_LOG_ERR ; 
 scalar_t__ NGX_OK ; 
 TYPE_6__* ngx_chain_get_free_buf (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_http_fastcgi_module ; 
 scalar_t__ ngx_http_fastcgi_process_record (TYPE_4__*,TYPE_5__*) ; 
 scalar_t__ ngx_http_fastcgi_st_data ; 
 scalar_t__ ngx_http_fastcgi_st_padding ; 
 void* ngx_http_fastcgi_st_version ; 
 TYPE_5__* ngx_http_get_module_ctx (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_log_debug0 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ngx_log_debug1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,char*) ; 

__attribute__((used)) static ngx_int_t
ngx_http_fastcgi_non_buffered_filter(void *data, ssize_t bytes)
{
    u_char                  *m, *msg;
    ngx_int_t                rc;
    ngx_buf_t               *b, *buf;
    ngx_chain_t             *cl, **ll;
    ngx_http_request_t      *r;
    ngx_http_upstream_t     *u;
    ngx_http_fastcgi_ctx_t  *f;

    r = data;
    f = ngx_http_get_module_ctx(r, ngx_http_fastcgi_module);

    u = r->upstream;
    buf = &u->buffer;

    buf->pos = buf->last;
    buf->last += bytes;

    for (cl = u->out_bufs, ll = &u->out_bufs; cl; cl = cl->next) {
        ll = &cl->next;
    }

    f->pos = buf->pos;
    f->last = buf->last;

    for ( ;; ) {
        if (f->state < ngx_http_fastcgi_st_data) {

            rc = ngx_http_fastcgi_process_record(r, f);

            if (rc == NGX_AGAIN) {
                break;
            }

            if (rc == NGX_ERROR) {
                return NGX_ERROR;
            }

            if (f->type == NGX_HTTP_FASTCGI_STDOUT && f->length == 0) {
                f->state = ngx_http_fastcgi_st_padding;

                ngx_log_debug0(NGX_LOG_DEBUG_HTTP, r->connection->log, 0,
                               "http fastcgi closed stdout");

                continue;
            }
        }

        if (f->state == ngx_http_fastcgi_st_padding) {

            if (f->type == NGX_HTTP_FASTCGI_END_REQUEST) {

                if (f->pos + f->padding < f->last) {
                    u->length = 0;
                    break;
                }

                if (f->pos + f->padding == f->last) {
                    u->length = 0;
                    u->keepalive = 1;
                    break;
                }

                f->padding -= f->last - f->pos;

                break;
            }

            if (f->pos + f->padding < f->last) {
                f->state = ngx_http_fastcgi_st_version;
                f->pos += f->padding;

                continue;
            }

            if (f->pos + f->padding == f->last) {
                f->state = ngx_http_fastcgi_st_version;

                break;
            }

            f->padding -= f->last - f->pos;

            break;
        }


        /* f->state == ngx_http_fastcgi_st_data */

        if (f->type == NGX_HTTP_FASTCGI_STDERR) {

            if (f->length) {

                if (f->pos == f->last) {
                    break;
                }

                msg = f->pos;

                if (f->pos + f->length <= f->last) {
                    f->pos += f->length;
                    f->length = 0;
                    f->state = ngx_http_fastcgi_st_padding;

                } else {
                    f->length -= f->last - f->pos;
                    f->pos = f->last;
                }

                for (m = f->pos - 1; msg < m; m--) {
                    if (*m != LF && *m != CR && *m != '.' && *m != ' ') {
                        break;
                    }
                }

                ngx_log_error(NGX_LOG_ERR, r->connection->log, 0,
                              "FastCGI sent in stderr: \"%*s\"",
                              m + 1 - msg, msg);

            } else {
                f->state = ngx_http_fastcgi_st_padding;
            }

            continue;
        }

        if (f->type == NGX_HTTP_FASTCGI_END_REQUEST) {

            if (f->pos + f->length <= f->last) {
                f->state = ngx_http_fastcgi_st_padding;
                f->pos += f->length;

                continue;
            }

            f->length -= f->last - f->pos;

            break;
        }


        /* f->type == NGX_HTTP_FASTCGI_STDOUT */

        if (f->pos == f->last) {
            break;
        }

        cl = ngx_chain_get_free_buf(r->pool, &u->free_bufs);
        if (cl == NULL) {
            return NGX_ERROR;
        }

        *ll = cl;
        ll = &cl->next;

        b = cl->buf;

        b->flush = 1;
        b->memory = 1;

        b->pos = f->pos;
        b->tag = u->output.tag;

        ngx_log_debug1(NGX_LOG_DEBUG_HTTP, r->connection->log, 0,
                       "http fastcgi output buf %p", b->pos);

        if (f->pos + f->length <= f->last) {
            f->state = ngx_http_fastcgi_st_padding;
            f->pos += f->length;
            b->last = f->pos;

            continue;
        }

        f->length -= f->last - f->pos;
        b->last = f->last;

        break;
    }

    return NGX_OK;
}
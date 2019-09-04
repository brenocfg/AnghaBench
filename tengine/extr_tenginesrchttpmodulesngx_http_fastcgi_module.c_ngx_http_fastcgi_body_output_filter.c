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

/* Type definitions */
typedef  void* u_char ;
typedef  scalar_t__ off_t ;
typedef  int ngx_uint_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_22__ {int /*<<< orphan*/  pool; TYPE_1__* upstream; TYPE_2__* connection; } ;
typedef  TYPE_3__ ngx_http_request_t ;
struct TYPE_23__ {int version; int request_id_lo; scalar_t__ reserved; void* padding_length; void* content_length_lo; void* content_length_hi; scalar_t__ request_id_hi; void* type; } ;
typedef  TYPE_4__ ngx_http_fastcgi_header_t ;
struct TYPE_24__ {int header_sent; TYPE_6__* free; int /*<<< orphan*/  busy; } ;
typedef  TYPE_5__ ngx_http_fastcgi_ctx_t ;
struct TYPE_25__ {TYPE_7__* buf; struct TYPE_25__* next; } ;
typedef  TYPE_6__ ngx_chain_t ;
typedef  void* ngx_buf_tag_t ;
struct TYPE_26__ {int temporary; void** start; void** pos; void** last; void** end; int last_buf; scalar_t__ file_pos; scalar_t__ file_last; int last_shadow; int sync; struct TYPE_26__* shadow; void* tag; scalar_t__ last_in_chain; int /*<<< orphan*/  in_file; } ;
typedef  TYPE_7__ ngx_buf_t ;
struct TYPE_21__ {int /*<<< orphan*/  log; } ;
struct TYPE_20__ {int /*<<< orphan*/  writer; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_ERROR ; 
 void* NGX_HTTP_FASTCGI_STDIN ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_EVENT ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_HTTP ; 
 TYPE_6__* ngx_alloc_chain_link (int /*<<< orphan*/ ) ; 
 scalar_t__ ngx_buf_special (TYPE_7__*) ; 
 TYPE_6__* ngx_chain_get_free_buf (int /*<<< orphan*/ ,TYPE_6__**) ; 
 int /*<<< orphan*/  ngx_chain_update_chains (int /*<<< orphan*/ ,TYPE_6__**,int /*<<< orphan*/ *,TYPE_6__**,void*) ; 
 int /*<<< orphan*/  ngx_chain_writer (int /*<<< orphan*/ *,TYPE_6__*) ; 
 int /*<<< orphan*/  ngx_http_fastcgi_module ; 
 TYPE_5__* ngx_http_get_module_ctx (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_log_debug0 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ngx_log_debug7 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,void**,void**,int,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  ngx_memcpy (TYPE_7__*,TYPE_7__*,int) ; 
 int /*<<< orphan*/  ngx_memzero (void**,size_t) ; 
 void* ngx_palloc (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static ngx_int_t
ngx_http_fastcgi_body_output_filter(void *data, ngx_chain_t *in)
{
    ngx_http_request_t  *r = data;

    off_t                       file_pos;
    u_char                     *pos, *start;
    size_t                      len, padding;
    ngx_buf_t                  *b;
    ngx_int_t                   rc;
    ngx_uint_t                  next, last;
    ngx_chain_t                *cl, *tl, *out, **ll;
    ngx_http_fastcgi_ctx_t     *f;
    ngx_http_fastcgi_header_t  *h;

    ngx_log_debug0(NGX_LOG_DEBUG_HTTP, r->connection->log, 0,
                   "fastcgi output filter");

    f = ngx_http_get_module_ctx(r, ngx_http_fastcgi_module);

    if (in == NULL) {
        out = in;
        goto out;
    }

    out = NULL;
    ll = &out;

    if (!f->header_sent) {
        /* first buffer contains headers, pass it unmodified */

        ngx_log_debug0(NGX_LOG_DEBUG_HTTP, r->connection->log, 0,
                       "fastcgi output header");

        f->header_sent = 1;

        tl = ngx_alloc_chain_link(r->pool);
        if (tl == NULL) {
            return NGX_ERROR;
        }

        tl->buf = in->buf;
        *ll = tl;
        ll = &tl->next;

        in = in->next;

        if (in == NULL) {
            tl->next = NULL;
            goto out;
        }
    }

    cl = ngx_chain_get_free_buf(r->pool, &f->free);
    if (cl == NULL) {
        return NGX_ERROR;
    }

    b = cl->buf;

    b->tag = (ngx_buf_tag_t) &ngx_http_fastcgi_body_output_filter;
    b->temporary = 1;

    if (b->start == NULL) {
        /* reserve space for maximum possible padding, 7 bytes */

        b->start = ngx_palloc(r->pool,
                              sizeof(ngx_http_fastcgi_header_t) + 7);
        if (b->start == NULL) {
            return NGX_ERROR;
        }

        b->pos = b->start;
        b->last = b->start;

        b->end = b->start + sizeof(ngx_http_fastcgi_header_t) + 7;
    }

    *ll = cl;

    last = 0;
    padding = 0;

#if (NGX_SUPPRESS_WARN)
    file_pos = 0;
    pos = NULL;
#endif

    while (in) {

        ngx_log_debug7(NGX_LOG_DEBUG_EVENT, r->connection->log, 0,
                       "fastcgi output in  l:%d f:%d %p, pos %p, size: %z "
                       "file: %O, size: %O",
                       in->buf->last_buf,
                       in->buf->in_file,
                       in->buf->start, in->buf->pos,
                       in->buf->last - in->buf->pos,
                       in->buf->file_pos,
                       in->buf->file_last - in->buf->file_pos);

        if (in->buf->last_buf) {
            last = 1;
        }

        if (ngx_buf_special(in->buf)) {
            in = in->next;
            continue;
        }

        if (in->buf->in_file) {
            file_pos = in->buf->file_pos;

        } else {
            pos = in->buf->pos;
        }

        next = 0;

        do {
            tl = ngx_chain_get_free_buf(r->pool, &f->free);
            if (tl == NULL) {
                return NGX_ERROR;
            }

            b = tl->buf;
            start = b->start;

            ngx_memcpy(b, in->buf, sizeof(ngx_buf_t));

            /*
             * restore b->start to preserve memory allocated in the buffer,
             * to reuse it later for headers and padding
             */

            b->start = start;

            if (in->buf->in_file) {
                b->file_pos = file_pos;
                file_pos += 32 * 1024;

                if (file_pos >= in->buf->file_last) {
                    file_pos = in->buf->file_last;
                    next = 1;
                }

                b->file_last = file_pos;
                len = (ngx_uint_t) (file_pos - b->file_pos);

            } else {
                b->pos = pos;
                pos += 32 * 1024;

                if (pos >= in->buf->last) {
                    pos = in->buf->last;
                    next = 1;
                }

                b->last = pos;
                len = (ngx_uint_t) (pos - b->pos);
            }

            b->tag = (ngx_buf_tag_t) &ngx_http_fastcgi_body_output_filter;
            b->shadow = in->buf;
            b->last_shadow = next;

            b->last_buf = 0;
            b->last_in_chain = 0;

            padding = 8 - len % 8;
            padding = (padding == 8) ? 0 : padding;

            h = (ngx_http_fastcgi_header_t *) cl->buf->last;
            cl->buf->last += sizeof(ngx_http_fastcgi_header_t);

            h->version = 1;
            h->type = NGX_HTTP_FASTCGI_STDIN;
            h->request_id_hi = 0;
            h->request_id_lo = 1;
            h->content_length_hi = (u_char) ((len >> 8) & 0xff);
            h->content_length_lo = (u_char) (len & 0xff);
            h->padding_length = (u_char) padding;
            h->reserved = 0;

            cl->next = tl;
            cl = tl;

            tl = ngx_chain_get_free_buf(r->pool, &f->free);
            if (tl == NULL) {
                return NGX_ERROR;
            }

            b = tl->buf;

            b->tag = (ngx_buf_tag_t) &ngx_http_fastcgi_body_output_filter;
            b->temporary = 1;

            if (b->start == NULL) {
                /* reserve space for maximum possible padding, 7 bytes */

                b->start = ngx_palloc(r->pool,
                                      sizeof(ngx_http_fastcgi_header_t) + 7);
                if (b->start == NULL) {
                    return NGX_ERROR;
                }

                b->pos = b->start;
                b->last = b->start;

                b->end = b->start + sizeof(ngx_http_fastcgi_header_t) + 7;
            }

            if (padding) {
                ngx_memzero(b->last, padding);
                b->last += padding;
            }

            cl->next = tl;
            cl = tl;

        } while (!next);

        in = in->next;
    }

    if (last) {
        h = (ngx_http_fastcgi_header_t *) cl->buf->last;
        cl->buf->last += sizeof(ngx_http_fastcgi_header_t);

        h->version = 1;
        h->type = NGX_HTTP_FASTCGI_STDIN;
        h->request_id_hi = 0;
        h->request_id_lo = 1;
        h->content_length_hi = 0;
        h->content_length_lo = 0;
        h->padding_length = 0;
        h->reserved = 0;

        cl->buf->last_buf = 1;

    } else if (padding == 0) {
        /* TODO: do not allocate buffers instead */
        cl->buf->temporary = 0;
        cl->buf->sync = 1;
    }

    cl->next = NULL;

out:

#if (NGX_DEBUG)

    for (cl = out; cl; cl = cl->next) {
        ngx_log_debug7(NGX_LOG_DEBUG_EVENT, r->connection->log, 0,
                       "fastcgi output out l:%d f:%d %p, pos %p, size: %z "
                       "file: %O, size: %O",
                       cl->buf->last_buf,
                       cl->buf->in_file,
                       cl->buf->start, cl->buf->pos,
                       cl->buf->last - cl->buf->pos,
                       cl->buf->file_pos,
                       cl->buf->file_last - cl->buf->file_pos);
    }

#endif

    rc = ngx_chain_writer(&r->upstream->writer, out);

    ngx_chain_update_chains(r->pool, &f->free, &f->busy, &out,
                         (ngx_buf_tag_t) &ngx_http_fastcgi_body_output_filter);

    for (cl = f->free; cl; cl = cl->next) {

        /* mark original buffers as sent */

        if (cl->buf->shadow) {
            if (cl->buf->last_shadow) {
                b = cl->buf->shadow;
                b->pos = b->last;
            }

            cl->buf->shadow = NULL;
        }
    }

    return rc;
}
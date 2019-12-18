#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  int u_char ;
typedef  size_t ngx_uint_t ;
struct TYPE_17__ {int /*<<< orphan*/  log; } ;
typedef  TYPE_1__ ngx_pool_t ;
struct TYPE_18__ {size_t saved_len; int* saved; scalar_t__ table; } ;
typedef  TYPE_2__ ngx_http_charset_ctx_t ;
struct TYPE_19__ {TYPE_4__* buf; struct TYPE_19__* next; } ;
typedef  TYPE_3__ ngx_chain_t ;
struct TYPE_20__ {int* pos; int* last; int sync; int* end; struct TYPE_20__* shadow; int /*<<< orphan*/  flush; int /*<<< orphan*/  last_in_chain; int /*<<< orphan*/  last_buf; scalar_t__ temporary; int /*<<< orphan*/  mmap; int /*<<< orphan*/  memory; } ;
typedef  TYPE_4__ ngx_buf_t ;

/* Variables and functions */
 size_t NGX_HTML_ENTITY_LEN ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_HTTP ; 
 size_t NGX_UTF_LEN ; 
 TYPE_3__* ngx_alloc_chain_link (TYPE_1__*) ; 
 TYPE_3__* ngx_http_charset_get_buf (TYPE_1__*,TYPE_2__*) ; 
 TYPE_3__* ngx_http_charset_get_buffer (TYPE_1__*,TYPE_2__*,size_t) ; 
 int /*<<< orphan*/  ngx_log_debug0 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ngx_log_debug1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,size_t) ; 
 int /*<<< orphan*/  ngx_memcpy (int*,int*,size_t) ; 
 int* ngx_sprintf (int*,char*,int) ; 
 int ngx_utf8_decode (int**,size_t) ; 

__attribute__((used)) static ngx_chain_t *
ngx_http_charset_recode_from_utf8(ngx_pool_t *pool, ngx_buf_t *buf,
    ngx_http_charset_ctx_t *ctx)
{
    size_t        len, size;
    u_char        c, *p, *src, *dst, *saved, **table;
    uint32_t      n;
    ngx_buf_t    *b;
    ngx_uint_t    i;
    ngx_chain_t  *out, *cl, **ll;

    src = buf->pos;

    if (ctx->saved_len == 0) {

        for ( /* void */ ; src < buf->last; src++) {

            if (*src < 0x80) {
                continue;
            }

            len = src - buf->pos;

            if (len > 512) {
                out = ngx_http_charset_get_buf(pool, ctx);
                if (out == NULL) {
                    return NULL;
                }

                b = out->buf;

                b->temporary = buf->temporary;
                b->memory = buf->memory;
                b->mmap = buf->mmap;
                b->flush = buf->flush;

                b->pos = buf->pos;
                b->last = src;

                out->buf = b;
                out->next = NULL;

                size = buf->last - src;

                saved = src;
                n = ngx_utf8_decode(&saved, size);

                if (n == 0xfffffffe) {
                    /* incomplete UTF-8 symbol */

                    ngx_memcpy(ctx->saved, src, size);
                    ctx->saved_len = size;

                    b->shadow = buf;

                    return out;
                }

            } else {
                out = NULL;
                size = len + buf->last - src;
                src = buf->pos;
            }

            if (size < NGX_HTML_ENTITY_LEN) {
                size += NGX_HTML_ENTITY_LEN;
            }

            cl = ngx_http_charset_get_buffer(pool, ctx, size);
            if (cl == NULL) {
                return NULL;
            }

            if (out) {
                out->next = cl;

            } else {
                out = cl;
            }

            b = cl->buf;
            dst = b->pos;

            goto recode;
        }

        out = ngx_alloc_chain_link(pool);
        if (out == NULL) {
            return NULL;
        }

        out->buf = buf;
        out->next = NULL;

        return out;
    }

    /* process incomplete UTF sequence from previous buffer */

    ngx_log_debug1(NGX_LOG_DEBUG_HTTP, pool->log, 0,
                   "http charset utf saved: %z", ctx->saved_len);

    p = src;

    for (i = ctx->saved_len; i < NGX_UTF_LEN; i++) {
        ctx->saved[i] = *p++;

        if (p == buf->last) {
            break;
        }
    }

    saved = ctx->saved;
    n = ngx_utf8_decode(&saved, i);

    c = '\0';

    if (n < 0x10000) {
        table = (u_char **) ctx->table;
        p = table[n >> 8];

        if (p) {
            c = p[n & 0xff];
        }

    } else if (n == 0xfffffffe) {

        /* incomplete UTF-8 symbol */

        if (i < NGX_UTF_LEN) {
            out = ngx_http_charset_get_buf(pool, ctx);
            if (out == NULL) {
                return NULL;
            }

            b = out->buf;

            b->pos = buf->pos;
            b->last = buf->last;
            b->sync = 1;
            b->shadow = buf;

            ngx_memcpy(&ctx->saved[ctx->saved_len], src, i);
            ctx->saved_len += i;

            return out;
        }
    }

    size = buf->last - buf->pos;

    if (size < NGX_HTML_ENTITY_LEN) {
        size += NGX_HTML_ENTITY_LEN;
    }

    cl = ngx_http_charset_get_buffer(pool, ctx, size);
    if (cl == NULL) {
        return NULL;
    }

    out = cl;

    b = cl->buf;
    dst = b->pos;

    if (c) {
        *dst++ = c;

    } else if (n == 0xfffffffe) {
        *dst++ = '?';

        ngx_log_debug0(NGX_LOG_DEBUG_HTTP, pool->log, 0,
                       "http charset invalid utf 0");

        saved = &ctx->saved[NGX_UTF_LEN];

    } else if (n > 0x10ffff) {
        *dst++ = '?';

        ngx_log_debug0(NGX_LOG_DEBUG_HTTP, pool->log, 0,
                       "http charset invalid utf 1");

    } else {
        dst = ngx_sprintf(dst, "&#%uD;", n);
    }

    src += (saved - ctx->saved) - ctx->saved_len;
    ctx->saved_len = 0;

recode:

    ll = &cl->next;

    table = (u_char **) ctx->table;

    while (src < buf->last) {

        if ((size_t) (b->end - dst) < NGX_HTML_ENTITY_LEN) {
            b->last = dst;

            size = buf->last - src + NGX_HTML_ENTITY_LEN;

            cl = ngx_http_charset_get_buffer(pool, ctx, size);
            if (cl == NULL) {
                return NULL;
            }

            *ll = cl;
            ll = &cl->next;

            b = cl->buf;
            dst = b->pos;
        }

        if (*src < 0x80) {
            *dst++ = *src++;
            continue;
        }

        len = buf->last - src;

        n = ngx_utf8_decode(&src, len);

        if (n < 0x10000) {

            p = table[n >> 8];

            if (p) {
                c = p[n & 0xff];

                if (c) {
                    *dst++ = c;
                    continue;
                }
            }

            dst = ngx_sprintf(dst, "&#%uD;", n);

            continue;
        }

        if (n == 0xfffffffe) {
            /* incomplete UTF-8 symbol */

            ngx_memcpy(ctx->saved, src, len);
            ctx->saved_len = len;

            if (b->pos == dst) {
                b->sync = 1;
                b->temporary = 0;
            }

            break;
        }

        if (n > 0x10ffff) {
            *dst++ = '?';

            ngx_log_debug0(NGX_LOG_DEBUG_HTTP, pool->log, 0,
                           "http charset invalid utf 2");

            continue;
        }

        /* n > 0xffff */

        dst = ngx_sprintf(dst, "&#%uD;", n);
    }

    b->last = dst;

    b->last_buf = buf->last_buf;
    b->last_in_chain = buf->last_in_chain;
    b->flush = buf->flush;

    b->shadow = buf;

    return out;
}
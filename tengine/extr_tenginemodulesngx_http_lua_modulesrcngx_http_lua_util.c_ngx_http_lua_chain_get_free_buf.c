#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
typedef  size_t off_t ;
typedef  int /*<<< orphan*/  ngx_pool_t ;
typedef  int /*<<< orphan*/  ngx_log_t ;
struct TYPE_12__ {struct TYPE_12__* next; TYPE_2__* buf; } ;
typedef  TYPE_1__ ngx_chain_t ;
typedef  int /*<<< orphan*/  ngx_buf_tag_t ;
struct TYPE_13__ {int temporary; int /*<<< orphan*/  tag; int /*<<< orphan*/ * start; int /*<<< orphan*/ * last; int /*<<< orphan*/ * pos; int /*<<< orphan*/ * end; } ;
typedef  TYPE_2__ ngx_buf_t ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_LOG_DEBUG_HTTP ; 
 int /*<<< orphan*/  dd (char*,int /*<<< orphan*/ *) ; 
 TYPE_1__* ngx_alloc_chain_link (int /*<<< orphan*/ *) ; 
 scalar_t__ ngx_buf_in_memory (TYPE_2__*) ; 
 TYPE_2__* ngx_calloc_buf (int /*<<< orphan*/ *) ; 
 TYPE_2__* ngx_create_temp_buf (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  ngx_http_lua_module ; 
 int /*<<< orphan*/  ngx_log_debug2 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,size_t,TYPE_1__*) ; 
 int /*<<< orphan*/  ngx_log_debug4 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,size_t,size_t,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_memzero (TYPE_2__*,int) ; 
 int /*<<< orphan*/ * ngx_palloc (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  ngx_pfree (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

ngx_chain_t *
ngx_http_lua_chain_get_free_buf(ngx_log_t *log, ngx_pool_t *p,
    ngx_chain_t **free, size_t len)
{
    ngx_buf_t    *b;
    ngx_chain_t  *cl;
    u_char       *start, *end;

    const ngx_buf_tag_t  tag = (ngx_buf_tag_t) &ngx_http_lua_module;

    if (*free) {
        cl = *free;
        *free = cl->next;
        cl->next = NULL;

        b = cl->buf;
        start = b->start;
        end = b->end;
        if (start && (size_t) (end - start) >= len) {
            ngx_log_debug4(NGX_LOG_DEBUG_HTTP, log, 0,
                           "lua reuse free buf memory %O >= %uz, cl:%p, p:%p",
                           (off_t) (end - start), len, cl, start);

            ngx_memzero(b, sizeof(ngx_buf_t));

            b->start = start;
            b->pos = start;
            b->last = start;
            b->end = end;
            b->tag = tag;

            if (len) {
                b->temporary = 1;
            }

            return cl;
        }

        ngx_log_debug4(NGX_LOG_DEBUG_HTTP, log, 0,
                       "lua reuse free buf chain, but reallocate memory "
                       "because %uz >= %O, cl:%p, p:%p", len,
                       (off_t) (b->end - b->start), cl, b->start);

        if (ngx_buf_in_memory(b) && b->start) {
            ngx_pfree(p, b->start);
        }

        ngx_memzero(b, sizeof(ngx_buf_t));

        if (len == 0) {
            return cl;
        }

        b->start = ngx_palloc(p, len);
        if (b->start == NULL) {
            return NULL;
        }

        b->end = b->start + len;

        dd("buf start: %p", cl->buf->start);

        b->pos = b->start;
        b->last = b->start;
        b->tag = tag;
        b->temporary = 1;

        return cl;
    }

    cl = ngx_alloc_chain_link(p);
    if (cl == NULL) {
        return NULL;
    }

    ngx_log_debug2(NGX_LOG_DEBUG_HTTP, log, 0,
                   "lua allocate new chainlink and new buf of size %uz, cl:%p",
                   len, cl);

    cl->buf = len ? ngx_create_temp_buf(p, len) : ngx_calloc_buf(p);
    if (cl->buf == NULL) {
        return NULL;
    }

    dd("buf start: %p", cl->buf->start);

    cl->buf->tag = tag;
    cl->next = NULL;

    return cl;
}
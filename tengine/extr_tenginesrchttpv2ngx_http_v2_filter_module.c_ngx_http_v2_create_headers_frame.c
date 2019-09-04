#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_8__ ;
typedef  struct TYPE_22__   TYPE_7__ ;
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
typedef  void* ngx_uint_t ;
struct TYPE_19__ {TYPE_3__* node; TYPE_1__* connection; } ;
typedef  TYPE_4__ ngx_http_v2_stream_t ;
struct TYPE_20__ {size_t length; int blocked; TYPE_7__* last; TYPE_7__* first; void* fin; TYPE_4__* stream; int /*<<< orphan*/  handler; } ;
typedef  TYPE_5__ ngx_http_v2_out_frame_t ;
struct TYPE_21__ {TYPE_2__* connection; int /*<<< orphan*/  pool; TYPE_4__* stream; } ;
typedef  TYPE_6__ ngx_http_request_t ;
struct TYPE_22__ {struct TYPE_22__* next; TYPE_8__* buf; } ;
typedef  TYPE_7__ ngx_chain_t ;
typedef  scalar_t__ ngx_buf_tag_t ;
struct TYPE_23__ {int temporary; void* last_buf; int /*<<< orphan*/ * last; int /*<<< orphan*/ * end; int /*<<< orphan*/ * pos; int /*<<< orphan*/ * start; scalar_t__ tag; } ;
typedef  TYPE_8__ ngx_buf_t ;
struct TYPE_18__ {int /*<<< orphan*/  id; } ;
struct TYPE_17__ {int /*<<< orphan*/  log; } ;
struct TYPE_16__ {size_t frame_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_HTTP_V2_CONTINUATION_FRAME ; 
 int /*<<< orphan*/  NGX_HTTP_V2_END_HEADERS_FLAG ; 
 int /*<<< orphan*/  NGX_HTTP_V2_END_STREAM_FLAG ; 
 scalar_t__ NGX_HTTP_V2_FRAME_HEADER_SIZE ; 
 int /*<<< orphan*/  NGX_HTTP_V2_HEADERS_FRAME ; 
 int /*<<< orphan*/  NGX_HTTP_V2_NO_FLAG ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_HTTP ; 
 TYPE_7__* ngx_alloc_chain_link (int /*<<< orphan*/ ) ; 
 TYPE_8__* ngx_calloc_buf (int /*<<< orphan*/ ) ; 
 TYPE_8__* ngx_create_temp_buf (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ngx_http_v2_headers_frame_handler ; 
 int /*<<< orphan*/  ngx_http_v2_module ; 
 int /*<<< orphan*/ * ngx_http_v2_write_len_and_type (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ngx_http_v2_write_sid (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_log_debug4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,TYPE_5__*,size_t,void*) ; 
 TYPE_5__* ngx_palloc (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static ngx_http_v2_out_frame_t *
ngx_http_v2_create_headers_frame(ngx_http_request_t *r, u_char *pos,
    u_char *end, ngx_uint_t fin)
{
    u_char                    type, flags;
    size_t                    rest, frame_size;
    ngx_buf_t                *b;
    ngx_chain_t              *cl, **ll;
    ngx_http_v2_stream_t     *stream;
    ngx_http_v2_out_frame_t  *frame;

    stream = r->stream;
    rest = end - pos;

    frame = ngx_palloc(r->pool, sizeof(ngx_http_v2_out_frame_t));
    if (frame == NULL) {
        return NULL;
    }

    frame->handler = ngx_http_v2_headers_frame_handler;
    frame->stream = stream;
    frame->length = rest;
    frame->blocked = 1;
    frame->fin = fin;

    ll = &frame->first;

    type = NGX_HTTP_V2_HEADERS_FRAME;
    flags = fin ? NGX_HTTP_V2_END_STREAM_FLAG : NGX_HTTP_V2_NO_FLAG;
    frame_size = stream->connection->frame_size;

    for ( ;; ) {
        if (rest <= frame_size) {
            frame_size = rest;
            flags |= NGX_HTTP_V2_END_HEADERS_FLAG;
        }

        b = ngx_create_temp_buf(r->pool, NGX_HTTP_V2_FRAME_HEADER_SIZE);
        if (b == NULL) {
            return NULL;
        }

        b->last = ngx_http_v2_write_len_and_type(b->last, frame_size, type);
        *b->last++ = flags;
        b->last = ngx_http_v2_write_sid(b->last, stream->node->id);

        b->tag = (ngx_buf_tag_t) &ngx_http_v2_module;

        cl = ngx_alloc_chain_link(r->pool);
        if (cl == NULL) {
            return NULL;
        }

        cl->buf = b;

        *ll = cl;
        ll = &cl->next;

        b = ngx_calloc_buf(r->pool);
        if (b == NULL) {
            return NULL;
        }

        b->pos = pos;

        pos += frame_size;

        b->last = pos;
        b->start = b->pos;
        b->end = b->last;
        b->temporary = 1;

        cl = ngx_alloc_chain_link(r->pool);
        if (cl == NULL) {
            return NULL;
        }

        cl->buf = b;

        *ll = cl;
        ll = &cl->next;

        rest -= frame_size;

        if (rest) {
            frame->length += NGX_HTTP_V2_FRAME_HEADER_SIZE;

            type = NGX_HTTP_V2_CONTINUATION_FRAME;
            flags = NGX_HTTP_V2_NO_FLAG;
            continue;
        }

        b->last_buf = fin;
        cl->next = NULL;
        frame->last = cl;

        ngx_log_debug4(NGX_LOG_DEBUG_HTTP, r->connection->log, 0,
                       "http2:%ui create HEADERS frame %p: len:%uz fin:%ui",
                       stream->node->id, frame, frame->length, fin);

        return frame;
    }
}
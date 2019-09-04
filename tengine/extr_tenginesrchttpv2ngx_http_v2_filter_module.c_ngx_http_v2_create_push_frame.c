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
typedef  scalar_t__ u_char ;
struct TYPE_18__ {TYPE_2__* node; TYPE_5__* connection; } ;
typedef  TYPE_3__ ngx_http_v2_stream_t ;
struct TYPE_19__ {size_t length; int blocked; TYPE_7__* last; TYPE_7__* first; scalar_t__ fin; TYPE_3__* stream; int /*<<< orphan*/  handler; } ;
typedef  TYPE_4__ ngx_http_v2_out_frame_t ;
struct TYPE_20__ {size_t frame_size; int last_push; } ;
typedef  TYPE_5__ ngx_http_v2_connection_t ;
struct TYPE_21__ {TYPE_1__* connection; int /*<<< orphan*/  pool; TYPE_3__* stream; } ;
typedef  TYPE_6__ ngx_http_request_t ;
struct TYPE_22__ {struct TYPE_22__* next; TYPE_8__* buf; } ;
typedef  TYPE_7__ ngx_chain_t ;
typedef  scalar_t__ ngx_buf_tag_t ;
struct TYPE_23__ {scalar_t__* last; scalar_t__* pos; scalar_t__* start; scalar_t__* end; int temporary; scalar_t__ tag; } ;
typedef  TYPE_8__ ngx_buf_t ;
struct TYPE_17__ {int id; } ;
struct TYPE_16__ {int /*<<< orphan*/  log; } ;

/* Variables and functions */
 scalar_t__ NGX_HTTP_V2_CONTINUATION_FRAME ; 
 scalar_t__ NGX_HTTP_V2_END_HEADERS_FLAG ; 
 scalar_t__ NGX_HTTP_V2_FRAME_HEADER_SIZE ; 
 scalar_t__ NGX_HTTP_V2_NO_FLAG ; 
 scalar_t__ NGX_HTTP_V2_PUSH_PROMISE_FRAME ; 
 int NGX_HTTP_V2_STREAM_ID_SIZE ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_HTTP ; 
 TYPE_7__* ngx_alloc_chain_link (int /*<<< orphan*/ ) ; 
 TYPE_8__* ngx_calloc_buf (int /*<<< orphan*/ ) ; 
 TYPE_8__* ngx_create_temp_buf (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ngx_http_v2_module ; 
 int /*<<< orphan*/  ngx_http_v2_push_frame_handler ; 
 scalar_t__* ngx_http_v2_write_len_and_type (scalar_t__*,size_t,scalar_t__) ; 
 void* ngx_http_v2_write_sid (scalar_t__*,int) ; 
 int /*<<< orphan*/  ngx_log_debug4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,TYPE_4__*,int,size_t) ; 
 TYPE_4__* ngx_palloc (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static ngx_http_v2_out_frame_t *
ngx_http_v2_create_push_frame(ngx_http_request_t *r, u_char *pos, u_char *end)
{
    u_char                     type, flags;
    size_t                     rest, frame_size, len;
    ngx_buf_t                 *b;
    ngx_chain_t               *cl, **ll;
    ngx_http_v2_stream_t      *stream;
    ngx_http_v2_out_frame_t   *frame;
    ngx_http_v2_connection_t  *h2c;

    stream = r->stream;
    h2c = stream->connection;
    rest = NGX_HTTP_V2_STREAM_ID_SIZE + (end - pos);

    frame = ngx_palloc(r->pool, sizeof(ngx_http_v2_out_frame_t));
    if (frame == NULL) {
        return NULL;
    }

    frame->handler = ngx_http_v2_push_frame_handler;
    frame->stream = stream;
    frame->length = rest;
    frame->blocked = 1;
    frame->fin = 0;

    ll = &frame->first;

    type = NGX_HTTP_V2_PUSH_PROMISE_FRAME;
    flags = NGX_HTTP_V2_NO_FLAG;
    frame_size = h2c->frame_size;

    for ( ;; ) {
        if (rest <= frame_size) {
            frame_size = rest;
            flags |= NGX_HTTP_V2_END_HEADERS_FLAG;
        }

        b = ngx_create_temp_buf(r->pool,
                                NGX_HTTP_V2_FRAME_HEADER_SIZE
                                + ((type == NGX_HTTP_V2_PUSH_PROMISE_FRAME)
                                   ? NGX_HTTP_V2_STREAM_ID_SIZE : 0));
        if (b == NULL) {
            return NULL;
        }

        b->last = ngx_http_v2_write_len_and_type(b->last, frame_size, type);
        *b->last++ = flags;
        b->last = ngx_http_v2_write_sid(b->last, stream->node->id);

        b->tag = (ngx_buf_tag_t) &ngx_http_v2_module;

        if (type == NGX_HTTP_V2_PUSH_PROMISE_FRAME) {
            h2c->last_push += 2;

            b->last = ngx_http_v2_write_sid(b->last, h2c->last_push);
            len = frame_size - NGX_HTTP_V2_STREAM_ID_SIZE;

        } else {
            len = frame_size;
        }

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

        pos += len;

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
            continue;
        }

        cl->next = NULL;
        frame->last = cl;

        ngx_log_debug4(NGX_LOG_DEBUG_HTTP, r->connection->log, 0,
                       "http2:%ui create PUSH_PROMISE frame %p: "
                       "sid:%ui len:%uz",
                       stream->node->id, frame, h2c->last_push,
                       frame->length);

        return frame;
    }
}
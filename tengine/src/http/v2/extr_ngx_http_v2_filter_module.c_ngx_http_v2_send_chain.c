#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_37__   TYPE_7__ ;
typedef  struct TYPE_36__   TYPE_6__ ;
typedef  struct TYPE_35__   TYPE_5__ ;
typedef  struct TYPE_34__   TYPE_4__ ;
typedef  struct TYPE_33__   TYPE_3__ ;
typedef  struct TYPE_32__   TYPE_2__ ;
typedef  struct TYPE_31__   TYPE_1__ ;
typedef  struct TYPE_30__   TYPE_18__ ;

/* Type definitions */
typedef  size_t off_t ;
struct TYPE_32__ {size_t send_window; scalar_t__ queued; TYPE_7__* free_bufs; TYPE_4__* connection; scalar_t__ out_closed; } ;
typedef  TYPE_2__ ngx_http_v2_stream_t ;
typedef  int /*<<< orphan*/  ngx_http_v2_out_frame_t ;
struct TYPE_33__ {size_t chunk_size; } ;
typedef  TYPE_3__ ngx_http_v2_loc_conf_t ;
struct TYPE_34__ {size_t send_window; size_t frame_size; } ;
typedef  TYPE_4__ ngx_http_v2_connection_t ;
struct TYPE_35__ {int /*<<< orphan*/  pool; TYPE_2__* stream; } ;
typedef  TYPE_5__ ngx_http_request_t ;
struct TYPE_36__ {TYPE_1__* write; int /*<<< orphan*/  buffered; int /*<<< orphan*/  log; TYPE_5__* data; } ;
typedef  TYPE_6__ ngx_connection_t ;
struct TYPE_37__ {TYPE_18__* buf; struct TYPE_37__* next; } ;
typedef  TYPE_7__ ngx_chain_t ;
typedef  scalar_t__ ngx_buf_tag_t ;
struct TYPE_31__ {int active; scalar_t__ ready; } ;
struct TYPE_30__ {scalar_t__ tag; size_t pos; size_t file_pos; scalar_t__ last_buf; scalar_t__ flush; struct TYPE_30__* shadow; } ;

/* Variables and functions */
 TYPE_7__* NGX_CHAIN_ERROR ; 
 scalar_t__ NGX_DECLINED ; 
 scalar_t__ NGX_ERROR ; 
 int /*<<< orphan*/  NGX_HTTP_V2_BUFFERED ; 
 int /*<<< orphan*/ * NGX_HTTP_V2_NO_TRAILERS ; 
 int /*<<< orphan*/  NGX_LOG_ERR ; 
 TYPE_7__* ngx_alloc_chain_link (int /*<<< orphan*/ ) ; 
 scalar_t__ ngx_buf_in_memory (TYPE_18__*) ; 
 size_t ngx_buf_size (TYPE_18__*) ; 
 int /*<<< orphan*/  ngx_free_chain (int /*<<< orphan*/ ,TYPE_7__*) ; 
 TYPE_3__* ngx_http_get_module_loc_conf (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ngx_http_v2_create_trailers_frame (TYPE_5__*) ; 
 int /*<<< orphan*/ * ngx_http_v2_filter_get_data_frame (TYPE_2__*,size_t,TYPE_7__*,TYPE_7__*) ; 
 TYPE_7__* ngx_http_v2_filter_get_shadow (TYPE_2__*,TYPE_18__*,size_t,size_t) ; 
 scalar_t__ ngx_http_v2_filter_send (TYPE_6__*,TYPE_2__*) ; 
 scalar_t__ ngx_http_v2_flow_control (TYPE_4__*,TYPE_2__*) ; 
 int /*<<< orphan*/  ngx_http_v2_module ; 
 int /*<<< orphan*/  ngx_http_v2_queue_frame (TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static ngx_chain_t *
ngx_http_v2_send_chain(ngx_connection_t *fc, ngx_chain_t *in, off_t limit)
{
    off_t                      size, offset;
    size_t                     rest, frame_size;
    ngx_chain_t               *cl, *out, **ln;
    ngx_http_request_t        *r;
    ngx_http_v2_stream_t      *stream;
    ngx_http_v2_loc_conf_t    *h2lcf;
    ngx_http_v2_out_frame_t   *frame, *trailers;
    ngx_http_v2_connection_t  *h2c;

    r = fc->data;
    stream = r->stream;

#if (NGX_SUPPRESS_WARN)
    size = 0;
#endif

    while (in) {
        size = ngx_buf_size(in->buf);

        if (size || in->buf->last_buf) {
            break;
        }

        in = in->next;
    }

    if (in == NULL || stream->out_closed) {

        if (size) {
            ngx_log_error(NGX_LOG_ERR, fc->log, 0,
                          "output on closed stream");
            return NGX_CHAIN_ERROR;
        }

        if (stream->queued) {
            fc->write->active = 1;
            fc->write->ready = 0;

        } else {
            fc->buffered &= ~NGX_HTTP_V2_BUFFERED;
        }

        return NULL;
    }

    h2c = stream->connection;

    if (size && ngx_http_v2_flow_control(h2c, stream) == NGX_DECLINED) {
        fc->write->active = 1;
        fc->write->ready = 0;
        return in;
    }

    if (in->buf->tag == (ngx_buf_tag_t) &ngx_http_v2_filter_get_shadow) {
        cl = ngx_alloc_chain_link(r->pool);
        if (cl == NULL) {
            return NGX_CHAIN_ERROR;
        }

        cl->buf = in->buf;
        in->buf = cl->buf->shadow;

        offset = ngx_buf_in_memory(in->buf)
                 ? (cl->buf->pos - in->buf->pos)
                 : (cl->buf->file_pos - in->buf->file_pos);

        cl->next = stream->free_bufs;
        stream->free_bufs = cl;

    } else {
        offset = 0;
    }

    if (limit == 0 || limit > (off_t) h2c->send_window) {
        limit = h2c->send_window;
    }

    if (limit > stream->send_window) {
        limit = (stream->send_window > 0) ? stream->send_window : 0;
    }

    h2lcf = ngx_http_get_module_loc_conf(r, ngx_http_v2_module);

    frame_size = (h2lcf->chunk_size < h2c->frame_size)
                 ? h2lcf->chunk_size : h2c->frame_size;

    trailers = NGX_HTTP_V2_NO_TRAILERS;

#if (NGX_SUPPRESS_WARN)
    cl = NULL;
#endif

    for ( ;; ) {
        if ((off_t) frame_size > limit) {
            frame_size = (size_t) limit;
        }

        ln = &out;
        rest = frame_size;

        while ((off_t) rest >= size) {

            if (offset) {
                cl = ngx_http_v2_filter_get_shadow(stream, in->buf,
                                                   offset, size);
                if (cl == NULL) {
                    return NGX_CHAIN_ERROR;
                }

                offset = 0;

            } else {
                cl = ngx_alloc_chain_link(r->pool);
                if (cl == NULL) {
                    return NGX_CHAIN_ERROR;
                }

                cl->buf = in->buf;
            }

            *ln = cl;
            ln = &cl->next;

            rest -= (size_t) size;
            in = in->next;

            if (in == NULL) {
                frame_size -= rest;
                rest = 0;
                break;
            }

            size = ngx_buf_size(in->buf);
        }

        if (rest) {
            cl = ngx_http_v2_filter_get_shadow(stream, in->buf, offset, rest);
            if (cl == NULL) {
                return NGX_CHAIN_ERROR;
            }

            cl->buf->flush = 0;
            cl->buf->last_buf = 0;

            *ln = cl;

            offset += rest;
            size -= rest;
        }

        if (cl->buf->last_buf) {
            trailers = ngx_http_v2_create_trailers_frame(r);
            if (trailers == NULL) {
                return NGX_CHAIN_ERROR;
            }

            if (trailers != NGX_HTTP_V2_NO_TRAILERS) {
                cl->buf->last_buf = 0;
            }
        }

        if (frame_size || cl->buf->last_buf) {
            frame = ngx_http_v2_filter_get_data_frame(stream, frame_size,
                                                      out, cl);
            if (frame == NULL) {
                return NGX_CHAIN_ERROR;
            }

            ngx_http_v2_queue_frame(h2c, frame);

            h2c->send_window -= frame_size;

            stream->send_window -= frame_size;
            stream->queued++;
        }

        if (in == NULL) {

            if (trailers != NGX_HTTP_V2_NO_TRAILERS) {
                ngx_http_v2_queue_frame(h2c, trailers);
                stream->queued++;
            }

            break;
        }

        limit -= frame_size;

        if (limit == 0) {
            break;
        }
    }

    if (offset) {
        cl = ngx_http_v2_filter_get_shadow(stream, in->buf, offset, size);
        if (cl == NULL) {
            return NGX_CHAIN_ERROR;
        }

        in->buf = cl->buf;
        ngx_free_chain(r->pool, cl);
    }

    if (ngx_http_v2_filter_send(fc, stream) == NGX_ERROR) {
        return NGX_CHAIN_ERROR;
    }

    if (in && ngx_http_v2_flow_control(h2c, stream) == NGX_DECLINED) {
        fc->write->active = 1;
        fc->write->ready = 0;
    }

    return in;
}
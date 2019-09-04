#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_32__   TYPE_9__ ;
typedef  struct TYPE_31__   TYPE_8__ ;
typedef  struct TYPE_30__   TYPE_7__ ;
typedef  struct TYPE_29__   TYPE_6__ ;
typedef  struct TYPE_28__   TYPE_5__ ;
typedef  struct TYPE_27__   TYPE_4__ ;
typedef  struct TYPE_26__   TYPE_3__ ;
typedef  struct TYPE_25__   TYPE_2__ ;
typedef  struct TYPE_24__   TYPE_1__ ;
typedef  struct TYPE_23__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
typedef  size_t ngx_uint_t ;
struct TYPE_28__ {int len; int /*<<< orphan*/ * data; } ;
struct TYPE_27__ {TYPE_5__ value; } ;
typedef  TYPE_4__ ngx_table_elt_t ;
typedef  TYPE_5__ ngx_str_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_29__ {TYPE_1__* request; int /*<<< orphan*/  queued; TYPE_8__* connection; } ;
typedef  TYPE_6__ ngx_http_v2_stream_t ;
struct TYPE_30__ {int offset; int /*<<< orphan*/  name; int /*<<< orphan*/  index; } ;
typedef  TYPE_7__ ngx_http_v2_push_header_t ;
typedef  int /*<<< orphan*/  ngx_http_v2_out_frame_t ;
struct TYPE_31__ {scalar_t__ pushing; scalar_t__ concurrent_pushes; int last_push; scalar_t__ table_update; TYPE_2__* connection; } ;
typedef  TYPE_8__ ngx_http_v2_connection_t ;
struct TYPE_26__ {int /*<<< orphan*/ * host; } ;
struct TYPE_32__ {TYPE_3__ headers_in; TYPE_5__ schema; int /*<<< orphan*/  pool; TYPE_6__* stream; TYPE_10__* connection; } ;
typedef  TYPE_9__ ngx_http_request_t ;
struct TYPE_23__ {int /*<<< orphan*/  log; } ;
typedef  TYPE_10__ ngx_connection_t ;
struct TYPE_25__ {int /*<<< orphan*/  log; } ;
struct TYPE_24__ {int request_length; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_ABORT ; 
 int /*<<< orphan*/  NGX_DECLINED ; 
 int /*<<< orphan*/  NGX_ERROR ; 
 int NGX_HTTP_V2_INT_OCTETS ; 
 int NGX_HTTP_V2_MAX_FIELD ; 
 int /*<<< orphan*/  NGX_HTTP_V2_METHOD_GET_INDEX ; 
 int /*<<< orphan*/  NGX_HTTP_V2_PATH_INDEX ; 
 size_t NGX_HTTP_V2_PUSH_HEADERS ; 
 int /*<<< orphan*/  NGX_HTTP_V2_SCHEME_HTTPS_INDEX ; 
 int /*<<< orphan*/  NGX_HTTP_V2_SCHEME_HTTP_INDEX ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_HTTP ; 
 int /*<<< orphan*/  NGX_LOG_WARN ; 
 int /*<<< orphan*/  NGX_OK ; 
 int /*<<< orphan*/ * ngx_cpymem (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * ngx_http_v2_create_push_frame (TYPE_9__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 void* ngx_http_v2_inc_indexed (int /*<<< orphan*/ ) ; 
 void* ngx_http_v2_indexed (int /*<<< orphan*/ ) ; 
 TYPE_7__* ngx_http_v2_push_headers ; 
 TYPE_6__* ngx_http_v2_push_stream (TYPE_6__*,TYPE_5__*) ; 
 int /*<<< orphan*/  ngx_http_v2_queue_blocked_frame (TYPE_8__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ngx_http_v2_write_value (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_log_debug0 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ngx_log_debug1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,TYPE_5__*) ; 
 int /*<<< orphan*/  ngx_log_debug2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,TYPE_5__*) ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,TYPE_5__*) ; 
 size_t ngx_max (size_t,int) ; 
 int /*<<< orphan*/ * ngx_palloc (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  ngx_path_separator (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ngx_pnalloc (int /*<<< orphan*/ ,size_t) ; 
 scalar_t__ ngx_strncmp (int /*<<< orphan*/ *,char*,int) ; 

__attribute__((used)) static ngx_int_t
ngx_http_v2_push_resource(ngx_http_request_t *r, ngx_str_t *path,
    ngx_str_t *binary)
{
    u_char                      *start, *pos, *tmp;
    size_t                       len;
    ngx_str_t                   *value;
    ngx_uint_t                   i;
    ngx_table_elt_t            **h;
    ngx_connection_t            *fc;
    ngx_http_v2_stream_t        *stream;
    ngx_http_v2_out_frame_t     *frame;
    ngx_http_v2_connection_t    *h2c;
    ngx_http_v2_push_header_t   *ph;

    fc = r->connection;

    ngx_log_debug0(NGX_LOG_DEBUG_HTTP, fc->log, 0, "http2 push resource");

    stream = r->stream;
    h2c = stream->connection;

    if (!ngx_path_separator(path->data[0])) {
        ngx_log_error(NGX_LOG_WARN, fc->log, 0,
                      "non-absolute path \"%V\" not pushed", path);
        return NGX_DECLINED;
    }

    ngx_log_debug2(NGX_LOG_DEBUG_HTTP, h2c->connection->log, 0,
                   "http2 pushing:%ui limit:%ui",
                   h2c->pushing, h2c->concurrent_pushes);

    if (h2c->pushing >= h2c->concurrent_pushes) {
        return NGX_ABORT;
    }

    if (h2c->last_push == 0x7ffffffe) {
        return NGX_ABORT;
    }

    if (path->len > NGX_HTTP_V2_MAX_FIELD) {
        return NGX_DECLINED;
    }

    if (r->headers_in.host == NULL) {
        return NGX_ABORT;
    }

    ph = ngx_http_v2_push_headers;

    len = ngx_max(r->schema.len, path->len);

    if (binary[0].len) {
        tmp = ngx_palloc(r->pool, len);
        if (tmp == NULL) {
            return NGX_ERROR;
        }

    } else {
        for (i = 0; i < NGX_HTTP_V2_PUSH_HEADERS; i++) {
            h = (ngx_table_elt_t **) ((char *) &r->headers_in + ph[i].offset);

            if (*h) {
                len = ngx_max(len, (*h)->value.len);
            }
        }

        tmp = ngx_palloc(r->pool, len);
        if (tmp == NULL) {
            return NGX_ERROR;
        }

        for (i = 0; i < NGX_HTTP_V2_PUSH_HEADERS; i++) {
            h = (ngx_table_elt_t **) ((char *) &r->headers_in + ph[i].offset);

            if (*h == NULL) {
                continue;
            }

            value = &(*h)->value;

            len = 1 + NGX_HTTP_V2_INT_OCTETS + value->len;

            pos = ngx_pnalloc(r->pool, len);
            if (pos == NULL) {
                return NGX_ERROR;
            }

            binary[i].data = pos;

            *pos++ = ngx_http_v2_inc_indexed(ph[i].index);
            pos = ngx_http_v2_write_value(pos, value->data, value->len, tmp);

            binary[i].len = pos - binary[i].data;
        }
    }

    len = (h2c->table_update ? 1 : 0)
          + 1
          + 1 + NGX_HTTP_V2_INT_OCTETS + path->len
          + 1 + NGX_HTTP_V2_INT_OCTETS + r->schema.len;

    for (i = 0; i < NGX_HTTP_V2_PUSH_HEADERS; i++) {
        len += binary[i].len;
    }

    pos = ngx_pnalloc(r->pool, len);
    if (pos == NULL) {
        return NGX_ERROR;
    }

    start = pos;

    if (h2c->table_update) {
        ngx_log_debug0(NGX_LOG_DEBUG_HTTP, fc->log, 0,
                       "http2 table size update: 0");
        *pos++ = (1 << 5) | 0;
        h2c->table_update = 0;
    }

    ngx_log_debug0(NGX_LOG_DEBUG_HTTP, fc->log, 0,
                   "http2 push header: \":method: GET\"");

    *pos++ = ngx_http_v2_indexed(NGX_HTTP_V2_METHOD_GET_INDEX);

    ngx_log_debug1(NGX_LOG_DEBUG_HTTP, fc->log, 0,
                   "http2 push header: \":path: %V\"", path);

    *pos++ = ngx_http_v2_inc_indexed(NGX_HTTP_V2_PATH_INDEX);
    pos = ngx_http_v2_write_value(pos, path->data, path->len, tmp);

    ngx_log_debug1(NGX_LOG_DEBUG_HTTP, fc->log, 0,
                   "http2 push header: \":scheme: %V\"", &r->schema);

    if (r->schema.len == 5 && ngx_strncmp(r->schema.data, "https", 5) == 0) {
        *pos++ = ngx_http_v2_indexed(NGX_HTTP_V2_SCHEME_HTTPS_INDEX);

    } else if (r->schema.len == 4
               && ngx_strncmp(r->schema.data, "http", 4) == 0)
    {
        *pos++ = ngx_http_v2_indexed(NGX_HTTP_V2_SCHEME_HTTP_INDEX);

    } else {
        *pos++ = ngx_http_v2_inc_indexed(NGX_HTTP_V2_SCHEME_HTTP_INDEX);
        pos = ngx_http_v2_write_value(pos, r->schema.data, r->schema.len, tmp);
    }

    for (i = 0; i < NGX_HTTP_V2_PUSH_HEADERS; i++) {
        h = (ngx_table_elt_t **) ((char *) &r->headers_in + ph[i].offset);

        if (*h == NULL) {
            continue;
        }

        ngx_log_debug2(NGX_LOG_DEBUG_HTTP, fc->log, 0,
                       "http2 push header: \"%V: %V\"",
                       &ph[i].name, &(*h)->value);

        pos = ngx_cpymem(pos, binary[i].data, binary[i].len);
    }

    frame = ngx_http_v2_create_push_frame(r, start, pos);
    if (frame == NULL) {
        return NGX_ERROR;
    }

    ngx_http_v2_queue_blocked_frame(h2c, frame);

    stream->queued++;

    stream = ngx_http_v2_push_stream(stream, path);

    if (stream) {
        stream->request->request_length = pos - start;
        return NGX_OK;
    }

    return NGX_ERROR;
}
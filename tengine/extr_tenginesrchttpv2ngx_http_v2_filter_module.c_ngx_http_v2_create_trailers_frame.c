#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_8__ ;
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
typedef  size_t ngx_uint_t ;
struct TYPE_13__ {size_t len; int /*<<< orphan*/  data; } ;
struct TYPE_18__ {size_t len; int /*<<< orphan*/  data; } ;
struct TYPE_14__ {scalar_t__ hash; TYPE_3__ value; TYPE_8__ key; } ;
typedef  TYPE_4__ ngx_table_elt_t ;
struct TYPE_15__ {size_t nelts; TYPE_4__* elts; struct TYPE_15__* next; } ;
typedef  TYPE_5__ ngx_list_part_t ;
typedef  int /*<<< orphan*/  ngx_http_v2_out_frame_t ;
struct TYPE_11__ {TYPE_5__ part; } ;
struct TYPE_12__ {TYPE_1__ trailers; } ;
struct TYPE_16__ {TYPE_2__ headers_out; int /*<<< orphan*/  pool; TYPE_7__* connection; } ;
typedef  TYPE_6__ ngx_http_request_t ;
struct TYPE_17__ {int /*<<< orphan*/  log; } ;
typedef  TYPE_7__ ngx_connection_t ;

/* Variables and functions */
 scalar_t__ NGX_HTTP_V2_INT_OCTETS ; 
 size_t NGX_HTTP_V2_MAX_FIELD ; 
 int /*<<< orphan*/ * NGX_HTTP_V2_NO_TRAILERS ; 
 int /*<<< orphan*/  NGX_LOG_CRIT ; 
 int /*<<< orphan*/ * ngx_http_v2_create_headers_frame (TYPE_6__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * ngx_http_v2_write_name (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ngx_http_v2_write_value (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,TYPE_8__*,...) ; 
 int /*<<< orphan*/ * ngx_palloc (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/ * ngx_pnalloc (int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static ngx_http_v2_out_frame_t *
ngx_http_v2_create_trailers_frame(ngx_http_request_t *r)
{
    u_char            *pos, *start, *tmp;
    size_t             len, tmp_len;
    ngx_uint_t         i;
    ngx_list_part_t   *part;
    ngx_table_elt_t   *header;
    ngx_connection_t  *fc;

    fc = r->connection;
    len = 0;
    tmp_len = 0;

    part = &r->headers_out.trailers.part;
    header = part->elts;

    for (i = 0; /* void */; i++) {

        if (i >= part->nelts) {
            if (part->next == NULL) {
                break;
            }

            part = part->next;
            header = part->elts;
            i = 0;
        }

        if (header[i].hash == 0) {
            continue;
        }

        if (header[i].key.len > NGX_HTTP_V2_MAX_FIELD) {
            ngx_log_error(NGX_LOG_CRIT, fc->log, 0,
                          "too long response trailer name: \"%V\"",
                          &header[i].key);
            return NULL;
        }

        if (header[i].value.len > NGX_HTTP_V2_MAX_FIELD) {
            ngx_log_error(NGX_LOG_CRIT, fc->log, 0,
                          "too long response trailer value: \"%V: %V\"",
                          &header[i].key, &header[i].value);
            return NULL;
        }

        len += 1 + NGX_HTTP_V2_INT_OCTETS + header[i].key.len
                 + NGX_HTTP_V2_INT_OCTETS + header[i].value.len;

        if (header[i].key.len > tmp_len) {
            tmp_len = header[i].key.len;
        }

        if (header[i].value.len > tmp_len) {
            tmp_len = header[i].value.len;
        }
    }

    if (len == 0) {
        return NGX_HTTP_V2_NO_TRAILERS;
    }

    tmp = ngx_palloc(r->pool, tmp_len);
    pos = ngx_pnalloc(r->pool, len);

    if (pos == NULL || tmp == NULL) {
        return NULL;
    }

    start = pos;

    part = &r->headers_out.trailers.part;
    header = part->elts;

    for (i = 0; /* void */; i++) {

        if (i >= part->nelts) {
            if (part->next == NULL) {
                break;
            }

            part = part->next;
            header = part->elts;
            i = 0;
        }

        if (header[i].hash == 0) {
            continue;
        }

#if (NGX_DEBUG)
        if (fc->log->log_level & NGX_LOG_DEBUG_HTTP) {
            ngx_strlow(tmp, header[i].key.data, header[i].key.len);

            ngx_log_debug3(NGX_LOG_DEBUG_HTTP, fc->log, 0,
                           "http2 output trailer: \"%*s: %V\"",
                           header[i].key.len, tmp, &header[i].value);
        }
#endif

        *pos++ = 0;

        pos = ngx_http_v2_write_name(pos, header[i].key.data,
                                     header[i].key.len, tmp);

        pos = ngx_http_v2_write_value(pos, header[i].value.data,
                                      header[i].value.len, tmp);
    }

    return ngx_http_v2_create_headers_frame(r, start, pos, 1);
}
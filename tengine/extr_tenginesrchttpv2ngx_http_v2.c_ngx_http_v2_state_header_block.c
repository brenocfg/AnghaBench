#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  int u_char ;
typedef  int ngx_uint_t ;
typedef  scalar_t__ ngx_int_t ;
struct TYPE_17__ {int flags; scalar_t__ length; int index; int parse_name; int parse_value; } ;
struct TYPE_18__ {TYPE_2__ state; TYPE_1__* connection; } ;
typedef  TYPE_3__ ngx_http_v2_connection_t ;
struct TYPE_16__ {int /*<<< orphan*/  log; } ;

/* Variables and functions */
 scalar_t__ NGX_AGAIN ; 
 scalar_t__ NGX_DECLINED ; 
 int /*<<< orphan*/  NGX_HTTP_V2_COMP_ERROR ; 
 int NGX_HTTP_V2_END_HEADERS_FLAG ; 
 scalar_t__ NGX_HTTP_V2_INT_OCTETS ; 
 int /*<<< orphan*/  NGX_HTTP_V2_SIZE_ERROR ; 
 int /*<<< orphan*/  NGX_LOG_INFO ; 
 scalar_t__ NGX_OK ; 
 int* ngx_http_v2_connection_error (TYPE_3__*,int /*<<< orphan*/ ) ; 
 scalar_t__ ngx_http_v2_get_indexed_header (TYPE_3__*,scalar_t__,int) ; 
 int* ngx_http_v2_handle_continuation (TYPE_3__*,int*,int*,int* (*) (TYPE_3__*,int*,int*)) ; 
 scalar_t__ ngx_http_v2_parse_int (TYPE_3__*,int**,int*,int) ; 
 int ngx_http_v2_prefix (int) ; 
 int* ngx_http_v2_state_field_len (TYPE_3__*,int*,int*) ; 
 int* ngx_http_v2_state_header_complete (TYPE_3__*,int*,int*) ; 
 int* ngx_http_v2_state_headers_save (TYPE_3__*,int*,int*,int* (*) (TYPE_3__*,int*,int*)) ; 
 int* ngx_http_v2_state_process_header (TYPE_3__*,int*,int*) ; 
 scalar_t__ ngx_http_v2_table_size (TYPE_3__*,scalar_t__) ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static u_char *
ngx_http_v2_state_header_block(ngx_http_v2_connection_t *h2c, u_char *pos,
    u_char *end)
{
    u_char      ch;
    ngx_int_t   value;
    ngx_uint_t  indexed, size_update, prefix;

    if (end - pos < 1) {
        return ngx_http_v2_state_headers_save(h2c, pos, end,
                                              ngx_http_v2_state_header_block);
    }

    if (!(h2c->state.flags & NGX_HTTP_V2_END_HEADERS_FLAG)
        && h2c->state.length < NGX_HTTP_V2_INT_OCTETS)
    {
        return ngx_http_v2_handle_continuation(h2c, pos, end,
                                               ngx_http_v2_state_header_block);
    }

    size_update = 0;
    indexed = 0;

    ch = *pos;

    if (ch >= (1 << 7)) {
        /* indexed header field */
        indexed = 1;
        prefix = ngx_http_v2_prefix(7);

    } else if (ch >= (1 << 6)) {
        /* literal header field with incremental indexing */
        h2c->state.index = 1;
        prefix = ngx_http_v2_prefix(6);

    } else if (ch >= (1 << 5)) {
        /* dynamic table size update */
        size_update = 1;
        prefix = ngx_http_v2_prefix(5);

    } else if (ch >= (1 << 4)) {
        /* literal header field never indexed */
        prefix = ngx_http_v2_prefix(4);

    } else {
        /* literal header field without indexing */
        prefix = ngx_http_v2_prefix(4);
    }

    value = ngx_http_v2_parse_int(h2c, &pos, end, prefix);

    if (value < 0) {
        if (value == NGX_AGAIN) {
            return ngx_http_v2_state_headers_save(h2c, pos, end,
                                               ngx_http_v2_state_header_block);
        }

        if (value == NGX_DECLINED) {
            ngx_log_error(NGX_LOG_INFO, h2c->connection->log, 0,
                          "client sent header block with too long %s value",
                          size_update ? "size update" : "header index");

            return ngx_http_v2_connection_error(h2c, NGX_HTTP_V2_COMP_ERROR);
        }

        ngx_log_error(NGX_LOG_INFO, h2c->connection->log, 0,
                      "client sent header block with incorrect length");

        return ngx_http_v2_connection_error(h2c, NGX_HTTP_V2_SIZE_ERROR);
    }

    if (indexed) {
        if (ngx_http_v2_get_indexed_header(h2c, value, 0) != NGX_OK) {
            return ngx_http_v2_connection_error(h2c, NGX_HTTP_V2_COMP_ERROR);
        }

        return ngx_http_v2_state_process_header(h2c, pos, end);
    }

    if (size_update) {
        if (ngx_http_v2_table_size(h2c, value) != NGX_OK) {
            return ngx_http_v2_connection_error(h2c, NGX_HTTP_V2_COMP_ERROR);
        }

        return ngx_http_v2_state_header_complete(h2c, pos, end);
    }

    if (value == 0) {
        h2c->state.parse_name = 1;

    } else if (ngx_http_v2_get_indexed_header(h2c, value, 1) != NGX_OK) {
        return ngx_http_v2_connection_error(h2c, NGX_HTTP_V2_COMP_ERROR);
    }

    h2c->state.parse_value = 1;

    return ngx_http_v2_state_field_len(h2c, pos, end);
}
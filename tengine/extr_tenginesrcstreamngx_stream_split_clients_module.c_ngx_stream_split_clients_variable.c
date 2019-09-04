#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
typedef  size_t ngx_uint_t ;
typedef  int /*<<< orphan*/  ngx_stream_variable_value_t ;
struct TYPE_12__ {scalar_t__ percent; int /*<<< orphan*/  value; } ;
typedef  TYPE_3__ ngx_stream_split_clients_part_t ;
struct TYPE_10__ {size_t nelts; TYPE_3__* elts; } ;
struct TYPE_13__ {TYPE_1__ parts; int /*<<< orphan*/  value; } ;
typedef  TYPE_4__ ngx_stream_split_clients_ctx_t ;
struct TYPE_14__ {TYPE_2__* connection; } ;
typedef  TYPE_5__ ngx_stream_session_t ;
struct TYPE_15__ {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
typedef  TYPE_6__ ngx_str_t ;
typedef  scalar_t__ ngx_int_t ;
struct TYPE_11__ {int /*<<< orphan*/  log; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_LOG_DEBUG_STREAM ; 
 scalar_t__ NGX_OK ; 
 int /*<<< orphan*/  ngx_log_debug2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,scalar_t__,scalar_t__) ; 
 scalar_t__ ngx_murmur_hash2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ngx_stream_complex_value (TYPE_5__*,int /*<<< orphan*/ *,TYPE_6__*) ; 
 int /*<<< orphan*/  ngx_stream_variable_null_value ; 

__attribute__((used)) static ngx_int_t
ngx_stream_split_clients_variable(ngx_stream_session_t *s,
    ngx_stream_variable_value_t *v, uintptr_t data)
{
    ngx_stream_split_clients_ctx_t *ctx =
                                       (ngx_stream_split_clients_ctx_t *) data;

    uint32_t                          hash;
    ngx_str_t                         val;
    ngx_uint_t                        i;
    ngx_stream_split_clients_part_t  *part;

    *v = ngx_stream_variable_null_value;

    if (ngx_stream_complex_value(s, &ctx->value, &val) != NGX_OK) {
        return NGX_OK;
    }

    hash = ngx_murmur_hash2(val.data, val.len);

    part = ctx->parts.elts;

    for (i = 0; i < ctx->parts.nelts; i++) {

        ngx_log_debug2(NGX_LOG_DEBUG_STREAM, s->connection->log, 0,
                       "stream split: %uD %uD", hash, part[i].percent);

        if (hash < part[i].percent || part[i].percent == 0) {
            *v = part[i].value;
            return NGX_OK;
        }
    }

    return NGX_OK;
}
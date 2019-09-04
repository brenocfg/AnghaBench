#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {int len; char* data; } ;
typedef  TYPE_2__ ngx_str_t ;
typedef  scalar_t__ ngx_int_t ;
struct TYPE_17__ {int valid; char* data; int len; scalar_t__ not_found; scalar_t__ no_cacheable; } ;
typedef  TYPE_3__ ngx_http_variable_value_t ;
struct TYPE_18__ {TYPE_1__* connection; } ;
typedef  TYPE_4__ ngx_http_request_t ;
struct TYPE_19__ {TYPE_3__* default_value; int /*<<< orphan*/  map; scalar_t__ hostnames; int /*<<< orphan*/  value; } ;
typedef  TYPE_5__ ngx_http_map_ctx_t ;
typedef  int /*<<< orphan*/  ngx_http_complex_value_t ;
struct TYPE_15__ {int /*<<< orphan*/  log; } ;

/* Variables and functions */
 scalar_t__ NGX_ERROR ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_HTTP ; 
 scalar_t__ NGX_OK ; 
 scalar_t__ ngx_http_complex_value (TYPE_4__*,int /*<<< orphan*/ *,TYPE_2__*) ; 
 TYPE_3__* ngx_http_map_find (TYPE_4__*,int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  ngx_log_debug0 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ngx_log_debug2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,TYPE_2__*,TYPE_3__*) ; 

__attribute__((used)) static ngx_int_t
ngx_http_map_variable(ngx_http_request_t *r, ngx_http_variable_value_t *v,
    uintptr_t data)
{
    ngx_http_map_ctx_t  *map = (ngx_http_map_ctx_t *) data;

    ngx_str_t                   val, str;
    ngx_http_complex_value_t   *cv;
    ngx_http_variable_value_t  *value;

    ngx_log_debug0(NGX_LOG_DEBUG_HTTP, r->connection->log, 0,
                   "http map started");

    if (ngx_http_complex_value(r, &map->value, &val) != NGX_OK) {
        return NGX_ERROR;
    }

    if (map->hostnames && val.len > 0 && val.data[val.len - 1] == '.') {
        val.len--;
    }

    value = ngx_http_map_find(r, &map->map, &val);

    if (value == NULL) {
        value = map->default_value;
    }

    if (!value->valid) {
        cv = (ngx_http_complex_value_t *) value->data;

        if (ngx_http_complex_value(r, cv, &str) != NGX_OK) {
            return NGX_ERROR;
        }

        v->valid = 1;
        v->no_cacheable = 0;
        v->not_found = 0;
        v->len = str.len;
        v->data = str.data;

    } else {
        *v = *value;
    }

    ngx_log_debug2(NGX_LOG_DEBUG_HTTP, r->connection->log, 0,
                   "http map: \"%V\" \"%v\"", &val, v);

    return NGX_OK;
}
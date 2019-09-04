#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;
typedef  struct TYPE_11__   TYPE_10__ ;

/* Type definitions */
struct TYPE_14__ {scalar_t__ conf_prefix; } ;
typedef  TYPE_3__ ngx_stream_script_full_name_code_t ;
struct TYPE_16__ {scalar_t__ data; scalar_t__ len; } ;
struct TYPE_15__ {scalar_t__ ip; TYPE_2__* session; TYPE_5__ buf; scalar_t__ pos; } ;
typedef  TYPE_4__ ngx_stream_script_engine_t ;
typedef  TYPE_5__ ngx_str_t ;
struct TYPE_13__ {TYPE_1__* connection; } ;
struct TYPE_12__ {int /*<<< orphan*/  log; int /*<<< orphan*/  pool; } ;
struct TYPE_11__ {int /*<<< orphan*/  prefix; int /*<<< orphan*/  conf_prefix; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_LOG_DEBUG_STREAM ; 
 scalar_t__ NGX_OK ; 
 TYPE_10__* ngx_cycle ; 
 scalar_t__ ngx_get_full_name (int /*<<< orphan*/ ,TYPE_5__*,TYPE_5__*) ; 
 int /*<<< orphan*/  ngx_log_debug1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,TYPE_5__*) ; 
 scalar_t__ ngx_stream_script_exit ; 

__attribute__((used)) static void
ngx_stream_script_full_name_code(ngx_stream_script_engine_t *e)
{
    ngx_stream_script_full_name_code_t  *code;

    ngx_str_t  value, *prefix;

    code = (ngx_stream_script_full_name_code_t *) e->ip;

    value.data = e->buf.data;
    value.len = e->pos - e->buf.data;

    prefix = code->conf_prefix ? (ngx_str_t *) &ngx_cycle->conf_prefix:
                                 (ngx_str_t *) &ngx_cycle->prefix;

    if (ngx_get_full_name(e->session->connection->pool, prefix, &value)
        != NGX_OK)
    {
        e->ip = ngx_stream_script_exit;
        return;
    }

    e->buf = value;

    ngx_log_debug1(NGX_LOG_DEBUG_STREAM, e->session->connection->log, 0,
                   "stream script fullname: \"%V\"", &value);

    e->ip += sizeof(ngx_stream_script_full_name_code_t);
}
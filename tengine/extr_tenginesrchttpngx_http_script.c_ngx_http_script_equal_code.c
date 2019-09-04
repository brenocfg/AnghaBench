#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ len; int /*<<< orphan*/  data; } ;
typedef  TYPE_3__ ngx_http_variable_value_t ;
struct TYPE_11__ {int ip; TYPE_2__* request; TYPE_3__* sp; } ;
typedef  TYPE_4__ ngx_http_script_engine_t ;
struct TYPE_9__ {TYPE_1__* connection; } ;
struct TYPE_8__ {int /*<<< orphan*/  log; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_LOG_DEBUG_HTTP ; 
 TYPE_3__ ngx_http_variable_null_value ; 
 TYPE_3__ ngx_http_variable_true_value ; 
 int /*<<< orphan*/  ngx_log_debug0 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ ngx_strncmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

void
ngx_http_script_equal_code(ngx_http_script_engine_t *e)
{
    ngx_http_variable_value_t  *val, *res;

    ngx_log_debug0(NGX_LOG_DEBUG_HTTP, e->request->connection->log, 0,
                   "http script equal");

    e->sp--;
    val = e->sp;
    res = e->sp - 1;

    e->ip += sizeof(uintptr_t);

    if (val->len == res->len
        && ngx_strncmp(val->data, res->data, res->len) == 0)
    {
        *res = ngx_http_variable_true_value;
        return;
    }

    ngx_log_debug0(NGX_LOG_DEBUG_HTTP, e->request->connection->log, 0,
                   "http script equal: no");

    *res = ngx_http_variable_null_value;
}
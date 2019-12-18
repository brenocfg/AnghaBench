#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int valid; int /*<<< orphan*/  data; scalar_t__ not_found; scalar_t__ no_cacheable; int /*<<< orphan*/  len; } ;
typedef  TYPE_2__ ngx_stream_variable_value_t ;
struct TYPE_12__ {TYPE_1__* connection; } ;
typedef  TYPE_3__ ngx_stream_session_t ;
struct TYPE_14__ {int /*<<< orphan*/  data; int /*<<< orphan*/  len; } ;
struct TYPE_13__ {TYPE_5__ addr_text; } ;
typedef  TYPE_4__ ngx_stream_realip_ctx_t ;
typedef  TYPE_5__ ngx_str_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_10__ {TYPE_5__ addr_text; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_OK ; 
 TYPE_4__* ngx_stream_get_module_ctx (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_stream_realip_module ; 

__attribute__((used)) static ngx_int_t
ngx_stream_realip_remote_addr_variable(ngx_stream_session_t *s,
    ngx_stream_variable_value_t *v, uintptr_t data)
{
    ngx_str_t                *addr_text;
    ngx_stream_realip_ctx_t  *ctx;

    ctx = ngx_stream_get_module_ctx(s, ngx_stream_realip_module);

    addr_text = ctx ? &ctx->addr_text : &s->connection->addr_text;

    v->len = addr_text->len;
    v->valid = 1;
    v->no_cacheable = 0;
    v->not_found = 0;
    v->data = addr_text->data;

    return NGX_OK;
}
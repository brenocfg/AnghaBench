#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_7__ ;
typedef  struct TYPE_24__   TYPE_6__ ;
typedef  struct TYPE_23__   TYPE_5__ ;
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;
typedef  struct TYPE_18__   TYPE_17__ ;

/* Type definitions */
typedef  int uint64_t ;
typedef  int uint32_t ;
typedef  size_t ngx_uint_t ;
struct TYPE_20__ {uintptr_t data; int /*<<< orphan*/  get_handler; } ;
typedef  TYPE_2__ ngx_stream_variable_t ;
struct TYPE_21__ {int percent; } ;
typedef  TYPE_3__ ngx_stream_split_clients_part_t ;
struct TYPE_18__ {size_t nelts; TYPE_3__* elts; } ;
struct TYPE_22__ {TYPE_17__ parts; int /*<<< orphan*/  value; } ;
typedef  TYPE_4__ ngx_stream_split_clients_ctx_t ;
struct TYPE_23__ {int /*<<< orphan*/ * complex_value; TYPE_6__* value; TYPE_7__* cf; } ;
typedef  TYPE_5__ ngx_stream_compile_complex_value_t ;
struct TYPE_24__ {char* data; int /*<<< orphan*/  len; } ;
typedef  TYPE_6__ ngx_str_t ;
struct TYPE_25__ {void* handler_conf; int /*<<< orphan*/  handler; TYPE_4__* ctx; int /*<<< orphan*/  pool; TYPE_1__* args; } ;
typedef  TYPE_7__ ngx_conf_t ;
typedef  int /*<<< orphan*/  ngx_command_t ;
struct TYPE_19__ {TYPE_6__* elts; } ;

/* Variables and functions */
 char* NGX_CONF_ERROR ; 
 char* NGX_CONF_OK ; 
 int /*<<< orphan*/  NGX_LOG_EMERG ; 
 scalar_t__ NGX_OK ; 
 int /*<<< orphan*/  NGX_STREAM_VAR_CHANGEABLE ; 
 scalar_t__ ngx_array_init (TYPE_17__*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  ngx_conf_log_error (int /*<<< orphan*/ ,TYPE_7__*,int /*<<< orphan*/ ,char*,...) ; 
 char* ngx_conf_parse (TYPE_7__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_memzero (TYPE_5__*,int) ; 
 TYPE_4__* ngx_pcalloc (int /*<<< orphan*/ ,int) ; 
 TYPE_2__* ngx_stream_add_variable (TYPE_7__*,TYPE_6__*,int /*<<< orphan*/ ) ; 
 scalar_t__ ngx_stream_compile_complex_value (TYPE_5__*) ; 
 int /*<<< orphan*/  ngx_stream_split_clients ; 
 int /*<<< orphan*/  ngx_stream_split_clients_variable ; 

__attribute__((used)) static char *
ngx_conf_split_clients_block(ngx_conf_t *cf, ngx_command_t *cmd, void *conf)
{
    char                                *rv;
    uint32_t                             sum, last;
    ngx_str_t                           *value, name;
    ngx_uint_t                           i;
    ngx_conf_t                           save;
    ngx_stream_variable_t               *var;
    ngx_stream_split_clients_ctx_t      *ctx;
    ngx_stream_split_clients_part_t     *part;
    ngx_stream_compile_complex_value_t   ccv;

    ctx = ngx_pcalloc(cf->pool, sizeof(ngx_stream_split_clients_ctx_t));
    if (ctx == NULL) {
        return NGX_CONF_ERROR;
    }

    value = cf->args->elts;

    ngx_memzero(&ccv, sizeof(ngx_stream_compile_complex_value_t));

    ccv.cf = cf;
    ccv.value = &value[1];
    ccv.complex_value = &ctx->value;

    if (ngx_stream_compile_complex_value(&ccv) != NGX_OK) {
        return NGX_CONF_ERROR;
    }

    name = value[2];

    if (name.data[0] != '$') {
        ngx_conf_log_error(NGX_LOG_EMERG, cf, 0,
                           "invalid variable name \"%V\"", &name);
        return NGX_CONF_ERROR;
    }

    name.len--;
    name.data++;

    var = ngx_stream_add_variable(cf, &name, NGX_STREAM_VAR_CHANGEABLE);
    if (var == NULL) {
        return NGX_CONF_ERROR;
    }

    var->get_handler = ngx_stream_split_clients_variable;
    var->data = (uintptr_t) ctx;

    if (ngx_array_init(&ctx->parts, cf->pool, 2,
                       sizeof(ngx_stream_split_clients_part_t))
        != NGX_OK)
    {
        return NGX_CONF_ERROR;
    }

    save = *cf;
    cf->ctx = ctx;
    cf->handler = ngx_stream_split_clients;
    cf->handler_conf = conf;

    rv = ngx_conf_parse(cf, NULL);

    *cf = save;

    if (rv != NGX_CONF_OK) {
        return rv;
    }

    sum = 0;
    last = 0;
    part = ctx->parts.elts;

    for (i = 0; i < ctx->parts.nelts; i++) {
        sum = part[i].percent ? sum + part[i].percent : 10000;
        if (sum > 10000) {
            ngx_conf_log_error(NGX_LOG_EMERG, cf, 0,
                               "percent total is greater than 100%%");
            return NGX_CONF_ERROR;
        }

        if (part[i].percent) {
            last += part[i].percent * (uint64_t) 0xffffffff / 10000;
            part[i].percent = last;
        }
    }

    return rv;
}
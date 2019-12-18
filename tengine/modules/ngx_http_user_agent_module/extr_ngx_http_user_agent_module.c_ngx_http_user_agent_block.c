#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
typedef  TYPE_2__ ngx_str_t ;
struct TYPE_17__ {uintptr_t data; int /*<<< orphan*/  get_handler; } ;
typedef  TYPE_3__ ngx_http_variable_t ;
struct TYPE_18__ {int /*<<< orphan*/ * default_value; TYPE_6__* trie; int /*<<< orphan*/  pool; } ;
typedef  TYPE_4__ ngx_http_user_agent_ctx_t ;
struct TYPE_19__ {void* handler_conf; int /*<<< orphan*/  handler; TYPE_4__* ctx; int /*<<< orphan*/  pool; TYPE_1__* args; } ;
typedef  TYPE_5__ ngx_conf_t ;
typedef  int /*<<< orphan*/  ngx_command_t ;
struct TYPE_20__ {scalar_t__ (* build_clue ) (TYPE_6__*) ;} ;
struct TYPE_15__ {TYPE_2__* elts; } ;

/* Variables and functions */
 char* NGX_CONF_ERROR ; 
 int /*<<< orphan*/  NGX_HTTP_VAR_CHANGEABLE ; 
 int /*<<< orphan*/  NGX_LOG_EMERG ; 
 scalar_t__ NGX_OK ; 
 int /*<<< orphan*/  ngx_conf_log_error (int /*<<< orphan*/ ,TYPE_5__*,int /*<<< orphan*/ ,char*) ; 
 char* ngx_conf_parse (TYPE_5__*,int /*<<< orphan*/ *) ; 
 TYPE_3__* ngx_http_add_variable (TYPE_5__*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_user_agent ; 
 int /*<<< orphan*/  ngx_http_user_agent_variable ; 
 TYPE_4__* ngx_palloc (int /*<<< orphan*/ ,int) ; 
 TYPE_6__* ngx_trie_create (int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (TYPE_6__*) ; 

__attribute__((used)) static char *
ngx_http_user_agent_block(ngx_conf_t *cf, ngx_command_t *cmd, void *conf)
{
    char                      *rv;
    ngx_str_t                 *value, name;
    ngx_conf_t                 save;
    ngx_http_variable_t       *var;
    ngx_http_user_agent_ctx_t *ctx;

    value = cf->args->elts;

    name = value[1];
    name.data++;
    name.len--;

    var = ngx_http_add_variable(cf, &name, NGX_HTTP_VAR_CHANGEABLE);
    if (var == NULL) {
        return NGX_CONF_ERROR;
    }

    ctx = ngx_palloc(cf->pool, sizeof(ngx_http_user_agent_ctx_t));
    if (ctx == NULL) {
        return NGX_CONF_ERROR;
    }

    ctx->pool = cf->pool;
    ctx->trie = ngx_trie_create(ctx->pool);
    if (ctx->trie == NULL) {
        return NGX_CONF_ERROR;
    }

    ctx->default_value = NULL;

    var->get_handler = ngx_http_user_agent_variable;
    var->data = (uintptr_t) ctx;

    save = *cf;
    cf->ctx = ctx;
    cf->handler = ngx_http_user_agent;
    cf->handler_conf = conf;

    rv = ngx_conf_parse(cf, NULL);
    if (NGX_OK != ctx->trie->build_clue(ctx->trie)) {
        return NGX_CONF_ERROR;
    }

    *cf = save;
    if (ctx->default_value == NULL) {
        ngx_conf_log_error(NGX_LOG_EMERG, cf, 0, "no default value");
        rv = NGX_CONF_ERROR;
    }

    return rv;
}
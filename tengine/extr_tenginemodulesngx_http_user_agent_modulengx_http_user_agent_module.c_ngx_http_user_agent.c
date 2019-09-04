#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_36__   TYPE_9__ ;
typedef  struct TYPE_35__   TYPE_8__ ;
typedef  struct TYPE_34__   TYPE_7__ ;
typedef  struct TYPE_33__   TYPE_6__ ;
typedef  struct TYPE_32__   TYPE_5__ ;
typedef  struct TYPE_31__   TYPE_4__ ;
typedef  struct TYPE_30__   TYPE_3__ ;
typedef  struct TYPE_29__   TYPE_2__ ;
typedef  struct TYPE_28__   TYPE_1__ ;
typedef  struct TYPE_27__   TYPE_10__ ;

/* Type definitions */
typedef  int ngx_uint_t ;
struct TYPE_31__ {TYPE_5__* (* insert ) (TYPE_4__*,TYPE_6__*,int) ;} ;
typedef  TYPE_4__ ngx_trie_t ;
struct TYPE_32__ {void* value; } ;
typedef  TYPE_5__ ngx_trie_node_t ;
struct TYPE_33__ {int /*<<< orphan*/  data; int /*<<< orphan*/  len; } ;
typedef  TYPE_6__ ngx_str_t ;
typedef  int /*<<< orphan*/  ngx_http_variable_value_t ;
typedef  int /*<<< orphan*/  ngx_http_variable_t ;
struct TYPE_34__ {scalar_t__ left; scalar_t__ right; TYPE_3__* var; } ;
typedef  TYPE_7__ ngx_http_user_agent_interval_t ;
struct TYPE_35__ {int /*<<< orphan*/  pool; TYPE_2__* default_value; TYPE_4__* trie; } ;
typedef  TYPE_8__ ngx_http_user_agent_ctx_t ;
struct TYPE_36__ {int /*<<< orphan*/  log; int /*<<< orphan*/  cycle; TYPE_1__* args; TYPE_8__* ctx; } ;
typedef  TYPE_9__ ngx_conf_t ;
typedef  int /*<<< orphan*/  ngx_command_t ;
struct TYPE_27__ {int nelts; scalar_t__ elts; } ;
typedef  TYPE_10__ ngx_array_t ;
struct TYPE_30__ {int valid; scalar_t__ no_cacheable; scalar_t__ not_found; int /*<<< orphan*/  data; int /*<<< orphan*/  len; } ;
struct TYPE_29__ {int valid; scalar_t__ no_cacheable; scalar_t__ not_found; int /*<<< orphan*/  data; int /*<<< orphan*/  len; } ;
struct TYPE_28__ {int nelts; TYPE_6__* elts; } ;

/* Variables and functions */
 char* NGX_CONF_ERROR ; 
 char* NGX_CONF_OK ; 
 scalar_t__ NGX_HTTP_UA_MAX_VERSION_VALUE ; 
 scalar_t__ NGX_HTTP_UA_MIN_VERSION_VALUE ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_CORE ; 
 int /*<<< orphan*/  NGX_LOG_EMERG ; 
 scalar_t__ NGX_OK ; 
 int NGX_TRIE_CONTINUE ; 
 int NGX_TRIE_REVERSE ; 
 TYPE_10__* ngx_array_create (int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ ngx_array_push (TYPE_10__*) ; 
 scalar_t__ ngx_conf_full_name (int /*<<< orphan*/ ,TYPE_6__*,int) ; 
 int /*<<< orphan*/  ngx_conf_log_error (int /*<<< orphan*/ ,TYPE_9__*,int /*<<< orphan*/ ,char*) ; 
 char* ngx_conf_parse (TYPE_9__*,TYPE_6__*) ; 
 TYPE_7__* ngx_http_user_agent_get_version (TYPE_9__*,TYPE_6__*) ; 
 int /*<<< orphan*/  ngx_log_debug1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 void* ngx_pcalloc (int /*<<< orphan*/ ,int) ; 
 scalar_t__ ngx_strcmp (int /*<<< orphan*/ ,char*) ; 
 TYPE_5__* stub1 (TYPE_4__*,TYPE_6__*,int) ; 
 TYPE_5__* stub2 (TYPE_4__*,TYPE_6__*,int) ; 

__attribute__((used)) static char *
ngx_http_user_agent(ngx_conf_t *cf, ngx_command_t *cmd, void *conf)
{
    ngx_str_t                      *args, *name, file;
    ngx_uint_t                      i, nelts, mode;
    ngx_trie_t                     *trie;
    ngx_array_t                    *value;
    ngx_trie_node_t                *node;
    ngx_http_user_agent_ctx_t      *ctx;
    ngx_http_user_agent_interval_t *interval, *p;

    ctx = cf->ctx;
    trie = ctx->trie;

    args = cf->args->elts;
    nelts = cf->args->nelts;

    name = NULL;

    if (nelts <= 1) {
        ngx_conf_log_error(NGX_LOG_EMERG, cf, 0,
                                 "invalid first parameter");
        return NGX_CONF_ERROR;

    }

    if (nelts == 2) {
        if (ngx_strcmp(args[0].data, "include") == 0) {

            file = args[1];
            if (ngx_conf_full_name(cf->cycle, &file, 1) != NGX_OK) {
                return NGX_CONF_ERROR;
            }

            ngx_log_debug1(NGX_LOG_DEBUG_CORE, cf->log, 0, "include %s",
                           file.data);
            return ngx_conf_parse(cf, &file);
        }

        if (ngx_strcmp(args[0].data, "default") == 0) {

            if (ctx->default_value != NULL) {
                ngx_conf_log_error(NGX_LOG_EMERG, cf, 0, "is duplicate");
                return NGX_CONF_ERROR;
            }

            ctx->default_value = ngx_pcalloc(ctx->pool,
                                             sizeof(ngx_http_variable_t));
            if (ctx->default_value == NULL) {
                return NGX_CONF_ERROR;
            }

            ctx->default_value->len = args[1].len;
            ctx->default_value->data = args[1].data;

            ctx->default_value->not_found = 0;
            ctx->default_value->no_cacheable =0;
            ctx->default_value->valid =1;

            return NGX_CONF_OK;
        }

        if (ngx_strcmp(args[0].data, "greedy") == 0) {
            mode = NGX_TRIE_REVERSE | NGX_TRIE_CONTINUE;
            trie->insert(trie, args + 1, mode);

            return NGX_CONF_OK;
        }
    }

    if (nelts == 2) {

        name = args;

        interval = ngx_pcalloc(ctx->pool,
                               sizeof(ngx_http_user_agent_interval_t));
        if (interval == NULL) {
            return NGX_CONF_ERROR;
        }

        interval->var = ngx_pcalloc(ctx->pool,
                                    sizeof(ngx_http_variable_value_t));
        if (interval->var == NULL) {
            return NGX_CONF_ERROR;
        }

        interval->left = NGX_HTTP_UA_MIN_VERSION_VALUE;
        interval->right = NGX_HTTP_UA_MAX_VERSION_VALUE;

        interval->var->len = args[1].len;
        interval->var->data = args[1].data;

        interval->var->not_found = 0;
        interval->var->no_cacheable = 0;
        interval->var->valid = 1;

        goto insert;
    }

    if (nelts == 3) {

        name = args;
        interval = ngx_http_user_agent_get_version(cf, args + 1);
        if (interval == NULL) {
            return NGX_CONF_ERROR;
        }

        interval->var->len = args[2].len;
        interval->var->data = args[2].data;

        interval->var->not_found = 0;
        interval->var->no_cacheable =0;
        interval->var->valid = 1;

        goto insert;
    }

    ngx_conf_log_error(NGX_LOG_EMERG, cf, 0, "too many args");
    return NGX_CONF_ERROR;

insert:

    mode = NGX_TRIE_REVERSE;
    node = trie->insert(trie, name, mode);
    if (node == NULL) {
        return NGX_CONF_ERROR;
    }

    value = (ngx_array_t *) node->value;
    if (value == NULL) {
        value = ngx_array_create(ctx->pool, 2,
                                 sizeof(ngx_http_user_agent_interval_t));
        if (value == NULL) {
            return NGX_CONF_ERROR;
        }
    }

    p = (ngx_http_user_agent_interval_t *) value->elts;
    for (i = 0; i < value->nelts; i++) {
        if ((p[i].left >= interval->left && p[i].left <= interval->right)
            || (p[i].right >= interval->left && p[i].right <= interval->right)
            || (interval->left >= p[i].left && interval->left <= p[i].right)
            || (interval->right >= p[i].left && interval->right <= p[i].right))
        {
            ngx_conf_log_error(NGX_LOG_EMERG, cf, 0, "interval covered");
            return NGX_CONF_ERROR;
        }
    }

    p = (ngx_http_user_agent_interval_t *) ngx_array_push(value);
    if (p == NULL) {
        return NGX_CONF_ERROR;
    }

    *p = *interval;
    node->value = (void *) value;

    return NGX_CONF_OK;
}
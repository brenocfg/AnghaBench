#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_33__   TYPE_9__ ;
typedef  struct TYPE_32__   TYPE_8__ ;
typedef  struct TYPE_31__   TYPE_7__ ;
typedef  struct TYPE_30__   TYPE_6__ ;
typedef  struct TYPE_29__   TYPE_5__ ;
typedef  struct TYPE_28__   TYPE_4__ ;
typedef  struct TYPE_27__   TYPE_3__ ;
typedef  struct TYPE_26__   TYPE_2__ ;
typedef  struct TYPE_25__   TYPE_1__ ;
typedef  struct TYPE_24__   TYPE_19__ ;
typedef  struct TYPE_23__   TYPE_10__ ;

/* Type definitions */
struct in6_addr {int /*<<< orphan*/  s6_addr; } ;
typedef  int ngx_uint_t ;
typedef  int /*<<< orphan*/  ngx_stream_variable_value_t ;
struct TYPE_29__ {uintptr_t data; int /*<<< orphan*/  get_handler; } ;
typedef  TYPE_5__ ngx_stream_variable_t ;
typedef  int /*<<< orphan*/  ngx_stream_geo_range_t ;
typedef  int /*<<< orphan*/  ngx_stream_geo_header_t ;
struct TYPE_25__ {int /*<<< orphan*/ * tree6; int /*<<< orphan*/ * tree; } ;
struct TYPE_28__ {int /*<<< orphan*/ * default_value; TYPE_19__** low; } ;
struct TYPE_27__ {TYPE_1__ trees; TYPE_4__ high; } ;
struct TYPE_30__ {scalar_t__ index; TYPE_3__ u; } ;
typedef  TYPE_6__ ngx_stream_geo_ctx_t ;
struct TYPE_31__ {int data_size; int allow_binary_include; int entries; int includes; int /*<<< orphan*/ * temp_pool; int /*<<< orphan*/ * tree6; int /*<<< orphan*/ * tree; TYPE_4__ high; int /*<<< orphan*/  outside_entries; int /*<<< orphan*/  binary_include; scalar_t__ ranges; int /*<<< orphan*/ * pool; int /*<<< orphan*/  sentinel; int /*<<< orphan*/  rbtree; } ;
typedef  TYPE_7__ ngx_stream_geo_conf_ctx_t ;
struct TYPE_32__ {char* data; int /*<<< orphan*/  len; } ;
typedef  TYPE_8__ ngx_str_t ;
typedef  int /*<<< orphan*/  ngx_pool_t ;
struct TYPE_33__ {int /*<<< orphan*/ * pool; void* handler_conf; int /*<<< orphan*/  handler; TYPE_7__* ctx; int /*<<< orphan*/  log; TYPE_2__* args; } ;
typedef  TYPE_9__ ngx_conf_t ;
typedef  int /*<<< orphan*/  ngx_command_t ;
struct TYPE_23__ {int nelts; int /*<<< orphan*/  elts; } ;
typedef  TYPE_10__ ngx_array_t ;
struct TYPE_26__ {int nelts; TYPE_8__* elts; } ;
struct TYPE_24__ {int /*<<< orphan*/ * value; } ;

/* Variables and functions */
 char* NGX_CONF_ERROR ; 
 char* NGX_CONF_OK ; 
 int /*<<< orphan*/  NGX_DEFAULT_POOL_SIZE ; 
 scalar_t__ NGX_ERROR ; 
 int /*<<< orphan*/  NGX_LOG_EMERG ; 
 int /*<<< orphan*/  NGX_STREAM_VAR_CHANGEABLE ; 
 int /*<<< orphan*/  ngx_conf_log_error (int /*<<< orphan*/ ,TYPE_9__*,int /*<<< orphan*/ ,char*,TYPE_8__*) ; 
 char* ngx_conf_parse (TYPE_9__*,int /*<<< orphan*/ *) ; 
 void* ngx_create_pool (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_destroy_pool (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_memcpy (TYPE_19__*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  ngx_memzero (TYPE_7__*,int) ; 
 void* ngx_palloc (int /*<<< orphan*/ *,int) ; 
 scalar_t__ ngx_radix128tree_insert (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,uintptr_t) ; 
 scalar_t__ ngx_radix32tree_insert (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,uintptr_t) ; 
 void* ngx_radix_tree_create (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ngx_rbtree_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_str_rbtree_insert_value ; 
 TYPE_5__* ngx_stream_add_variable (TYPE_9__*,TYPE_8__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_stream_geo ; 
 int /*<<< orphan*/  ngx_stream_geo_cidr_variable ; 
 int /*<<< orphan*/  ngx_stream_geo_create_binary_base (TYPE_7__*) ; 
 int /*<<< orphan*/  ngx_stream_geo_range_variable ; 
 scalar_t__ ngx_stream_get_variable_index (TYPE_9__*,TYPE_8__*) ; 
 int /*<<< orphan*/  ngx_stream_variable_null_value ; 

__attribute__((used)) static char *
ngx_stream_geo_block(ngx_conf_t *cf, ngx_command_t *cmd, void *conf)
{
    char                       *rv;
    size_t                      len;
    ngx_str_t                  *value, name;
    ngx_uint_t                  i;
    ngx_conf_t                  save;
    ngx_pool_t                 *pool;
    ngx_array_t                *a;
    ngx_stream_variable_t      *var;
    ngx_stream_geo_ctx_t       *geo;
    ngx_stream_geo_conf_ctx_t   ctx;
#if (NGX_HAVE_INET6)
    static struct in6_addr      zero;
#endif

    value = cf->args->elts;

    geo = ngx_palloc(cf->pool, sizeof(ngx_stream_geo_ctx_t));
    if (geo == NULL) {
        return NGX_CONF_ERROR;
    }

    name = value[1];

    if (name.data[0] != '$') {
        ngx_conf_log_error(NGX_LOG_EMERG, cf, 0,
                           "invalid variable name \"%V\"", &name);
        return NGX_CONF_ERROR;
    }

    name.len--;
    name.data++;

    if (cf->args->nelts == 3) {

        geo->index = ngx_stream_get_variable_index(cf, &name);
        if (geo->index == NGX_ERROR) {
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

    } else {
        geo->index = -1;
    }

    var = ngx_stream_add_variable(cf, &name, NGX_STREAM_VAR_CHANGEABLE);
    if (var == NULL) {
        return NGX_CONF_ERROR;
    }

    pool = ngx_create_pool(NGX_DEFAULT_POOL_SIZE, cf->log);
    if (pool == NULL) {
        return NGX_CONF_ERROR;
    }

    ngx_memzero(&ctx, sizeof(ngx_stream_geo_conf_ctx_t));

    ctx.temp_pool = ngx_create_pool(NGX_DEFAULT_POOL_SIZE, cf->log);
    if (ctx.temp_pool == NULL) {
        ngx_destroy_pool(pool);
        return NGX_CONF_ERROR;
    }

    ngx_rbtree_init(&ctx.rbtree, &ctx.sentinel, ngx_str_rbtree_insert_value);

    ctx.pool = cf->pool;
    ctx.data_size = sizeof(ngx_stream_geo_header_t)
                  + sizeof(ngx_stream_variable_value_t)
                  + 0x10000 * sizeof(ngx_stream_geo_range_t *);
    ctx.allow_binary_include = 1;

    save = *cf;
    cf->pool = pool;
    cf->ctx = &ctx;
    cf->handler = ngx_stream_geo;
    cf->handler_conf = conf;

    rv = ngx_conf_parse(cf, NULL);

    *cf = save;

    if (rv != NGX_CONF_OK) {
        goto failed;
    }

    if (ctx.ranges) {

        if (ctx.high.low && !ctx.binary_include) {
            for (i = 0; i < 0x10000; i++) {
                a = (ngx_array_t *) ctx.high.low[i];

                if (a == NULL) {
                    continue;
                }

                if (a->nelts == 0) {
                    ctx.high.low[i] = NULL;
                    continue;
                }

                len = a->nelts * sizeof(ngx_stream_geo_range_t);

                ctx.high.low[i] = ngx_palloc(cf->pool, len + sizeof(void *));
                if (ctx.high.low[i] == NULL) {
                    goto failed;
                }

                ngx_memcpy(ctx.high.low[i], a->elts, len);
                ctx.high.low[i][a->nelts].value = NULL;
                ctx.data_size += len + sizeof(void *);
            }

            if (ctx.allow_binary_include
                && !ctx.outside_entries
                && ctx.entries > 100000
                && ctx.includes == 1)
            {
                ngx_stream_geo_create_binary_base(&ctx);
            }
        }

        if (ctx.high.default_value == NULL) {
            ctx.high.default_value = &ngx_stream_variable_null_value;
        }

        geo->u.high = ctx.high;

        var->get_handler = ngx_stream_geo_range_variable;
        var->data = (uintptr_t) geo;

    } else {
        if (ctx.tree == NULL) {
            ctx.tree = ngx_radix_tree_create(cf->pool, -1);
            if (ctx.tree == NULL) {
                goto failed;
            }
        }

        geo->u.trees.tree = ctx.tree;

#if (NGX_HAVE_INET6)
        if (ctx.tree6 == NULL) {
            ctx.tree6 = ngx_radix_tree_create(cf->pool, -1);
            if (ctx.tree6 == NULL) {
                goto failed;
            }
        }

        geo->u.trees.tree6 = ctx.tree6;
#endif

        var->get_handler = ngx_stream_geo_cidr_variable;
        var->data = (uintptr_t) geo;

        if (ngx_radix32tree_insert(ctx.tree, 0, 0,
                                   (uintptr_t) &ngx_stream_variable_null_value)
            == NGX_ERROR)
        {
            goto failed;
        }

        /* NGX_BUSY is okay (default was set explicitly) */

#if (NGX_HAVE_INET6)
        if (ngx_radix128tree_insert(ctx.tree6, zero.s6_addr, zero.s6_addr,
                                    (uintptr_t) &ngx_stream_variable_null_value)
            == NGX_ERROR)
        {
            goto failed;
        }
#endif
    }

    ngx_destroy_pool(ctx.temp_pool);
    ngx_destroy_pool(pool);

    return NGX_CONF_OK;

failed:

    ngx_destroy_pool(ctx.temp_pool);
    ngx_destroy_pool(pool);

    return NGX_CONF_ERROR;
}
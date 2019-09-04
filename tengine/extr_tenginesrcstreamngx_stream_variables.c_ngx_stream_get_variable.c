#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_30__   TYPE_8__ ;
typedef  struct TYPE_29__   TYPE_7__ ;
typedef  struct TYPE_28__   TYPE_6__ ;
typedef  struct TYPE_27__   TYPE_5__ ;
typedef  struct TYPE_26__   TYPE_4__ ;
typedef  struct TYPE_25__   TYPE_3__ ;
typedef  struct TYPE_24__   TYPE_2__ ;
typedef  struct TYPE_23__   TYPE_1__ ;

/* Type definitions */
typedef  size_t ngx_uint_t ;
struct TYPE_26__ {int not_found; } ;
typedef  TYPE_4__ ngx_stream_variable_value_t ;
struct TYPE_24__ {size_t len; int /*<<< orphan*/  data; } ;
struct TYPE_27__ {int flags; scalar_t__ (* get_handler ) (TYPE_6__*,TYPE_4__*,uintptr_t) ;uintptr_t data; TYPE_2__ name; int /*<<< orphan*/  index; } ;
typedef  TYPE_5__ ngx_stream_variable_t ;
struct TYPE_28__ {TYPE_1__* connection; } ;
typedef  TYPE_6__ ngx_stream_session_t ;
struct TYPE_25__ {size_t nelts; TYPE_5__* elts; } ;
struct TYPE_29__ {TYPE_3__ prefix_variables; int /*<<< orphan*/  variables_hash; } ;
typedef  TYPE_7__ ngx_stream_core_main_conf_t ;
struct TYPE_30__ {size_t len; int /*<<< orphan*/  data; } ;
typedef  TYPE_8__ ngx_str_t ;
struct TYPE_23__ {int /*<<< orphan*/  pool; int /*<<< orphan*/  log; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_LOG_ERR ; 
 scalar_t__ NGX_OK ; 
 int NGX_STREAM_VAR_INDEXED ; 
 TYPE_5__* ngx_hash_find (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,TYPE_8__*) ; 
 TYPE_4__* ngx_palloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ngx_stream_core_module ; 
 TYPE_4__* ngx_stream_get_flushed_variable (TYPE_6__*,int /*<<< orphan*/ ) ; 
 TYPE_7__* ngx_stream_get_module_main_conf (TYPE_6__*,int /*<<< orphan*/ ) ; 
 scalar_t__ ngx_stream_variable_depth ; 
 scalar_t__ ngx_strncmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 
 scalar_t__ stub1 (TYPE_6__*,TYPE_4__*,uintptr_t) ; 
 scalar_t__ stub2 (TYPE_6__*,TYPE_4__*,uintptr_t) ; 

ngx_stream_variable_value_t *
ngx_stream_get_variable(ngx_stream_session_t *s, ngx_str_t *name,
    ngx_uint_t key)
{
    size_t                        len;
    ngx_uint_t                    i, n;
    ngx_stream_variable_t        *v;
    ngx_stream_variable_value_t  *vv;
    ngx_stream_core_main_conf_t  *cmcf;

    cmcf = ngx_stream_get_module_main_conf(s, ngx_stream_core_module);

    v = ngx_hash_find(&cmcf->variables_hash, key, name->data, name->len);

    if (v) {
        if (v->flags & NGX_STREAM_VAR_INDEXED) {
            return ngx_stream_get_flushed_variable(s, v->index);
        }

        if (ngx_stream_variable_depth == 0) {
            ngx_log_error(NGX_LOG_ERR, s->connection->log, 0,
                          "cycle while evaluating variable \"%V\"", name);
            return NULL;
        }

        ngx_stream_variable_depth--;

        vv = ngx_palloc(s->connection->pool,
                        sizeof(ngx_stream_variable_value_t));

        if (vv && v->get_handler(s, vv, v->data) == NGX_OK) {
            ngx_stream_variable_depth++;
            return vv;
        }

        ngx_stream_variable_depth++;
        return NULL;
    }

    vv = ngx_palloc(s->connection->pool, sizeof(ngx_stream_variable_value_t));
    if (vv == NULL) {
        return NULL;
    }

    len = 0;

    v = cmcf->prefix_variables.elts;
    n = cmcf->prefix_variables.nelts;

    for (i = 0; i < cmcf->prefix_variables.nelts; i++) {
        if (name->len >= v[i].name.len && name->len > len
            && ngx_strncmp(name->data, v[i].name.data, v[i].name.len) == 0)
        {
            len = v[i].name.len;
            n = i;
        }
    }

    if (n != cmcf->prefix_variables.nelts) {
        if (v[n].get_handler(s, vv, (uintptr_t) name) == NGX_OK) {
            return vv;
        }

        return NULL;
    }

    vv->not_found = 1;

    return vv;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_8__ ;
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {int /*<<< orphan*/  line; int /*<<< orphan*/  file; int /*<<< orphan*/  name; } ;
typedef  TYPE_4__ ngx_thread_pool_t ;
struct TYPE_17__ {int /*<<< orphan*/  pools; } ;
typedef  TYPE_5__ ngx_thread_pool_conf_t ;
typedef  int /*<<< orphan*/  ngx_str_t ;
struct TYPE_18__ {TYPE_8__* cycle; TYPE_3__* conf_file; int /*<<< orphan*/  pool; } ;
typedef  TYPE_6__ ngx_conf_t ;
struct TYPE_19__ {int /*<<< orphan*/  conf_ctx; } ;
struct TYPE_13__ {int /*<<< orphan*/  data; } ;
struct TYPE_14__ {TYPE_1__ name; } ;
struct TYPE_15__ {int /*<<< orphan*/  line; TYPE_2__ file; } ;

/* Variables and functions */
 TYPE_4__** ngx_array_push (int /*<<< orphan*/ *) ; 
 scalar_t__ ngx_get_conf (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_4__* ngx_pcalloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ngx_thread_pool_default ; 
 TYPE_4__* ngx_thread_pool_get (TYPE_8__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_thread_pool_module ; 

ngx_thread_pool_t *
ngx_thread_pool_add(ngx_conf_t *cf, ngx_str_t *name)
{
    ngx_thread_pool_t       *tp, **tpp;
    ngx_thread_pool_conf_t  *tcf;

    if (name == NULL) {
        name = &ngx_thread_pool_default;
    }

    tp = ngx_thread_pool_get(cf->cycle, name);

    if (tp) {
        return tp;
    }

    tp = ngx_pcalloc(cf->pool, sizeof(ngx_thread_pool_t));
    if (tp == NULL) {
        return NULL;
    }

    tp->name = *name;
    tp->file = cf->conf_file->file.name.data;
    tp->line = cf->conf_file->line;

    tcf = (ngx_thread_pool_conf_t *) ngx_get_conf(cf->cycle->conf_ctx,
                                                  ngx_thread_pool_module);

    tpp = ngx_array_push(&tcf->pools);
    if (tpp == NULL) {
        return NULL;
    }

    *tpp = tp;

    return tp;
}
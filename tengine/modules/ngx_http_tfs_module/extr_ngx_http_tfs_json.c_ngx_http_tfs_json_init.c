#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/ * yajl_gen ;
typedef  int /*<<< orphan*/  ngx_pool_t ;
typedef  int /*<<< orphan*/  ngx_log_t ;
struct TYPE_4__ {int /*<<< orphan*/ * log; int /*<<< orphan*/ * pool; int /*<<< orphan*/ * gen; } ;
typedef  TYPE_1__ ngx_http_tfs_json_gen_t ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_LOG_ERR ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 TYPE_1__* ngx_pcalloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * yajl_gen_alloc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  yajl_gen_beautify ; 
 int /*<<< orphan*/  yajl_gen_config (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

ngx_http_tfs_json_gen_t *
ngx_http_tfs_json_init(ngx_log_t *log, ngx_pool_t *pool)
{
    yajl_gen                  g;
    ngx_http_tfs_json_gen_t  *tj_gen;

    g = yajl_gen_alloc(NULL);
    if (g == NULL) {
        ngx_log_error(NGX_LOG_ERR, log, errno, "alloc yajl_gen failed");
        return NULL;
    }

    tj_gen = ngx_pcalloc(pool, sizeof(ngx_http_tfs_json_gen_t));
    if (tj_gen == NULL) {
        return NULL;
    }

    yajl_gen_config(g, yajl_gen_beautify, 1);

    tj_gen->gen = g;
    tj_gen->pool = pool;
    tj_gen->log = log;

    return tj_gen;
}
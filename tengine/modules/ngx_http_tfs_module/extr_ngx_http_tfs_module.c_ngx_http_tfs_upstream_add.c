#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;
typedef  struct TYPE_17__   TYPE_15__ ;
typedef  struct TYPE_16__   TYPE_13__ ;

/* Type definitions */
struct TYPE_16__ {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
struct TYPE_18__ {TYPE_13__ host; TYPE_13__ url; scalar_t__ err; } ;
typedef  TYPE_1__ ngx_url_t ;
typedef  size_t ngx_uint_t ;
struct TYPE_19__ {TYPE_13__ host; } ;
typedef  TYPE_2__ ngx_http_tfs_upstream_t ;
struct TYPE_17__ {size_t nelts; TYPE_2__** elts; } ;
struct TYPE_20__ {TYPE_15__ upstreams; } ;
typedef  TYPE_3__ ngx_http_tfs_main_conf_t ;
struct TYPE_21__ {int /*<<< orphan*/  pool; } ;
typedef  TYPE_4__ ngx_conf_t ;

/* Variables and functions */
 size_t NGX_HTTP_TFS_UPSTREAM_CREATE ; 
 size_t NGX_HTTP_TFS_UPSTREAM_FIND ; 
 int /*<<< orphan*/  NGX_LOG_EMERG ; 
 scalar_t__ NGX_OK ; 
 TYPE_2__** ngx_array_push (TYPE_15__*) ; 
 int /*<<< orphan*/  ngx_conf_log_error (int /*<<< orphan*/ ,TYPE_4__*,int /*<<< orphan*/ ,char*,TYPE_13__*,...) ; 
 TYPE_3__* ngx_http_conf_get_module_main_conf (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_tfs_module ; 
 scalar_t__ ngx_parse_url (int /*<<< orphan*/ ,TYPE_1__*) ; 
 TYPE_2__* ngx_pcalloc (int /*<<< orphan*/ ,int) ; 
 scalar_t__ ngx_strncasecmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

ngx_http_tfs_upstream_t *
ngx_http_tfs_upstream_add(ngx_conf_t *cf, ngx_url_t *u, ngx_uint_t flags)
{
    ngx_uint_t                 i;
    ngx_http_tfs_upstream_t   *tu, **tup;
    ngx_http_tfs_main_conf_t  *tmcf;

    if (!(flags & NGX_HTTP_TFS_UPSTREAM_CREATE)) {

        if (ngx_parse_url(cf->pool, u) != NGX_OK) {
            if (u->err) {
                ngx_conf_log_error(NGX_LOG_EMERG, cf, 0,
                                   "%s in tfs upstream \"%V\"",
                                   u->err, &u->url);
            }

            return NULL;
        }
    }

    tmcf = ngx_http_conf_get_module_main_conf(cf, ngx_http_tfs_module);

    tup = tmcf->upstreams.elts;

    for (i = 0; i < tmcf->upstreams.nelts; i++)  {

        if (tup[i]->host.len != u->host.len
            || ngx_strncasecmp(tup[i]->host.data, u->host.data, u->host.len)
               != 0)
        {
            continue;
        }

        if (flags & NGX_HTTP_TFS_UPSTREAM_CREATE)
        {
            ngx_conf_log_error(NGX_LOG_EMERG, cf, 0,
                               "duplicate tfs upstream \"%V\"", &u->host);
            return NULL;
        }

        return tup[i];
    }

    if (flags & NGX_HTTP_TFS_UPSTREAM_FIND) {
        ngx_conf_log_error(NGX_LOG_EMERG, cf, 0,
                           " host not found in tfs upstream \"%V\"", &u->url);
        return NULL;
    }

    /* NGX_HTTP_TFS_UPSTREAM_CREATE */

    tu = ngx_pcalloc(cf->pool, sizeof(ngx_http_tfs_upstream_t));
    if (tu == NULL) {
        return NULL;
    }

    tu->host = u->host;

    tup = ngx_array_push(&tmcf->upstreams);
    if (tup == NULL) {
        return NULL;
    }

    *tup = tu;

    return tu;
}
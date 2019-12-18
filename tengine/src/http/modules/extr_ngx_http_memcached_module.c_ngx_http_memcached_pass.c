#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_7__ ;
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_18__ {int no_resolve; int /*<<< orphan*/  url; } ;
typedef  TYPE_4__ ngx_url_t ;
typedef  int /*<<< orphan*/  ngx_str_t ;
struct TYPE_16__ {int /*<<< orphan*/ * upstream; } ;
struct TYPE_19__ {scalar_t__ index; TYPE_2__ upstream; } ;
typedef  TYPE_5__ ngx_http_memcached_loc_conf_t ;
struct TYPE_17__ {int len; char* data; } ;
struct TYPE_20__ {int auto_redirect; TYPE_3__ name; int /*<<< orphan*/  handler; } ;
typedef  TYPE_6__ ngx_http_core_loc_conf_t ;
struct TYPE_21__ {TYPE_1__* args; } ;
typedef  TYPE_7__ ngx_conf_t ;
typedef  int /*<<< orphan*/  ngx_command_t ;
struct TYPE_15__ {int /*<<< orphan*/ * elts; } ;

/* Variables and functions */
 char* NGX_CONF_ERROR ; 
 char* NGX_CONF_OK ; 
 scalar_t__ NGX_ERROR ; 
 TYPE_6__* ngx_http_conf_get_module_loc_conf (TYPE_7__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_core_module ; 
 scalar_t__ ngx_http_get_variable_index (TYPE_7__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_http_memcached_handler ; 
 int /*<<< orphan*/  ngx_http_memcached_key ; 
 int /*<<< orphan*/ * ngx_http_upstream_add (TYPE_7__*,TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_memzero (TYPE_4__*,int) ; 

__attribute__((used)) static char *
ngx_http_memcached_pass(ngx_conf_t *cf, ngx_command_t *cmd, void *conf)
{
    ngx_http_memcached_loc_conf_t *mlcf = conf;

    ngx_str_t                 *value;
    ngx_url_t                  u;
    ngx_http_core_loc_conf_t  *clcf;

    if (mlcf->upstream.upstream) {
        return "is duplicate";
    }

    value = cf->args->elts;

    ngx_memzero(&u, sizeof(ngx_url_t));

    u.url = value[1];
    u.no_resolve = 1;

    mlcf->upstream.upstream = ngx_http_upstream_add(cf, &u, 0);
    if (mlcf->upstream.upstream == NULL) {
        return NGX_CONF_ERROR;
    }

    clcf = ngx_http_conf_get_module_loc_conf(cf, ngx_http_core_module);

    clcf->handler = ngx_http_memcached_handler;

    if (clcf->name.len && clcf->name.data[clcf->name.len - 1] == '/') {
        clcf->auto_redirect = 1;
    }

    mlcf->index = ngx_http_get_variable_index(cf, &ngx_http_memcached_key);

    if (mlcf->index == NGX_ERROR) {
        return NGX_CONF_ERROR;
    }

    return NGX_CONF_OK;
}
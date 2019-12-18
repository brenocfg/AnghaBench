#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ngx_str_t ;
struct TYPE_15__ {int /*<<< orphan*/  init_upstream; } ;
struct TYPE_16__ {int flags; TYPE_2__ peer; } ;
typedef  TYPE_3__ ngx_http_upstream_srv_conf_t ;
struct TYPE_17__ {int /*<<< orphan*/  values; int /*<<< orphan*/  lengths; } ;
typedef  TYPE_4__ ngx_http_upstream_chash_srv_conf_t ;
struct TYPE_18__ {int complete_lengths; int complete_values; int /*<<< orphan*/ * values; int /*<<< orphan*/ * lengths; int /*<<< orphan*/ * source; TYPE_6__* cf; } ;
typedef  TYPE_5__ ngx_http_script_compile_t ;
struct TYPE_19__ {TYPE_1__* args; } ;
typedef  TYPE_6__ ngx_conf_t ;
typedef  int /*<<< orphan*/  ngx_command_t ;
struct TYPE_14__ {int /*<<< orphan*/ * elts; } ;

/* Variables and functions */
 char* NGX_CONF_ERROR ; 
 char* NGX_CONF_OK ; 
 int NGX_HTTP_UPSTREAM_CREATE ; 
 int NGX_HTTP_UPSTREAM_DOWN ; 
 int NGX_HTTP_UPSTREAM_FAIL_TIMEOUT ; 
 int NGX_HTTP_UPSTREAM_ID ; 
 int NGX_HTTP_UPSTREAM_MAX_FAILS ; 
 int NGX_HTTP_UPSTREAM_WEIGHT ; 
 scalar_t__ NGX_OK ; 
 TYPE_3__* ngx_http_conf_get_module_srv_conf (TYPE_6__*,int /*<<< orphan*/ ) ; 
 TYPE_4__* ngx_http_conf_upstream_srv_conf (TYPE_3__*,int /*<<< orphan*/ ) ; 
 scalar_t__ ngx_http_script_compile (TYPE_5__*) ; 
 int /*<<< orphan*/  ngx_http_upstream_consistent_hash_module ; 
 int /*<<< orphan*/  ngx_http_upstream_init_chash ; 
 int /*<<< orphan*/  ngx_http_upstream_module ; 
 int /*<<< orphan*/  ngx_memzero (TYPE_5__*,int) ; 

__attribute__((used)) static char *
ngx_http_upstream_chash(ngx_conf_t *cf, ngx_command_t *cmd, void *conf)
{
    ngx_str_t                           *value;
    ngx_http_script_compile_t            sc;
    ngx_http_upstream_srv_conf_t        *uscf;
    ngx_http_upstream_chash_srv_conf_t  *ucscf;

    uscf = ngx_http_conf_get_module_srv_conf(cf, ngx_http_upstream_module);
    if (uscf == NULL) {
        return NGX_CONF_ERROR;
    }

    ucscf = ngx_http_conf_upstream_srv_conf(uscf,
                                     ngx_http_upstream_consistent_hash_module);
    if(ucscf == NULL) {
        return NGX_CONF_ERROR;
    }

    value = cf->args->elts;
    if (value == NULL) {
        return NGX_CONF_ERROR;
    }

    ngx_memzero(&sc, sizeof(ngx_http_script_compile_t));

    sc.cf = cf;
    sc.source = &value[1];
    sc.lengths = &ucscf->lengths;
    sc.values = &ucscf->values;
    sc.complete_lengths = 1;
    sc.complete_values = 1;

    if (ngx_http_script_compile(&sc) != NGX_OK) {
        return NGX_CONF_ERROR;
    }

    uscf->peer.init_upstream = ngx_http_upstream_init_chash;

    uscf->flags = NGX_HTTP_UPSTREAM_CREATE
#if (T_NGX_HTTP_UPSTREAM_ID) 
                  |NGX_HTTP_UPSTREAM_ID
#endif                  
                  |NGX_HTTP_UPSTREAM_WEIGHT
                  |NGX_HTTP_UPSTREAM_MAX_FAILS
                  |NGX_HTTP_UPSTREAM_FAIL_TIMEOUT
                  |NGX_HTTP_UPSTREAM_DOWN;

    return NGX_CONF_OK;
}
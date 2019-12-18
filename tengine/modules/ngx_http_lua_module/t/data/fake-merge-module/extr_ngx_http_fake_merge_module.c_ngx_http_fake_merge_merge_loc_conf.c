#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  a; } ;
typedef  TYPE_1__ ngx_http_fake_merge_main_conf_t ;
struct TYPE_5__ {int /*<<< orphan*/  a; } ;
typedef  TYPE_2__ ngx_http_fake_merge_loc_conf_t ;
typedef  int /*<<< orphan*/  ngx_conf_t ;

/* Variables and functions */
 char* NGX_CONF_ERROR ; 
 char* NGX_CONF_OK ; 
 int /*<<< orphan*/  NGX_LOG_ALERT ; 
 int /*<<< orphan*/  ngx_conf_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ngx_conf_merge_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* ngx_http_conf_get_module_main_conf (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_fake_merge_module ; 

__attribute__((used)) static char *
ngx_http_fake_merge_merge_loc_conf(ngx_conf_t *cf, void *parent, void *child)
{
    ngx_http_fake_merge_loc_conf_t    *conf = child;
    ngx_http_fake_merge_loc_conf_t    *prev = parent;
    ngx_http_fake_merge_main_conf_t   *fmcf;

    ngx_conf_merge_value(conf->a, prev->a, 0);

    fmcf = ngx_http_conf_get_module_main_conf(cf,
                                              ngx_http_fake_merge_module);
    if (fmcf == NULL) {
        ngx_conf_log_error(NGX_LOG_ALERT, cf, 0,
                           "get module main conf failed in merge loc conf");
        return NGX_CONF_ERROR;
    }
   

    fmcf->a = conf->a;

    return NGX_CONF_OK;
}
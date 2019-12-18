#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/ * variable; int /*<<< orphan*/  types; int /*<<< orphan*/  types_keys; } ;
typedef  TYPE_1__ ngx_http_footer_loc_conf_t ;
typedef  int /*<<< orphan*/  ngx_http_complex_value_t ;
typedef  int /*<<< orphan*/  ngx_conf_t ;

/* Variables and functions */
 char* NGX_CONF_ERROR ; 
 char* NGX_CONF_OK ; 
 scalar_t__ NGX_OK ; 
 int /*<<< orphan*/  ngx_http_html_default_types ; 
 scalar_t__ ngx_http_merge_types (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static char *
ngx_http_footer_merge_loc_conf(ngx_conf_t *cf, void *parent, void *child)
{
    ngx_http_footer_loc_conf_t  *prev = parent;
    ngx_http_footer_loc_conf_t  *conf = child;

    if (ngx_http_merge_types(cf, &conf->types_keys, &conf->types,
                             &prev->types_keys,&prev->types,
                             ngx_http_html_default_types)
        != NGX_OK)
    {
       return NGX_CONF_ERROR;
    }

    if (conf->variable == NULL) {
        conf->variable = prev->variable;
    }

    if (conf->variable == NULL) {
        conf->variable = (ngx_http_complex_value_t *) -1;
    }

    return NGX_CONF_OK;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_6__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  size_t ngx_uint_t ;
struct TYPE_7__ {scalar_t__ src; scalar_t__ dst; } ;
typedef  TYPE_1__ ngx_http_charset_recode_t ;
struct TYPE_10__ {size_t nelts; TYPE_1__* elts; } ;
struct TYPE_8__ {TYPE_6__ recodes; } ;
typedef  TYPE_2__ ngx_http_charset_main_conf_t ;
struct TYPE_9__ {scalar_t__ override_charset; scalar_t__ charset; scalar_t__ source_charset; int /*<<< orphan*/  types; int /*<<< orphan*/  types_keys; } ;
typedef  TYPE_3__ ngx_http_charset_loc_conf_t ;
typedef  int /*<<< orphan*/  ngx_conf_t ;

/* Variables and functions */
 char* NGX_CONF_ERROR ; 
 char* NGX_CONF_OK ; 
 scalar_t__ NGX_HTTP_CHARSET_OFF ; 
 scalar_t__ NGX_HTTP_CHARSET_VAR ; 
 scalar_t__ NGX_OK ; 
 TYPE_1__* ngx_array_push (TYPE_6__*) ; 
 int /*<<< orphan*/  ngx_conf_merge_value (scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  ngx_http_charset_default_types ; 
 int /*<<< orphan*/  ngx_http_charset_filter_module ; 
 TYPE_2__* ngx_http_conf_get_module_main_conf (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ ngx_http_merge_types (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static char *
ngx_http_charset_merge_loc_conf(ngx_conf_t *cf, void *parent, void *child)
{
    ngx_http_charset_loc_conf_t *prev = parent;
    ngx_http_charset_loc_conf_t *conf = child;

    ngx_uint_t                     i;
    ngx_http_charset_recode_t     *recode;
    ngx_http_charset_main_conf_t  *mcf;

    if (ngx_http_merge_types(cf, &conf->types_keys, &conf->types,
                             &prev->types_keys, &prev->types,
                             ngx_http_charset_default_types)
        != NGX_OK)
    {
        return NGX_CONF_ERROR;
    }

    ngx_conf_merge_value(conf->override_charset, prev->override_charset, 0);
    ngx_conf_merge_value(conf->charset, prev->charset, NGX_HTTP_CHARSET_OFF);
    ngx_conf_merge_value(conf->source_charset, prev->source_charset,
                         NGX_HTTP_CHARSET_OFF);

    if (conf->charset == NGX_HTTP_CHARSET_OFF
        || conf->source_charset == NGX_HTTP_CHARSET_OFF
        || conf->charset == conf->source_charset)
    {
        return NGX_CONF_OK;
    }

    if (conf->source_charset >= NGX_HTTP_CHARSET_VAR
        || conf->charset >= NGX_HTTP_CHARSET_VAR)
    {
        return NGX_CONF_OK;
    }

    mcf = ngx_http_conf_get_module_main_conf(cf,
                                             ngx_http_charset_filter_module);
    recode = mcf->recodes.elts;
    for (i = 0; i < mcf->recodes.nelts; i++) {
        if (conf->source_charset == recode[i].src
            && conf->charset == recode[i].dst)
        {
            return NGX_CONF_OK;
        }
    }

    recode = ngx_array_push(&mcf->recodes);
    if (recode == NULL) {
        return NGX_CONF_ERROR;
    }

    recode->src = conf->source_charset;
    recode->dst = conf->charset;

    return NGX_CONF_OK;
}
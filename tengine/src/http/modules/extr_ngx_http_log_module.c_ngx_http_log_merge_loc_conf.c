#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/ * format; int /*<<< orphan*/ * file; } ;
typedef  TYPE_2__ ngx_http_log_t ;
struct TYPE_11__ {int /*<<< orphan*/ * elts; } ;
struct TYPE_13__ {int combined_used; TYPE_1__ formats; } ;
typedef  TYPE_3__ ngx_http_log_main_conf_t ;
struct TYPE_14__ {int /*<<< orphan*/ * logs; scalar_t__ off; int /*<<< orphan*/ * open_file_cache; int /*<<< orphan*/  open_file_cache_min_uses; int /*<<< orphan*/  open_file_cache_valid; } ;
typedef  TYPE_4__ ngx_http_log_loc_conf_t ;
typedef  int /*<<< orphan*/  ngx_http_log_fmt_t ;
struct TYPE_15__ {int /*<<< orphan*/  cycle; int /*<<< orphan*/  pool; } ;
typedef  TYPE_5__ ngx_conf_t ;

/* Variables and functions */
 char* NGX_CONF_ERROR ; 
 char* NGX_CONF_OK ; 
 int /*<<< orphan*/ * NGX_CONF_UNSET_PTR ; 
 int /*<<< orphan*/ * ngx_array_create (int /*<<< orphan*/ ,int,int) ; 
 TYPE_2__* ngx_array_push (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ngx_conf_open_file (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_http_access_log ; 
 TYPE_3__* ngx_http_conf_get_module_main_conf (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_log_module ; 
 int /*<<< orphan*/  ngx_memzero (TYPE_2__*,int) ; 

__attribute__((used)) static char *
ngx_http_log_merge_loc_conf(ngx_conf_t *cf, void *parent, void *child)
{
    ngx_http_log_loc_conf_t *prev = parent;
    ngx_http_log_loc_conf_t *conf = child;

    ngx_http_log_t            *log;
    ngx_http_log_fmt_t        *fmt;
    ngx_http_log_main_conf_t  *lmcf;

    if (conf->open_file_cache == NGX_CONF_UNSET_PTR) {

        conf->open_file_cache = prev->open_file_cache;
        conf->open_file_cache_valid = prev->open_file_cache_valid;
        conf->open_file_cache_min_uses = prev->open_file_cache_min_uses;

        if (conf->open_file_cache == NGX_CONF_UNSET_PTR) {
            conf->open_file_cache = NULL;
        }
    }

    if (conf->logs || conf->off) {
        return NGX_CONF_OK;
    }

    conf->logs = prev->logs;
    conf->off = prev->off;

    if (conf->logs || conf->off) {
        return NGX_CONF_OK;
    }

    conf->logs = ngx_array_create(cf->pool, 2, sizeof(ngx_http_log_t));
    if (conf->logs == NULL) {
        return NGX_CONF_ERROR;
    }

    log = ngx_array_push(conf->logs);
    if (log == NULL) {
        return NGX_CONF_ERROR;
    }

    ngx_memzero(log, sizeof(ngx_http_log_t));

    log->file = ngx_conf_open_file(cf->cycle, &ngx_http_access_log);
    if (log->file == NULL) {
        return NGX_CONF_ERROR;
    }

    lmcf = ngx_http_conf_get_module_main_conf(cf, ngx_http_log_module);
    fmt = lmcf->formats.elts;

    /* the default "combined" format */
    log->format = &fmt[0];
    lmcf->combined_used = 1;

    return NGX_CONF_OK;
}
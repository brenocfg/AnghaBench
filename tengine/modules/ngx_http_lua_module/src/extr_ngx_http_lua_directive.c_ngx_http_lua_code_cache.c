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
typedef  int /*<<< orphan*/  ngx_flag_t ;
typedef  int /*<<< orphan*/  ngx_conf_t ;
struct TYPE_4__ {int offset; } ;
typedef  TYPE_1__ ngx_command_t ;

/* Variables and functions */
 char* NGX_CONF_OK ; 
 int /*<<< orphan*/  NGX_LOG_ALERT ; 
 int /*<<< orphan*/  ngx_conf_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 char* ngx_conf_set_flag_slot (int /*<<< orphan*/ *,TYPE_1__*,void*) ; 

char *
ngx_http_lua_code_cache(ngx_conf_t *cf, ngx_command_t *cmd, void *conf)
{
    char             *p = conf;
    ngx_flag_t       *fp;
    char             *ret;

    ret = ngx_conf_set_flag_slot(cf, cmd, conf);
    if (ret != NGX_CONF_OK) {
        return ret;
    }

    fp = (ngx_flag_t *) (p + cmd->offset);

    if (!*fp) {
        ngx_conf_log_error(NGX_LOG_ALERT, cf, 0,
                           "lua_code_cache is off; this will hurt "
                           "performance");
    }

    return NGX_CONF_OK;
}
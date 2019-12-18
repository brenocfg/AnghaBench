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
typedef  int /*<<< orphan*/  ngx_http_script_code_pt ;
struct TYPE_4__ {int /*<<< orphan*/  codes; } ;
typedef  TYPE_1__ ngx_http_rewrite_loc_conf_t ;
struct TYPE_5__ {int /*<<< orphan*/  pool; } ;
typedef  TYPE_2__ ngx_conf_t ;
typedef  int /*<<< orphan*/  ngx_command_t ;

/* Variables and functions */
 char* NGX_CONF_ERROR ; 
 char* NGX_CONF_OK ; 
 int /*<<< orphan*/  ngx_http_script_break_code ; 
 int /*<<< orphan*/ * ngx_http_script_start_code (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static char *
ngx_http_rewrite_break(ngx_conf_t *cf, ngx_command_t *cmd, void *conf)
{
    ngx_http_rewrite_loc_conf_t *lcf = conf;

    ngx_http_script_code_pt  *code;

    code = ngx_http_script_start_code(cf->pool, &lcf->codes, sizeof(uintptr_t));
    if (code == NULL) {
        return NGX_CONF_ERROR;
    }

    *code = ngx_http_script_break_code;

    return NGX_CONF_OK;
}
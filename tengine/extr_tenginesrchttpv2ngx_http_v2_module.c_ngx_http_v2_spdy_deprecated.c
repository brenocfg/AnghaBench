#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ngx_conf_t ;
struct TYPE_3__ {int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ ngx_command_t ;

/* Variables and functions */
 char* NGX_CONF_OK ; 
 int /*<<< orphan*/  NGX_LOG_WARN ; 
 int /*<<< orphan*/  ngx_conf_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static char *
ngx_http_v2_spdy_deprecated(ngx_conf_t *cf, ngx_command_t *cmd, void *conf)
{
    ngx_conf_log_error(NGX_LOG_WARN, cf, 0,
                       "invalid directive \"%V\": ngx_http_spdy_module "
                       "was superseded by ngx_http_v2_module", &cmd->name);

    return NGX_CONF_OK;
}
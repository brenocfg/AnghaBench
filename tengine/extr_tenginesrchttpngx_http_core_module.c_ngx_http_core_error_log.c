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
struct TYPE_2__ {int /*<<< orphan*/  error_log; } ;
typedef  TYPE_1__ ngx_http_core_loc_conf_t ;
typedef  int /*<<< orphan*/  ngx_conf_t ;
typedef  int /*<<< orphan*/  ngx_command_t ;

/* Variables and functions */
 char* ngx_log_set_log (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static char *
ngx_http_core_error_log(ngx_conf_t *cf, ngx_command_t *cmd, void *conf)
{
    ngx_http_core_loc_conf_t *clcf = conf;

    return ngx_log_set_log(cf, &clcf->error_log);
}
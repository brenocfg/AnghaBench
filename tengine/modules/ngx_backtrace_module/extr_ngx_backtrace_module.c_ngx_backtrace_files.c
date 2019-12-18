#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_1__* cycle; } ;
typedef  TYPE_2__ ngx_conf_t ;
typedef  int /*<<< orphan*/  ngx_command_t ;
struct TYPE_8__ {int /*<<< orphan*/  log; } ;
typedef  TYPE_3__ ngx_backtrace_conf_t ;
struct TYPE_6__ {int /*<<< orphan*/  conf_ctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  ngx_backtrace_module ; 
 scalar_t__ ngx_get_conf (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* ngx_log_set_log (TYPE_2__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static char *
ngx_backtrace_files(ngx_conf_t *cf, ngx_command_t *cmd,
    void *conf)
{
    ngx_backtrace_conf_t *bcf;

    bcf = (ngx_backtrace_conf_t *) ngx_get_conf(cf->cycle->conf_ctx,
                                                ngx_backtrace_module);

    return ngx_log_set_log(cf, &bcf->log);
}
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
struct TYPE_4__ {int /*<<< orphan*/  path; int /*<<< orphan*/  name; int /*<<< orphan*/  envp; int /*<<< orphan*/  argv; } ;
typedef  TYPE_1__ ngx_exec_ctx_t ;
struct TYPE_5__ {int /*<<< orphan*/  log; } ;
typedef  TYPE_2__ ngx_cycle_t ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_LOG_ALERT ; 
 int execve (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  ngx_errno ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ngx_execute_proc(ngx_cycle_t *cycle, void *data)
{
    ngx_exec_ctx_t  *ctx = data;

    if (execve(ctx->path, ctx->argv, ctx->envp) == -1) {
        ngx_log_error(NGX_LOG_ALERT, cycle->log, ngx_errno,
                      "execve() failed while executing %s \"%s\"",
                      ctx->name, ctx->path);
    }

    exit(1);
}
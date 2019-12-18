#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  size_t ngx_uint_t ;
typedef  int /*<<< orphan*/  ngx_str_t ;
struct TYPE_15__ {int /*<<< orphan*/ * flag; } ;
typedef  TYPE_4__ ngx_http_upstream_check_status_ctx_t ;
struct TYPE_12__ {scalar_t__ len; } ;
struct TYPE_16__ {TYPE_3__* connection; TYPE_1__ args; } ;
typedef  TYPE_5__ ngx_http_request_t ;
struct TYPE_13__ {scalar_t__ len; int /*<<< orphan*/  data; } ;
struct TYPE_17__ {scalar_t__ (* handler ) (TYPE_4__*,int /*<<< orphan*/ *) ;TYPE_2__ name; } ;
typedef  TYPE_6__ ngx_check_status_command_t ;
struct TYPE_14__ {int /*<<< orphan*/  log; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_LOG_DEBUG ; 
 int /*<<< orphan*/  NGX_LOG_ERR ; 
 scalar_t__ NGX_OK ; 
 TYPE_6__* ngx_check_status_commands ; 
 scalar_t__ ngx_http_arg (TYPE_5__*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 scalar_t__ stub1 (TYPE_4__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ngx_http_upstream_check_status_parse_args(ngx_http_request_t *r,
    ngx_http_upstream_check_status_ctx_t *ctx)
{
    ngx_str_t                    value;
    ngx_uint_t                   i;
    ngx_check_status_command_t  *command;

    if (r->args.len == 0) {
        return;
    }

    for (i = 0; /* void */ ; i++) {

        command = &ngx_check_status_commands[i];

        if (command->name.len == 0) {
            break;
        }

        if (ngx_http_arg(r, command->name.data, command->name.len, &value)
            == NGX_OK) {

           if (command->handler(ctx, &value) != NGX_OK) {
               ngx_log_error(NGX_LOG_ERR, r->connection->log, 0,
                             "http upstream check, bad argument: \"%V\"",
                             &value);
           }
        }
    }

    ngx_log_error(NGX_LOG_DEBUG, r->connection->log, 0,
            "http upstream check, flag: \"%ui\"", ctx->flag);
}
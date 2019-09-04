#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
typedef  int /*<<< orphan*/  ngx_log_t ;
struct TYPE_6__ {TYPE_1__* connection; } ;
typedef  TYPE_2__ ngx_http_request_t ;
struct TYPE_7__ {int /*<<< orphan*/ * log; } ;
struct TYPE_5__ {int /*<<< orphan*/ * log; } ;

/* Variables and functions */
 int NGX_ERROR ; 
 int NGX_LOG_DEBUG ; 
 int NGX_LOG_STDERR ; 
 int NGX_OK ; 
 TYPE_4__* ngx_cycle ; 
 int /*<<< orphan*/  ngx_log_error (unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,size_t,int /*<<< orphan*/ *) ; 

int
ngx_http_lua_ffi_raw_log(ngx_http_request_t *r, int level, u_char *s,
    size_t s_len)
{
    ngx_log_t           *log;

    if (level > NGX_LOG_DEBUG || level < NGX_LOG_STDERR) {
        return NGX_ERROR;
    }

    if (r && r->connection && r->connection->log) {
        log = r->connection->log;

    } else {
        log = ngx_cycle->log;
    }

    ngx_log_error((unsigned) level, log, 0, "%*s", s_len, s);

    return NGX_OK;
}
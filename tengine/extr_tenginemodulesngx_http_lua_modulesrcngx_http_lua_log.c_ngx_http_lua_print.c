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
typedef  int /*<<< orphan*/  ngx_log_t ;
struct TYPE_6__ {TYPE_1__* connection; } ;
typedef  TYPE_2__ ngx_http_request_t ;
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_7__ {int /*<<< orphan*/ * log; } ;
struct TYPE_5__ {int /*<<< orphan*/ * log; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_LOG_NOTICE ; 
 int log_wrapper (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_4__* ngx_cycle ; 
 TYPE_2__* ngx_http_lua_get_req (int /*<<< orphan*/ *) ; 

int
ngx_http_lua_print(lua_State *L)
{
    ngx_log_t                   *log;
    ngx_http_request_t          *r;

    r = ngx_http_lua_get_req(L);

    if (r && r->connection && r->connection->log) {
        log = r->connection->log;

    } else {
        log = ngx_cycle->log;
    }

    return log_wrapper(log, "[lua] ", NGX_LOG_NOTICE, L);
}
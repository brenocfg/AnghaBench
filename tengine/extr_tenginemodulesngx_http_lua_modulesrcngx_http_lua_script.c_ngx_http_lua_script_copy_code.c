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
typedef  int /*<<< orphan*/  u_char ;
struct TYPE_4__ {int /*<<< orphan*/ * pos; int /*<<< orphan*/  log; scalar_t__ ip; int /*<<< orphan*/  skip; } ;
typedef  TYPE_1__ ngx_http_lua_script_engine_t ;
struct TYPE_5__ {int len; } ;
typedef  TYPE_2__ ngx_http_lua_script_copy_code_t ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_LOG_DEBUG_HTTP ; 
 int /*<<< orphan*/ * ngx_copy (int /*<<< orphan*/ *,scalar_t__,int) ; 
 int /*<<< orphan*/  ngx_log_debug2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ngx_http_lua_script_copy_code(ngx_http_lua_script_engine_t *e)
{
    u_char                           *p;
    ngx_http_lua_script_copy_code_t  *code;

    code = (ngx_http_lua_script_copy_code_t *) e->ip;

    p = e->pos;

    if (!e->skip) {
        e->pos = ngx_copy(p, e->ip + sizeof(ngx_http_lua_script_copy_code_t),
                          code->len);
    }

    e->ip += sizeof(ngx_http_lua_script_copy_code_t)
          + ((code->len + sizeof(uintptr_t) - 1) & ~(sizeof(uintptr_t) - 1));

    ngx_log_debug2(NGX_LOG_DEBUG_HTTP, e->log, 0,
                   "lua script copy: \"%*s\"", e->pos - p, p);
}
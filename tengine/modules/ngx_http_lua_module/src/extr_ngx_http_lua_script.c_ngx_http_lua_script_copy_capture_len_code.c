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
typedef  int ngx_uint_t ;
struct TYPE_4__ {int ncaptures; int* captures; scalar_t__ ip; } ;
typedef  TYPE_1__ ngx_http_lua_script_engine_t ;
struct TYPE_5__ {int n; } ;
typedef  TYPE_2__ ngx_http_lua_script_capture_code_t ;

/* Variables and functions */

__attribute__((used)) static size_t
ngx_http_lua_script_copy_capture_len_code(ngx_http_lua_script_engine_t *e)
{
    int                                  *cap;
    ngx_uint_t                            n;
    ngx_http_lua_script_capture_code_t   *code;

    code = (ngx_http_lua_script_capture_code_t *) e->ip;

    e->ip += sizeof(ngx_http_lua_script_capture_code_t);

    n = code->n;

    if (n < e->ncaptures) {
        cap = e->captures;
        return cap[n + 1] - cap[n];
    }

    return 0;
}
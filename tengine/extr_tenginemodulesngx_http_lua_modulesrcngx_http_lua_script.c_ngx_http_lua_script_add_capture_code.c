#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int ngx_uint_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_5__ {int /*<<< orphan*/ * values; int /*<<< orphan*/ * lengths; } ;
typedef  TYPE_1__ ngx_http_lua_script_compile_t ;
typedef  int /*<<< orphan*/  ngx_http_lua_script_code_pt ;
struct TYPE_6__ {int n; int /*<<< orphan*/  code; } ;
typedef  TYPE_2__ ngx_http_lua_script_capture_code_t ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_ERROR ; 
 int /*<<< orphan*/  NGX_OK ; 
 TYPE_2__* ngx_http_lua_script_add_code (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ngx_http_lua_script_copy_capture_code ; 
 scalar_t__ ngx_http_lua_script_copy_capture_len_code ; 

__attribute__((used)) static ngx_int_t
ngx_http_lua_script_add_capture_code(ngx_http_lua_script_compile_t *sc,
    ngx_uint_t n)
{
    ngx_http_lua_script_capture_code_t  *code;

    code = ngx_http_lua_script_add_code(*sc->lengths,
                                  sizeof(ngx_http_lua_script_capture_code_t));
    if (code == NULL) {
        return NGX_ERROR;
    }

    code->code = (ngx_http_lua_script_code_pt) (void *)
                 ngx_http_lua_script_copy_capture_len_code;
    code->n = 2 * n;

    code = ngx_http_lua_script_add_code(*sc->values,
                                  sizeof(ngx_http_lua_script_capture_code_t));
    if (code == NULL) {
        return NGX_ERROR;
    }

    code->code = ngx_http_lua_script_copy_capture_code;
    code->n = 2 * n;

    return NGX_OK;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
typedef  int /*<<< orphan*/  ngx_uint_t ;
struct TYPE_7__ {size_t len; int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ ngx_str_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_8__ {size_t len; int /*<<< orphan*/  code; } ;
typedef  TYPE_2__ ngx_http_lua_script_copy_code_t ;
struct TYPE_9__ {int /*<<< orphan*/ * values; int /*<<< orphan*/ * lengths; } ;
typedef  TYPE_3__ ngx_http_lua_script_compile_t ;
typedef  int /*<<< orphan*/  ngx_http_lua_script_code_pt ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_ERROR ; 
 int /*<<< orphan*/  NGX_OK ; 
 TYPE_2__* ngx_http_lua_script_add_code (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  ngx_http_lua_script_copy_code ; 
 scalar_t__ ngx_http_lua_script_copy_len_code ; 
 int /*<<< orphan*/  ngx_memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static ngx_int_t
ngx_http_lua_script_add_copy_code(ngx_http_lua_script_compile_t *sc,
    ngx_str_t *value, ngx_uint_t last)
{
    size_t                            size, len;
    ngx_http_lua_script_copy_code_t  *code;

    len = value->len;

    code = ngx_http_lua_script_add_code(*sc->lengths,
                                    sizeof(ngx_http_lua_script_copy_code_t));
    if (code == NULL) {
        return NGX_ERROR;
    }

    code->code = (ngx_http_lua_script_code_pt) (void *)
                 ngx_http_lua_script_copy_len_code;
    code->len = len;

    size = (sizeof(ngx_http_lua_script_copy_code_t) + len +
            sizeof(uintptr_t) - 1) & ~(sizeof(uintptr_t) - 1);

    code = ngx_http_lua_script_add_code(*sc->values, size);
    if (code == NULL) {
        return NGX_ERROR;
    }

    code->code = ngx_http_lua_script_copy_code;
    code->len = len;

    ngx_memcpy((u_char *) code + sizeof(ngx_http_lua_script_copy_code_t),
               value->data, value->len);

    return NGX_OK;
}
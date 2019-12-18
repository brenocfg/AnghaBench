#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int ngx_uint_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
typedef  int /*<<< orphan*/  ngx_http_lua_script_copy_code_t ;
struct TYPE_3__ {int variables; int /*<<< orphan*/ ** values; int /*<<< orphan*/  pool; int /*<<< orphan*/ ** lengths; } ;
typedef  TYPE_1__ ngx_http_lua_script_compile_t ;
typedef  int /*<<< orphan*/  ngx_http_lua_script_capture_code_t ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_ERROR ; 
 int /*<<< orphan*/  NGX_OK ; 
 void* ngx_array_create (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static ngx_int_t
ngx_http_lua_script_init_arrays(ngx_http_lua_script_compile_t *sc)
{
    ngx_uint_t   n;

    if (*sc->lengths == NULL) {
        n = sc->variables * (2 * sizeof(ngx_http_lua_script_copy_code_t)
                             + sizeof(ngx_http_lua_script_capture_code_t))
            + sizeof(uintptr_t);

        *sc->lengths = ngx_array_create(sc->pool, n, 1);
        if (*sc->lengths == NULL) {
            return NGX_ERROR;
        }
    }

    if (*sc->values == NULL) {
        n = (sc->variables * (2 * sizeof(ngx_http_lua_script_copy_code_t)
                              + sizeof(ngx_http_lua_script_capture_code_t))
                + sizeof(uintptr_t)
                + sizeof(uintptr_t) - 1)
            & ~(sizeof(uintptr_t) - 1);

        *sc->values = ngx_array_create(sc->pool, n, 1);
        if (*sc->values == NULL) {
            return NGX_ERROR;
        }
    }

    sc->variables = 0;

    return NGX_OK;
}
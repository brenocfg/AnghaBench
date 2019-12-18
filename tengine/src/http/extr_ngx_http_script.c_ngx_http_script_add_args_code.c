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
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_3__ {int /*<<< orphan*/  main; int /*<<< orphan*/ * values; int /*<<< orphan*/ * lengths; } ;
typedef  TYPE_1__ ngx_http_script_compile_t ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_ERROR ; 
 int /*<<< orphan*/  NGX_OK ; 
 uintptr_t* ngx_http_script_add_code (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_http_script_mark_args_code ; 
 int /*<<< orphan*/  ngx_http_script_start_args_code ; 

__attribute__((used)) static ngx_int_t
ngx_http_script_add_args_code(ngx_http_script_compile_t *sc)
{
    uintptr_t   *code;

    code = ngx_http_script_add_code(*sc->lengths, sizeof(uintptr_t), NULL);
    if (code == NULL) {
        return NGX_ERROR;
    }

    *code = (uintptr_t) ngx_http_script_mark_args_code;

    code = ngx_http_script_add_code(*sc->values, sizeof(uintptr_t), &sc->main);
    if (code == NULL) {
        return NGX_ERROR;
    }

    *code = (uintptr_t) ngx_http_script_start_args_code;

    return NGX_OK;
}
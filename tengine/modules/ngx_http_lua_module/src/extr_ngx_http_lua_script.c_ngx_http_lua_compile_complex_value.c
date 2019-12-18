#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  size_t ngx_uint_t ;
struct TYPE_12__ {size_t len; char* data; } ;
typedef  TYPE_2__ ngx_str_t ;
typedef  scalar_t__ ngx_int_t ;
typedef  int /*<<< orphan*/  ngx_http_lua_script_copy_code_t ;
struct TYPE_13__ {int complete_lengths; int complete_values; TYPE_5__** values; TYPE_5__** lengths; TYPE_2__* source; int /*<<< orphan*/  log; int /*<<< orphan*/  pool; } ;
typedef  TYPE_3__ ngx_http_lua_script_compile_t ;
typedef  int /*<<< orphan*/  ngx_http_lua_script_capture_code_t ;
struct TYPE_14__ {TYPE_1__* complex_value; int /*<<< orphan*/  log; int /*<<< orphan*/  pool; TYPE_2__* value; } ;
typedef  TYPE_4__ ngx_http_lua_compile_complex_value_t ;
struct TYPE_15__ {int /*<<< orphan*/ * elts; } ;
typedef  TYPE_5__ ngx_array_t ;
struct TYPE_11__ {int /*<<< orphan*/ * values; int /*<<< orphan*/ * lengths; TYPE_2__ value; } ;

/* Variables and functions */
 scalar_t__ NGX_ERROR ; 
 scalar_t__ NGX_OK ; 
 int /*<<< orphan*/  ngx_array_destroy (TYPE_5__*) ; 
 scalar_t__ ngx_array_init (TYPE_5__*,int /*<<< orphan*/ ,size_t,int) ; 
 scalar_t__ ngx_http_lua_script_compile (TYPE_3__*) ; 
 int /*<<< orphan*/  ngx_memzero (TYPE_3__*,int) ; 

ngx_int_t
ngx_http_lua_compile_complex_value(ngx_http_lua_compile_complex_value_t *ccv)
{
    ngx_str_t                  *v;
    ngx_uint_t                  i, n, nv;
    ngx_array_t                 lengths, values, *pl, *pv;

    ngx_http_lua_script_compile_t   sc;

    v = ccv->value;

    nv = 0;

    for (i = 0; i < v->len; i++) {
        if (v->data[i] == '$') {
            nv++;
        }
    }

    ccv->complex_value->value = *v;
    ccv->complex_value->lengths = NULL;
    ccv->complex_value->values = NULL;

    if (nv == 0) {
        return NGX_OK;
    }

    n = nv * (2 * sizeof(ngx_http_lua_script_copy_code_t)
              + sizeof(ngx_http_lua_script_capture_code_t))
        + sizeof(uintptr_t);

    if (ngx_array_init(&lengths, ccv->pool, n, 1) != NGX_OK) {
        return NGX_ERROR;
    }

    n = (nv * (2 * sizeof(ngx_http_lua_script_copy_code_t)
                   + sizeof(ngx_http_lua_script_capture_code_t))
                + sizeof(uintptr_t)
                + sizeof(uintptr_t) - 1)
            & ~(sizeof(uintptr_t) - 1);

    if (ngx_array_init(&values, ccv->pool, n, 1) != NGX_OK) {
        return NGX_ERROR;
    }

    pl = &lengths;
    pv = &values;

    ngx_memzero(&sc, sizeof(ngx_http_lua_script_compile_t));

    sc.pool = ccv->pool;
    sc.log = ccv->log;
    sc.source = v;
    sc.lengths = &pl;
    sc.values = &pv;
    sc.complete_lengths = 1;
    sc.complete_values = 1;

    if (ngx_http_lua_script_compile(&sc) != NGX_OK) {
        ngx_array_destroy(&lengths);
        ngx_array_destroy(&values);
        return NGX_ERROR;
    }

    ccv->complex_value->lengths = lengths.elts;
    ccv->complex_value->values = values.elts;

    return NGX_OK;
}